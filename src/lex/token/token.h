#pragma once

#include <string>
#include <cstdint>
#include <memory>

namespace lex
{
  class Token
  {
  public:
    virtual ~Token() = default;
    virtual std::string to_string() const = 0;
  };

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
