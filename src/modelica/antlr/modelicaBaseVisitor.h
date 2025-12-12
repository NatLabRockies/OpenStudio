
// Generated from modelica.g4 by ANTLR 4.13.2

#pragma once

#include "antlr4-runtime.h"
#include "modelicaVisitor.h"

/**
 * This class provides an empty implementation of modelicaVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class modelicaBaseVisitor : public modelicaVisitor
{
 public:
  virtual std::any visitStored_definition(modelicaParser::Stored_definitionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWithin_statement(modelicaParser::Within_statementContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClass_definition(modelicaParser::Class_definitionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClass_specifier(modelicaParser::Class_specifierContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClass_prefixes(modelicaParser::Class_prefixesContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLong_class_specifier(modelicaParser::Long_class_specifierContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShort_class_specifier(modelicaParser::Short_class_specifierContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDer_class_specifier(modelicaParser::Der_class_specifierContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBase_prefix(modelicaParser::Base_prefixContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnum_list(modelicaParser::Enum_listContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumeration_literal(modelicaParser::Enumeration_literalContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComposition(modelicaParser::CompositionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLanguage_specification(modelicaParser::Language_specificationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExternal_function_call(modelicaParser::External_function_callContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement_list(modelicaParser::Element_listContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement(modelicaParser::ElementContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImport_clause(modelicaParser::Import_clauseContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImport_list(modelicaParser::Import_listContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExtends_clause(modelicaParser::Extends_clauseContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstraining_clause(modelicaParser::Constraining_clauseContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComponent_clause(modelicaParser::Component_clauseContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_prefix(modelicaParser::Type_prefixContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_specifier(modelicaParser::Type_specifierContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComponent_list(modelicaParser::Component_listContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComponent_declaration(modelicaParser::Component_declarationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition_attribute(modelicaParser::Condition_attributeContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(modelicaParser::DeclarationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModification(modelicaParser::ModificationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClass_modification(modelicaParser::Class_modificationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_list(modelicaParser::Argument_listContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(modelicaParser::ArgumentContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement_modification_or_replaceable(modelicaParser::Element_modification_or_replaceableContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement_modification(modelicaParser::Element_modificationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement_redeclaration(modelicaParser::Element_redeclarationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement_replaceable(modelicaParser::Element_replaceableContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComponent_clause1(modelicaParser::Component_clause1Context* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComponent_declaration1(modelicaParser::Component_declaration1Context* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShort_class_definition(modelicaParser::Short_class_definitionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEquation_section(modelicaParser::Equation_sectionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAlgorithm_section(modelicaParser::Algorithm_sectionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEquation(modelicaParser::EquationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(modelicaParser::StatementContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_equation(modelicaParser::If_equationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_statement(modelicaParser::If_statementContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_equation(modelicaParser::For_equationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_statement(modelicaParser::For_statementContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_indices(modelicaParser::For_indicesContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_index(modelicaParser::For_indexContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhile_statement(modelicaParser::While_statementContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhen_equation(modelicaParser::When_equationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhen_statement(modelicaParser::When_statementContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnect_clause(modelicaParser::Connect_clauseContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(modelicaParser::ExpressionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimple_expression(modelicaParser::Simple_expressionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogical_expression(modelicaParser::Logical_expressionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogical_term(modelicaParser::Logical_termContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogical_factor(modelicaParser::Logical_factorContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelation(modelicaParser::RelationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRel_op(modelicaParser::Rel_opContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArithmetic_expression(modelicaParser::Arithmetic_expressionContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdd_op(modelicaParser::Add_opContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTerm(modelicaParser::TermContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMul_op(modelicaParser::Mul_opContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFactor(modelicaParser::FactorContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary(modelicaParser::PrimaryContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitName(modelicaParser::NameContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComponent_reference(modelicaParser::Component_referenceContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_call_args(modelicaParser::Function_call_argsContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_arguments(modelicaParser::Function_argumentsContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_arguments(modelicaParser::Named_argumentsContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_argument(modelicaParser::Named_argumentContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_argument(modelicaParser::Function_argumentContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOutput_expression_list(modelicaParser::Output_expression_listContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression_list(modelicaParser::Expression_listContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray_subscripts(modelicaParser::Array_subscriptsContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubscript(modelicaParser::SubscriptContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComment(modelicaParser::CommentContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitString_comment(modelicaParser::String_commentContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModel_annotation(modelicaParser::Model_annotationContext* ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotation(modelicaParser::AnnotationContext* ctx) override {
    return visitChildren(ctx);
  }
};
