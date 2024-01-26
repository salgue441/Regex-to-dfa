#include <sstream>
#include <functional>
#include "ast_builder.h"

namespace ast
{
  /**
   * @brief Builds a new node and sets it as the root node
   *
   * @return AST_ptr The root node
   */
  AST_ptr ConcreteBuilder::build()
  {
    return std::move(m_root);
  }

  /**
   * @brief Resets the builder
   *
   */
  void ConcreteBuilder::reset()
  {
    m_root = nullptr;
  }

  /**
   * @brief Builds a new literal node
   *
   * @param[in] value The value of the literal
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::literal(const std::string &value)
  {
    m_root = std::make_unique<LiteralNode>(value);
    return *this;
  }

  /**
   * @brief Builds a new metacharacter node
   *
   * @param[in] character The character of the metacharacter
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::metacharacter(char character)
  {
    m_root = std::make_unique<MetacharacterNode>(character);
    return *this;
  }

  /**
   * @brief Builds a new character class node
   *
   * @param[in] value The value of the character class
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::character_class(const std::string &value)
  {
    m_root = std::make_unique<CharacterClassNode>(value);
    return *this;
  }

  /**
   * @brief Builds a new grouping node
   *
   * @param[in] node The node to group
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::grouping(AST_ptr &&node)
  {
    std::vector<std::unique_ptr<ASTNode>> children;

    children.push_back(std::move(node));
    m_root = std::make_unique<GroupingNode>(std::move(children));

    return *this;
  }

  /**
   * @brief Builds a new quantifier node
   *
   * @param[in] node The node to quantify
   * @param[in] min The minimum number of times to match the node
   * @param[in] max The maximum number of times to match the node
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::quantifier(AST_ptr &&node, int min, int max)
  {
    m_root = std::make_unique<QuantifierNode>(std::move(node),
                                              min, max);
    return *this;
  }

  /**
   * @brief Builds a new anchor node
   *
   * @param[in] character The character of the anchor
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::anchor(char character)
  {
    m_root = std::make_unique<AnchorNode>(std::string(1, character));
    return *this;
  }

  /**
   * @brief Builds a new escape sequence node
   *
   * @param[in] character The character of the escape sequence
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::escape_sequence(char character)
  {
    m_root = std::make_unique<EscapeSequenceNode>(character);
    return *this;
  }

  /**
   * @brief Builds a new wildcard node
   *
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::wildcard()
  {
    m_root = std::make_unique<WildcardNode>();
    return *this;
  }

  /**
   * @brief Builds a new alternation node
   *
   * @param[in] left The left node of the alternation
   * @param[in] right The right node of the alternation
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::alternation(AST_ptr &&left, AST_ptr &&right)
  {
    std::vector<std::unique_ptr<ASTNode>> children;

    children.push_back(std::move(left));
    children.push_back(std::move(right));

    m_root = std::make_unique<AlternationNode>(std::move(children));
    return *this;
  }

  /**
   * @brief Builds a new boundary node
   *
   * @param[in] character The character of the boundary
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::boundary(char character)
  {
    m_root = std::make_unique<BoundaryNode>(std::string(1, character));
    return *this;
  }

  /**
   * @brief Builds a new modifier node
   *
   * @param[in] character The character of the modifier
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::modifier(char character)
  {
    m_root = std::make_unique<ModifierNode>(std::string(1, character));
    return *this;
  }

  /**
   * @brief Builds a new invalid node
   *
   * @param[in] character The character of the invalid node
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::invalid(char character)
  {
    m_root = std::make_unique<InvalidNode>(std::string(1, character));
    return *this;
  }

  /**
   * @brief Builds a new end of input node
   *
   * @return ASTBuilder& The builder
   */
  ASTBuilder &ConcreteBuilder::end_of_input()
  {
    m_root = std::make_unique<EndOfInputNode>();
    return *this;
  }

  /**
   * @brief Gets the children of the root node
   *
   * @return std::vector<ASTNode *> The children of the root node
   */
  std::vector<ASTNode *> ConcreteBuilder::get_children() const
  {
    std::vector<ASTNode *> children;

    if (m_root)
      collect_children(m_root.get(), children);

    return children;
  }

  /**
   * @brief Collects the children of a node
   *
   * @param[in] node The node to collect the children of
   * @param[out] children The children of the node
   */
  void ConcreteBuilder::collect_children(ASTNode *node,
                                         std::vector<ASTNode *> &children) const
  {
    children.emplace_back(node);

    for (auto &child : node->get_children())
      collect_children(child.get(), children);
  }

  /**
   * @brief Prints the AST
   *
   */
  std::string ConcreteBuilder::to_string() const
  {
    std::stringstream ss;
    std::function<void(ASTNode *, int)> print;

    print = [&ss, &print](ASTNode *node, int depth)
    {
      ss << std::string(depth, ' ') << node->to_string() << std::endl;

      for (auto &child : node->get_children())
        print(child.get(), depth + 1);
    };

    if (m_root)
      print(m_root.get(), 0);

    return ss.str();
  }

} // namespace ast