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

      notify_observers(token);

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
    boost::regex grouping_regex(R"((\(|\)|\[|\]|\{|\}))");
    boost::regex metacharacter_regex(R"((\*|\+|\?|\||\\|\^|\$|\.))");
    boost::regex literal_regex(R"((\d|\w|\s))");

    if (boost::regex_match(value, grouping_regex))
      return lex::TokenType::GROUPING;

    else if (boost::regex_match(value, metacharacter_regex))
      return lex::TokenType::METACHARACTER;

    else if (boost::regex_match(value, literal_regex))
      return lex::TokenType::LITERAL;

    else
      throw std::runtime_error("Lexer: Could not determine token type");
  }

  /**
   * @brief Notify all observers that a token has been created
   *
   * @param[in] token Token that was created
   */
  void Lexer::notify_observers(std::shared_ptr<lex::Token> token) const
  {
    for (auto &observer : m_observers)
      observer->on_token(token);
  }
}