#ifndef PARSER_MAKER_EXTRACTOR_HPP
#define PARSER_MAKER_EXTRACTOR_HPP


#include <set>
#include "parser.hpp"


namespace parser_maker::extractor {


    using ast_node = parserlib::ast_node<parser::AST_ID, typename parser::parse_context_type::iterator_type>;
    using ast_node_ptr = std::shared_ptr<ast_node>;


    using terminal_string_container = std::set<std::string>;


    struct RULE {
        std::string name;
        ast_node_ptr ast;
        bool is_recursive;
    };


    struct LANGUAGE_PART {
        std::vector<std::string> token_enum;
        std::vector<RULE> rules;
    };


    struct LANGUAGE_LEXER : LANGUAGE_PART {
        terminal_string_container terminal_strings;
    };


    struct LANGUAGE_PARSER : LANGUAGE_PART {
    };


    struct LANGUAGE {
        LANGUAGE_LEXER lexer;
        LANGUAGE_PARSER parser;
    };


    void extract(const parser::parse_context_type& pc, LANGUAGE& lang);


} //namespace parser_maker::extractor


#endif //PARSER_MAKER_EXTRACTOR_HPP
