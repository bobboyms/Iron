
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "IronListener.h"


/**
 * This class provides an empty implementation of IronListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  IronBaseListener : public IronListener {
public:

  virtual void enterProgram(IronParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(IronParser::ProgramContext * /*ctx*/) override { }

  virtual void enterImportStatement(IronParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(IronParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterQualifiedName(IronParser::QualifiedNameContext * /*ctx*/) override { }
  virtual void exitQualifiedName(IronParser::QualifiedNameContext * /*ctx*/) override { }

  virtual void enterStatementList(IronParser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(IronParser::StatementListContext * /*ctx*/) override { }

  virtual void enterBreakStatement(IronParser::BreakStatementContext * /*ctx*/) override { }
  virtual void exitBreakStatement(IronParser::BreakStatementContext * /*ctx*/) override { }

  virtual void enterContinueStatement(IronParser::ContinueStatementContext * /*ctx*/) override { }
  virtual void exitContinueStatement(IronParser::ContinueStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(IronParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(IronParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterWhileStatement(IronParser::WhileStatementContext * /*ctx*/) override { }
  virtual void exitWhileStatement(IronParser::WhileStatementContext * /*ctx*/) override { }

  virtual void enterRepeatStatement(IronParser::RepeatStatementContext * /*ctx*/) override { }
  virtual void exitRepeatStatement(IronParser::RepeatStatementContext * /*ctx*/) override { }

  virtual void enterForStatement(IronParser::ForStatementContext * /*ctx*/) override { }
  virtual void exitForStatement(IronParser::ForStatementContext * /*ctx*/) override { }

  virtual void enterIntervals(IronParser::IntervalsContext * /*ctx*/) override { }
  virtual void exitIntervals(IronParser::IntervalsContext * /*ctx*/) override { }

  virtual void enterFormatStatement(IronParser::FormatStatementContext * /*ctx*/) override { }
  virtual void exitFormatStatement(IronParser::FormatStatementContext * /*ctx*/) override { }

  virtual void enterFormatArguments(IronParser::FormatArgumentsContext * /*ctx*/) override { }
  virtual void exitFormatArguments(IronParser::FormatArgumentsContext * /*ctx*/) override { }

  virtual void enterFormatArgument(IronParser::FormatArgumentContext * /*ctx*/) override { }
  virtual void exitFormatArgument(IronParser::FormatArgumentContext * /*ctx*/) override { }

  virtual void enterExternBlock(IronParser::ExternBlockContext * /*ctx*/) override { }
  virtual void exitExternBlock(IronParser::ExternBlockContext * /*ctx*/) override { }

  virtual void enterExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterExternFunctionArgs(IronParser::ExternFunctionArgsContext * /*ctx*/) override { }
  virtual void exitExternFunctionArgs(IronParser::ExternFunctionArgsContext * /*ctx*/) override { }

  virtual void enterExternFunctionArg(IronParser::ExternFunctionArgContext * /*ctx*/) override { }
  virtual void exitExternFunctionArg(IronParser::ExternFunctionArgContext * /*ctx*/) override { }

  virtual void enterCTypes(IronParser::CTypesContext * /*ctx*/) override { }
  virtual void exitCTypes(IronParser::CTypesContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(IronParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(IronParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterArrowFunctionInline(IronParser::ArrowFunctionInlineContext * /*ctx*/) override { }
  virtual void exitArrowFunctionInline(IronParser::ArrowFunctionInlineContext * /*ctx*/) override { }

  virtual void enterFunctionSignature(IronParser::FunctionSignatureContext * /*ctx*/) override { }
  virtual void exitFunctionSignature(IronParser::FunctionSignatureContext * /*ctx*/) override { }

  virtual void enterFunctionReturnType(IronParser::FunctionReturnTypeContext * /*ctx*/) override { }
  virtual void exitFunctionReturnType(IronParser::FunctionReturnTypeContext * /*ctx*/) override { }

  virtual void enterFunctionArgs(IronParser::FunctionArgsContext * /*ctx*/) override { }
  virtual void exitFunctionArgs(IronParser::FunctionArgsContext * /*ctx*/) override { }

  virtual void enterFunctionArg(IronParser::FunctionArgContext * /*ctx*/) override { }
  virtual void exitFunctionArg(IronParser::FunctionArgContext * /*ctx*/) override { }

  virtual void enterFnsignature(IronParser::FnsignatureContext * /*ctx*/) override { }
  virtual void exitFnsignature(IronParser::FnsignatureContext * /*ctx*/) override { }

  virtual void enterFunctionCall(IronParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(IronParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterFunctionCallArgs(IronParser::FunctionCallArgsContext * /*ctx*/) override { }
  virtual void exitFunctionCallArgs(IronParser::FunctionCallArgsContext * /*ctx*/) override { }

  virtual void enterFunctionCallArg(IronParser::FunctionCallArgContext * /*ctx*/) override { }
  virtual void exitFunctionCallArg(IronParser::FunctionCallArgContext * /*ctx*/) override { }

  virtual void enterVarDeclaration(IronParser::VarDeclarationContext * /*ctx*/) override { }
  virtual void exitVarDeclaration(IronParser::VarDeclarationContext * /*ctx*/) override { }

  virtual void enterAssignment(IronParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(IronParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterVarAssignment(IronParser::VarAssignmentContext * /*ctx*/) override { }
  virtual void exitVarAssignment(IronParser::VarAssignmentContext * /*ctx*/) override { }

  virtual void enterIfBlock(IronParser::IfBlockContext * /*ctx*/) override { }
  virtual void exitIfBlock(IronParser::IfBlockContext * /*ctx*/) override { }

  virtual void enterIfStatement(IronParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(IronParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterElseStatement(IronParser::ElseStatementContext * /*ctx*/) override { }
  virtual void exitElseStatement(IronParser::ElseStatementContext * /*ctx*/) override { }

  virtual void enterBoolExpr(IronParser::BoolExprContext * /*ctx*/) override { }
  virtual void exitBoolExpr(IronParser::BoolExprContext * /*ctx*/) override { }

  virtual void enterExpr(IronParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(IronParser::ExprContext * /*ctx*/) override { }

  virtual void enterNumber(IronParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(IronParser::NumberContext * /*ctx*/) override { }

  virtual void enterDataFormat(IronParser::DataFormatContext * /*ctx*/) override { }
  virtual void exitDataFormat(IronParser::DataFormatContext * /*ctx*/) override { }

  virtual void enterVarTypes(IronParser::VarTypesContext * /*ctx*/) override { }
  virtual void exitVarTypes(IronParser::VarTypesContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

