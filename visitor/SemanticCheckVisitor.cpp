#include "SemanticCheckVisitor.h"
#include <iostream>
#include <string>
#include <deque>
#include <utility>
#include <algorithm>

#include <errors/derr.defs.h>
#include <errors/InternalCompilerException.h>

#include <types/alltypes.h>
#include <types/IsTypeHelper.h>

#include <visitor/ConstExprEvalVisitor.h>

#include <valuetypes/ValueType.h>
#include <valuetypes/FunctionDesignator.h>
#include <valuetypes/LValue.h>
#include <valuetypes/RValue.h>
#include <valuetypes/CValue.h>
#include <valuetypes/IsValueTypeHelper.h>
#include <valuetypes/PromotionHelper.h>
#include <valuetypes/ConstHelper.h>

// only include the int tokens
#define YYSTYPE int
#include <parser.hpp>

using namespace dtcc;
using namespace dtcc::visitor;


/* constructor */

SemanticCheckVisitor::SemanticCheckVisitor()
{
    this->m_loopStack = std::deque<std::pair<astnodes::LabelStatement*, astnodes::LabelStatement*> >();
    this->m_symbolTable = new symboltable::SymbolTable();
    this->m_errorList = errors::ErrorList();
    this->m_AutomaticLabels = std::set<std::string>();
    this->m_switchStack = std::deque<astnodes::SwitchStatement*>();
    this->m_funcLabels = std::map<std::string, astnodes::LabelStatement*>();
    this->m_invalidValType = new valuetypes::RValue(new types::InvalidType());
    this->m_declTypeStack = std::deque<types::Type*>();
    this->m_declNameStack = std::deque<std::string>();
    this->m_declIsStored = std::deque<bool>();
    this->m_saveParams = std::deque<bool>();
}

// TODO this is just while dev, to be removed in final version:
void SemanticCheckVisitor::printAstName(const char * name)
{
    std::cout << "TODO implement semantic check for node '" << name << "'." << std::endl;
}

valuetypes::ValueType* SemanticCheckVisitor::getInvalidValType()
{
    return new valuetypes::RValue(new types::InvalidType());
}


/******************************/
/* break and continue         */
/* label management           */
/******************************/

void SemanticCheckVisitor::initLoopStack()
{
    this->m_loopStack.clear();
}
void SemanticCheckVisitor::popLoopStack()
{
    this->m_loopStack.pop_back();
}

void SemanticCheckVisitor::pushLoopStack(astnodes::LabelStatement* breakLabel, astnodes::LabelStatement* continueLabel)
{
    this->m_loopStack.push_back(std::pair<astnodes::LabelStatement*, astnodes::LabelStatement*>(breakLabel, continueLabel));
}

astnodes::LabelStatement* SemanticCheckVisitor::getBreakLabel()
{
    if (this->m_loopStack.size() > 0)
    {
        return this->m_loopStack.back().first;
    }
    else
    {
        return NULL;
    }
}

astnodes::LabelStatement* SemanticCheckVisitor::getContinueLabel()
{
    // this can be inside a switch (which just uses break)
    // so search in the list for the next non NULL continue label
    for (std::deque<std::pair<astnodes::LabelStatement*, astnodes::LabelStatement*> >::reverse_iterator it = this->m_loopStack.rbegin(); it != this->m_loopStack.rend(); it++)
        if (it->second != NULL)
            return it->second;
    return NULL;
}

// Generates a random, unique label for use in code.
astnodes::LabelStatement* SemanticCheckVisitor::getRandomLabel(std::string prefix)
{
    std::string result = "";
    
    while ((result == "") || (this->m_AutomaticLabels.find(result) != this->m_AutomaticLabels.end()))
        result = "__" + prefix + "_" + SemanticCheckVisitor::getRandomString(10);
    
    return new astnodes::LabelStatement(result, new astnodes::EmptyStatement());
}

// Generates a random character.
char SemanticCheckVisitor::getRandomCharacter()
{
    unsigned char c;
    
    while (!std::isalnum(c = static_cast<unsigned char>(std::rand() % 256))) ;
    
    return c;
}

// Generates a random string.
std::string SemanticCheckVisitor::getRandomString(std::string::size_type sz)
{
    std::string s;
    s.reserve(sz);
    std::generate_n(std::back_inserter(s), sz, SemanticCheckVisitor::getRandomCharacter);
    return s;
}



/******************************/
/* error & warning management */
/******************************/

void SemanticCheckVisitor::addError(astnodes::Node* node, int errid)
{
    this->m_errorList.addError(node->line, node->file, errid);
}

void SemanticCheckVisitor::addError(astnodes::Node* node, int errid, std::string msg)
{
    this->m_errorList.addError(node->line, node->file, errid, msg);
}

void SemanticCheckVisitor::addWarning(astnodes::Node* node, int errid)
{
    this->m_errorList.addWarning(node->line, node->file, errid);
}

void SemanticCheckVisitor::addWarning(astnodes::Node* node, int errid, std::string msg)
{
    this->m_errorList.addWarning(node->line, node->file, errid, msg);
}




/******************************/
/* visit functions            */
/******************************/


void SemanticCheckVisitor::visit(astnodes::Program * program)
{
    // analyse everything
    program->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::FunctionDefinition * functionDefinition)
{
    // clear labels
    m_funcLabels.clear();
    
    // get type from declaration specifiers
    types::Type* returnType = declSpecsToType(functionDefinition->declSpecifiers);
    
    // check that the type is either void or an object type, but not an array
    if (types::IsTypeHelper::isArrayType(returnType) || (!types::IsTypeHelper::isObjectType(returnType) && ! types::IsTypeHelper::isVoid(returnType)))
    {
        addError(functionDefinition, ERR_CC_FUNC_RETURN_TYPE);
    }
    
    // next check for the storage specifiers
    if (functionDefinition->declSpecifiers->storageSpecifiers.size() > 1)
    {
        addError(functionDefinition->declSpecifiers->storageSpecifiers.front(), ERR_CC_STORSPEC_CONFL);
        return;
    } else if (functionDefinition->declSpecifiers->storageSpecifiers.size() == 1)
    {
        switch(functionDefinition->declSpecifiers->storageSpecifiers.front()->token)
        {
            case STATIC:
            case EXTERN:
                // TODO use it do decide on visibility
                break;
            case TYPEDEF:
            case AUTO:
            case REGISTER:
                addError(functionDefinition->declSpecifiers->storageSpecifiers.front(), ERR_CC_FUNC_RETURN_STORAGE);
                return;
                break;
            default:
                throw new errors::InternalCompilerException("unknown storage specifier encountered");
        }
    }
    
    
    symboltable::SymbolTableScope* funScope = this->m_symbolTable->beginNewScope();
    
    // get all the parameters with their names into the scope
    this->m_saveParams.push_back(true);
    this->m_declTypeStack.push_back(returnType);
    functionDefinition->declarator->accept(*this);
    
    types::Type* funType = this->m_declTypeStack.back();
    
    // check that it is actually a function type
    if (! types::IsTypeHelper::isFunctionType(funType))
    {
        addError(functionDefinition, ERR_CC_FUNC_IS_NOT_A_FUNC_TYPE);
        return;
    }
    
    this->m_declTypeStack.pop_back();
    this->m_saveParams.pop_back();
    std::string name = this->m_declNameStack.back();
    this->m_declNameStack.pop_back();
    this->m_symbolTable->endScope();
    

    
    symboltable::SymbolObject obj;
    // search for functions only at global scope:
    if(this->m_symbolTable->getGlobalScope().findSymbol(name, obj))
    {
        if (obj.declType == symboltable::FUNCTION_DEF)
        {
            addError(functionDefinition, ERR_CC_REDECL, name);
            return;
        }
        else if (obj.declType != symboltable::FUNCTION_DECL)
        {
            addError(functionDefinition, ERR_CC_REDECL, name);
            return;
        }
    }
    
    // insert function
    this->m_symbolTable->getGlobalScope().insertSymbol(name, symboltable::FUNCTION_DEF, funType, symboltable::GLOBAL);
    
    // give the block its scope
    functionDefinition->block->scope = funScope;
    // analyse the declarations and statements in the block
    functionDefinition->block->accept(*this);
    
    // the scope is closed by the block itself
    // no need to do it here
    
    
    // set the name of the function
    functionDefinition->name = name;
    
    // set the parameter and locals size
    functionDefinition->stackSize = funScope->getLocalStackSize();
    functionDefinition->paramSize = funScope->getParameterStackSize();
    
    // TODO call goto label resolval visitor here:
    
    // clear labels
    m_funcLabels.clear();
}


