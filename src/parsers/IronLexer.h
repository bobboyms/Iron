
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, COMMA = 2, COLON = 3, EQ = 4, SEMICOLON = 5, DOT = 6, STAR = 7, 
    L_CURLY = 8, R_CURLY = 9, L_PAREN = 10, R_PAREN = 11, PLUS = 12, MINUS = 13, 
    DIV = 14, L_BRACKET = 15, R_BRACKET = 16, ARROW = 17, FUNCTION = 18, 
    LET = 19, PUBLIC = 20, IMPORT = 21, RETURN = 22, TYPE_INT = 23, TYPE_CHAR = 24, 
    TYPE_FLOAT = 25, TYPE_STRING = 26, TYPE_BOOLEAN = 27, TYPE_DOUBLE = 28, 
    REAL_NUMBER = 29, INT_NUMBER = 30, BOOLEAN_VALUE = 31, STRING_LITERAL = 32, 
    IDENTIFIER = 33, NEWLINE = 34, WS = 35
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

