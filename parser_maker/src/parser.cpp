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


    static const auto choice_operator
        = newline >> TOKEN_ID::CHOICE_OPERATOR
        | TOKEN_ID::CHOICE_OPERATOR >> newline
        | TOKEN_ID::CHOICE_OPERATOR
        | newline
        ;


    template <class IdentifierType>
    static rule_type alternation_for_identifier(const IdentifierType& identifier) {
        rule_type alternation;

        const parse_node_ptr_type term
            = TOKEN_ID::GROUP_START >> alternation >> TOKEN_ID::GROUP_END
            | (TOKEN_ID::OPTIONAL_START >> alternation >> TOKEN_ID::OPTIONAL_END)->*AST_ID::OPTIONAL
            | (TOKEN_ID::REPETITION_START >> alternation >> TOKEN_ID::REPETITION_END)->*AST_ID::LOOP_0
            | identifier
            | char_range
            | terminal(TOKEN_ID::TERMINAL)->*AST_ID::TERMINAL
            ;

        const parse_node_ptr_type factor
            = (terminal(TOKEN_ID::INTEGER) >> TOKEN_ID::MULTIPLICATION_OPERATOR >> term)->*AST_ID::LOOP_N_RIGHT
            | (term >> TOKEN_ID::MULTIPLICATION_OPERATOR >> TOKEN_ID::INTEGER)->*AST_ID::LOOP_N_LEFT
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


    static const auto terminator
        = TOKEN_ID::TERMINATOR >> newline
        | TOKEN_ID::TERMINATOR >> end
        | newline >> TOKEN_ID::TERMINATOR >> newline
        | newline >> newline
        | newline >> end
        | end
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


} //namespace parser_maker::parser