void SemanticCheckVisitor::visit(astnodes::GotoStatement * gotoStatement)
{
    // goto statements are resolved in an extra pass
}


void SemanticCheckVisitor::visit(astnodes::ContinueStatement * continueStatement)
{
    astnodes::LabelStatement* label = getContinueLabel();
    if (label == NULL)
    {
        addError(continueStatement, ERR_CC_CONTINUE_OUTSIDE_OF_LOOP);
        return;
    }
    continueStatement->label = label;
}


void SemanticCheckVisitor::visit(astnodes::BreakStatement * breakStatement)
{
    astnodes::LabelStatement* label = getBreakLabel();
    if (label == NULL)
    {
        addError(breakStatement, ERR_CC_BREAK_OUTSIDE_OF_LOOP);
        return;
    }
    breakStatement->label = label;
}


void SemanticCheckVisitor::visit(astnodes::Expression * expression)
{
    throw new errors::InternalCompilerException("Expression Node is only abstract and cannot be visited");
}


void SemanticCheckVisitor::visit(astnodes::Statement * statement)
{
    throw new errors::InternalCompilerException("Statement Node is only abstract and cannot be visited");
}


void SemanticCheckVisitor::visit(astnodes::ExternalDeclaration * externalDeclaration)
{
    throw new errors::InternalCompilerException("ExternalDeclaration Node is only abstract and cannot be visited");
}


void SemanticCheckVisitor::visit(astnodes::ReturnStatement * returnStatement)
{
    // first check the expression
    returnStatement->allChildrenAccept(*this);
    // then check if it is compatible with the function return value
    // TODO TODO FIXME
    // TODO  get the label to the end of the function to jump to
}


void SemanticCheckVisitor::visit(astnodes::ForStatement * forStatement)
{
    // Create labels for the for statement:
    forStatement->startLbl = getRandomLabel("for_start");
    forStatement->endLbl = getRandomLabel("for_end");
    forStatement->continueLbl = getRandomLabel("for_continue");
    // put the labels on the loop stack
    pushLoopStack(forStatement->endLbl, forStatement->continueLbl);
    // evaluate all children
    forStatement->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(forStatement->condExpr->expr->valType->type))
    {
        addError(forStatement, ERR_CC_EXPECTED_SCALAR_FOR);
    }
    
    // pop loop stack
    popLoopStack();
}


void SemanticCheckVisitor::visit(astnodes::DoWhileStatement * doWhileStatement)
{
    // Create labels for the for statement:
    doWhileStatement->startLbl = getRandomLabel("dowhile_start");
    doWhileStatement->endLbl = getRandomLabel("dowhile_end");
    doWhileStatement->continueLbl = getRandomLabel("dowhile_continue");
    
    // put the labels on the loop stack
    pushLoopStack(doWhileStatement->endLbl, doWhileStatement->continueLbl);
    // evaluate all children
    doWhileStatement->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(doWhileStatement->condExpr->valType->type))
    {
        addError(doWhileStatement, ERR_CC_EXPECTED_SCALAR_DOWHILE);
    }
    
    // pop loop stack
    popLoopStack();
}


void SemanticCheckVisitor::visit(astnodes::WhileStatement * whileStatement)
{
    // Create labels for the for statement:
    whileStatement->startLbl = getRandomLabel("while_start");
    whileStatement->endLbl = getRandomLabel("while_end");
    
    // put the labels on the loop stack
    pushLoopStack(whileStatement->endLbl, whileStatement->startLbl);
    // evaluate all children
    whileStatement->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(whileStatement->condExpr->valType->type))
    {
        addError(whileStatement, ERR_CC_EXPECTED_SCALAR_WHILE);
    }
    
    // pop loop stack
    popLoopStack();
}


void SemanticCheckVisitor::visit(astnodes::SwitchStatement * switchStatement)
{
    // first evaluate the controlling expression
    switchStatement->expr->accept(*this);
    
    // check for integral type
    if(!types::IsTypeHelper::isIntegralType(switchStatement->expr->valType->type))
    {
        addError(switchStatement, ERR_CC_EXPECTED_INTEGRAL_SWITCH);
        // don't handle anything inside the switch statement
        return;
    }
    
    // set promoted type
    switchStatement->promotedType = switchStatement->expr->valType->type;
    
    // push switch statement on switch-statement stack
    this->m_switchStack.push_back(switchStatement);
    
    // now check the block statement
    switchStatement->statement->accept(*this);
    
    // pop switch statement stack
    this->m_switchStack.pop_back();
    
    // check if this is still an integral type
    if(!types::IsTypeHelper::isIntegralType(switchStatement->promotedType))
    {
        addError(switchStatement, ERR_CC_EXPECTED_INTEGRAL_SWITCH);
    }
}


void SemanticCheckVisitor::visit(astnodes::IfStatement * ifStatement)
{
    // first evaluate the controlling expression
    ifStatement->condExpr->accept(*this);
    
    // check for integral type
    if(!types::IsTypeHelper::isScalarType(ifStatement->condExpr->valType->type))
    {
        addError(ifStatement, ERR_CC_EXPECTED_SCALAR_IF);
        // don't handle anything inside the if statement
        return;
    }
    
    // Create labels for the if statement:
    ifStatement->endlbl = getRandomLabel("if_end");
    if (ifStatement->elseStmt != NULL)
        ifStatement->elselbl = getRandomLabel("if_else");
    
    // recurse into the statements
    ifStatement->ifStmt->accept(*this);
    if (ifStatement->elseStmt != NULL)
        ifStatement->elseStmt->accept(*this);
}


void SemanticCheckVisitor::visit(astnodes::ExpressionStatement * expressionStatement)
{
    // just pass through
    expressionStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::EmptyStatement * emptyStatement)
{
    // nothing to do here
}


void SemanticCheckVisitor::visit(astnodes::BlockStatement * blockStatement)
{
    // create new scope, or if this is the main block of a function
    // then use the scope already filled with the function parameters
    if (blockStatement->scope == NULL)
        blockStatement->scope = m_symbolTable->beginNewScope();
    else
        m_symbolTable->beginScope(blockStatement->scope);
    
    // analyse the statements 
    blockStatement->allChildrenAccept(*this);
    
    // end the scope
    m_symbolTable->endScope();
}


void SemanticCheckVisitor::visit(astnodes::DefaultStatement * defaultStatement)
{
    if (m_switchStack.empty())
    {
        addError(defaultStatement, ERR_CC_DEFAULT_OUTSIDE_OF_SWITCH);
        // don't handle anything inside the default statement
        return;
    }
    
    if (m_switchStack.back()->defaultLbl != NULL)
    {
        addError(defaultStatement, ERR_CC_MULTIPLE_DEFAULT);
        // don't handle anything inside the default statement
        return;
    }
    
    defaultStatement->lbl = getRandomLabel("default");
    
    m_switchStack.back()->defaultLbl = defaultStatement->lbl;
    
    // analyse child statement:
    defaultStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::CaseStatement * caseStatement)
{
    // TODO const expression evaluator
    // TODO
    // TODO the expression evaluator (first finish semantic check for expressions)
    printAstName("CaseStatement");
    caseStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::LabelStatement * labelStatement)
{
    // look if a label with the same name already exists
    std::map<std::string, astnodes::LabelStatement*>::iterator it;
    if ((it = this->m_funcLabels.find(labelStatement->label)) != this->m_funcLabels.end())
    {
        addError(labelStatement, ERR_CC_DUPLICATE_LABEL, labelStatement->label);
        addError(it->second, ERR_CC_NOTE_DUPLICATE_LABEL, labelStatement->label);
        // don't handle anything inside the default statement
        return;
    }
    
    // insert label into the map
    this->m_funcLabels[labelStatement->label] = labelStatement;
    
    // go on analysing the statement after the label:
    labelStatement->allChildrenAccept(*this);
}






