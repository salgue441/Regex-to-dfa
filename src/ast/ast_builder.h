#pragma once

#include "node/node.h"

namespace ast
{
  /**
   * @class AstBuilder
   * @brief Interface for classes that build AST nodes
   *
   */
  class AstBuilder
  {
  public:
    virtual ~AstBuilder() = default;

    virtual void build_literal_node(const std::string &value) = 0;
    virtual void build_metacharacter_node(lex::TokenType type) = 0;
    virtual void build_character_class_node(const std::string &value) = 0;
    virtual void build_group_node(const std::string &value) = 0;
    virtual void build_quantifier_node(const std::string &value) = 0;
    virtual void build_anchor_node(lex::TokenType type) = 0;
    virtual void build_escape_sequence_node(const std::string &value) = 0;
    virtual void build_wildcard_node() = 0;
    virtual void build_alternation_node() = 0;
    virtual void build_boundary_node(lex::TokenType type) = 0;
    virtual void build_modifier_node(const std::string &value) = 0;
    virtual void build_invalid_node(const std::string &value) = 0;
    virtual void build_end_of_input_node() = 0;

    virtual AstNodePtr get_result() = 0;
  };

  /**
   * @class ConcreteAstBuilder
   * @brief Builds AST nodes
   *
   */
  class ConcreteAstBuilder : public AstBuilder
  {
  public:
    void build_literal_node(const std::string &value) override;
    void build_metacharacter_node(lex::TokenType type) override;
    void build_character_class_node(const std::string &value) override;
    void build_group_node(const std::string &value) override;
    void build_quantifier_node(const std::string &value) override;
    void build_anchor_node(lex::TokenType type) override;
    void build_escape_sequence_node(const std::string &value) override;
    void build_wildcard_node() override;
    void build_alternation_node() override;
    void build_boundary_node(lex::TokenType type) override;
    void build_modifier_node(const std::string &value) override;
    void build_invalid_node(const std::string &value) override;
    void build_end_of_input_node() override;

    AstNodePtr get_result() override;

  private:
    AstNodePtr m_result;
  };
} // namespace ast