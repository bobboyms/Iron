
// Generated from HightLavelIR.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  HightLavelIRLexer : public antlr4::Lexer {
public:
  enum {
    COLON = 1, COMMA = 2, EQ = 3, SEMICOLON = 4, DOT = 5, STAR = 6, L_CURLY = 7, 
    R_CURLY = 8, L_PAREN = 9, R_PAREN = 10, MULT = 11, PLUS = 12, MINUS = 13, 
    DIV = 14, L_BRACKET = 15, R_BRACKET = 16, AT = 17, ARROW = 18, UNDERSCORE = 19, 
    FUNCTION = 20, LET = 21, PUBLIC = 22, PRIVATE = 23, IMPORT = 24, RETURN = 25, 
    TO = 26, TYPE_INT = 27, TYPE_CHAR = 28, TYPE_FLOAT = 29, TYPE_STRING = 30, 
    TYPE_BOOLEAN = 31, TYPE_DOUBLE = 32, VOID = 33, CAST = 34, REAL_NUMBER = 35, 
    INT_NUMBER = 36, BOOLEAN_VALUE = 37, STRING_LITERAL = 38, IDENTIFIER = 39, 
    NEWLINE = 40, WS = 41
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

