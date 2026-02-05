#include "extractor.hpp"


namespace parser_maker::extractor {


    static void extract_terminal_strings(const parser::parse_context_type::match_type& match, terminal_string_container& terminal_strings) {
        if (match.get_id() == parser::AST_ID::TERMINAL) {
            const std::string terminal{match.begin()->begin(), std::prev(match.end())->end()};
            terminal_strings.insert(terminal);
        }
        for (const auto& child_match : match.get_children()) {
            extract_terminal_strings(child_match, terminal_strings);
        }
    }


    static void extract_terminal_strings(const parser::parse_context_type& pc, terminal_string_container& terminal_strings) {
        for (const auto& match : pc.get_matches()) {
            if (match.get_id() == parser::AST_ID::RULE) {
                extract_terminal_strings(match, terminal_strings);
            }
        }
    }


    void extract(const parser::parse_context_type& pc, LANGUAGE& lang) {
        extract_terminal_strings(pc, lang.lexer.terminal_strings);
        //extract_rules(pc, lang.lexer.rules, lang.parser.rules);
    }


} //namespace parser_maker::extractor
