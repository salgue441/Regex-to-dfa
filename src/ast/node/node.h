#include <cstdint>
#include <memory>
#include <vector>

#include "../visitors/ast_visitor.h"

namespace ast
{
  class ASTNode
  {
  public:
    virtual ~ASTNode() = default;

    virtual std::vector<std::unique_ptr<ASTNode>> &get_children() = 0;
    virtual void add_child(std::unique_ptr<ASTNode> child) = 0;
    virtual void accept(AstVisitor &visitor) = 0;
    virtual std::string to_string() const = 0;
  };

  /**
   * @class AlternationNode
   * @brief The AlternationNode class represents an alternation in a regex
   *        expression
   *b
   */
  class LiteralNode : public ASTNode
  {
  public:
    std::string value;

    /**
     * @brief Construct a new Literal Node:: Literal Node object
     *
     * @param[in] value The value of the literal
     */
    explicit LiteralNode(const std::string &value) : value(value) {}

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details Literals cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Adds a child to the node
     *
     * @param[in] child The child to add
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_literal_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return value;
    }
  };

  /**
   * @class MetacharacterNode
   * @brief The MetacharacterNode class represents a metacharacter in a regex
   *        expression
   *
   */
  class MetacharacterNode : public ASTNode
  {
  public:
    char character;

    /**
     * @brief Construct a new Metacharacter Node:: Metacharacter Node object
     *
     * @param[in] character The character of the metacharacter
     */
    explicit MetacharacterNode(char character) : character(character) {}

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details Metacharacters cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_metacharacter_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return std::string(1, character);
    }
  };

  /**
   * @class CharacterClassNode
   * @brief The CharacterClassNode class represents a character class in a regex
   *        expression
   *
   */
  class CharacterClassNode : public ASTNode
  {
  public:
    std::string value;

    /**
     * @brief Construct a new Character Class Node:: Character Class Node object
     *
     * @param[in] value The value of the character class
     */
    explicit CharacterClassNode(const std::string &value) : value(value) {}

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details Character classes cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_character_class_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return value;
    }
  };

  /**
   * @class GroupingNode
   * @brief The GroupingNode class represents a grouping in a regex expression
   *
   */
  class GroupingNode : public ASTNode
  {
  public:
    std::vector<std::unique_ptr<ASTNode>> children;

    /**
     * @brief Construct a new Grouping Node:: Grouping Node object
     *
     * @param[in] children The children of the grouping
     */
    explicit GroupingNode(std::vector<std::unique_ptr<ASTNode>> children)
        : children(std::move(children))
    {
    }

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      return children;
    }

    /**
     * @brief Adds a child to the node
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> child) override
    {
      children.push_back(std::move(child));
    }

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_grouping_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      std::string result = "(";

      for (const auto &child : children)
        result += child->to_string();

      result += ")";

      return result;
    }
  };

  /**
   * @class QuantifierNode
   * @brief The QuantifierNode class represents a quantifier in a regex
   *        expression
   *
   */
  class QuantifierNode : public ASTNode
  {
  public:
    std::unique_ptr<ASTNode> child;
    std::uint8_t min_occurrences;
    std::uint8_t max_occurrences;

    /**
     * @brief Construct a new Quantifier Node:: Quantifier Node object
     *
     * @param[in] child The child of the quantifier
     * @param[in] min_occurrences The minimum number of occurrences
     * @param[in] max_occurrences The maximum number of occurrences
     */
    QuantifierNode(std::unique_ptr<ASTNode> child, std::uint8_t min_occurrences,
                   std::uint8_t max_occurrences)
        : child(std::move(child)), min_occurrences(min_occurrences),
          max_occurrences(max_occurrences)
    {
    }

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_quantifier_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      std::string result = child->to_string();

      if (min_occurrences == 0 && max_occurrences == 1)
        result += "?";

      else if (min_occurrences == 0 && max_occurrences == 255)
        result += "*";

      else if (min_occurrences == 1 && max_occurrences == 255)
        result += "+";

      else if (min_occurrences == max_occurrences)
        result += "{" + std::to_string(min_occurrences) + "}";

      else
        result += "{" + std::to_string(min_occurrences) + "," +
                  std::to_string(max_occurrences) + "}";

      return result;
    }
  };

  /**
   * @class AnchorNode
   * @brief The AnchorNode class represents an anchor in a regex expression
   *
   */
  class AnchorNode : public ASTNode
  {
  public:
    std::string value;

    /**
     * @brief Construct a new Anchor Node:: Anchor Node object
     *
     * @param[in] value The value of the anchor
     */
    explicit AnchorNode(const std::string &value) : value(value) {}

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details Anchors cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_anchor_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return value;
    }
  };

  /**
   * @class EscapeSequenceNode
   * @brief The EscapeSequenceNode class represents an escape sequence in a
   *        regex expression
   *
   */
  class EscapeSequenceNode : public ASTNode
  {
  public:
    char character;

    /**
     * @brief Construct a new Escape Sequence Node:: Escape Sequence Node object
     *
     * @param[in] character The character of the escape sequence
     */
    explicit EscapeSequenceNode(char character) : character(character) {}

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details Escape sequences cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_escape_sequence_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return std::string(1, character);
    }
  };

  /**
   * @class WildcardNode
   * @brief The WildcardNode class represents a wildcard in a regex expression
   *
   */
  class WildcardNode : public ASTNode
  {
  public:
    /**
     * @brief Construct a new Wildcard Node:: Wildcard Node object
     *
     */
    explicit WildcardNode() {}

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details Wildcards cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_wildcard_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return ".";
    }
  };

  /**
   * @class AlternationNode
   * @brief The AlternationNode class represents an alternation in a regex
   *        expression
   *
   */
  class AlternationNode : public ASTNode
  {
  public:
    std::vector<std::unique_ptr<ASTNode>> children;

    /**
     * @brief Construct a new Alternation Node:: Alternation Node object
     *
     * @param[in] children The children of the alternation
     */
    explicit AlternationNode(std::vector<std::unique_ptr<ASTNode>> children)
        : children(std::move(children)) {}

    /**
     * @brief Gets the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      return children;
    }

    /**
     * @brief Adds a child to the node
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> child) override
    {
      children.push_back(std::move(child));
    }

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_alternation_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      std::string result = "(";

      for (const auto &child : children)
        result += child->to_string() + "|";

      result.pop_back();
      result += ")";

      return result;
    }
  };

  /**
   * @class BoundaryNode
   * @brief The BoundaryNode class represents a boundary in a regex expression
   *
   */
  class BoundaryNode : public ASTNode
  {
  public:
    std::string value;

    /**
     * @brief Construct a new Boundary Node:: Boundary Node object
     *
     * @param[in] value The value of the boundary
     */
    explicit BoundaryNode(const std::string &value) : value(value) {}

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details Boundaries cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_boundary_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return value;
    }
  };

  /**
   * @class ModifierNode
   * @brief The ModifierNode class represents a modifier in a regex expression
   *
   */
  class ModifierNode : public ASTNode
  {
  public:
    std::string value;

    /**
     * @brief Construct a new Modifier Node:: Modifier Node object
     *
     * @param[in] value The value of the modifier
     */
    explicit ModifierNode(const std::string &value) : value(value) {}

    /**
     * @brief Returns the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details Modifiers cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_modifier_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return value;
    }
  };

  /**
   * @class InvalidNode
   * @brief The InvalidNode class represents an invalid token in a regex
   *        expression
   *
   */
  class InvalidNode : public ASTNode
  {
  public:
    std::string value;

    /**
     * @brief Construct a new Invalid Node:: Invalid Node object
     *
     * @param[in] value The value of the invalid token
     */
    explicit InvalidNode(const std::string &value) : value(value) {}

    /**
     * @brief Gets the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details Invalid tokens cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_invalid_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return value;
    }
  };

  /**
   * @class EndOfInputNode
   * @brief The EndOfInputNode class represents the end of the input string in
   *        a regex expression
   *
   */
  class EndOfInputNode : public ASTNode
  {
  public:
    /**
     * @brief Construct a new End Of Input Node:: End Of Input Node object
     *
     */
    explicit EndOfInputNode() {}

    /**
     * @brief Gets the children of the node
     *
     * @return std::vector<std::unique_ptr<ASTNode>>& The children of the node
     */
    std::vector<std::unique_ptr<ASTNode>> &get_children() override
    {
      static std::vector<std::unique_ptr<ASTNode>> empty;
      return empty;
    }

    /**
     * @brief Adds a child to the node
     * @details End of input nodes cannot have children
     *
     * @param[in] child The child to add
     */
    void add_child(std::unique_ptr<ASTNode> /* child */) override {}

    /**
     * @brief Accepts a visitor
     *
     * @param[in] visitor The visitor to accept
     */
    void accept(AstVisitor &visitor) override
    {
      visitor.visit_end_of_input_node(*this);
    }

    /**
     * @brief Returns the string representation of the node
     *
     * @return std::string The string representation of the node
     */
    std::string to_string() const override
    {
      return "$";
    }
  };
} // namespace ast