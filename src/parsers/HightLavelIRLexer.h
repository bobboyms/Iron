
// Generated from HightLavelIR.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  HightLavelIRLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, COLON = 2, COMMA = 3, EQ = 4, SEMICOLON = 5, DOT = 6, STAR = 7, 
    L_CURLY = 8, R_CURLY = 9, L_PAREN = 10, R_PAREN = 11, MULT = 12, PLUS = 13, 
    MINUS = 14, DIV = 15, L_BRACKET = 16, R_BRACKET = 17, AT = 18, ARROW = 19, 
    UNDERSCORE = 20, FUNCTION = 21, LET = 22, PUBLIC = 23, PRIVATE = 24, 
    IMPORT = 25, RETURN = 26, TO = 27, TYPE_INT = 28, TYPE_CHAR = 29, TYPE_FLOAT = 30, 
    TYPE_STRING = 31, TYPE_BOOLEAN = 32, TYPE_DOUBLE = 33, VOID = 34, CAST = 35, 
    CALL = 36, REAL_NUMBER = 37, INT_NUMBER = 38, BOOLEAN_VALUE = 39, STRING_LITERAL = 40, 
    IDENTIFIER = 41, NEWLINE = 42, WS = 43
  };

  explicit HightLavelIRLexer(antlr4::CharStream *input);

  ~HightLavelIRLexer() override;


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

