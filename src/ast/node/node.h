#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../lex/token/token.h"

namespace ast
{
  class AstVisitor;

  /**
   * @class AstNode
   * @brief Interface for all AST nodes.
   *
   */
  class AstNode
  {
  public:
    virtual ~AstNode() = default;
    virtual void accepts(AstVisitor &visitor) const = 0;
  };

  using AstNodePtr = std::unique_ptr<AstNode>;

  /**
   * @class LiteralNode
   * @brief Constructs nodes based off literal token types
   *
   */
  class LiteralNode : public AstNode
  {
  public:
    explicit LiteralNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::string m_value;
  };

  /**
   * @class MetacharacterNode
   * @brief Constructs nodes based off metacharacter token types
   *
   */
  class MetacharacterNode : public AstNode
  {
  public:
    explicit MetacharacterNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    lex::TokenType m_type;
  };

  /**
   * @class GroupNode
   * @brief Constructs nodes based off group token types
   *
   */
  class GroupNode : public AstNode
  {
  public:
    void add(AstNodePtr child);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::vector<AstNodePtr> m_children;
  };

  /**
   * @class QuantifierNode
   * @brief Constructs nodes based off quantifier token types
   *
   */
  class QuantifierNode : public AstNode
  {
  public:
    explicit QuantifierNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::string m_value;
  };

  /**
   * @class AnchorNode
   * @brief Constructs nodes based off anchor token types
   *
   */
  class AnchorNode : public AstNode
  {
  public:
    explicit AnchorNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::string m_value;
  };

  /**
   * @class EscapeSequenceNode
   * @brief Constructs nodes based off escape sequence token types
   *
   */
  class EscapeSequenceNode : public AstNode
  {
  public:
    explicit EscapeSequenceNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::string m_value;
  };

  /**
   * @class WildcardNode
   * @brief Constructs nodes based off wildcard token types
   *
   */
  class WildcardNode : public AstNode
  {
  public:
    explicit WildcardNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::string m_value;
  };

  /**
   * @class AlternationNode
   * @brief Constructs nodes based off alternation token types
   *
   */
  class AlternationNode : public AstNode
  {
  public:
    void add(AstNodePtr child);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::vector<AstNodePtr> m_children;
  };

  /**
   * @class BoundaryNode
   * @brief Constructs nodes based off boundary token types
   *
   */
  class BoundaryNode : public AstNode
  {
  public:
    explicit BoundaryNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::string m_value;
  };

  /**
   * @class ModifierNode
   * @brief Constructs nodes based off modifier token types
   *
   */
  class ModifierNode : public AstNode
  {
  public:
    explicit ModifierNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::string m_value;
  };

  /**
   * @class InvalidNode
   * @brief Constructs nodes based off invalid token types
   *
   */
  class InvalidNode : public AstNode
  {
  public:
    explicit InvalidNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::string m_value;
  };

  /**
   * @class EndOfInputNode
   * @brief Constructs nodes based off end of input token types
   *
   */
  class EndOfInputNode : public AstNode
  {
  public:
    explicit EndOfInputNode(const std::string &value);
    void accepts(AstVisitor &visitor) const override;

  private:
    std::string m_value;
  };

} // namespace ast