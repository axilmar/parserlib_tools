#include <stdexcept>
#include "lexer.hpp"


namespace parser_maker::lexer {


    static const auto newline
        = parserlib::newline('\n')->*TOKEN_ID::NEWLINE
        ;


    static const auto comment = 
        "(*" >> *((newline | any) - "*)") >> "*)"
        ;


    static const auto whitespace_character
        = range('\0', ' ')
        ;


    static const auto whitespace
        = whitespace_character
        | comment
        ;


    static const auto digit
        = range('0', '9')
        ;


    static const auto capital_letter
        = range('A', 'Z')
        ;


    static const auto identifier_body_lexer
        = (capital_letter | '_') >> *(capital_letter | digit | '_' | '-')
        ;


    static const auto identifier_lexer
        = terminal('<') >> identifier_body_lexer >> terminal('>')
        | identifier_body_lexer
        ;


    static const auto letter
        = range('a', 'z')
        | capital_letter
        ;


    static const auto identifier_body
        = (letter | '_') >> *(letter | digit | '_' | '-')
        ;


    static const auto identifier
        = terminal('<') >> identifier_body >> terminal('>')
        | identifier_body
        ;


    static const auto character 
        = terminal("\\\\")
        | terminal("\\\"")
        | terminal("\\\'")
        | terminal("\\n")
        | terminal("\\r")
        | terminal("\\0")
        | any
        ;


    static const auto char_
        = '\'' >> character >> '\''
        ;


    static const auto terminal_
        = '"' >> *(character - '"') >> '"'
        | '\'' >> *(character - '\'') >> '\''
        ;


    static const auto integer
        = +digit
        ;


    static const auto token
        = identifier_lexer->*TOKEN_ID::IDENTIFIER_LEXER
        | identifier->*TOKEN_ID::IDENTIFIER
        | char_->*TOKEN_ID::CHAR
        | terminal_->*TOKEN_ID::TERMINAL
        | integer->*TOKEN_ID::INTEGER
        | terminal("::=")->*TOKEN_ID::ASSIGNMENT_OPERATOR
        | terminal(":=")->*TOKEN_ID::ASSIGNMENT_OPERATOR
        | terminal("..")->*TOKEN_ID::RANGE_OPERATOR
        | terminal("->")->*TOKEN_ID::ERROR_SKIP_OPERATOR
        | terminal('=')->*TOKEN_ID::ASSIGNMENT_OPERATOR
        | terminal(':')->*TOKEN_ID::ASSIGNMENT_OPERATOR
        | terminal('(')->*TOKEN_ID::GROUP_START
        | terminal(')')->*TOKEN_ID::GROUP_END
        | terminal('[')->*TOKEN_ID::OPTIONAL_START
        | terminal(']')->*TOKEN_ID::OPTIONAL_END
        | terminal('{')->*TOKEN_ID::REPETITION_START
        | terminal('}')->*TOKEN_ID::REPETITION_END
        | terminal('*')->*TOKEN_ID::LOOP_0_OPERATOR
        | terminal('+')->*TOKEN_ID::LOOP_1_OPERATOR
        | terminal('-')->*TOKEN_ID::EXCLUSION_OPERATOR
        | terminal('?')->*TOKEN_ID::OPTIONAL_OPERATOR
        | terminal('!')->*TOKEN_ID::LOGICAL_NOT_OPERATOR
        | terminal('&')->*TOKEN_ID::LOGICAL_AND_OPERATOR
        | terminal(',')->*TOKEN_ID::SEQUENCE_OPERATOR
        | terminal('|')->*TOKEN_ID::CHOICE_OPERATOR
        | terminal(';')->*TOKEN_ID::TERMINATOR
        | terminal('.')->*TOKEN_ID::TERMINATOR
        | terminal("$BEFORE")->*TOKEN_ID::SKIP_BEFORE
        | terminal("$AFTER")->*TOKEN_ID::SKIP_AFTER
        | terminal("$ERROR")->*TOKEN_ID::ERROR
        | terminal("$FALSE")->*TOKEN_ID::FALSE
        | terminal("$TRUE")->*TOKEN_ID::TRUE
        | terminal("$ANY")->*TOKEN_ID::ANY
        | terminal("$END")->*TOKEN_ID::END
        ;


    static const auto element
        = newline
        | whitespace
        | token
        ;


    static const auto element_or_error
        = element
        | error(ERROR_ID::INVALID_CHARACTERS, skip_before(element))
        ;


    static const auto grammar
        = *element_or_error >> end
        ;


    bool tokenize(parse_context_type& pc) {
        return grammar.parse(pc);
    }


    std::string get_lexer_error_string(ERROR_ID id) {
        switch (id) {
            case ERROR_ID::INVALID_CHARACTERS:
                return "invalid characters";
        }

        throw std::logic_error("parser_maker::lexer::get_lexer_error_string: invalid error id");
    }


} //namespace parser_maker::lexer
