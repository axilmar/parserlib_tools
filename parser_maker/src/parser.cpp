#include <stdexcept>
#include "parser.hpp"


namespace parser_maker::parser {


    using namespace lexer;


    using rule_type = parserlib::rule<parse_context_type>;
    using parse_node_ptr_type = parserlib::parse_node_ptr<parse_context_type>;


    extern const rule_type alternation;


    static const auto newline
        = terminal(TOKEN_ID::NEWLINE)
        ;


    static const auto identifier_lexer
        = (terminal(TOKEN_ID::IDENTIFIER_LEXER))->*AST_ID::IDENTIFIER_LEXER
        ;


    static const auto identifier
        = (terminal(TOKEN_ID::IDENTIFIER))->*AST_ID::IDENTIFIER
        ;


    static const auto char_
        = terminal(TOKEN_ID::CHAR)->*AST_ID::CHAR
        ;


    static const auto char_range
        = (char_ >> TOKEN_ID::RANGE_OPERATOR >> char_)->*AST_ID::CHAR_RANGE
        ;


    static const auto terminal_
        = terminal(TOKEN_ID::TERMINAL)->*AST_ID::TERMINAL
        | terminal(TOKEN_ID::CHAR)->*AST_ID::TERMINAL
        ;


    static const auto choice_operator
        = newline >> TOKEN_ID::CHOICE_OPERATOR
        | TOKEN_ID::CHOICE_OPERATOR >> newline
        | TOKEN_ID::CHOICE_OPERATOR
        | newline
        ;


    static const auto terminator
        = TOKEN_ID::TERMINATOR >> newline
        | TOKEN_ID::TERMINATOR >> end
        | newline >> TOKEN_ID::TERMINATOR >> newline
        | debug(newline >> newline)
        | newline >> end
        | end
        ;


    //lexer has one possible identifier type (lexer identifier), parser has two (lexer identifier and identifier);
    //therefore, to avoid repetition, the main grammar is put into a function.
    template <class IdentifierType>
    static rule_type alternation_for_identifier(const IdentifierType& identifier) {
        rule_type alternation;

        const auto group_term
            = TOKEN_ID::GROUP_START >> alternation >> TOKEN_ID::GROUP_END
            ;

        const auto skip_term
            = group_term
            | identifier
            | char_range
            | terminal_
            ;

        const auto skip_before
            = -terminal(TOKEN_ID::SKIP_BEFORE) >> skip_term
            ;

        const auto skip_after
            = TOKEN_ID::SKIP_AFTER >> skip_term
            ;

        const auto error_skip
            = skip_before
            | skip_after
            ;

        static const auto error_term =
            TOKEN_ID::ERROR >> identifier >> -(TOKEN_ID::ERROR_SKIP_OPERATOR >> error_skip)
            ;

        const parse_node_ptr_type term
            = group_term
            | (TOKEN_ID::OPTIONAL_START >> alternation >> TOKEN_ID::OPTIONAL_END)->*AST_ID::OPTIONAL
            | (TOKEN_ID::REPETITION_START >> alternation >> TOKEN_ID::REPETITION_END)->*AST_ID::LOOP_0
            | identifier
            | char_range
            | terminal_
            | error_term
            | terminal(TOKEN_ID::FALSE)->*AST_ID::FALSE
            | terminal(TOKEN_ID::TRUE)->*AST_ID::TRUE
            | terminal(TOKEN_ID::ANY)->*AST_ID::ANY
            | terminal(TOKEN_ID::END)->*AST_ID::END
            ;

        const parse_node_ptr_type factor
            = (TOKEN_ID::LOGICAL_AND_OPERATOR >> term)->*AST_ID::LOGICAL_AND
            | (TOKEN_ID::LOGICAL_NOT_OPERATOR >> term)->*AST_ID::LOGICAL_NOT
            | (terminal(TOKEN_ID::INTEGER) >> TOKEN_ID::MULTIPLICATION_OPERATOR >> term)->*AST_ID::LOOP_N_RIGHT
            | (term >> TOKEN_ID::MULTIPLICATION_OPERATOR >> terminal(TOKEN_ID::INTEGER))->*AST_ID::LOOP_N_LEFT
            | (term >> TOKEN_ID::EXCLUSION_OPERATOR >> term)->*AST_ID::EXCLUSION
            | (term >> TOKEN_ID::OPTIONAL_OPERATOR)->*AST_ID::OPTIONAL
            | (term >> TOKEN_ID::LOOP_0_OPERATOR)->*AST_ID::LOOP_0
            | (term >> TOKEN_ID::LOOP_1_OPERATOR)->*AST_ID::LOOP_1
            | term
            ;

        const parse_node_ptr_type concatenation
            = (factor >> +(-terminal(TOKEN_ID::SEQUENCE_OPERATOR) >> factor))->*AST_ID::SEQUENCE
            | factor
            ;

        alternation
            = (concatenation >> +(choice_operator >> concatenation))->*AST_ID::CHOICE
            | concatenation
            ;

        return alternation;
    }


    static const auto assignment_operator
        = TOKEN_ID::ASSIGNMENT_OPERATOR >> -newline
        ;


    static const parse_node_ptr_type rule_lexer
        = (identifier_lexer >> assignment_operator >> alternation_for_identifier(identifier_lexer) >> terminator)->*AST_ID::RULE_LEXER
        ;


    static const parse_node_ptr_type rule
        = (identifier >> assignment_operator >> alternation_for_identifier(identifier_lexer | identifier) >> terminator)->*AST_ID::RULE
        ;


    static const auto element
        = rule_lexer
        | rule
        | newline
        ;


    static const auto grammar 
        = *element >> end
        ;


    bool parse(parse_context_type& pc) {
        return grammar.parse(pc);
    }


    std::string get_parser_error_string(ERROR_ID id) {
        switch (id) {
            case ERROR_ID::SYNTAX_ERROR:
                return "syntax error";
        }

        throw std::logic_error("parser_maker::parser::get_parser_error_string: invalid error id");
    }


} //namespace parser_maker::parser
