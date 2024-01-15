#include "lexer.h"

namespace lexer
{
  /**
   * @brief Construct a new Lexer:: Lexer object
   *
   * @param[in] input The input string to analyze
   */
  Lexer::Lexer(const std::string_view &input) : m_input(input)
  {
    m_token_grammar %= (qi::lit(m_patterns[TokenType::CHARACTER]) |
                        qi::lit(m_patterns[TokenType::CONCATENATION]) |
                        qi::lit(m_patterns[TokenType::ALTERNATION]) |
                        qi::lit(m_patterns[TokenType::KLEENE_STAR]) |
                        qi::lit(m_patterns[TokenType::LEFT_PARENTHESIS]) |
                        qi::lit(m_patterns[TokenType::RIGHT_PARENTHESIS]) |
                        qi::lit(m_patterns[TokenType::LEFT_BRACKET]) |
                        qi::lit(m_patterns[TokenType::RIGHT_BRACKET]) |
                        qi::lit(m_patterns[TokenType::LEFT_BRACE]) |
                        qi::lit(m_patterns[TokenType::RIGHT_BRACE]) |
                        qi::lit(m_patterns[TokenType::LEFT_ANGLE_BRACKET]) |
                        qi::lit(m_patterns[TokenType::RIGHT_ANGLE_BRACKET]) |
                        qi::lit(m_patterns[TokenType::END_OF_FILE]));

    spdlog::set_level(spdlog::level::debug);
  }

  /**
   * @brief Analyzes the input string and returns a vector of tokens
   *
   * @return std::vector<Token> The vector of tokens
   * @throw LexerException If an invalid token is found
   * @throw std::exception If an exception is thrown by the parser
   */
  std::vector<Token> Lexer::analyze()
  {
    std::vector<Token> tokens;
    std::string::iterator first = m_input.begin();
    std::string::iterator last = m_input.end();

    try
    {
      while (first != last)
      {
        std::string token_value;

        if (qi::parse(first, last, m_token_grammar, token_value))
        {
          std::size_t position = std::distance(m_input.begin(),
                                               first - token_value.size());

          tokens.emplace_back(TokenType::CHARACTER, token_value, position);
        }

        else
        {
          auto position = std::distance(m_input.begin(), first);
          throw LexerException("Invalid token at", position);
        }
      }

      tokens.emplace_back(TokenType::END_OF_FILE, "", m_input.size());
    }
    catch (const LexerException &e)
    {
      spdlog::error("Lexer Error: {}", e.what());
      throw;
    }
    catch (const std::exception &e)
    {
      spdlog::error("Exception: {}", e.what());
      throw;
    }

    log_debug("Lexer finished analyzing");
    return tokens;
  }

  /**
   * @brief Prints the message using the logger
   *
   * @param[in] message The message to print
   */
  void Lexer::log_debug(const std::string &message)
  {
    spdlog::debug("Lexer Debug: {}", message);
  }
}
