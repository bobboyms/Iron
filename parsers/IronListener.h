
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

  virtual void enterMulDiv(IronParser::MulDivContext *ctx) = 0;
  virtual void exitMulDiv(IronParser::MulDivContext *ctx) = 0;

  virtual void enterAddSub(IronParser::AddSubContext *ctx) = 0;
  virtual void exitAddSub(IronParser::AddSubContext *ctx) = 0;

  virtual void enterParens(IronParser::ParensContext *ctx) = 0;
  virtual void exitParens(IronParser::ParensContext *ctx) = 0;

  virtual void enterInt(IronParser::IntContext *ctx) = 0;
  virtual void exitInt(IronParser::IntContext *ctx) = 0;


};