/*######################################*/
/*        3.5 DECLARATIONS              */
/*######################################*/



// TODO TODO FIXME TODO TODO FIXME
// implement declarators ;)
// first now implementing expressions

void SemanticCheckVisitor::visit(astnodes::Declaration * declaration)
{
    // get type from declaration specifiers
    types::Type* declType = declSpecsToType(declaration->declSpecifiers);
    
    // next check for the storage specifiers
    if (declaration->declSpecifiers->storageSpecifiers.size() > 1)
    {
        addError(declaration->declSpecifiers->storageSpecifiers.front(), ERR_CC_STORSPEC_CONFL);
        return;
    } else if (declaration->declSpecifiers->storageSpecifiers.size() == 1)
    {
        switch(declaration->declSpecifiers->storageSpecifiers.front()->token)
        {
            case TYPEDEF:
                declaration->storageSpecifier = astnodes::STORAGE_TYPEDEF;
                break;
            case EXTERN:
                declaration->storageSpecifier = astnodes::STORAGE_EXTERN;
                break;
            case STATIC:
                declaration->storageSpecifier = astnodes::STORAGE_STATIC;
                break;
            case AUTO:
                declaration->storageSpecifier = astnodes::STORAGE_AUTO;
                break;
            case REGISTER:
                declaration->storageSpecifier = astnodes::STORAGE_REGISTER;
                break;
            default:
                throw new errors::InternalCompilerException("unknown storage specifier encountered");
        }
    }
    else
    {
        // empty storage specifiers
        declaration->storageSpecifier = astnodes::STORAGE_DEFAULT;
    }
    
    // now visit all the declarators
    if (!declaration->isParamDecl)
    {
        for (astnodes::Declarators::iterator i = declaration->declarators->begin(); i != declaration->declarators->end(); ++i)
        {
            // put the declaration type on the stack
            this->m_declTypeStack.push_back(declType);
            
            // push whether the declaration needs to be stored (i.e. an array can consist of unknown length or not)
            switch(declaration->storageSpecifier)
            {
                case astnodes::STORAGE_TYPEDEF:
                case astnodes::STORAGE_EXTERN:
                    m_declIsStored.push_back(false);
                    break;
                    
                case astnodes::STORAGE_STATIC:
                case astnodes::STORAGE_AUTO:
                case astnodes::STORAGE_REGISTER:
                case astnodes::STORAGE_DEFAULT:
                    m_declIsStored.push_back(true);
                    break;
                    
                default:
                    throw new errors::InternalCompilerException("unknown storage specifier encountered");
            }
            
            // call declarator recursively in order to get the actuay declaration type
            this->m_saveParams.push_back(false);
            (*i)->accept(*this);
            
            // get type and name of actual declarator
            types::Type* actualDeclType = this->m_declTypeStack.back();
            this->m_declTypeStack.pop_back();
            std::string declName = this->m_declNameStack.back();
            this->m_declNameStack.pop_back();
            this->m_saveParams.pop_back();
            
            if (types::IsTypeHelper::isInvalidType(actualDeclType))
                // errors have already been generated in this case, just ignore this declaration
                return;
            
            
            if (types::IsTypeHelper::isFunctionType(actualDeclType))   
            {
                // put encountered function into symbol table
                symboltable::SymbolObject obj;
                switch(declaration->storageSpecifier)
                {
                    case astnodes::STORAGE_TYPEDEF:
                    case astnodes::STORAGE_REGISTER:
                    case astnodes::STORAGE_AUTO:
                        // this is a function declaration
                        addError(declaration, ERR_CC_FUNC_RETURN_STORAGE);
                        return;
                        break;
                        
                    case astnodes::STORAGE_STATIC:
                        // TODO do something special with static
                    case astnodes::STORAGE_EXTERN:
                    case astnodes::STORAGE_DEFAULT:
                        // search for functions only at global scope:
                        if(this->m_symbolTable->getCurrentScope().findSymbol(declName, obj))
                        {
                            if (obj.declType == symboltable::FUNCTION_DEF)
                            {
                                addError(declaration, ERR_CC_REDECL, declName);
                                return;
                            }
                            else if (obj.declType != symboltable::FUNCTION_DECL)
                            {
                                addError(declaration, ERR_CC_REDECL, declName);
                                return;
                            }
                        }
                        
                        // insert function
                        this->m_symbolTable->getCurrentScope().insertSymbol(declName, symboltable::FUNCTION_DECL, actualDeclType, symboltable::GLOBAL);
                        break;
                    default:
                        throw new errors::InternalCompilerException("unknown storage specifier encountered");
                }
            }
            else
            {
                // put encountered symbol into symbol table
                switch(declaration->storageSpecifier)
                {
                    case astnodes::STORAGE_TYPEDEF:
                        
                        if (m_symbolTable->getCurrentScope().containsTag(declName))
                        {
                            addError(declaration, ERR_CC_REDECL, declName);
                            return;
                        }
                        // put in typedef table
                        m_symbolTable->getCurrentScope().insertTag(declName, symboltable::TYPEDEF_TAG, actualDeclType);
                        break;
                    case astnodes::STORAGE_EXTERN:
                        // TODO
                        break;
                    case astnodes::STORAGE_STATIC:
                        // TODO put somehow as global static variable
                        // TODO which has only local scope ..
                        break;
                        
                    case astnodes::STORAGE_AUTO:
                        // this is the default storage for declarations:
                    case astnodes::STORAGE_REGISTER:
                        // handle register just normally as well
                        // just fucking ignore the request for register storage for now :P
                        // TODO maybe handle it specially some time ;P
                    case astnodes::STORAGE_DEFAULT:
                        // check if the symbol has been declared before
                        if (m_symbolTable->getCurrentScope().containsSymbol(declName))
                        {
                            addError(declaration, ERR_CC_REDECL, declName);
                            return;
                        }
                        
                        if (m_symbolTable->isGlobalCurScope())
                            // put onto global storage
                            m_symbolTable->getCurrentScope().insertSymbol(declName, symboltable::VARIABLE_DECL, actualDeclType, symboltable::GLOBAL);
                        else
                            // put onto local stack symbol table
                            m_symbolTable->getCurrentScope().insertSymbol(declName, symboltable::VARIABLE_DECL, actualDeclType, symboltable::LOCAL_STACK);
                        break;
                        
                    
                    default:
                        throw new errors::InternalCompilerException("unknown storage specifier encountered");
                }
            }
        }
    }
    else
    {

        // check that the function parameter declaration doesn't use any 
        // storage specifiers besides `register`
        switch(declaration->storageSpecifier)
        {
            case astnodes::STORAGE_TYPEDEF:
            case astnodes::STORAGE_EXTERN:
            case astnodes::STORAGE_STATIC:
            case astnodes::STORAGE_AUTO:
                addError(declaration, ERR_CC_FUNC_PARAM_STORAGE);
                return;
            case astnodes::STORAGE_REGISTER:
            case astnodes::STORAGE_DEFAULT:
               // everything is fine
                break;
                
            default:
                throw new errors::InternalCompilerException("unknown storage specifier encountered");
        }
        
        // put the declaration type on the stack
        this->m_declTypeStack.push_back(declType);
        this->m_declIsStored.push_back(false);
        this->m_saveParams.push_back(false);
        
        // call declarator recursively in order to get the actuay declaration type
        declaration->singleDeclarator->accept(*this);
        
        // get type and name of actual declarator
        types::Type* actualDeclType = this->m_declTypeStack.back();
        this->m_declTypeStack.pop_back();
        std::string declName = this->m_declNameStack.back();
        this->m_declNameStack.pop_back();
        this->m_saveParams.pop_back();
        
        if (types::IsTypeHelper::isInvalidType(actualDeclType))
            // errors have already been generated in this case, just ignore this declaration
            return;
        
        // set the associated type
        declaration->type = actualDeclType;
        
        // if this is a parameter, there must be another declarator somewhere which set this
        if (this->m_saveParams.back() && !types::IsTypeHelper::isVoid(actualDeclType))
        {
            if (declName == std::string(""))
            {
                addError(declaration, ERR_CC_FUNC_PARAM_NO_NAME, declName);
                return;
            }
            
            if (m_symbolTable->getCurrentScope().containsTag(declName))
            {
                addError(declaration, ERR_CC_REDECL, declName);
                return;
            }
            
            // save as parameter in current scope
            m_symbolTable->getCurrentScope().insertSymbol(declName, symboltable::VARIABLE_DECL, declType, symboltable::PARAMETER_STACK);
        }
    }
}




