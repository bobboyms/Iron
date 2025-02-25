
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronLexer : public antlr4::Lexer {
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

  explicit IronLexer(antlr4::CharStream *input);

  ~IronLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

