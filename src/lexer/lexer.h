#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <map>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include "spdlog/spdlog.h"

namespace qi = boost::spirit::qi;

namespace lexer
{
  /**
   * @enum TokenType
   * @brief Enumerates the different types of tokens that can be found
   *        in a regular expression
   *
   */
  enum class TokenType
  {
    CHARACTER,
    CONCATENATION,
    ALTERNATION,
    KLEENE_STAR,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_ANGLE_BRACKET,
    RIGHT_ANGLE_BRACKET,
    END_OF_FILE,
    INVALID
  };

  /**
   * @struct Token
   * @brief Represents a token in a regular expression
   *
   */
  struct Token
  {
    TokenType m_type;
    std::string m_value;
    std::size_t m_position;

    // Constructor
    /**
     * @brief Construct a new Token:: Token object
     *
     * @param[in] type The type of the token
     * @param[in] value The value of the token
     * @param[in] position The position of the token
     */
    explicit Token(TokenType type, std::string value, std::size_t position)
        : m_type(type), m_value(value), m_position(position) {}
  };

  // Classes
  /**
   * @class LexerException
   * @brief Provides an exception for the lexer
   */
  class LexerException : public std::exception
  {
  public:
    /**
     * @brief Construct a new LexerException:: LexerException object
     *
     * @param[in] message The message to be displayed
     */
    explicit LexerException(const std::string &message) : m_message(message)
    {
      spdlog::error("LexerException: {}", message);
    }

    /**
     * @brief Construct a new LexerException:: LexerException object
     *
     */
    explicit LexerException(const std::string &message, std::size_t position)
        : m_message(message)
    {
      spdlog::error("LexerException: {} at position {}",
                    message, position);
    }

    /**
     * @brief Returns the message
     *
     * @return const char* The message to be displayed
     */
    inline const char *what() const noexcept override
    {
      return m_message.c_str();
    }

  private:
    std::string m_message;
  };

  /**
   * @class Lexer
   * @brief Defines the lexer for the regular expression parser
   */
  class Lexer
  {
  public:
    Lexer(const std::string_view &input);
    std::vector<Token> analyze();

  private:
    std::string m_input;
    std::map<TokenType, std::string> m_patterns;
    qi::rule<std::string::iterator, std::string()> m_token_grammar;

    // Helper functions
    void log_debug(const std::string &message);
  };

} //! namespace lexer