/******************************/
/*     3.5.4 Declarators      */
/******************************/

void SemanticCheckVisitor::visit(astnodes::Declarator * declarator)
{
    throw new errors::InternalCompilerException("Declarator Node is only abstract and cannot be visited");
}

void SemanticCheckVisitor::visit(astnodes::NoIdentifierDeclarator * noIdentifierDeclarator)
{
    // add pointers
    noIdentifierDeclarator->allChildrenAccept(*this);
    // nothing else to do
    // push an empty name to the stack, so that
    // nothing of importance is popped of
    this->m_declNameStack.push_back(std::string(""));
}

void SemanticCheckVisitor::visit(astnodes::IdentifierDeclarator * identifierDeclarator)
{
    // add pointers
    if (identifierDeclarator->pointers != NULL)
        for (astnodes::Pointers::iterator i = identifierDeclarator->pointers->begin(); i != identifierDeclarator->pointers->end(); ++i)
            (*i)->accept(*this);
    // no change in the type, we've reached the bottom in the declarator recursion
    // just push the namespace
    this->m_declNameStack.push_back(identifierDeclarator->name);
    
    // TODO get initializer
    if (identifierDeclarator->initializers != NULL)
    {
        // check that there is at most 1 initializer
        if (identifierDeclarator->initializers->size() > 1)
        {
            addError(identifierDeclarator, ERR_CC_TOO_MANY_INITS, identifierDeclarator->name);
            return;
        }
        
        if (identifierDeclarator->initializers->size() == 1)
        {
            // visit the expression
            identifierDeclarator->initializers->front()->accept(*this);
            
            // now check for compatible types
            // TODO
        }
    }
    

    
}


/* 3.5.4.1 Pointer declarators */

void SemanticCheckVisitor::visit(astnodes::Pointer * pointer)
{
    // get base type
    types::Type* baseType = this->m_declTypeStack.back();
    this->m_declTypeStack.pop_back();
    // construct pointer type with that base type
    types::Type* result = new types::PointerType(baseType);
    // now check for type qualifiers and add them to the pointer type
    for (std::vector<astnodes::TypeQualifier*>::iterator i = pointer->typeQualifiers->begin(); i != pointer->typeQualifiers->end(); ++i)
    {
        switch ((*i)->token)
        {
            case CONST:
                result->isConst = true;
                break;
            case VOLATILE:
                result->isVolatile = true;
                break;
            default:
                throw new errors::InternalCompilerException("unknown type qualifier encountered");
        }
    }
    
    // now push new type back on the stack
    this->m_declTypeStack.push_back(result);
}


/* 3.5.4.2 Array declarators */

void SemanticCheckVisitor::visit(astnodes::ArrayDeclarator * arrayDeclarator)
{
    // first add pointers to the type 
    if (arrayDeclarator->pointers != NULL)
        for (astnodes::Pointers::iterator i = arrayDeclarator->pointers->begin(); i != arrayDeclarator->pointers->end(); ++i)
            (*i)->acceptPostRecursive(*this);
    
    // get base type
    types::Type* baseType = this->m_declTypeStack.back();
    this->m_declTypeStack.pop_back();
    
    types::Type* result = NULL;
    
    long size = -1;
    if (arrayDeclarator->constExpr != NULL)
    {
        // first visit the expression with this visitor
        arrayDeclarator->constExpr->accept(*this);
        
        // get size 
        if (! valuetypes::IsValueTypeHelper::isCValue(arrayDeclarator->constExpr->valType))
        {
            addError(arrayDeclarator, ERR_CC_ARRAY_SIZE_NOT_CONST);
            this->m_declTypeStack.push_back(new types::InvalidType());
            return;
        }
        
        ConstExprEvalVisitor ceval;
        arrayDeclarator->constExpr->accept(ceval);
        size = valuetypes::ConstHelper::getIntegralConst(arrayDeclarator->constExpr->valType);
        
        // TODO maybe support GNU C like arrays of size 0
        if (size < 1)
        {
            addError(arrayDeclarator, ERR_CC_ARRAY_SIZE_NOT_POS);
            this->m_declTypeStack.push_back(new types::InvalidType());
            return;
        }
    }
    else
    {
        if (m_declIsStored.back())
        {
            addError(arrayDeclarator, ERR_CC_ARRAY_SIZE_MISSING);
            this->m_declTypeStack.push_back(new types::InvalidType());
            return;
        }
        size = -1;
    }
    
    if (!baseType->isComplete())
    {
        addError(arrayDeclarator, ERR_CC_ARRAY_INCOMPL_TYPE);
        this->m_declTypeStack.push_back(new types::InvalidType());
        return;
    }
    
    uint16_t typeSize = baseType->getWordSize();
    
    result = new types::ArrayType(baseType, (int) size, typeSize);
    this->m_declTypeStack.push_back(result);
    
    // visit recursively
    arrayDeclarator->baseDeclarator->accept(*this);
    
    // and the initializers
    if (arrayDeclarator->initializers != NULL)
        for (astnodes::Expressions::iterator i = arrayDeclarator->initializers->begin(); i != arrayDeclarator->initializers->end(); ++i)
            (*i)->accept(*this);
        
    // TODO check for compatibility of init types
    for (astnodes::Expressions::iterator init = arrayDeclarator->initializers->begin(); init != arrayDeclarator->initializers->end(); ++init)
    {
        
        // check that the type is compatible
        // TODO
    }
}


/* 3.5.4.3 Function declarators */

void SemanticCheckVisitor::visit(astnodes::FunctionDeclarator * functionDeclarator)
{
    // first add pointers to the type 
    if (functionDeclarator->pointers != NULL)
        for (astnodes::Pointers::iterator i = functionDeclarator->pointers->begin(); i != functionDeclarator->pointers->end(); ++i)
            (*i)->acceptPostRecursive(*this);
    
    // get return type
    types::Type* returnType = this->m_declTypeStack.back();
    this->m_declTypeStack.pop_back();
    
    // check that return type is not a function
    if (types::IsTypeHelper::isFunctionType(returnType))
    {
        addError(functionDeclarator, ERR_CC_FUNCDECL_RETURN_FUNCT);
        this->m_declTypeStack.push_back(new types::InvalidType());
        return;
    }
    
    // check that return type is not an array
    if (types::IsTypeHelper::isArrayType(returnType))
    {
        addError(functionDeclarator, ERR_CC_FUNCDECL_RETURN_ARRAY);
        this->m_declTypeStack.push_back(new types::InvalidType());
        return;
    }
    
    symboltable::SymbolTableScope* scope = NULL;
    if (!this->m_saveParams.back())
    {
        symboltable::SymbolTableScope* scope = m_symbolTable->beginNewScope();
    }
    
    // visit all declarators in the parameter list
    for (std::vector<astnodes::Declaration*>::iterator i = functionDeclarator->parameterList->declarations.begin(); i != functionDeclarator->parameterList->declarations.end(); ++i)
    {
        (*i)->accept(*this);
    }
    
    
    if (!this->m_saveParams.back())
    {
        m_symbolTable->endScope();
        delete scope;
        scope = NULL;
    }
    
    // get the type list
    types::ParameterTypeList* paramTypes = new types::ParameterTypeList();
    

    for (std::vector<astnodes::Declaration*>::iterator i = functionDeclarator->parameterList->declarations.begin(); i != functionDeclarator->parameterList->declarations.end(); ++i)
    {
        // check that it is a valid type
        if (types::IsTypeHelper::isInvalidType((*i)->type))
        {
            // in this case error message has already been output
            this->m_declTypeStack.push_back(new types::InvalidType());
            return;
        }
        
        // add to param list
        paramTypes->push_back((*i)->type);
    }
    
    // check if this is a paramter list like:  foo(void)
    if (paramTypes->size() == 1
        && types::IsTypeHelper::isVoid(paramTypes->back()))
    {
        // only one void paramter -> same as empty parameter list
        paramTypes->clear();
    }
    
    // get var args 
    bool varargs = functionDeclarator->parameterList->varArgs;
    
    // now we have everything to construct the function type
    types::Type* funtype = new types::FunctionType(returnType, paramTypes, varargs);
    
    // push type
    this->m_declTypeStack.push_back(funtype);
    
    // visit recursively
    functionDeclarator->baseDeclarator->accept(*this);
    
    // and the initializers (if any)
    if (functionDeclarator->initializers != NULL)
    {
        // check that there is at most 1 initializer
        if (functionDeclarator->initializers->size() > 1)
        {
            addError(functionDeclarator, ERR_CC_TOO_MANY_INITS, this->m_declNameStack.back());
            return;
        }
        
        if (functionDeclarator->initializers->size() == 1)
        {
            // visit the expression
            functionDeclarator->initializers->front()->accept(*this);
            
            // now check for compatible types
            // TODO
        }
    }
}











