#pragma once

namespace ast
{
  /**
   * @class AstVisitor
   * @brief Interface for visitor interaction
   *
   */
  class AstVisitor
  {
  public:
    virtual ~AstVisitor() = default;

    virtual void visit_literal_node(const class LiteralNode &node) const = 0;
    virtual void visit_metacharacter_node(
        const class MetacharacterNode &node) const = 0;

    virtual void visit_group_node(const class GroupNode &node) const = 0;
    virtual void visit_sequence_node(const class SequenceNode &node) const = 0;
    virtual void visit_eof_node(const class EndOfInputNode &node) const = 0;
  };
} // namespace ast