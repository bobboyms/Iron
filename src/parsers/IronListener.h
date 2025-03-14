
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "IronParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by IronParser.
 */
class  IronListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(IronParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(IronParser::ProgramContext *ctx) = 0;

  virtual void enterImportStatement(IronParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(IronParser::ImportStatementContext *ctx) = 0;

  virtual void enterQualifiedName(IronParser::QualifiedNameContext *ctx) = 0;
  virtual void exitQualifiedName(IronParser::QualifiedNameContext *ctx) = 0;

  virtual void enterStatementList(IronParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(IronParser::StatementListContext *ctx) = 0;

  virtual void enterBreakStatement(IronParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(IronParser::BreakStatementContext *ctx) = 0;

  virtual void enterContinueStatement(IronParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(IronParser::ContinueStatementContext *ctx) = 0;

  virtual void enterStructStatement(IronParser::StructStatementContext *ctx) = 0;
  virtual void exitStructStatement(IronParser::StructStatementContext *ctx) = 0;

  virtual void enterStructBody(IronParser::StructBodyContext *ctx) = 0;
  virtual void exitStructBody(IronParser::StructBodyContext *ctx) = 0;

  virtual void enterOptionsStatement(IronParser::OptionsStatementContext *ctx) = 0;
  virtual void exitOptionsStatement(IronParser::OptionsStatementContext *ctx) = 0;

  virtual void enterOptionsBody(IronParser::OptionsBodyContext *ctx) = 0;
  virtual void exitOptionsBody(IronParser::OptionsBodyContext *ctx) = 0;

  virtual void enterReturnStatement(IronParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(IronParser::ReturnStatementContext *ctx) = 0;

  virtual void enterWhileStatement(IronParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(IronParser::WhileStatementContext *ctx) = 0;

  virtual void enterRepeatStatement(IronParser::RepeatStatementContext *ctx) = 0;
  virtual void exitRepeatStatement(IronParser::RepeatStatementContext *ctx) = 0;

  virtual void enterForStatement(IronParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(IronParser::ForStatementContext *ctx) = 0;

  virtual void enterIntervals(IronParser::IntervalsContext *ctx) = 0;
  virtual void exitIntervals(IronParser::IntervalsContext *ctx) = 0;

  virtual void enterFormatStatement(IronParser::FormatStatementContext *ctx) = 0;
  virtual void exitFormatStatement(IronParser::FormatStatementContext *ctx) = 0;

  virtual void enterFormatArguments(IronParser::FormatArgumentsContext *ctx) = 0;
  virtual void exitFormatArguments(IronParser::FormatArgumentsContext *ctx) = 0;

  virtual void enterFormatArgument(IronParser::FormatArgumentContext *ctx) = 0;
  virtual void exitFormatArgument(IronParser::FormatArgumentContext *ctx) = 0;

  virtual void enterExternBlock(IronParser::ExternBlockContext *ctx) = 0;
  virtual void exitExternBlock(IronParser::ExternBlockContext *ctx) = 0;

  virtual void enterExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx) = 0;
  virtual void exitExternFunctionDeclaration(IronParser::ExternFunctionDeclarationContext *ctx) = 0;

  virtual void enterExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx) = 0;
  virtual void exitExternFunctionArgs(IronParser::ExternFunctionArgsContext *ctx) = 0;

  virtual void enterExternFunctionArg(IronParser::ExternFunctionArgContext *ctx) = 0;
  virtual void exitExternFunctionArg(IronParser::ExternFunctionArgContext *ctx) = 0;

  virtual void enterCTypes(IronParser::CTypesContext *ctx) = 0;
  virtual void exitCTypes(IronParser::CTypesContext *ctx) = 0;

  virtual void enterFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx) = 0;
  virtual void exitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx) = 0;

  virtual void enterFunctionSignature(IronParser::FunctionSignatureContext *ctx) = 0;
  virtual void exitFunctionSignature(IronParser::FunctionSignatureContext *ctx) = 0;

  virtual void enterFunctionReturnType(IronParser::FunctionReturnTypeContext *ctx) = 0;
  virtual void exitFunctionReturnType(IronParser::FunctionReturnTypeContext *ctx) = 0;

  virtual void enterFunctionArgs(IronParser::FunctionArgsContext *ctx) = 0;
  virtual void exitFunctionArgs(IronParser::FunctionArgsContext *ctx) = 0;

  virtual void enterFunctionArg(IronParser::FunctionArgContext *ctx) = 0;
  virtual void exitFunctionArg(IronParser::FunctionArgContext *ctx) = 0;

  virtual void enterFnsignature(IronParser::FnsignatureContext *ctx) = 0;
  virtual void exitFnsignature(IronParser::FnsignatureContext *ctx) = 0;

  virtual void enterFunctionCall(IronParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(IronParser::FunctionCallContext *ctx) = 0;

  virtual void enterFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx) = 0;
  virtual void exitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx) = 0;

  virtual void enterFunctionCallArg(IronParser::FunctionCallArgContext *ctx) = 0;
  virtual void exitFunctionCallArg(IronParser::FunctionCallArgContext *ctx) = 0;

  virtual void enterVarDeclaration(IronParser::VarDeclarationContext *ctx) = 0;
  virtual void exitVarDeclaration(IronParser::VarDeclarationContext *ctx) = 0;

  virtual void enterAssignment(IronParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(IronParser::AssignmentContext *ctx) = 0;

  virtual void enterStructInit(IronParser::StructInitContext *ctx) = 0;
  virtual void exitStructInit(IronParser::StructInitContext *ctx) = 0;

  virtual void enterStructInitBody(IronParser::StructInitBodyContext *ctx) = 0;
  virtual void exitStructInitBody(IronParser::StructInitBodyContext *ctx) = 0;

  virtual void enterVariableQualifiedName(IronParser::VariableQualifiedNameContext *ctx) = 0;
  virtual void exitVariableQualifiedName(IronParser::VariableQualifiedNameContext *ctx) = 0;

  virtual void enterVarAssignment(IronParser::VarAssignmentContext *ctx) = 0;
  virtual void exitVarAssignment(IronParser::VarAssignmentContext *ctx) = 0;

  virtual void enterIfBlock(IronParser::IfBlockContext *ctx) = 0;
  virtual void exitIfBlock(IronParser::IfBlockContext *ctx) = 0;

  virtual void enterIfStatement(IronParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(IronParser::IfStatementContext *ctx) = 0;

  virtual void enterElseStatement(IronParser::ElseStatementContext *ctx) = 0;
  virtual void exitElseStatement(IronParser::ElseStatementContext *ctx) = 0;

  virtual void enterBoolExpr(IronParser::BoolExprContext *ctx) = 0;
  virtual void exitBoolExpr(IronParser::BoolExprContext *ctx) = 0;

  virtual void enterExpr(IronParser::ExprContext *ctx) = 0;
  virtual void exitExpr(IronParser::ExprContext *ctx) = 0;

  virtual void enterNumber(IronParser::NumberContext *ctx) = 0;
  virtual void exitNumber(IronParser::NumberContext *ctx) = 0;

  virtual void enterDataFormat(IronParser::DataFormatContext *ctx) = 0;
  virtual void exitDataFormat(IronParser::DataFormatContext *ctx) = 0;

  virtual void enterVarTypes(IronParser::VarTypesContext *ctx) = 0;
  virtual void exitVarTypes(IronParser::VarTypesContext *ctx) = 0;


};

