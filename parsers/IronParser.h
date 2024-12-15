
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, COLON = 2, EQ = 3, SEMICOLON = 4, DOT = 5, STAR = 6, L_CURLY = 7, 
    R_CURLY = 8, L_BRACKET = 9, R_BRACKET = 10, L_PAREN = 11, R_PAREN = 12, 
    FUNCTION = 13, LET = 14, PUBLIC = 15, IMPORT = 16, TYPE_INT = 17, TYPE_CHAR = 18, 
    TYPE_FLOAT = 19, TYPE_STRING = 20, TYPE_BOOLEAN = 21, TYPE_DOUBLE = 22, 
    REAL_NUMBER = 23, INT_NUMBER = 24, BOOLEAN_VALUE = 25, STRING_LITERAL = 26, 
    IDENTIFIER = 27, NEWLINE = 28, WS = 29
  };

  enum {
    RuleProgram = 0, RuleImportStatement = 1, RuleQualifiedName = 2, RuleEntryPoint = 3, 
    RuleBody = 4, RuleFunctionDeclaration = 5, RuleStatement = 6, RuleVarDeclaration = 7, 
    RuleDataFormat = 8, RuleVarTypes = 9
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
  class EntryPointContext;
  class BodyContext;
  class FunctionDeclarationContext;
  class StatementContext;
  class VarDeclarationContext;
  class DataFormatContext;
  class VarTypesContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BodyContext *body();
    antlr4::tree::TerminalNode *EOF();
    std::vector<ImportStatementContext *> importStatement();
    ImportStatementContext* importStatement(size_t i);
    EntryPointContext *entryPoint();
    antlr4::tree::TerminalNode *NEWLINE();

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
    antlr4::tree::TerminalNode *NEWLINE();
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

  class  EntryPointContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *argVar = nullptr;
    EntryPointContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EntryPointContext* entryPoint();

  class  BodyContext : public antlr4::ParserRuleContext {
  public:
    BodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    std::vector<FunctionDeclarationContext *> functionDeclaration();
    FunctionDeclarationContext* functionDeclaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BodyContext* body();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *functionName = nullptr;
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *PUBLIC();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarDeclarationContext *varDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  VarDeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    VarDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *COLON();
    VarTypesContext *varTypes();
    antlr4::tree::TerminalNode *NEWLINE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQ();
    DataFormatContext *dataFormat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarDeclarationContext* varDeclaration();

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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarTypesContext* varTypes();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

