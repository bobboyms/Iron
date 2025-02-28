
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, LINE_COMMENT = 5, BLOCK_COMMENT = 6, 
    COMMA = 7, COLON = 8, EQ = 9, SEMICOLON = 10, DOT = 11, STAR = 12, L_CURLY = 13, 
    R_CURLY = 14, L_PAREN = 15, R_PAREN = 16, PLUS = 17, MINUS = 18, DIV = 19, 
    L_BRACKET = 20, R_BRACKET = 21, ARROW = 22, AND = 23, OR = 24, NOT = 25, 
    EQEQ = 26, NEQ = 27, LT = 28, LTE = 29, GT = 30, GTE = 31, IF = 32, 
    FUNCTION = 33, LET = 34, ELSE = 35, PUBLIC = 36, IMPORT = 37, RETURN = 38, 
    TYPE_INT = 39, TYPE_CHAR = 40, TYPE_FLOAT = 41, TYPE_STRING = 42, TYPE_BOOLEAN = 43, 
    TYPE_DOUBLE = 44, TYPE_VOID = 45, REAL_NUMBER = 46, INT_NUMBER = 47, 
    BOOLEAN_VALUE = 48, STRING_LITERAL = 49, IDENTIFIER = 50, NEWLINE = 51, 
    WS = 52
  };

  enum {
    RuleProgram = 0, RuleImportStatement = 1, RuleQualifiedName = 2, RuleStatementList = 3, 
    RuleReturnStatement = 4, RuleFormatStatement = 5, RuleFormatArguments = 6, 
    RuleFormatArgument = 7, RuleExternBlock = 8, RuleExternFunctionDeclaration = 9, 
    RuleExternFunctionArgs = 10, RuleExternFunctionArg = 11, RuleCTypes = 12, 
    RuleFunctionDeclaration = 13, RuleArrowFunctionInline = 14, RuleArrowFunctionBlock = 15, 
    RuleFunctionSignature = 16, RuleFunctionReturnType = 17, RuleFunctionArgs = 18, 
    RuleFunctionArg = 19, RuleFnsignature = 20, RuleFunctionCall = 21, RuleFunctionCallArgs = 22, 
    RuleFunctionCallArg = 23, RuleVarDeclaration = 24, RuleAssignment = 25, 
    RuleVarAssignment = 26, RuleIfBlock = 27, RuleIfStatement = 28, RuleElseStatement = 29, 
    RuleBoolExpr = 30, RulePrimary = 31, RuleExpr = 32, RuleNumber = 33, 
    RuleDataFormat = 34, RuleVarTypes = 35
  };

  explicit IronParser(antlr4::TokenStream *input);

  IronParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~IronParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class ImportStatementContext;
  class QualifiedNameContext;
  class StatementListContext;
  class ReturnStatementContext;
  class FormatStatementContext;
  class FormatArgumentsContext;
  class FormatArgumentContext;
  class ExternBlockContext;
  class ExternFunctionDeclarationContext;
  class ExternFunctionArgsContext;
  class ExternFunctionArgContext;
  class CTypesContext;
  class FunctionDeclarationContext;
  class ArrowFunctionInlineContext;
  class ArrowFunctionBlockContext;
  class FunctionSignatureContext;
  class FunctionReturnTypeContext;
  class FunctionArgsContext;
  class FunctionArgContext;
  class FnsignatureContext;
  class FunctionCallContext;
  class FunctionCallArgsContext;
  class FunctionCallArgContext;
  class VarDeclarationContext;
  class AssignmentContext;
  class VarAssignmentContext;
  class IfBlockContext;
  class IfStatementContext;
  class ElseStatementContext;
  class BoolExprContext;
  class PrimaryContext;
  class ExprContext;
  class NumberContext;
  class DataFormatContext;
  class VarTypesContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ImportStatementContext *> importStatement();
    ImportStatementContext* importStatement(size_t i);
    ExternBlockContext *externBlock();
    std::vector<FunctionDeclarationContext *> functionDeclaration();
    FunctionDeclarationContext* functionDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    QualifiedNameContext *qualifiedName();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *STAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportStatementContext* importStatement();

  class  QualifiedNameContext : public antlr4::ParserRuleContext {
  public:
    QualifiedNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QualifiedNameContext* qualifiedName();

  class  StatementListContext : public antlr4::ParserRuleContext {
  public:
    StatementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VarDeclarationContext *> varDeclaration();
    VarDeclarationContext* varDeclaration(size_t i);
    std::vector<VarAssignmentContext *> varAssignment();
    VarAssignmentContext* varAssignment(size_t i);
    std::vector<FunctionCallContext *> functionCall();
    FunctionCallContext* functionCall(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<IfStatementContext *> ifStatement();
    IfStatementContext* ifStatement(size_t i);
    std::vector<ReturnStatementContext *> returnStatement();
    ReturnStatementContext* returnStatement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementListContext* statementList();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    DataFormatContext *dataFormat();
    FunctionCallContext *functionCall();
    ExprContext *expr();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  FormatStatementContext : public antlr4::ParserRuleContext {
  public:
    FormatStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *R_PAREN();
    FormatArgumentsContext *formatArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormatStatementContext* formatStatement();

  class  FormatArgumentsContext : public antlr4::ParserRuleContext {
  public:
    FormatArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FormatArgumentContext *> formatArgument();
    FormatArgumentContext* formatArgument(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormatArgumentsContext* formatArguments();

  class  FormatArgumentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    FormatArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DataFormatContext *dataFormat();
    FunctionCallContext *functionCall();
    ExprContext *expr();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormatArgumentContext* formatArgument();

  class  ExternBlockContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *language = nullptr;
    ExternBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<ExternFunctionDeclarationContext *> externFunctionDeclaration();
    ExternFunctionDeclarationContext* externFunctionDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExternBlockContext* externBlock();

  class  ExternFunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *exterFunctionName = nullptr;
    antlr4::Token *varied = nullptr;
    ExternFunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ExternFunctionArgsContext *externFunctionArgs();
    antlr4::tree::TerminalNode *COMMA();
    FunctionReturnTypeContext *functionReturnType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExternFunctionDeclarationContext* externFunctionDeclaration();

  class  ExternFunctionArgsContext : public antlr4::ParserRuleContext {
  public:
    ExternFunctionArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExternFunctionArgContext *> externFunctionArg();
    ExternFunctionArgContext* externFunctionArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExternFunctionArgsContext* externFunctionArgs();

  class  ExternFunctionArgContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    antlr4::Token *ptr = nullptr;
    ExternFunctionArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    CTypesContext *cTypes();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExternFunctionArgContext* externFunctionArg();

  class  CTypesContext : public antlr4::ParserRuleContext {
  public:
    CTypesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE_BOOLEAN();
    antlr4::tree::TerminalNode *TYPE_CHAR();
    antlr4::tree::TerminalNode *TYPE_DOUBLE();
    antlr4::tree::TerminalNode *TYPE_FLOAT();
    antlr4::tree::TerminalNode *TYPE_INT();
    antlr4::tree::TerminalNode *TYPE_VOID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CTypesContext* cTypes();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *functionName = nullptr;
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    FunctionSignatureContext *functionSignature();
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *PUBLIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  ArrowFunctionInlineContext : public antlr4::ParserRuleContext {
  public:
    ArrowFunctionInlineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionSignatureContext *functionSignature();
    antlr4::tree::TerminalNode *ARROW();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrowFunctionInlineContext* arrowFunctionInline();

  class  ArrowFunctionBlockContext : public antlr4::ParserRuleContext {
  public:
    ArrowFunctionBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionSignatureContext *functionSignature();
    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrowFunctionBlockContext* arrowFunctionBlock();

  class  FunctionSignatureContext : public antlr4::ParserRuleContext {
  public:
    FunctionSignatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    FunctionArgsContext *functionArgs();
    FunctionReturnTypeContext *functionReturnType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionSignatureContext* functionSignature();

  class  FunctionReturnTypeContext : public antlr4::ParserRuleContext {
  public:
    FunctionReturnTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    VarTypesContext *varTypes();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionReturnTypeContext* functionReturnType();

  class  FunctionArgsContext : public antlr4::ParserRuleContext {
  public:
    FunctionArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FunctionArgContext *> functionArg();
    FunctionArgContext* functionArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionArgsContext* functionArgs();

  class  FunctionArgContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    FunctionArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *IDENTIFIER();
    FnsignatureContext *fnsignature();
    VarTypesContext *varTypes();
    AssignmentContext *assignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionArgContext* functionArg();

  class  FnsignatureContext : public antlr4::ParserRuleContext {
  public:
    FnsignatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    FunctionSignatureContext *functionSignature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FnsignatureContext* fnsignature();

  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *functionName = nullptr;
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *IDENTIFIER();
    FunctionCallArgsContext *functionCallArgs();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallContext* functionCall();

  class  FunctionCallArgsContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FunctionCallArgContext *> functionCallArg();
    FunctionCallArgContext* functionCallArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallArgsContext* functionCallArgs();

  class  FunctionCallArgContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    antlr4::Token *anotherVarName = nullptr;
    FunctionCallArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    DataFormatContext *dataFormat();
    FunctionCallContext *functionCall();
    ArrowFunctionInlineContext *arrowFunctionInline();
    ArrowFunctionBlockContext *arrowFunctionBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallArgContext* functionCallArg();

  class  VarDeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    VarDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *COLON();
    VarTypesContext *varTypes();
    antlr4::tree::TerminalNode *IDENTIFIER();
    AssignmentContext *assignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarDeclarationContext* varDeclaration();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQ();
    ArrowFunctionInlineContext *arrowFunctionInline();
    ArrowFunctionBlockContext *arrowFunctionBlock();
    DataFormatContext *dataFormat();
    FunctionCallContext *functionCall();
    ExprContext *expr();
    BoolExprContext *boolExpr();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssignmentContext* assignment();

  class  VarAssignmentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    VarAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ArrowFunctionInlineContext *arrowFunctionInline();
    ArrowFunctionBlockContext *arrowFunctionBlock();
    DataFormatContext *dataFormat();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarAssignmentContext* varAssignment();

  class  IfBlockContext : public antlr4::ParserRuleContext {
  public:
    IfBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    StatementListContext *statementList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfBlockContext* ifBlock();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *L_PAREN();
    BoolExprContext *boolExpr();
    antlr4::tree::TerminalNode *R_PAREN();
    IfBlockContext *ifBlock();
    antlr4::tree::TerminalNode *ELSE();
    ElseStatementContext *elseStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfStatementContext* ifStatement();

  class  ElseStatementContext : public antlr4::ParserRuleContext {
  public:
    ElseStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IfStatementContext *ifStatement();
    IfBlockContext *ifBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElseStatementContext* elseStatement();

  class  BoolExprContext : public antlr4::ParserRuleContext {
  public:
    IronParser::BoolExprContext *left = nullptr;
    antlr4::Token *not_ = nullptr;
    antlr4::Token *booleanValue = nullptr;
    antlr4::Token *varName = nullptr;
    antlr4::Token *op = nullptr;
    IronParser::BoolExprContext *right = nullptr;
    BoolExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    std::vector<BoolExprContext *> boolExpr();
    BoolExprContext* boolExpr(size_t i);
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *BOOLEAN_VALUE();
    NumberContext *number();
    antlr4::tree::TerminalNode *IDENTIFIER();
    FunctionCallContext *functionCall();
    ExprContext *expr();
    antlr4::tree::TerminalNode *EQEQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LTE();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GTE();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *OR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BoolExprContext* boolExpr();
  BoolExprContext* boolExpr(int precedence);
  class  PrimaryContext : public antlr4::ParserRuleContext {
  public:
    PrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberContext *number();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *BOOLEAN_VALUE();
    FunctionCallContext *functionCall();
    antlr4::tree::TerminalNode *L_PAREN();
    BoolExprContext *boolExpr();
    antlr4::tree::TerminalNode *R_PAREN();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrimaryContext* primary();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    IronParser::ExprContext *left = nullptr;
    antlr4::Token *varName = nullptr;
    antlr4::Token *mult = nullptr;
    antlr4::Token *mod = nullptr;
    antlr4::Token *div = nullptr;
    IronParser::ExprContext *right = nullptr;
    antlr4::Token *plus = nullptr;
    antlr4::Token *minus = nullptr;
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberContext *number();
    FunctionCallContext *functionCall();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REAL_NUMBER();
    antlr4::tree::TerminalNode *INT_NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumberContext* number();

  class  DataFormatContext : public antlr4::ParserRuleContext {
  public:
    DataFormatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REAL_NUMBER();
    antlr4::tree::TerminalNode *INT_NUMBER();
    antlr4::tree::TerminalNode *BOOLEAN_VALUE();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DataFormatContext* dataFormat();

  class  VarTypesContext : public antlr4::ParserRuleContext {
  public:
    VarTypesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE_BOOLEAN();
    antlr4::tree::TerminalNode *TYPE_CHAR();
    antlr4::tree::TerminalNode *TYPE_DOUBLE();
    antlr4::tree::TerminalNode *TYPE_FLOAT();
    antlr4::tree::TerminalNode *TYPE_INT();
    antlr4::tree::TerminalNode *TYPE_STRING();
    antlr4::tree::TerminalNode *FUNCTION();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarTypesContext* varTypes();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool boolExprSempred(BoolExprContext *_localctx, size_t predicateIndex);
  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

