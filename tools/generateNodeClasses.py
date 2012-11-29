import string


CLASS_NAMES_FILE="../ASTClasses.txt"
OUTPUT_FOLDER="nodes"
H_TEMPLATE="node_template.hpp"
CPP_TEMPLATE="node_template.cpp"


def parsefile(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    
    for row in lines:
        parserow(row)


def parserow(row):
    s1 = row.split("(")
    ClassName = s1[0].strip();
    s2 = s1[1].split(")")
    params_argument_list = s2[0].strip()
    if params_argument_list == "":
        params_str = []
    else:
        params_str = s2[0].split(",")
    s3 = s2[1].split(":");
    if len(s3) > 1:
        superclass = s3[1].strip()
    else:
        superclass = "Node"
    
    param_names = []
    # parse params
    for str4 in params_str:
        str5 = str4.split(" ");
        param_name = str5[-1].strip()
        param_names.append(param_name)
    
    paramlist = params_str;
    
    
    
    otherclasses = []
    for s in params_str:
        otherclass_name = s.strip().split(" ")[0].split("*")[0].split("&")[0].strip()
        if otherclass_name != superclass and otherclass_name != "" and otherclass_name != "int" and otherclass_name != "std::string":
            otherclasses.append(otherclass_name);
            
    includes="#include \"" + superclass + ".h\"\n"
    for s in list(set(otherclasses)):
        includes += "#include \"" + s + ".h\"\n"
    
    contr_init = ""
    if len(param_names) > 0:
        contr_init = ": "
    for i,s in enumerate(param_names):
        contr_init += s + "(" + s + ")"
        if i < len(param_names)-1:
            contr_init += ", "
        
    
    classmember = ""
    for s in params_str:
        classmember += " "*12 + s.strip() + ";\n"
        
    CLASSNAME = ClassName.upper();
    
    deleteclassmembers = ""
    for s in param_names:
        deleteclassmembers += "    delete this->" + s + ";\n"
    
    doxygenparams = ""
    for s in param_names:
        doxygenparams += " "*12 + "/// @param " + s + " TODO: FILLOUT\n"
    
    childaccept = ""
    for s in param_names:
        childaccept += "    this->" + s + "->accept(visitor);\n"
    
    hTemplate = ""
    with open(H_TEMPLATE, 'r') as f:
        hTemplate = f.read()
    
    hResult = hTemplate
    hResult = hResult.replace("%ClassName%", ClassName);
    hResult = hResult.replace("%CLASSNAME%", CLASSNAME);
    hResult = hResult.replace("%SuperClassName%", superclass);
    hResult = hResult.replace("%DoxygenConstructorParams%", doxygenparams);
    hResult = hResult.replace("%Params%", params_argument_list);
    hResult = hResult.replace("%ClassMembers%", classmember);
    hResult = hResult.replace("%ParamInit%", contr_init);
    hResult = hResult.replace("%deleteClassMembers%", deleteclassmembers);
    hResult = hResult.replace("%nodes_include%", includes);
    includes
    
    cppTemplate = ""
    with open(CPP_TEMPLATE, 'r') as f:
        cppTemplate = f.read()
        
    cppResult = cppTemplate
    cppResult = cppResult.replace("%ClassName%", ClassName);
    cppResult = cppResult.replace("%CLASSNAME%", CLASSNAME);
    cppResult = cppResult.replace("%SuperClassName%", superclass);
    cppResult = cppResult.replace("%DoxygenConstructorParams%", doxygenparams);
    cppResult = cppResult.replace("%Params%", params_argument_list);
    cppResult = cppResult.replace("%ClassMembers%", classmember);
    cppResult = cppResult.replace("%ParamInit%", contr_init);
    cppResult = cppResult.replace("%deleteClassMembers%", deleteclassmembers);
    cppResult = cppResult.replace("%nodes_include%", includes);
    cppResult = cppResult.replace("%ChildrenVisitor%", childaccept);
    
    
    with open(OUTPUT_FOLDER + "/" + ClassName + ".h", 'w') as f:
        f.write(hResult)
    with open(OUTPUT_FOLDER + "/" + ClassName + ".cpp", 'w') as f:
        f.write(cppResult)
        
    className = ClassName[0].lower() + ClassName[1:]
    ##print "#include \"" + ClassName + ".h\""
    
    # # for printing out the abstract visitor
    #print " "*12 + "///"
    #print " "*12 + "/// @brief      Visit function of the visitor pattern."
    #print " "*12 + "/// @sa         http://en.wikipedia.org/wiki/Visitor_pattern"
    #print " "*12 + "/// @param " + className + "    The node to visit this visitor"
    #print " "*12 + "virtual void visit(astnodes::" + ClassName + " * " + className + ") = 0;"
    #print " "*12
    #print " "*12
    
    # # for printing out a print-out-visitor
    #print " "*12 + "///"
    #print " "*12 + "/// @brief      Visit function of the visitor pattern."
    #print " "*12 + "/// @sa         http://en.wikipedia.org/wiki/Visitor_pattern"
    #print " "*12 + "/// @param " + className + "    The node to visit this visitor"
    #print " "*12 + "virtual void visit(astnodes::" + ClassName + " * " + className + ");"
    #print " "*12
    #print " "*12
    
    print "void PrintAstVisitor::visit(astnodes::" + ClassName + " * " + className + ")"
    print "{"
    print " "*4 + "printAstName(\"" + ClassName + "\");"
    print "}"
    print ""
    print ""
    
    
    
def main():
    parsefile(CLASS_NAMES_FILE)
    
    
main()