/**********************************/
/*       3.5.5 Type names         */
/**********************************/

// the type for cast and size of expression
// TODO do something very similar to declaration
// in order to get the type to return
void SemanticCheckVisitor::visit(astnodes::TypeName * typeName)
{
    printAstName("TypeName");
    typeName->allChildrenAccept(*this);
}











/**********************************/
/* 3.5.1 Storage-class specifiers */
/**********************************/

void SemanticCheckVisitor::visit(astnodes::StorageSpecifier * storageSpecifier)
{
    throw new errors::InternalCompilerException("a storage specifier should not be visited");
}




/******************************/
/*  3.5.2 Type specifiers     */
/******************************/


types::Type* SemanticCheckVisitor::declSpecsToType(astnodes::DeclarationSpecifiers* declSpecs)
{
    
    // first get the type from the type specifier
    resetDeclSpecs();
    // visit all type specifiers
    for (std::vector<astnodes::TypeSpecifier*>::iterator i = declSpecs->typeSpecifiers.begin(); i != declSpecs->typeSpecifiers.end(); ++i)
    {
        (*i)->accept(*this);
    }
    // now get the type
    types::Type* declType = typeSpecsToType(declSpecs->typeSpecifiers.front());
    // is it a valid type?
    if (types::IsTypeHelper::isInvalidType(declType))
        // errors have already been generated in this case, just ignore this declaration
        return new types::InvalidType();
    
    // now check for type qualifiers
    for (std::vector<astnodes::TypeQualifier*>::iterator i = declSpecs->typeQualifiers.begin(); i != declSpecs->typeQualifiers.end(); ++i)
    {
        switch ((*i)->token)
        {
            case CONST:
                declType->isConst = true;
                break;
            case VOLATILE:
                declType->isVolatile = true;
                break;
            default:
                throw new errors::InternalCompilerException("unknown type qualifier encountered");
        }
    }
    
    return declType;
}



void SemanticCheckVisitor::resetDeclSpecs()
{
    declSpecs.isAdvType = false;
    declSpecs.type = NULL;
    declSpecs.isVoid = false;
    declSpecs.isChar = false;
    declSpecs.isSigned = false;
    declSpecs.isUnsigned = false;
    declSpecs.isInt = false;
    declSpecs.isLong = false;
    declSpecs.isShort = false;
    declSpecs.isFloat = false;
    declSpecs.isDouble = false;
}

types::Type* SemanticCheckVisitor::typeSpecsToType(astnodes::Node* decl)
{
    types::Type* result = NULL;
    
    // check for non-basic types
    if (declSpecs.isAdvType && declSpecs.type != NULL)
    {
        result = declSpecs.type;
    }
    // now check for all the basic types
    else if (declSpecs.isVoid)
    {
        result = new types::Void();
        declSpecs.isVoid = false;
    }
    else if (declSpecs.isFloat)
    {
        result = new types::Float();
        declSpecs.isFloat = false;
    }
    else if (declSpecs.isDouble && declSpecs.isLong)
    {
        result = new types::LongDouble();
        declSpecs.isDouble = false;
        declSpecs.isLong = false;
    }
    else if (declSpecs.isDouble)
    {
        result = new types::Double();
        declSpecs.isDouble = false;
    }
    else if (declSpecs.isChar && declSpecs.isSigned)
    {
        result = new types::SignedChar();
        declSpecs.isSigned = false;
        declSpecs.isChar = false;
    }
    else if (declSpecs.isChar)
    {
        result = new types::UnsignedChar();
        declSpecs.isUnsigned = false;
        declSpecs.isChar = false;
    }
    else if (declSpecs.isShort && declSpecs.isUnsigned)
    {
        result = new types::UnsignedShort();
        declSpecs.isUnsigned = false;
        declSpecs.isShort = false;
        declSpecs.isInt = false;
    }
    else if (declSpecs.isShort)
    {
        result = new types::SignedShort();
        declSpecs.isSigned = false;
        declSpecs.isShort = false;
        declSpecs.isInt = false;
    }

    else if (declSpecs.isLong && declSpecs.isUnsigned)
    {
        result = new types::UnsignedLong();
        declSpecs.isUnsigned = false;
        declSpecs.isLong = false;
        declSpecs.isInt = false;
    }
    else if (declSpecs.isLong)
    {
        result = new types::SignedLong();
        declSpecs.isSigned = false;
        declSpecs.isLong = false;
        declSpecs.isInt = false;
    }
    else if (declSpecs.isUnsigned)
    {
        result = new types::UnsignedInt();
        declSpecs.isUnsigned = false;
        declSpecs.isInt = false;
    }
    else if (declSpecs.isInt)
    {
        result = new types::SignedInt();
        declSpecs.isSigned = false;
        declSpecs.isInt = false;
    }
    else
    {
        addError(decl, ERR_CC_DECLSPEC_NO_TYPE);
        return new types::InvalidType();
    }
    
    // if any of the bools are still set, we've got a conflict
    if (   declSpecs.isVoid
        || declSpecs.isChar
        || declSpecs.isSigned
        || declSpecs.isUnsigned
        || declSpecs.isInt
        || declSpecs.isLong
        || declSpecs.isShort
        || declSpecs.isFloat
        || declSpecs.isDouble)
    {
        addError(decl, ERR_CC_DECLSPEC_CONFL);
        return new types::InvalidType();
    }
    
    if (result == NULL)
        throw new errors::InternalCompilerException("something weird has happend during resolution of type specifiers");
    
    return result;
}

void SemanticCheckVisitor::visit(astnodes::TypeSpecifier * typeSpecifier)
{
    throw new errors::InternalCompilerException("Declarator Node is only abstract and cannot be visited");
}

void SemanticCheckVisitor::visit(astnodes::TypeBaseSpecifier * typeBaseSpecifier)
{
    switch(typeBaseSpecifier->token)
    {
        case VOID:
            if (declSpecs.isVoid)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_VOID_DUPL);
            else
                declSpecs.isVoid = true;
            break;
        case CHAR:
            if (declSpecs.isChar)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_CHAR_DUPL);
            else
                declSpecs.isChar = true;
            break;
        case SHORT:
            if (declSpecs.isShort)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_SHORT_DUPL);
            else
                declSpecs.isShort = true;
            break;
        case INT:
            if (declSpecs.isInt)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_INT_DUPL);
            else
                declSpecs.isInt = true;
            break;
        case LONG:
            if (declSpecs.isLong)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_LONG_DUPL);
            else
                declSpecs.isLong = true;
            break;
        case FLOAT:
            if (declSpecs.isFloat)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_FLOAT_DUPL);
            else
                declSpecs.isFloat = true;
            break;
        case DOUBLE:
            if (declSpecs.isDouble)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_DOUBLE_DUPL);
            else
                declSpecs.isDouble = true;
            break;
        case SIGNED:
            if (declSpecs.isSigned)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_SIGNED_DUPL);
            else if (declSpecs.isUnsigned)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_CONFL_SIGNED);
            else
                declSpecs.isSigned = true;
            break;
        case UNSIGNED:
            if (declSpecs.isUnsigned)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_UNSIGNED_DUPL);
            else if (declSpecs.isSigned)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_CONFL_SIGNED);
            else
                declSpecs.isUnsigned = true;
            break;
        default:
            throw new errors::InternalCompilerException("unkown type specifier encountered");
    }
}



