
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

  virtual void enterEntryPoint(IronParser::EntryPointContext *ctx) = 0;
  virtual void exitEntryPoint(IronParser::EntryPointContext *ctx) = 0;

  virtual void enterBody(IronParser::BodyContext *ctx) = 0;
  virtual void exitBody(IronParser::BodyContext *ctx) = 0;

  virtual void enterFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterStatement(IronParser::StatementContext *ctx) = 0;
  virtual void exitStatement(IronParser::StatementContext *ctx) = 0;

  virtual void enterVarDeclaration(IronParser::VarDeclarationContext *ctx) = 0;
  virtual void exitVarDeclaration(IronParser::VarDeclarationContext *ctx) = 0;

  virtual void enterDataFormat(IronParser::DataFormatContext *ctx) = 0;
  virtual void exitDataFormat(IronParser::DataFormatContext *ctx) = 0;

  virtual void enterVarTypes(IronParser::VarTypesContext *ctx) = 0;
  virtual void exitVarTypes(IronParser::VarTypesContext *ctx) = 0;


};

