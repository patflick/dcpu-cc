#include <iostream>
#include <fstream>

#include <Compiler.h>

int main(int argc, char **argv) {
    if ( argc < 2)
    {
        std::cerr << "Usage dtcc2 <filename>" << std::endl;
        return 1;
    }
    
    char * filename = argv[1];
    
    // read input file
    std::ifstream ifs (filename , std::ifstream::in);
    
    if (!ifs.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }
    
    Compiler cc;
    
    // compile code
    cc.compile(ifs);
    
    // check for errors (in that case exit with error code)
    if (cc.hasErrors())
    {
        cc.printErrors();
        exit(1);
    }
    
    // check for warnings and print them
    if (cc.hasWarnings())
    {
        cc.printErrors();
    }
    
    // output asm code to stdout
    std::cout << cc.getAssembler();
    
    return 0;
}
