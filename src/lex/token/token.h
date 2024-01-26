#pragma once

#include <string>
#include <cstdint>
#include <memory>

namespace lex
{
  /**
   * @brief The TokenType enum represents the different types of tokens
   *        that can be created
   *
   * @details Each type categorizes elements in a regex pattern:
   *       - LITERAL: Represents a literal character (e.g., "a" in "abc").
   *       - METACHARACTER: Represents special characters (e.g., "." in "a.b").
   *       - CHARACTER_CLASS: Represents a set of characters (e.g., "[0-9]" in
   *                          "[0-9]abc").
   *       - GROUPING: Represents grouped subpatterns (e.g., 
   *                   "(abc)" in "(abc)+").
   *       - QUANTIFIER: Represents occurrences of the preceding element
   *                     (e.g., "a{2,4}" in "aaabc").
   *       - ANCHOR: Represents a position in the input
   *                 (e.g., "^start" in "^start.*").
   *       - ESCAPE_SEQUENCE: Represents an escaped character
   *                          (e.g., "\." in "\.abc").
   *       - WILDCARD: Represents a wildcard character (e.g., "a.b"
   *                   matches "a1b").
   *       - ALTERNATION: Represents a choice between subpatterns
   *                      (e.g., "cat|dog" matches "cat" or "dog").
   *       - BOUNDARY: Represents a boundary between characters
   *                   (e.g., "word\b" matches "word" but not "wording").
   *       - MODIFIER: Represents a modifier affecting regex behavior
   *                   (e.g., "(?i)" for case insensitivity).
   *       - INVALID: Represents an unrecognized token.
   *       - END_OF_INPUT: Represents the end of the input string.
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
   * @class Token
   * @brief Interface for classes that represent tokens
   *
   */
  class Token
  {
  public:
    virtual ~Token() = default;
    virtual std::string to_string() const = 0;

    // Getters
    [[nodiscard]] virtual std::string get_value() const noexcept = 0;
    [[nodiscard]] virtual std::size_t get_position() const noexcept = 0;
    [[nodiscard]] virtual TokenType get_type() const noexcept = 0;
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

    [[nodiscard]] std::string get_value() const noexcept override;
    [[nodiscard]] std::size_t get_position() const noexcept override;
    [[nodiscard]] TokenType get_type() const noexcept override;

  private:
    TokenType m_type;
    std::string m_value;
    std::size_t m_position;

    // Helper functions
    std::string token_type_to_string() const;
  };
} // namespace lex
