#ifndef PARSER_MAKER_PARSER_HPP
#define PARSER_MAKER_PARSER_HPP


#include "lexer.hpp"


namespace parser_maker::parser {


    enum class AST_ID {
        RULE,
        RULE_LEXER,
        CHOICE,
        SEQUENCE,
        LOOP_N_LEFT,
        LOOP_N_RIGHT,
        EXCLUSION,
        OPTIONAL,
        LOOP_0,
        LOOP_1,
        TERMINAL,
        IDENTIFIER,
        IDENTIFIER_LEXER,
        CHAR,
        CHAR_RANGE,
        LOGICAL_AND,
        LOGICAL_NOT,
        FALSE,
        TRUE,
        ANY,
        END
    };


    enum class ERROR_ID {
        SYNTAX_ERROR
    };


    using parse_context_type = lexer::parse_context_type::derived_parse_context_type<AST_ID, ERROR_ID>;


    bool parse(parse_context_type& pc);


    std::string get_parser_error_string(ERROR_ID id);


} //namespace parser_maker::parser


namespace parserlib {
    template <> struct id_to_string<parser_maker::parser::AST_ID> {
        template <class Stream> static void exec(Stream& stream, parser_maker::parser::AST_ID id) {
            switch (id) {
                case parser_maker::parser::AST_ID::RULE:
                    stream << "RULE";
                    break;

                case parser_maker::parser::AST_ID::RULE_LEXER:
                    stream << "RULE_LEXER";
                    break;

                case parser_maker::parser::AST_ID::CHOICE:
                    stream << "CHOICE";
                    break;

                case parser_maker::parser::AST_ID::SEQUENCE:
                    stream << "SEQUENCE";
                    break;

                case parser_maker::parser::AST_ID::LOOP_N_LEFT:
                    stream << "LOOP_N_LEFT";
                    break;

                case parser_maker::parser::AST_ID::LOOP_N_RIGHT:
                    stream << "LOOP_N_RIGHT";
                    break;

                case parser_maker::parser::AST_ID::EXCLUSION:
                    stream << "EXCLUSION";
                    break;

                case parser_maker::parser::AST_ID::OPTIONAL:
                    stream << "OPTIONAL";
                    break;

                case parser_maker::parser::AST_ID::LOOP_0:
                    stream << "LOOP_0";
                    break;

                case parser_maker::parser::AST_ID::LOOP_1:
                    stream << "LOOP_1";
                    break;

                case parser_maker::parser::AST_ID::TERMINAL:
                    stream << "TERMINAL";
                    break;

                case parser_maker::parser::AST_ID::IDENTIFIER:
                    stream << "IDENTIFIER";
                    break;

                case parser_maker::parser::AST_ID::IDENTIFIER_LEXER:
                    stream << "IDENTIFIER_LEXER";
                    break;

                case parser_maker::parser::AST_ID::CHAR:
                    stream << "CHAR";
                    break;

                case parser_maker::parser::AST_ID::CHAR_RANGE:
                    stream << "CHAR_RANGE";
                    break;

                case parser_maker::parser::AST_ID::LOGICAL_AND:
                    stream << "LOGICAL_AND";
                    break;

                case parser_maker::parser::AST_ID::LOGICAL_NOT:
                    stream << "LOGICAL_NOT";
                    break;

                case parser_maker::parser::AST_ID::FALSE:
                    stream << "FALSE";
                    break;

                case parser_maker::parser::AST_ID::TRUE:
                    stream << "TRUE";
                    break;

                case parser_maker::parser::AST_ID::ANY:
                    stream << "ANY";
                    break;

                case parser_maker::parser::AST_ID::END:
                    stream << "END";
                    break;
            }
        }
    };
}


#endif //PARSER_MAKER_PARSER_HPP
