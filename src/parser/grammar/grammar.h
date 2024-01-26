#pragma once

#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include "../../ast/ast_builder.h"

namespace parser
{
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;
  namespace phoenix = boost::phoenix;

  /**
   * @brief Defines the grammar for the parser.
   *
   * @tparam Iterator The iterator type.
   *
   */
  template <typename Iterator>
  struct RegexGrammar : qi::grammar<Iterator, ast::AST_ptr(), ascii::space_type>
  {
    /**
     * @brief Construct a new Regex Grammar:: Regex Grammar object
     *
     */
    RegexGrammar() : RegexGrammar::base_type(start)
    {
      using qi::_1;
      using qi::_val;
      using qi::char_;
      using qi::lit;

      start = term >> *(lit('|') >> term);
      term = factor >> *(factor);
      factor = primary >> *(lit('*') | lit('+') |
                            lit('?') | lit('{') >> qi::int_ >> lit(',') >> qi::int_ >> lit('}'));

      primary = literal | metacharacter |
                character_class | grouping |
                anchor | wildcard | end_of_input;

      literal = char_("a-zA-Z0-9");
    }

    qi::rule<Iterator, ast::AST_ptr(), ascii::space_type> start;
    qi::rule<Iterator, ast::AST_ptr(), ascii::space_type> term;
    qi::rule<Iterator, ast::AST_ptr(), ascii::space_type> factor;
    qi::rule<Iterator, ast::AST_ptr(), ascii::space_type> primary;
    qi::rule<Iterator, ast::AST_ptr(), ascii::space_type> literal;
  };
} // namespace parser