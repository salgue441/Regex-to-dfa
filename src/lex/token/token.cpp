#include <limits>
#include "token.h"

namespace lex
{
  /**
   * @brief Construct a new Regex Token:: Regex Token object
   *
   * @param[in] type     Type of the token
   * @param[in] value    Value of the token
   * @param[in] position Position of the token in the regex
   */
  RegexToken::RegexToken(TokenType type,
                         const std::string &value, std::size_t position)
      : m_type(type), m_value(value), m_position(position)
  {
    if (m_type < TokenType::LITERAL || m_type > TokenType::END_OF_INPUT)
      throw std::invalid_argument("Invalid TokenType");

    if (m_position < 0 || m_position > std::numeric_limits<std::size_t>::max())
      throw std::invalid_argument("Invalid position");
  }

  /**
   * @brief Converts the information stored in RegexToken to a string
   *        format
   *
   * @return std::string The string representation of the RegexToken
   */
  std::string RegexToken::to_string() const
  {
    return "Token Type: " + token_type_to_string() +
           ", Value: " + m_value +
           ", Position: " + std::to_string(m_position);
  }

  /**
   * @brief Converts the TokenType enum to a string format
   *
   * @return std::string The string representation of the TokenType
   * @throw std::runtime_error If the TokenType is invalid
   */
  std::string RegexToken::token_type_to_string() const
  {
    switch (m_type)
    {
    case TokenType::LITERAL:
      return "LITERAL";

    case TokenType::METACHARACTER:
      return "METACHARACTER";

    case TokenType::CHARACTER_CLASS:
      return "CHARACTER_CLASS";

    case TokenType::GROUPING:
      return "GROUPING";

    case TokenType::QUANTIFIER:
      return "QUANTIFIER";

    case TokenType::ANCHOR:
      return "ANCHOR";

    case TokenType::ESCAPE_SEQUENCE:
      return "ESCAPE_SEQUENCE";

    case TokenType::WILDCARD:
      return "WILDCARD";

    case TokenType::ALTERNATION:
      return "ALTERNATION";

    case TokenType::BOUNDARY:
      return "BOUNDARY";

    case TokenType::MODIFIER:
      return "MODIFIER";

    case TokenType::INVALID:
      return "INVALID";

    case TokenType::END_OF_INPUT:
      return "END_OF_INPUT";

    default:
      throw std::runtime_error("Invalid token type");
    }
  }
}