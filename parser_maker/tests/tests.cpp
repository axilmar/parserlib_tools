#include <cassert>
#include <iostream>
#include "parser.hpp"


using namespace parserlib;
using namespace parser_maker;


static void do_test_ebnf_standard() {
    static const std::string source =
    R"(
        TERMINAL1 = "terminal1";
        tERMINAL2 = "terminal2";
        TERMINAL3 = 'terminal3';

        term1 = (factor1 | factor2 | factor3)
              | [factor1 | factor2 | factor3]
              | {factor1 | factor2 | factor3}
              | terminal1
              | terminal2
              | terminal3
              ;

        factor1 = term1?
                | term2*
                | term3+
                | term4 - term5
                ;

        factor2 = term1?
                | term2*
                | term3+
                | term4 - term5
                ;

        factor3 = term1?
                | term2*
                | term3+
                | term4 - term5
                ;

        sequence1 = factor1, factor2, factor3;
        sequence2 = factor1, factor2, factor3;
        sequence3 = factor1, factor2, factor3;

        rule1 = sequence1
              | sequence2
              | sequence3
              ;

        rule2 = sequence1
              | sequence2
              | sequence3
              ;

        rule3 = sequence1
              | sequence2
              | sequence3
              ;

        digit = '0' .. '9';
    )";

    lexer::parse_context_type lexer_pc(source);
    const bool lexer_ok = tokenize(lexer_pc);
    assert(lexer_ok);

    parser::parse_context_type parser_pc(lexer_pc.get_matches());
    const bool parser_ok = parse(parser_pc);
    assert(parser_ok);

    //parserlib::to_string(std::cout, parser_pc.get_matches());
}


static void do_test_ebnf_style_1() {
    static const std::string source =
    R"(
        TERMINAL1:
            "terminal1"

        tERMINAL2:
            "terminal2"

        TERMINAL:
            'terminal3'

        term1:
            factor1
            [factor1 | factor2 | factor3]
            {factor1 | factor2 | factor3}
            terminal11
            terminal2
            terminal3

        factor1:
            term1?
            term2*
            term3+
            term4 - term5

        factor2:
            term1?
            term2*
            term3+
            term4 - term5
            ;

        fact-or3:
            term1?
            term2*
            term3+
            term4 - term5

        sequence1:
            factor1 factor2 factor3

        sequence2:
            factor1 factor2 factor3

        sequence3:
            factor1 factor2 factor3

        rule1:
            sequence1
            sequence2
            sequence3

        rule2:
            sequence1
            sequence2
            sequence3

        rule3:
            sequence1
            sequence2
            sequence3


        digit:
            '0' .. '9'
    )";

    lexer::parse_context_type lexer_pc(source);
    const bool lexer_ok = tokenize(lexer_pc);
    assert(lexer_ok);

    parser::parse_context_type parser_pc(lexer_pc.get_matches());
    const bool parser_ok = parse(parser_pc);
    assert(parser_ok);

    //parserlib::to_string(std::cout, parser_pc.get_matches());
}


static void do_test_ebnf_gold_parser_builder() {
    static const std::string source =
    R"(
        TERMINAL1 = "terminal1";
        tERMINAL2 = "terminal2";
        TERMINAL3 = 'terminal3';

        <term1> ::= (factor1 | factor2 | factor3)
              | [factor1 | factor2 | factor3]
              | {factor1 | factor2 | factor3}
              | terminal1
              | terminal2
              | terminal3
              ;

        <factor1> ::= <term1>?
                  | <term2>*
                  | <term3>+
                  | <term4> - <term5>
                  ;

        <factor2> ::= <term1>?
                  | <term2>*
                  | <term3>+
                  | <term4> - <term5>
                  ;

        <factor3> ::= <term1>?
                  | <term2>*
                  | <term3>+
                  | <term4> - <term5>
                  ;

        <sequence1> ::= <factor1> <factor2> <factor3>;
        <sequence2> ::= <factor1> <factor2> <factor3>;
        <sequence3> ::= <factor1> <factor2> <factor3>;

        <rule1> ::= <sequence1>
                | <sequence2>
                | <sequence3>;

        <rule2> ::= <sequence1>
                | <sequence2>
                | <sequence3>;

        <rule3> ::= <sequence1>
                |   <sequence2>
                |   <sequence3>;

        <digit> ::= '0' .. '9';
    )";

    lexer::parse_context_type lexer_pc(source);
    const bool lexer_ok = tokenize(lexer_pc);
    assert(lexer_ok);

    parser::parse_context_type parser_pc(lexer_pc.get_matches());
    const bool parser_ok = parse(parser_pc);
    assert(parser_ok);

    //parserlib::to_string(std::cout, parser_pc.get_matches());
}


void run_tests() {
    do_test_ebnf_standard();
    do_test_ebnf_style_1();
    do_test_ebnf_gold_parser_builder();
}
