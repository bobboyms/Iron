
// Generated from HightLavelIR.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "HightLavelIRParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by HightLavelIRParser.
 */
class  HightLavelIRListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(HightLavelIRParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(HightLavelIRParser::ProgramContext *ctx) = 0;

  virtual void enterImportStatement(HightLavelIRParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(HightLavelIRParser::ImportStatementContext *ctx) = 0;

  virtual void enterQualifiedName(HightLavelIRParser::QualifiedNameContext *ctx) = 0;
  virtual void exitQualifiedName(HightLavelIRParser::QualifiedNameContext *ctx) = 0;

  virtual void enterStatementList(HightLavelIRParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(HightLavelIRParser::StatementListContext *ctx) = 0;

  virtual void enterFunctionDeclaration(HightLavelIRParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(HightLavelIRParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterFunctionSignature(HightLavelIRParser::FunctionSignatureContext *ctx) = 0;
  virtual void exitFunctionSignature(HightLavelIRParser::FunctionSignatureContext *ctx) = 0;

  virtual void enterFunctionReturnType(HightLavelIRParser::FunctionReturnTypeContext *ctx) = 0;
  virtual void exitFunctionReturnType(HightLavelIRParser::FunctionReturnTypeContext *ctx) = 0;

  virtual void enterFunctionArgs(HightLavelIRParser::FunctionArgsContext *ctx) = 0;
  virtual void exitFunctionArgs(HightLavelIRParser::FunctionArgsContext *ctx) = 0;

  virtual void enterFunctionArg(HightLavelIRParser::FunctionArgContext *ctx) = 0;
  virtual void exitFunctionArg(HightLavelIRParser::FunctionArgContext *ctx) = 0;

  virtual void enterFunctionCall(HightLavelIRParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(HightLavelIRParser::FunctionCallContext *ctx) = 0;

  virtual void enterFunctionCallArgs(HightLavelIRParser::FunctionCallArgsContext *ctx) = 0;
  virtual void exitFunctionCallArgs(HightLavelIRParser::FunctionCallArgsContext *ctx) = 0;

  virtual void enterFunctionCallArg(HightLavelIRParser::FunctionCallArgContext *ctx) = 0;
  virtual void exitFunctionCallArg(HightLavelIRParser::FunctionCallArgContext *ctx) = 0;

  virtual void enterOp(HightLavelIRParser::OpContext *ctx) = 0;
  virtual void exitOp(HightLavelIRParser::OpContext *ctx) = 0;

  virtual void enterOpRight(HightLavelIRParser::OpRightContext *ctx) = 0;
  virtual void exitOpRight(HightLavelIRParser::OpRightContext *ctx) = 0;

  virtual void enterOpLeft(HightLavelIRParser::OpLeftContext *ctx) = 0;
  virtual void exitOpLeft(HightLavelIRParser::OpLeftContext *ctx) = 0;

  virtual void enterTypeRight(HightLavelIRParser::TypeRightContext *ctx) = 0;
  virtual void exitTypeRight(HightLavelIRParser::TypeRightContext *ctx) = 0;

  virtual void enterTypeLeft(HightLavelIRParser::TypeLeftContext *ctx) = 0;
  virtual void exitTypeLeft(HightLavelIRParser::TypeLeftContext *ctx) = 0;

  virtual void enterCast(HightLavelIRParser::CastContext *ctx) = 0;
  virtual void exitCast(HightLavelIRParser::CastContext *ctx) = 0;

  virtual void enterMath_op(HightLavelIRParser::Math_opContext *ctx) = 0;
  virtual void exitMath_op(HightLavelIRParser::Math_opContext *ctx) = 0;

  virtual void enterExpr(HightLavelIRParser::ExprContext *ctx) = 0;
  virtual void exitExpr(HightLavelIRParser::ExprContext *ctx) = 0;

  virtual void enterNumber(HightLavelIRParser::NumberContext *ctx) = 0;
  virtual void exitNumber(HightLavelIRParser::NumberContext *ctx) = 0;

  virtual void enterDataFormat(HightLavelIRParser::DataFormatContext *ctx) = 0;
  virtual void exitDataFormat(HightLavelIRParser::DataFormatContext *ctx) = 0;

  virtual void enterVarTypes(HightLavelIRParser::VarTypesContext *ctx) = 0;
  virtual void exitVarTypes(HightLavelIRParser::VarTypesContext *ctx) = 0;


};

