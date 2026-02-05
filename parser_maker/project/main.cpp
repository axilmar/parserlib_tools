#include <iostream>
#include <sstream>
#include <fstream>
#include "extractor.hpp"


using namespace parserlib;
using namespace parser_maker;
using namespace extractor;


#ifndef NDEBUG
extern void run_tests();
#endif


static void show_help() {
    std::cout << "parser_maker version 1.0\n";
    std::cout << "------------------------\n";
    
    std::cout << "\n";
    std::cout << "Command line tool that creates 4 files: 'lexer.hpp', 'parser.hpp', 'lexer.cpp', 'parser.cpp', from an ebnf grammar file; the files contain the implementation of a lexer and a parser for the Parserlib library.\n";

    std::cout << "\n";
    std::cout << "Command line syntax:\n";
    std::cout << "    parser_maker <options> <grammar_file>\n";

    std::cout << "\n";
    std::cout << "Options:\n";

    std::cout << "    -out <folder>: optional folder to write the output files to; if not given, then the current folder will be used; it can be relative or absolute.\n";
    std::cout << "    -pre <prefix>: optional prefix for the output files; if no given, no prefix is added to the filenames.\n";
}


struct options {
    std::string destination_folder;
    std::string filename_prefix;
};


template <class DefaultT, class ResultT>
static bool get_option(int argc, const char* argv[], const std::string& name, const DefaultT &default_value, ResultT& result) {
    result = default_value;
    for (int i = 0; i < argc; ++i) {
        const char* arg = argv[i];
        if (name == arg) {
            if (i < argc - 1) {
                std::stringstream stream;
                stream << argv[i + 1];
                stream >> result;
                return true;
            }
            return false;
        }
    }
    return false;
}


template <class Elem, class Traits, class Alloc>
static void trim_end(std::basic_string<Elem, Traits, Alloc>& str) {
    while (str.size() > 0) {
        const auto ch = str.back();
        if (std::isspace(str.back()) || ch < ' ') {
            str.resize(str.size() - 1);
            continue;
        }
        break;
    }
}


static std::string load_file(const char* filename) {
    std::ifstream file(filename, std::ios::ate);
    file.exceptions(std::ios_base::badbit);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::string result;
    result.resize(size);
    file.read(result.data(), size);
    trim_end(result);
    return result;
}


static void print_error(const std::string& msg, const lexer::parse_context_type::iterator_type& begin, const lexer::parse_context_type::iterator_type& end) {
    std::cout << "ERROR: " << begin.get_text_position().to_string() << ": " << msg << ": " << std::string(begin, end) << std::endl;
}


int main(int argc, const char* argv[]) {
    try {
        //run_tests();
        //return 0;

        //show help
        if (argc == 1) {
            show_help();
        }

        //get options
        options opts;
        get_option(argc, argv, "-out", "./", opts.destination_folder);
        get_option(argc, argv, "-pre", "", opts.filename_prefix);

        //get the file
        std::string source = load_file(argv[argc - 1]);

        //tokenize the file
        lexer::parse_context_type lexer_pc(source);
        const bool lexer_ok = lexer::tokenize(lexer_pc);
        for (const auto& lexer_error : lexer_pc.get_errors()) {
            print_error(lexer::get_lexer_error_string(lexer_error.get_id()), lexer_error.begin(), lexer_error.end());
        }
        assert(lexer_ok);

        //parse the tokens
        parser::parse_context_type parser_pc = lexer_pc.derive_parse_context<parser::AST_ID, parser::ERROR_ID>();
        const bool parser_ok = parser::parse(parser_pc);
        for (const auto& parser_error : parser_pc.get_errors()) {
            print_error(parser::get_parser_error_string(parser_error.get_id()), parser_error.begin()->begin(), std::prev(parser_error.end())->end());
        }
        assert(parser_ok);

        //extract the content
        LANGUAGE lang;
        extract(parser_pc, lang);
    }

    catch (const std::exception& ex) {
        std::cout << "ERROR: " << ex.what() << '\n';
        return -1;
    }

    return 0;
}
