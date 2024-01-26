#include <memory>
#include <vector>
#include <string>

#include "node/node.h"

namespace ast
{
  using AST_ptr = std::unique_ptr<ASTNode>;

  /**
   * @class ASTBuilder
   * @brief The ASTBuilder class is an interface for building an AST
   *
   */
  class ASTBuilder
  {
  public:
    virtual ~ASTBuilder() = default;

    virtual AST_ptr build() = 0;

    // Node builders
    virtual ASTBuilder &literal(const std::string &value) = 0;
    virtual ASTBuilder &metacharacter(char character) = 0;
    virtual ASTBuilder &character_class(const std::string &value) = 0;
    virtual ASTBuilder &grouping(AST_ptr &&node) = 0;
    virtual ASTBuilder &quantifier(AST_ptr &&node, int min, int max) = 0;
    virtual ASTBuilder &anchor(char character) = 0;
    virtual ASTBuilder &escape_sequence(char character) = 0;
    virtual ASTBuilder &wildcard() = 0;
    virtual ASTBuilder &alternation(AST_ptr &&left, AST_ptr &&right) = 0;
    virtual ASTBuilder &boundary(char character) = 0;
    virtual ASTBuilder &modifier(char character) = 0;
    virtual ASTBuilder &invalid(char character) = 0;
    virtual ASTBuilder &end_of_input() = 0;
  };

  /**
   * @class ConcreteBuilder
   * @brief The ConcreteBuilder class is an implementation of the ASTBuilder
   *        interface
   *
   */
  class ConcreteBuilder : public ASTBuilder
  {
  public:
    /**
     * @brief Construct a new Concrete Builder:: Concrete Builder object
     *
     */
    ConcreteBuilder() : m_root(nullptr) {}

    AST_ptr build() override;
    void reset();

    // Node builders
    ASTBuilder &literal(const std::string &value) override;
    ASTBuilder &metacharacter(char character) override;
    ASTBuilder &character_class(const std::string &value) override;
    ASTBuilder &grouping(AST_ptr &&node) override;
    ASTBuilder &quantifier(AST_ptr &&node, int min, int max) override;
    ASTBuilder &anchor(char character) override;
    ASTBuilder &escape_sequence(char character) override;
    ASTBuilder &wildcard() override;
    ASTBuilder &alternation(AST_ptr &&left, AST_ptr &&right) override;
    ASTBuilder &boundary(char character) override;
    ASTBuilder &modifier(char character) override;
    ASTBuilder &invalid(char character) override;
    ASTBuilder &end_of_input() override;

    // TODO: Add a print method
    std::vector<ASTNode *> get_children() const;
    std::string to_string() const;

  private:
    AST_ptr m_root;

    void collect_children(ASTNode *node,
                          std::vector<ASTNode *> &children) const;
  };
} // namespace ast