#ifndef PARSER_MAKER_LEXER_HPP
#define PARSER_MAKER_LEXER_HPP


#include "parserlib.hpp"


namespace parser_maker::lexer {


    using namespace parserlib;


    enum class TOKEN_ID {
        NEWLINE,
        IDENTIFIER,
        IDENTIFIER_LEXER,
        TERMINAL,
        INTEGER,
        ASSIGNMENT_OPERATOR,
        GROUP_START,
        GROUP_END,
        OPTIONAL_START,
        OPTIONAL_END,
        REPETITION_START,
        REPETITION_END,
        LOOP_0_OPERATOR,
        LOOP_1_OPERATOR,
        EXCLUSION_OPERATOR,
        MULTIPLICATION_OPERATOR = LOOP_0_OPERATOR,
        OPTIONAL_OPERATOR,
        LOGICAL_NOT_OPERATOR,
        LOGICAL_AND_OPERATOR,
        SEQUENCE_OPERATOR,
        CHOICE_OPERATOR,
        TERMINATOR,
        CHAR,
        RANGE_OPERATOR,
        SKIP_BEFORE,
        SKIP_AFTER,
        ERROR_SKIP_OPERATOR,
        ERROR,
        FALSE,
        TRUE,
        ANY,
        END
    };


    enum class ERROR_ID {
        INVALID_CHARACTERS
    };


    using parse_context_type = parse_context<parse_iterator<>, TOKEN_ID, ERROR_ID>;


    bool tokenize(parse_context_type& pc);


    std::string get_lexer_error_string(ERROR_ID id);


} //namespace parser_maker::lexer


namespace parserlib {
    template <> struct id_to_string<parser_maker::lexer::TOKEN_ID> {
        template <class Stream> static void exec(Stream& stream, parser_maker::lexer::TOKEN_ID id) {
            switch (id) {
                case parser_maker::lexer::TOKEN_ID::NEWLINE:
                    stream << "NEWLINE";
                    break;

                case parser_maker::lexer::TOKEN_ID::IDENTIFIER:
                    stream << "IDENTIFIER";
                    break;

                case parser_maker::lexer::TOKEN_ID::IDENTIFIER_LEXER:
                    stream << "IDENTIFIER_LEXER";
                    break;

                case parser_maker::lexer::TOKEN_ID::TERMINAL:
                    stream << "TERMINAL";
                    break;

                case parser_maker::lexer::TOKEN_ID::INTEGER:
                    stream << "INTEGER";
                    break;

                case parser_maker::lexer::TOKEN_ID::ASSIGNMENT_OPERATOR:
                    stream << "ASSIGNMENT_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::GROUP_START:
                    stream << "GROUP_START";
                    break;

                case parser_maker::lexer::TOKEN_ID::GROUP_END:
                    stream << "GROUP_END";
                    break;

                case parser_maker::lexer::TOKEN_ID::OPTIONAL_START:
                    stream << "OPTIONAL_START";
                    break;

                case parser_maker::lexer::TOKEN_ID::OPTIONAL_END:
                    stream << "OPTIONAL_END";
                    break;

                case parser_maker::lexer::TOKEN_ID::REPETITION_START:
                    stream << "REPETITION_START";
                    break;

                case parser_maker::lexer::TOKEN_ID::REPETITION_END:
                    stream << "REPETITION_END";
                    break;

                case parser_maker::lexer::TOKEN_ID::LOOP_0_OPERATOR:
                    stream << "LOOP_0_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::LOOP_1_OPERATOR:
                    stream << "LOOP_1_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::EXCLUSION_OPERATOR:
                    stream << "EXCLUSION_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::OPTIONAL_OPERATOR:
                    stream << "OPTIONAL_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::LOGICAL_NOT_OPERATOR:
                    stream << "LOGICAL_NOT_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::LOGICAL_AND_OPERATOR:
                    stream << "LOGICAL_AND_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::SEQUENCE_OPERATOR:
                    stream << "SEQUENCE_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::CHOICE_OPERATOR:
                    stream << "CHOICE_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::TERMINATOR:
                    stream << "TERMINATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::CHAR:
                    stream << "CHAR";
                    break;

                case parser_maker::lexer::TOKEN_ID::RANGE_OPERATOR:
                    stream << "RANGE_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::SKIP_BEFORE:
                    stream << "SKIP_BEFORE";
                    break;

                case parser_maker::lexer::TOKEN_ID::SKIP_AFTER:
                    stream << "SKIP_AFTER";
                    break;

                case parser_maker::lexer::TOKEN_ID::ERROR_SKIP_OPERATOR:
                    stream << "ERROR_SKIP_OPERATOR";
                    break;

                case parser_maker::lexer::TOKEN_ID::ERROR:
                    stream << "ERROR";
                    break;

                case parser_maker::lexer::TOKEN_ID::FALSE:
                    stream << "FALSE";
                    break;

                case parser_maker::lexer::TOKEN_ID::TRUE:
                    stream << "TRUE";
                    break;

                case parser_maker::lexer::TOKEN_ID::ANY:
                    stream << "ANY";
                    break;

                case parser_maker::lexer::TOKEN_ID::FALSE:
                    stream << "END";
                    break;
            }
        }
    };
}


#endif //PARSER_MAKER_LEXER_HPP