void SemanticCheckVisitor::visit(astnodes::StructUnionSpecifier * structUnionSpecifier)
{
    printAstName("StructUnionSpecifier");
    structUnionSpecifier->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::EnumSpecifier * enumSpecifier)
{
    printAstName("EnumSpecifier");
    enumSpecifier->allChildrenAccept(*this);
}



void SemanticCheckVisitor::visit(astnodes::TypeNameSpecifier * typeNameSpecifier)
{
    printAstName("TypeNameSpecifier");
    typeNameSpecifier->allChildrenAccept(*this);
}


/******************************/
/*  3.5.3 Type qualifiers     */
/******************************/

void SemanticCheckVisitor::visit(astnodes::TypeQualifier * typeQualifier)
{
    throw new errors::InternalCompilerException("a type qualifier should not be visited");
}



/*######################################*/
/*      3.3 Expressions                 */
/*######################################*/


/******************************/
/*  3.3.1 Primary expressions */
/******************************/

/* identifier */

void SemanticCheckVisitor::visit(astnodes::Identifier * identifier)
{
    if (!this->m_symbolTable->containsRec(identifier->name))
    {
        addError(identifier, ERR_CC_VARIABLE_NOT_IN_SCOPE, identifier->name);
        identifier->valType = getInvalidValType();
        // don't handle anything below
        return;
    }
    
    // TODO enum types are constants!! 
    
    types::Type* varType = this->m_symbolTable->getTypeOfVariable(identifier->name);
    if (varType == NULL)
    {
        // this must be a function then
        types::FunctionType* funcType = this->m_symbolTable->getFunction(identifier->name);
        if (funcType == NULL)
        {
            throw new errors::InternalCompilerException("Neither a variable nor a function was found by the name '" + identifier->name + "'.");
        }
        identifier->valType = new valuetypes::FunctionDesignator(funcType);
    }
    else
    {
        identifier->valType = new valuetypes::LValue(varType);
    }
}


/* constants */

void SemanticCheckVisitor::visit(astnodes::CharacterLiteral * characterLiteral)
{
    characterLiteral->valType = new valuetypes::CValue(new types::UnsignedChar());
}


void SemanticCheckVisitor::visit(astnodes::SignedIntLiteral * signedIntLiteral)
{
    signedIntLiteral->valType = new valuetypes::CValue(new types::SignedInt());
}


void SemanticCheckVisitor::visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral)
{
    unsignedIntLiteral->valType = new valuetypes::CValue(new types::UnsignedInt());
}


void SemanticCheckVisitor::visit(astnodes::SignedLongLiteral * signedLongLiteral)
{
    signedLongLiteral->valType = new valuetypes::CValue(new types::SignedLong());
}


void SemanticCheckVisitor::visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral)
{
    unsignedLongLiteral->valType = new valuetypes::CValue(new types::UnsignedLong());
}


void SemanticCheckVisitor::visit(astnodes::FloatLiteral * floatLiteral)
{
    floatLiteral->valType = new valuetypes::CValue(new types::Float());
}


void SemanticCheckVisitor::visit(astnodes::DoubleLiteral * doubleLiteral)
{
    doubleLiteral->valType = new valuetypes::CValue(new types::Double());
}


void SemanticCheckVisitor::visit(astnodes::LongDoubleLiteral * longDoubleLiteral)
{
    longDoubleLiteral->valType = new valuetypes::CValue(new types::LongDouble());
}


/* string literal */

void SemanticCheckVisitor::visit(astnodes::StringLiteral * stringLiteral)
{
   stringLiteral->valType = new valuetypes::LValue(new types::ArrayType(new types::UnsignedChar(), stringLiteral->str.length(), 1));
}




/******************************/
/*  3.3.2 Postfix expressions */
/******************************/

/* 3.3.2.1 array subscripting */

void SemanticCheckVisitor::visit(astnodes::ArrayAccessOperator * arrayAccessOperator)
{
    // analyse both sub expressions
    arrayAccessOperator->allChildrenAccept(*this);
    
    // check LHS type
    types::Type* lhsType = arrayAccessOperator->lhsExpr->valType->type;
    
    if (types::IsTypeHelper::isArrayType(lhsType))
    {
        // convert array to pointer type
        lhsType = types::IsTypeHelper::pointerFromArrayType(lhsType);
    }
    else
    {
        // get LtoR state
        if (valuetypes::IsValueTypeHelper::isLValue(arrayAccessOperator->lhsExpr->valType))
        {
            arrayAccessOperator->lhsLtoR = true;
        }
    }
    
    if(!types::IsTypeHelper::isPointerType(lhsType))
    {
        addError(arrayAccessOperator, ERR_CC_ARRAY_ACCESS_NO_POINTER);
        arrayAccessOperator->valType = getInvalidValType();
        return;
    }
    if (!types::IsTypeHelper::isObjectType(types::IsTypeHelper::getPointerType(lhsType)->baseType))
    {
        addError(arrayAccessOperator, ERR_CC_DEREF_INCOMPLETE_TYPE);
        arrayAccessOperator->valType = getInvalidValType();
        return;
    }
    
    arrayAccessOperator->pointerSize = types::IsTypeHelper::getPointerType(lhsType)->baseType->getWordSize();
    
    // check RHS type
    types::Type* rhsType = arrayAccessOperator->rhsExpr->valType->type;
    
    // get LtoR state
    if (valuetypes::IsValueTypeHelper::isLValue(arrayAccessOperator->rhsExpr->valType))
    {
        arrayAccessOperator->rhsLtoR = true;
    }
    
    if(!types::IsTypeHelper::isIntegralType(rhsType))
    {
        addError(arrayAccessOperator, ERR_CC_ARRAY_SUB_NOT_INT);
        arrayAccessOperator->valType = getInvalidValType();
        return;
    }
    
    arrayAccessOperator->valType = new valuetypes::LValue(types::IsTypeHelper::getPointerType(lhsType)->baseType);
}


/* 3.3.2.2 Function calls */

void SemanticCheckVisitor::visit(astnodes::MethodCall * methodCall)
{
    // analyse lhs and all arguments
    methodCall->allChildrenAccept(*this);
    
    // check LHS type
    types::Type* lhsType = methodCall->lhsExpr->valType->type;
    
    types::FunctionType* funType = NULL;
    
    if (! valuetypes::IsValueTypeHelper::isFunctionDesignator(methodCall->lhsExpr->valType))
    {
        if (!types::IsTypeHelper::isFunctionType(lhsType)){
            if(!types::IsTypeHelper::isPointerType(lhsType))
            {
                addError(methodCall, ERR_CC_CALLED_OBJ_NOT_FUNC);
                methodCall->valType = getInvalidValType();
                return;
            }
            if (!types::IsTypeHelper::isFunctionType(types::IsTypeHelper::getPointerType(lhsType)->baseType))
            {
                addError(methodCall, ERR_CC_CALLED_OBJ_NOT_FUNC);
                methodCall->valType = getInvalidValType();
                return;
            }
            funType = types::IsTypeHelper::getFunctionType(types::IsTypeHelper::getPointerType(lhsType)->baseType);
        }
        else
        {
            funType = types::IsTypeHelper::getFunctionType(lhsType);
        }
    }
    else
    {
        funType = types::IsTypeHelper::getFunctionType(methodCall->lhsExpr->valType->type);
    }
    
    // now we are sure it is a pointer to a function, get the functiontype
    methodCall->valType = new valuetypes::RValue(funType->returnType);
    
    // check for same size (or in case of variable arguments (...) for the call having
    // at least as many arguments as there are parameters in the function type.
    if ((funType->isVarArgs && methodCall->rhsExprs->size() < funType->paramTypes->size())
        || (!funType->isVarArgs && methodCall->rhsExprs->size() != funType->paramTypes->size()))
    {
        addError(methodCall, ERR_CC_CALLED_FUNC_NUM_PARAMS);
        return;
    }
    
    for (unsigned int i = 0; i < methodCall->rhsExprs->size(); i++)
    {
        valuetypes::ValueType* from = (*methodCall->rhsExprs)[i]->valType;
        types::Type* to = (*funType->paramTypes)[i];
        // make sure all the parameter types match
        // TODO check that they are assignable (see assignment operator)
        // TODO FIXME TODO FIXME
    }
    
    // TODO what to do if return type is bigger than 1 word??
}


