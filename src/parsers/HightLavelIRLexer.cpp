
// Generated from HightLavelIR.g4 by ANTLR 4.13.2


#include "HightLavelIRLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct HightLavelIRLexerStaticData final {
  HightLavelIRLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  HightLavelIRLexerStaticData(const HightLavelIRLexerStaticData&) = delete;
  HightLavelIRLexerStaticData(HightLavelIRLexerStaticData&&) = delete;
  HightLavelIRLexerStaticData& operator=(const HightLavelIRLexerStaticData&) = delete;
  HightLavelIRLexerStaticData& operator=(HightLavelIRLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag hightlavelirlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<HightLavelIRLexerStaticData> hightlavelirlexerLexerStaticData = nullptr;

void hightlavelirlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (hightlavelirlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(hightlavelirlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<HightLavelIRLexerStaticData>(
    std::vector<std::string>{
      "COLON", "COMMA", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", "R_CURLY", 
      "L_PAREN", "R_PAREN", "MULT", "PLUS", "MINUS", "DIV", "L_BRACKET", 
      "R_BRACKET", "AT", "ARROW", "UNDERSCORE", "FUNCTION", "LET", "PUBLIC", 
      "PRIVATE", "IMPORT", "RETURN", "TO", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", 
      "TYPE_STRING", "TYPE_BOOLEAN", "TYPE_DOUBLE", "VOID", "CAST", "REAL_NUMBER", 
      "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", "IDENTIFIER", "NEWLINE", 
      "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "':'", "','", "'='", "';'", "'.'", "'*'", "'{'", "'}'", "'('", 
      "')'", "'MULT'", "'PLUS'", "'MINUS'", "'DIV'", "'['", "']'", "'@'", 
      "'->'", "'_'", "'fn'", "'let'", "'public'", "'private'", "'import'", 
      "'return'", "'to'", "'int'", "'char'", "'float'", "'string'", "'boolean'", 
      "'double'", "'void'", "'cast'"
    },
    std::vector<std::string>{
      "", "COLON", "COMMA", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", 
      "R_CURLY", "L_PAREN", "R_PAREN", "MULT", "PLUS", "MINUS", "DIV", "L_BRACKET", 
      "R_BRACKET", "AT", "ARROW", "UNDERSCORE", "FUNCTION", "LET", "PUBLIC", 
      "PRIVATE", "IMPORT", "RETURN", "TO", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", 
      "TYPE_STRING", "TYPE_BOOLEAN", "TYPE_DOUBLE", "VOID", "CAST", "REAL_NUMBER", 
      "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", "IDENTIFIER", "NEWLINE", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,41,297,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,1,0,1,0,1,1,1,
  	1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,
  	1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,13,1,13,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,17,
  	1,18,1,18,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,26,
  	1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,28,1,28,
  	1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,30,1,30,1,30,1,30,1,30,1,30,1,30,
  	1,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,32,1,32,1,33,
  	1,33,1,33,1,33,1,33,1,34,3,34,222,8,34,1,34,4,34,225,8,34,11,34,12,34,
  	226,1,34,1,34,4,34,231,8,34,11,34,12,34,232,1,34,1,34,3,34,237,8,34,1,
  	34,4,34,240,8,34,11,34,12,34,241,3,34,244,8,34,1,34,3,34,247,8,34,1,35,
  	3,35,250,8,35,1,35,4,35,253,8,35,11,35,12,35,254,1,36,1,36,1,36,1,36,
  	1,36,1,36,1,36,1,36,1,36,3,36,266,8,36,1,37,1,37,5,37,270,8,37,10,37,
  	12,37,273,9,37,1,37,1,37,1,38,1,38,5,38,279,8,38,10,38,12,38,282,9,38,
  	1,39,3,39,285,8,39,1,39,1,39,1,39,1,39,1,40,4,40,292,8,40,11,40,12,40,
  	293,1,40,1,40,0,0,41,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,
  	11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,
  	45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,
  	34,69,35,71,36,73,37,75,38,77,39,79,40,81,41,1,0,8,1,0,48,57,2,0,69,69,
  	101,101,2,0,43,43,45,45,2,0,68,68,70,70,3,0,10,10,13,13,34,34,3,0,65,
  	90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,2,0,9,9,32,32,310,0,1,1,
  	0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,
  	13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,
  	0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,
  	0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,
  	45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,
  	0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,
  	0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,0,
  	77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,1,83,1,0,0,0,3,85,1,0,0,0,5,87,1,
  	0,0,0,7,89,1,0,0,0,9,91,1,0,0,0,11,93,1,0,0,0,13,95,1,0,0,0,15,97,1,0,
  	0,0,17,99,1,0,0,0,19,101,1,0,0,0,21,103,1,0,0,0,23,108,1,0,0,0,25,113,
  	1,0,0,0,27,119,1,0,0,0,29,123,1,0,0,0,31,125,1,0,0,0,33,127,1,0,0,0,35,
  	129,1,0,0,0,37,132,1,0,0,0,39,134,1,0,0,0,41,137,1,0,0,0,43,141,1,0,0,
  	0,45,148,1,0,0,0,47,156,1,0,0,0,49,163,1,0,0,0,51,170,1,0,0,0,53,173,
  	1,0,0,0,55,177,1,0,0,0,57,182,1,0,0,0,59,188,1,0,0,0,61,195,1,0,0,0,63,
  	203,1,0,0,0,65,210,1,0,0,0,67,215,1,0,0,0,69,221,1,0,0,0,71,249,1,0,0,
  	0,73,265,1,0,0,0,75,267,1,0,0,0,77,276,1,0,0,0,79,284,1,0,0,0,81,291,
  	1,0,0,0,83,84,5,58,0,0,84,2,1,0,0,0,85,86,5,44,0,0,86,4,1,0,0,0,87,88,
  	5,61,0,0,88,6,1,0,0,0,89,90,5,59,0,0,90,8,1,0,0,0,91,92,5,46,0,0,92,10,
  	1,0,0,0,93,94,5,42,0,0,94,12,1,0,0,0,95,96,5,123,0,0,96,14,1,0,0,0,97,
  	98,5,125,0,0,98,16,1,0,0,0,99,100,5,40,0,0,100,18,1,0,0,0,101,102,5,41,
  	0,0,102,20,1,0,0,0,103,104,5,77,0,0,104,105,5,85,0,0,105,106,5,76,0,0,
  	106,107,5,84,0,0,107,22,1,0,0,0,108,109,5,80,0,0,109,110,5,76,0,0,110,
  	111,5,85,0,0,111,112,5,83,0,0,112,24,1,0,0,0,113,114,5,77,0,0,114,115,
  	5,73,0,0,115,116,5,78,0,0,116,117,5,85,0,0,117,118,5,83,0,0,118,26,1,
  	0,0,0,119,120,5,68,0,0,120,121,5,73,0,0,121,122,5,86,0,0,122,28,1,0,0,
  	0,123,124,5,91,0,0,124,30,1,0,0,0,125,126,5,93,0,0,126,32,1,0,0,0,127,
  	128,5,64,0,0,128,34,1,0,0,0,129,130,5,45,0,0,130,131,5,62,0,0,131,36,
  	1,0,0,0,132,133,5,95,0,0,133,38,1,0,0,0,134,135,5,102,0,0,135,136,5,110,
  	0,0,136,40,1,0,0,0,137,138,5,108,0,0,138,139,5,101,0,0,139,140,5,116,
  	0,0,140,42,1,0,0,0,141,142,5,112,0,0,142,143,5,117,0,0,143,144,5,98,0,
  	0,144,145,5,108,0,0,145,146,5,105,0,0,146,147,5,99,0,0,147,44,1,0,0,0,
  	148,149,5,112,0,0,149,150,5,114,0,0,150,151,5,105,0,0,151,152,5,118,0,
  	0,152,153,5,97,0,0,153,154,5,116,0,0,154,155,5,101,0,0,155,46,1,0,0,0,
  	156,157,5,105,0,0,157,158,5,109,0,0,158,159,5,112,0,0,159,160,5,111,0,
  	0,160,161,5,114,0,0,161,162,5,116,0,0,162,48,1,0,0,0,163,164,5,114,0,
  	0,164,165,5,101,0,0,165,166,5,116,0,0,166,167,5,117,0,0,167,168,5,114,
  	0,0,168,169,5,110,0,0,169,50,1,0,0,0,170,171,5,116,0,0,171,172,5,111,
  	0,0,172,52,1,0,0,0,173,174,5,105,0,0,174,175,5,110,0,0,175,176,5,116,
  	0,0,176,54,1,0,0,0,177,178,5,99,0,0,178,179,5,104,0,0,179,180,5,97,0,
  	0,180,181,5,114,0,0,181,56,1,0,0,0,182,183,5,102,0,0,183,184,5,108,0,
  	0,184,185,5,111,0,0,185,186,5,97,0,0,186,187,5,116,0,0,187,58,1,0,0,0,
  	188,189,5,115,0,0,189,190,5,116,0,0,190,191,5,114,0,0,191,192,5,105,0,
  	0,192,193,5,110,0,0,193,194,5,103,0,0,194,60,1,0,0,0,195,196,5,98,0,0,
  	196,197,5,111,0,0,197,198,5,111,0,0,198,199,5,108,0,0,199,200,5,101,0,
  	0,200,201,5,97,0,0,201,202,5,110,0,0,202,62,1,0,0,0,203,204,5,100,0,0,
  	204,205,5,111,0,0,205,206,5,117,0,0,206,207,5,98,0,0,207,208,5,108,0,
  	0,208,209,5,101,0,0,209,64,1,0,0,0,210,211,5,118,0,0,211,212,5,111,0,
  	0,212,213,5,105,0,0,213,214,5,100,0,0,214,66,1,0,0,0,215,216,5,99,0,0,
  	216,217,5,97,0,0,217,218,5,115,0,0,218,219,5,116,0,0,219,68,1,0,0,0,220,
  	222,5,45,0,0,221,220,1,0,0,0,221,222,1,0,0,0,222,224,1,0,0,0,223,225,
  	7,0,0,0,224,223,1,0,0,0,225,226,1,0,0,0,226,224,1,0,0,0,226,227,1,0,0,
  	0,227,228,1,0,0,0,228,230,5,46,0,0,229,231,7,0,0,0,230,229,1,0,0,0,231,
  	232,1,0,0,0,232,230,1,0,0,0,232,233,1,0,0,0,233,243,1,0,0,0,234,236,7,
  	1,0,0,235,237,7,2,0,0,236,235,1,0,0,0,236,237,1,0,0,0,237,239,1,0,0,0,
  	238,240,7,0,0,0,239,238,1,0,0,0,240,241,1,0,0,0,241,239,1,0,0,0,241,242,
  	1,0,0,0,242,244,1,0,0,0,243,234,1,0,0,0,243,244,1,0,0,0,244,246,1,0,0,
  	0,245,247,7,3,0,0,246,245,1,0,0,0,246,247,1,0,0,0,247,70,1,0,0,0,248,
  	250,5,45,0,0,249,248,1,0,0,0,249,250,1,0,0,0,250,252,1,0,0,0,251,253,
  	7,0,0,0,252,251,1,0,0,0,253,254,1,0,0,0,254,252,1,0,0,0,254,255,1,0,0,
  	0,255,72,1,0,0,0,256,257,5,116,0,0,257,258,5,114,0,0,258,259,5,117,0,
  	0,259,266,5,101,0,0,260,261,5,102,0,0,261,262,5,97,0,0,262,263,5,108,
  	0,0,263,264,5,115,0,0,264,266,5,101,0,0,265,256,1,0,0,0,265,260,1,0,0,
  	0,266,74,1,0,0,0,267,271,5,34,0,0,268,270,8,4,0,0,269,268,1,0,0,0,270,
  	273,1,0,0,0,271,269,1,0,0,0,271,272,1,0,0,0,272,274,1,0,0,0,273,271,1,
  	0,0,0,274,275,5,34,0,0,275,76,1,0,0,0,276,280,7,5,0,0,277,279,7,6,0,0,
  	278,277,1,0,0,0,279,282,1,0,0,0,280,278,1,0,0,0,280,281,1,0,0,0,281,78,
  	1,0,0,0,282,280,1,0,0,0,283,285,5,13,0,0,284,283,1,0,0,0,284,285,1,0,
  	0,0,285,286,1,0,0,0,286,287,5,10,0,0,287,288,1,0,0,0,288,289,6,39,0,0,
  	289,80,1,0,0,0,290,292,7,7,0,0,291,290,1,0,0,0,292,293,1,0,0,0,293,291,
  	1,0,0,0,293,294,1,0,0,0,294,295,1,0,0,0,295,296,6,40,0,0,296,82,1,0,0,
  	0,15,0,221,226,232,236,241,243,246,249,254,265,271,280,284,293,1,6,0,
  	0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  hightlavelirlexerLexerStaticData = std::move(staticData);
}

}

HightLavelIRLexer::HightLavelIRLexer(CharStream *input) : Lexer(input) {
  HightLavelIRLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *hightlavelirlexerLexerStaticData->atn, hightlavelirlexerLexerStaticData->decisionToDFA, hightlavelirlexerLexerStaticData->sharedContextCache);
}

HightLavelIRLexer::~HightLavelIRLexer() {
  delete _interpreter;
}

std::string HightLavelIRLexer::getGrammarFileName() const {
  return "HightLavelIR.g4";
}

const std::vector<std::string>& HightLavelIRLexer::getRuleNames() const {
  return hightlavelirlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& HightLavelIRLexer::getChannelNames() const {
  return hightlavelirlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& HightLavelIRLexer::getModeNames() const {
  return hightlavelirlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& HightLavelIRLexer::getVocabulary() const {
  return hightlavelirlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView HightLavelIRLexer::getSerializedATN() const {
  return hightlavelirlexerLexerStaticData->serializedATN;
}

const atn::ATN& HightLavelIRLexer::getATN() const {
  return *hightlavelirlexerLexerStaticData->atn;
}




void HightLavelIRLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  hightlavelirlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(hightlavelirlexerLexerOnceFlag, hightlavelirlexerLexerInitialize);
#endif
}
