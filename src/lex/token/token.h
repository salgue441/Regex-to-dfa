#pragma once

#include <string>
#include <cstdint>
#include <memory>

namespace lex
{
  /**
   * @class Token
   * @brief Interface for classes that represent tokens
   *
   */
  class Token
  {
  public:
    virtual ~Token() = default;
    virtual std::string to_string() const = 0;
  };

  /**
   * @brief The TokenType enum represents the different types of tokens
   *        that can be created
   *
   */
  enum class TokenType : std::uint8_t
  {
    LITERAL,
    METACHARACTER,
    CHARACTER_CLASS,
    GROUPING,
    QUANTIFIER,
    ANCHOR,
    ESCAPE_SEQUENCE,
    WILDCARD,
    ALTERNATION,
    BOUNDARY,
    MODIFIER,
    INVALID,
    END_OF_INPUT
  };

  /**
   * @class RegexToken
   * @brief The RegexToken class represents a token that was created by the
   *        lexer
   *
   */
  class RegexToken : public Token
  {
  public:
    explicit RegexToken(TokenType type,
                        const std::string &value, std::size_t position);

    std::string to_string() const override;

  private:
    TokenType m_type;
    std::string m_value;
    std::size_t m_position;

    // Helper functions
    std::string token_type_to_string() const;
  };
} // namespace lex
