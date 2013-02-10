#include <iostream>
#include <fstream>
#include <sstream>
#include <list>



typedef struct
{
    std::string define;
    std::string alias;
    std::string msg;
} ErrDef;


void generate_errors(std::istream& err_defs, std::ostream& out_hdr, std::ostream& out_src)
{
    std::list<ErrDef> errors;
    std::list<ErrDef> warnings;
    
    std::string line;
    while (std::getline(err_defs, line))
    {
        
        std::istringstream iss(line);
        ErrDef errdef;
        if (!(iss >> errdef.define >> std::ws >> errdef.alias >> std::ws)) { continue; } // error
        std::string errmsg( (std::istreambuf_iterator<char>( iss )),
                             (std::istreambuf_iterator<char>()) );
        
        errmsg.erase(errmsg.find(std::string("\"")), 1);
        errmsg.erase(errmsg.rfind(std::string("\"")));
        errdef.msg = errmsg;
        
        if (errdef.define.substr(0,4) == std::string("ERR_"))
            errors.push_back(errdef);
        else if (errdef.define.substr(0,5) == std::string("WARN_"))
            warnings.push_back(errdef);
    }
    
    /* output header file */
    
    out_hdr << "#ifndef __DCPUCC_ERRORS" << std::endl;
    out_hdr << "#define __DCPUCC_ERRORS" << std::endl;
    out_hdr << "#include \"derr.h\"" << std::endl;
    unsigned int error_count = 0;
    for (std::list<ErrDef>::iterator it = errors.begin(); it != errors.end(); ++it)
    {
        out_hdr << "#define " << it->define << " " << error_count++ << std::endl;
    }
    unsigned int warn_count = error_count;
    for (std::list<ErrDef>::iterator it = warnings.begin(); it != warnings.end(); ++it)
    {
        out_hdr << "#define " << it->define << " " << warn_count++ << std::endl;
    }
    out_hdr << "#define _WARN_OFFSET " << error_count << std::endl;
    out_hdr << "#define _ERR_COUNT " << warn_count << std::endl;
    out_hdr << "#define _WARN_COUNT (_ERR_COUNT - _WARN_OFFSET)" << std::endl;
    out_hdr << "extern const char* derrstr[" << warn_count << "];" << std::endl;
    out_hdr << "extern struct warnpolicy dwarnpolicy[" << warn_count-error_count << "];" << std::endl;
    out_hdr << "#endif" << std::endl;
    
    
    /* output source file */
    out_src << "#include \"derr.h\"" << std::endl;
    out_src << "const char* derrstr[" << warn_count << "] =" << std::endl;
    out_src << "{" << std::endl;
    for (std::list<ErrDef>::iterator it = errors.begin(); it != errors.end(); ++it)
    {
        out_src << "    \"" << it->msg << "\\n\","<< std::endl;
    }
    for (std::list<ErrDef>::iterator it = warnings.begin(); it != warnings.end(); ++it)
    {
        out_src << "    \"" << it->msg << "\\n\","<< std::endl;
    }
    out_src << "};" << std::endl;
    out_src << "struct warnpolicy dwarnpolicy[" << warn_count-error_count <<  "] =" << std::endl;
    out_src << "{" << std::endl;
    for (std::list<ErrDef>::iterator it = warnings.begin(); it != warnings.end(); ++it)
    {
        out_src << "    {" << it->define << ", \"" << it->alias << "\", 0, 0}, " << std::endl;
    }
    out_src << "};" << std::endl;
}


int main(int argc, char* argv[])
{
    // Check arguments.
    if (argc != 4)
    {
        std::cerr << "usage: " << argv[0] << " <input> <output-header> <output-source>" << std::endl;
        return 1;
    }
    
    // open input file
    std::ifstream ifs (argv[1], std::ifstream::in);
    if (!ifs.is_open())
    {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }
    
    // open both output files
    std::ofstream ofs_hdr (argv[2]);
    std::ofstream ofs_src (argv[3]);
    if (!ofs_hdr.is_open())
    {
        std::cerr << "Error opening file: " << argv[2] << std::endl;
        return 1;
    }
    if (!ofs_src.is_open())
    {
        std::cerr << "Error opening file: " << argv[3] << std::endl;
        return 1;
    }
    
    generate_errors(ifs, ofs_hdr, ofs_src);
    return 0;
}