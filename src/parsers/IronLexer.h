
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, LINE_COMMENT = 4, BLOCK_COMMENT = 5, COMMA = 6, 
    COLON = 7, EQ = 8, SEMICOLON = 9, DOT = 10, STAR = 11, L_CURLY = 12, 
    R_CURLY = 13, L_PAREN = 14, R_PAREN = 15, PLUS = 16, MINUS = 17, DIV = 18, 
    L_BRACKET = 19, R_BRACKET = 20, ARROW = 21, FUNCTION = 22, LET = 23, 
    PUBLIC = 24, IMPORT = 25, RETURN = 26, TYPE_INT = 27, TYPE_CHAR = 28, 
    TYPE_FLOAT = 29, TYPE_STRING = 30, TYPE_BOOLEAN = 31, TYPE_DOUBLE = 32, 
    TYPE_VOID = 33, REAL_NUMBER = 34, INT_NUMBER = 35, BOOLEAN_VALUE = 36, 
    STRING_LITERAL = 37, IDENTIFIER = 38, NEWLINE = 39, WS = 40
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

