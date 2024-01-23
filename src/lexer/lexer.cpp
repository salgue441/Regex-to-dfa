#include <boost/regex.hpp>
#include "lexer.h"

namespace lexer
{
  /**
   * @brief Construct a new Lexer:: Lexer object
   *
   * @param[in] input The regex string to tokenize
   */
  Lexer::Lexer(const std::string &input)
      : m_input(input), m_logger(logger::Logger::get_logger()),
        m_token_factory(std::make_shared<lex::TokenFactory>())
  {
    m_logger->debug("Lexer: Tokenizing input: {}", m_input);
  }

  /**
   * @brief Tokenize the input string
   *
   * @return std::vector<std::shared_ptr<Token>> List of tokens
   */
  std::vector<std::shared_ptr<lex::Token>> Lexer::tokenize() const
  {
    std::vector<std::shared_ptr<lex::Token>> tokens;

    boost::regex pattern(R"((\(|\)|\[|\]|\{|\}|\*|\+|\?|\||\\|\^|\$|\.|\d|\w|\s))");

    boost::smatch matches;
    std::string::const_iterator start = m_input.begin();
    std::string::const_iterator end = m_input.end();

    while (boost::regex_search(start, end, matches, pattern))
    {
      std::string value = matches[0];
      std::size_t position = std::distance(m_input.begin(), matches[0].first);

      lex::TokenType type = determine_type(value);
      auto token = m_token_factory->create_token(type, value, position);

      tokens.emplace_back(token);
      start = matches[0].second;
    }

    return tokens;
  }

  /**
   * @brief Add an observer to be notified when a token is created
   *
   * @param[in] observer Observer to be notified
   */
  void Lexer::register_observer(
      std::shared_ptr<lex::TokenObserver> observer) noexcept
  {
    m_observers.emplace_back(observer);
    m_token_factory->register_observer(observer);
  }

  /**
   * @brief Determine the type of the token
   *
   * @param[in] value Value of the token
   * @return lex::TokenType Type of the token
   * @throw std::runtime_error If the token type cannot be determined
   */
  lex::TokenType Lexer::determine_type(const std::string &value) const
  {
    boost::regex grouping_regex(R"([\(\)\[\]\{\}])");
    boost::regex metacharacter_regex(R"([\\^$.*+?])");
    boost::regex literal_regex(R"(\d+|\w+|\s+)");
    boost::regex quantifier_regex(R"(\{\d*,?\d*\})");
    boost::regex character_class_regex(R"(\[[^\]]*\])");
    boost::regex boundary_regex(R"(\b)");
    boost::regex modifier_regex(R"(\\[ig])");
    boost::regex alternation_regex(R"(\|)");
    boost::regex escape_sequence_regex(R"(\\[dws])");

    if (boost::regex_match(value, grouping_regex))
      return lex::TokenType::GROUPING;

    else if (boost::regex_match(value, metacharacter_regex))
      return lex::TokenType::METACHARACTER;

    else if (boost::regex_match(value, literal_regex))
      return lex::TokenType::LITERAL;

    else if (boost::regex_match(value, quantifier_regex))
      return lex::TokenType::QUANTIFIER;

    else if (boost::regex_match(value, character_class_regex))
      return lex::TokenType::CHARACTER_CLASS;

    else if (boost::regex_match(value, boundary_regex))
      return lex::TokenType::BOUNDARY;

    else if (boost::regex_match(value, modifier_regex))
      return lex::TokenType::MODIFIER;

    else if (boost::regex_match(value, alternation_regex))
      return lex::TokenType::ALTERNATION;

    else if (boost::regex_match(value, escape_sequence_regex))
      return lex::TokenType::ESCAPE_SEQUENCE;

    else if (value == ".")
      return lex::TokenType::WILDCARD;

    else if (value == "$")
      return lex::TokenType::ANCHOR;

    else if (value == "")
      return lex::TokenType::END_OF_INPUT;

    else

      return lex::TokenType::INVALID;
  }
}