/* 3.3.2.3 Structure and union members */

void SemanticCheckVisitor::visit(astnodes::StructureResolutionOperator * structureResolutionOperator)
{
    // TODO FIXME TODO FIXME
    // TODO implement structs properly
    printAstName("StructureResolutionOperator");
    structureResolutionOperator->allChildrenAccept(*this);
}


/* 3.3.2.4 Postfix increment and decrement operators */

void SemanticCheckVisitor::visit(astnodes::PostIncDec * postIncDec)
{
    // fist analyse the inner expression
    postIncDec->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(postIncDec->expr->valType->type))
    {
        addError(postIncDec, ERR_CC_EXPECTED_SCALAR_INCDEC);
    }
    
    // if this is a pointer operation, set the size of the pointer
    if (types::IsTypeHelper::isPointerType(postIncDec->expr->valType->type))
    {
        postIncDec->pointerSize = types::IsTypeHelper::getPointerBaseSize(postIncDec->expr->valType->type);
    }
    
    // check that the expression type is a scalar type
    if(!valuetypes::IsValueTypeHelper::isModifiableLValue(postIncDec->expr->valType))
    {
        addError(postIncDec, ERR_CC_INCDEC_NO_MOD_LVALUE);
    }
    
    // same value type
    postIncDec->valType = valuetypes::IsValueTypeHelper::toRValue(postIncDec->expr->valType);
}



/******************************/
/*  3.3.3 Unary operators     */
/******************************/

/* 3.3.3.1 Prefix increment and decrement operators */

void SemanticCheckVisitor::visit(astnodes::PreIncDec * preIncDec)
{
    // fist analyse the inner expression
    preIncDec->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(preIncDec->expr->valType->type))
    {
        addError(preIncDec, ERR_CC_EXPECTED_SCALAR_INCDEC);
    }
    
    // if this is a pointer operation, set the size of the pointer
    if (types::IsTypeHelper::isPointerType(preIncDec->expr->valType->type))
    {
        preIncDec->pointerSize = types::IsTypeHelper::getPointerBaseSize(preIncDec->expr->valType->type);
    }
    
    // check that the expression type is a scalar type
    if(!valuetypes::IsValueTypeHelper::isModifiableLValue(preIncDec->expr->valType))
    {
        addError(preIncDec, ERR_CC_INCDEC_NO_MOD_LVALUE);
    }
    
    // same value type
    preIncDec->valType = valuetypes::IsValueTypeHelper::toRValue(preIncDec->expr->valType);
}

/* 3.3.3.2 Address and indirection operators */
// TODO add the Address of Operator!


/* 3.3.3.3 Unary arithmetic operators */

void SemanticCheckVisitor::visit(astnodes::UnaryOperator * unaryOperator)
{
    // analyse inner expression first:
    unaryOperator->allChildrenAccept(*this);
    
    valuetypes::ValueType* vtype = unaryOperator->expr->valType;
    types::Type* type = vtype->type;
    
    if (valuetypes::IsValueTypeHelper::isLValue(vtype))
    {
        unaryOperator->LtoR = true;
        if (types::IsTypeHelper::isArrayType(type))
        {
            type = types::IsTypeHelper::pointerFromArrayType(type);
        }
    }
    
    switch(unaryOperator->optoken)
    {
        case ADD_OP:
        case SUB_OP:
            // check that the expression type is a arithmetic type
            if(!types::IsTypeHelper::isArithmeticType(type))
            {
                addError(unaryOperator, ERR_CC_UNARY_PLUS_MINUS_ARITH);
                unaryOperator->valType = getInvalidValType();
                return;
            }
            unaryOperator->valType = valuetypes::PromotionHelper::promote(vtype);
            break;
            
        case BIN_INV_OP:
            // check that the expression type is a arithmetic type
            if(!types::IsTypeHelper::isIntegralType(type))
            {
                addError(unaryOperator, ERR_CC_UNARY_INV_INTEGRAL);
                unaryOperator->valType = getInvalidValType();
                return;
            }
            unaryOperator->valType = valuetypes::PromotionHelper::promote(vtype);
            break;
            
        case NOT_OP:
            // check that the expression type is a arithmetic type
            if(!types::IsTypeHelper::isScalarType(type))
            {
                addError(unaryOperator, ERR_CC_UNARY_NOT_SCALAR);
                unaryOperator->valType = getInvalidValType();
                return;
            }
            unaryOperator->valType = new valuetypes::RValue(new types::SignedInt());
            break;
        default:
            throw new errors::InternalCompilerException("Unknown unary operator encountered");
    }
}


/* 3.3.3.4 The sizeof operator */

void SemanticCheckVisitor::visit(astnodes::SizeOfOperator * sizeOfOperator)
{
    // analyse the expression inside the sizeof operator
    sizeOfOperator->allChildrenAccept(*this);
    
    // set return type as a CValue (constant RValue)
    sizeOfOperator->valType = new valuetypes::CValue(new types::UnsignedInt());
    
    // check it is not a function type
    if (valuetypes::IsValueTypeHelper::isFunctionDesignator(sizeOfOperator->valType))
    {
        addError(sizeOfOperator, ERR_CC_SIZEOF_FUNC);
        return;
    }
    
    // return the word size of the expression type
    // TODO special return value for array types??
    sizeOfOperator->constExpr = new astnodes::UnsignedIntLiteral(sizeOfOperator->valType->type->getByteSize());
    sizeOfOperator->constExpr->accept(*this);
}


/******************************/
/*  3.3.4 Cast operators      */
/******************************/

void SemanticCheckVisitor::visit(astnodes::ExplicitCastOperator * explicitCastOperator)
{
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    printAstName("ExplicitCastOperator");
    explicitCastOperator->allChildrenAccept(*this);
}



/******************************/
/*     binary operators       */
/******************************/

void SemanticCheckVisitor::visit(astnodes::BinaryOperator * binaryOperator)
{
    // analyse both sub-expressions
    binaryOperator->allChildrenAccept(*this);
    
    valuetypes::ValueType* lhsVtype = binaryOperator->lhsExrp->valType;
    valuetypes::ValueType* rhsVtype = binaryOperator->rhsExpr->valType;
    types::Type* lhsType = lhsVtype->type;
    types::Type* rhsType = rhsVtype->type;
    
    /* check for LValue to RValue conversions */
    if (valuetypes::IsValueTypeHelper::isLValue(lhsVtype))
    {
        binaryOperator->lhsLtoR = true;
        if (types::IsTypeHelper::isArrayType(lhsType))
        {
            lhsType = types::IsTypeHelper::pointerFromArrayType(lhsType);
        }
    }
    if (valuetypes::IsValueTypeHelper::isLValue(rhsVtype))
    {
        binaryOperator->rhsLtoR = true;
        if (types::IsTypeHelper::isArrayType(rhsType))
        {
            rhsType = types::IsTypeHelper::pointerFromArrayType(rhsType);
        }
    }
    
    
    switch(binaryOperator->optoken)
    {
        
        /* 3.3.5 Multiplicative operators */
        
        case MUL_OP:
        case DIV_OP:
            // check that the expression type is a arithmetic type
            if((!types::IsTypeHelper::isArithmeticType(lhsType))
                || !types::IsTypeHelper::isArithmeticType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_ARITH);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
            binaryOperator->commonType = binaryOperator->valType->type;
            break;
        case MOD_OP:
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
            binaryOperator->commonType = binaryOperator->valType->type;
            break;
        
            
        /* 3.3.6 Additive operators */
        
        case ADD_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
                binaryOperator->commonType = binaryOperator->valType->type;
            }
            else if(((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType)))

            {
                // pointer op
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                binaryOperator->commonType = types::IntegralPromotion::promote(rhsType);
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(lhsType, lhsVtype, rhsVtype);
            }
            else if ((types::IsTypeHelper::isIntegralType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                // pointer op
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(rhsType);
                binaryOperator->commonType = types::IntegralPromotion::promote(lhsType);
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(rhsType, lhsVtype, rhsVtype);
            }
            else
            {
                addError(binaryOperator, ERR_CC_BIN_ADD_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
        case SUB_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
                binaryOperator->commonType = binaryOperator->valType->type;
            } else if((binaryOperator->optoken == SUB_OP)
                && (types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                // TODO add ptrdiff_t to stddef.h
                binaryOperator->lhsPtr = true;
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                binaryOperator->commonType = new types::UnsignedInt();
                // TODO properly check for compatible types pointed to
                if (binaryOperator->pointerSize != types::IsTypeHelper::getPointerBaseSize(rhsType))
                {
                    addError(binaryOperator, ERR_CC_PTR_NOT_COMPAT);
                    binaryOperator->valType = getInvalidValType();
                    return;
                }
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            } else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType))
            {
                binaryOperator->lhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                binaryOperator->commonType = new types::UnsignedInt();
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(lhsType, lhsVtype, rhsVtype);
            }
            else
            {
                addError(binaryOperator, ERR_CC_BIN_SUB_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
            
            
        /* 3.3.7 Bitwise shift operators */
            
        case LEFT_OP:
        case RIGHT_OP:
            // check that the expression type is a integral type
            // TODO check that RHS is size 1 otherwise convert!!
            // TODO (same for the pointer ops above)
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            
            binaryOperator->commonType = valuetypes::PromotionHelper::promote(lhsVtype)->type;
            binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(binaryOperator->commonType, lhsVtype, rhsVtype);
            break;
            
        /* 3.3.8 Relational operators */
        case LT_OP:
        case GT_OP:
        case LE_OP:
        case GE_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            } else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                binaryOperator->lhsPtr = true;
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                
                // TODO properly check for compatible types pointed to
                if (binaryOperator->pointerSize != types::IsTypeHelper::getPointerBaseSize(rhsType))
                {
                    addError(binaryOperator, ERR_CC_PTR_NOT_COMPAT);
                    binaryOperator->valType = getInvalidValType();
                    return;
                }
                
                binaryOperator->commonType = new types::UnsignedInt();
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            }
            else
            {
                addError(binaryOperator, ERR_CC_COMP_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
            
        
        /* 3.3.9 Equality operators */
        
        case EQ_OP:
        case NE_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            } else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                binaryOperator->lhsPtr = true;
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                
                // TODO properly check for compatible types pointed to
                if (binaryOperator->pointerSize != types::IsTypeHelper::getPointerBaseSize(rhsType))
                {
                    addError(binaryOperator, ERR_CC_PTR_NOT_COMPAT);
                    binaryOperator->valType = getInvalidValType();
                    return;
                }
                binaryOperator->commonType = new types::UnsignedInt();
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            }
            // TODO case for Null pointer constant
            else
            {
                addError(binaryOperator, ERR_CC_COMP_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
        
            
        /* 3.3.10 Bitwise AND operator */
        /* 3.3.11 Bitwise exclusive OR operator */
        /* 3.3.12 Bitwise inclusive OR operator */
        
        case BIN_AND_OP:
        case BIN_XOR_OP:
        case BIN_OR_OP:
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            
            binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
            binaryOperator->commonType = binaryOperator->valType->type;
            break;
            
            
            /* 3.3.13 Logical AND operator */
            /* 3.3.14 Logical OR operator */
            
        case AND_OP:
        case OR_OP:
            
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }

            binaryOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            break;
            
        default:
            throw new errors::InternalCompilerException("unknown binary operator encountered");
    }
}

/********************************/
/* 3.3.15 Conditional operator  */
/********************************/
 
void SemanticCheckVisitor::visit(astnodes::ConditionalOperator * conditionalOperator)
{
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    printAstName("ConditionalOperator");
    conditionalOperator->allChildrenAccept(*this);
}



/********************************/
/* 3.3.16 Assignment operators  */
/********************************/

void SemanticCheckVisitor::visit(astnodes::AssignmentOperator * assignmentOperator)
{
    // first check lhs and rhs expression
    assignmentOperator->allChildrenAccept(*this);
    
    valuetypes::ValueType* lhsVtype = assignmentOperator->lhsExrp->valType;
    valuetypes::ValueType* rhsVtype = assignmentOperator->rhsExpr->valType;
    types::Type* lhsType = lhsVtype->type;
    types::Type* rhsType = rhsVtype->type;
   
    
    // check that the lhs is a modifiable LValue
    if(!valuetypes::IsValueTypeHelper::isModifiableLValue(assignmentOperator->lhsExrp->valType))
    {
        addError(assignmentOperator, ERR_CC_ASSIGN_NO_MOD_LVALUE);
    }
    
    /* check for LtoR conversion */
    if (valuetypes::IsValueTypeHelper::isLValue(rhsVtype))
    {
        assignmentOperator->rhsLtoR = true;
        if (types::IsTypeHelper::isArrayType(rhsType))
        {
            rhsType = types::IsTypeHelper::pointerFromArrayType(rhsType);
        }
    }
    
    /* convert array to pointer type */
    if (types::IsTypeHelper::isArrayType(lhsType))
    {
        lhsType = types::IsTypeHelper::pointerFromArrayType(lhsType);
    }
    
    switch (assignmentOperator->optoken)
    {
        
        /* 3.3.16.1 Simple assignment */
        
        case ASSIGN_EQUAL:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                // TODO properly check for compatible types pointed to
                assignmentOperator->ptrop = true;
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
            }
            else if((types::IsTypeHelper::isStructUnionType(lhsType))
                && types::IsTypeHelper::isStructUnionType(rhsType))
            {
                // TODO properly check for compatible structs/unions
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
            
            
        /* 3.3.16.2 Compound assignment */
            
        case ADD_ASSIGN:
        case SUB_ASSIGN:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else if(((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType)))
                
            {
                // pointer op
                assignmentOperator->ptrop = true;
                assignmentOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
            
        case MUL_ASSIGN:
        case DIV_ASSIGN:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
            
        case MOD_ASSIGN:
        case LEFT_ASSIGN:
        case RIGHT_ASSIGN:
        case AND_ASSIGN:
        case XOR_ASSIGN:
        case OR_ASSIGN:
            if((types::IsTypeHelper::isIntegralType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
        default:
            throw new errors::InternalCompilerException("unknown assignment operator encountered");
    }
}



/********************************/
/*  3.3.17 Comma operator       */
/********************************/

void SemanticCheckVisitor::visit(astnodes::ChainExpressions * chainExpressions)
{
    // analyse all children
    chainExpressions->allChildrenAccept(*this);
    
    // check if all values types are constant
    bool isCValue = true;
    if (chainExpressions->exprs != NULL && chainExpressions->exprs->size() > 0)
    {
        for (astnodes::Expressions::iterator i = chainExpressions->exprs->begin(); i != chainExpressions->exprs->end(); ++i)
        {
            if (!valuetypes::IsValueTypeHelper::isCValue((*i)->valType))
                isCValue = false;
        }
        
        if (isCValue)
            chainExpressions->valType = new valuetypes::CValue(chainExpressions->exprs->back()->valType->type);
        else
            chainExpressions->valType = new valuetypes::RValue(chainExpressions->exprs->back()->valType->type);
    }
    else
    {
        throw new errors::InternalCompilerException("chain expressions without any expressions");
    }
}






// TODO implement those below
// TODO implement deref und address of operators!!





void SemanticCheckVisitor::visit(astnodes::Enumerator * enumerator)
{
    printAstName("Enumerator");
    enumerator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::AssemblyStatement * assemblyStatement)
{
    printAstName("AssemblyStatement");
    assemblyStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::BuiltInVaStart * builtInVaStart)
{
    printAstName("BuiltInVaStart");
    builtInVaStart->allChildrenAccept(*this);
}

