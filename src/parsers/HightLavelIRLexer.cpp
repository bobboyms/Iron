
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
      "T__0", "COLON", "COMMA", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", 
      "R_CURLY", "L_PAREN", "R_PAREN", "MULT", "PLUS", "MINUS", "DIV", "L_BRACKET", 
      "R_BRACKET", "AT", "ARROW", "UNDERSCORE", "FUNCTION", "LET", "PUBLIC", 
      "PRIVATE", "IMPORT", "RETURN", "TO", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", 
      "TYPE_STRING", "TYPE_BOOLEAN", "TYPE_DOUBLE", "VOID", "CAST", "CALL", 
      "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", "IDENTIFIER", 
      "NEWLINE", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'fptr'", "':'", "','", "'='", "';'", "'.'", "'*'", "'{'", "'}'", 
      "'('", "')'", "'MULT'", "'PLUS'", "'MINUS'", "'DIV'", "'['", "']'", 
      "'@'", "'->'", "'_'", "'fn'", "'let'", "'public'", "'private'", "'import'", 
      "'return'", "'to'", "'int'", "'char'", "'float'", "'string'", "'boolean'", 
      "'double'", "'void'", "'cast'", "'call'"
    },
    std::vector<std::string>{
      "", "", "COLON", "COMMA", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", 
      "R_CURLY", "L_PAREN", "R_PAREN", "MULT", "PLUS", "MINUS", "DIV", "L_BRACKET", 
      "R_BRACKET", "AT", "ARROW", "UNDERSCORE", "FUNCTION", "LET", "PUBLIC", 
      "PRIVATE", "IMPORT", "RETURN", "TO", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", 
      "TYPE_STRING", "TYPE_BOOLEAN", "TYPE_DOUBLE", "VOID", "CAST", "CALL", 
      "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", "IDENTIFIER", 
      "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,43,311,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,
  	1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,12,1,
  	12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,
  	15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,18,1,19,1,19,1,20,1,20,1,20,1,
  	21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,
  	23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,
  	25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,28,1,28,1,
  	28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,29,1,30,1,30,1,30,1,30,1,30,1,
  	30,1,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,32,1,
  	32,1,32,1,32,1,33,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,35,1,
  	35,1,35,1,35,1,35,1,36,3,36,236,8,36,1,36,4,36,239,8,36,11,36,12,36,240,
  	1,36,1,36,4,36,245,8,36,11,36,12,36,246,1,36,1,36,3,36,251,8,36,1,36,
  	4,36,254,8,36,11,36,12,36,255,3,36,258,8,36,1,36,3,36,261,8,36,1,37,3,
  	37,264,8,37,1,37,4,37,267,8,37,11,37,12,37,268,1,38,1,38,1,38,1,38,1,
  	38,1,38,1,38,1,38,1,38,3,38,280,8,38,1,39,1,39,5,39,284,8,39,10,39,12,
  	39,287,9,39,1,39,1,39,1,40,1,40,5,40,293,8,40,10,40,12,40,296,9,40,1,
  	41,3,41,299,8,41,1,41,1,41,1,41,1,41,1,42,4,42,306,8,42,11,42,12,42,307,
  	1,42,1,42,0,0,43,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,
  	23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,
  	23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,
  	69,35,71,36,73,37,75,38,77,39,79,40,81,41,83,42,85,43,1,0,8,1,0,48,57,
  	2,0,69,69,101,101,2,0,43,43,45,45,2,0,68,68,70,70,3,0,10,10,13,13,34,
  	34,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,2,0,9,9,32,32,
  	324,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,
  	1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,
  	0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,
  	0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,
  	1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,
  	0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,
  	0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,
  	1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,
  	0,0,1,87,1,0,0,0,3,92,1,0,0,0,5,94,1,0,0,0,7,96,1,0,0,0,9,98,1,0,0,0,
  	11,100,1,0,0,0,13,102,1,0,0,0,15,104,1,0,0,0,17,106,1,0,0,0,19,108,1,
  	0,0,0,21,110,1,0,0,0,23,112,1,0,0,0,25,117,1,0,0,0,27,122,1,0,0,0,29,
  	128,1,0,0,0,31,132,1,0,0,0,33,134,1,0,0,0,35,136,1,0,0,0,37,138,1,0,0,
  	0,39,141,1,0,0,0,41,143,1,0,0,0,43,146,1,0,0,0,45,150,1,0,0,0,47,157,
  	1,0,0,0,49,165,1,0,0,0,51,172,1,0,0,0,53,179,1,0,0,0,55,182,1,0,0,0,57,
  	186,1,0,0,0,59,191,1,0,0,0,61,197,1,0,0,0,63,204,1,0,0,0,65,212,1,0,0,
  	0,67,219,1,0,0,0,69,224,1,0,0,0,71,229,1,0,0,0,73,235,1,0,0,0,75,263,
  	1,0,0,0,77,279,1,0,0,0,79,281,1,0,0,0,81,290,1,0,0,0,83,298,1,0,0,0,85,
  	305,1,0,0,0,87,88,5,102,0,0,88,89,5,112,0,0,89,90,5,116,0,0,90,91,5,114,
  	0,0,91,2,1,0,0,0,92,93,5,58,0,0,93,4,1,0,0,0,94,95,5,44,0,0,95,6,1,0,
  	0,0,96,97,5,61,0,0,97,8,1,0,0,0,98,99,5,59,0,0,99,10,1,0,0,0,100,101,
  	5,46,0,0,101,12,1,0,0,0,102,103,5,42,0,0,103,14,1,0,0,0,104,105,5,123,
  	0,0,105,16,1,0,0,0,106,107,5,125,0,0,107,18,1,0,0,0,108,109,5,40,0,0,
  	109,20,1,0,0,0,110,111,5,41,0,0,111,22,1,0,0,0,112,113,5,77,0,0,113,114,
  	5,85,0,0,114,115,5,76,0,0,115,116,5,84,0,0,116,24,1,0,0,0,117,118,5,80,
  	0,0,118,119,5,76,0,0,119,120,5,85,0,0,120,121,5,83,0,0,121,26,1,0,0,0,
  	122,123,5,77,0,0,123,124,5,73,0,0,124,125,5,78,0,0,125,126,5,85,0,0,126,
  	127,5,83,0,0,127,28,1,0,0,0,128,129,5,68,0,0,129,130,5,73,0,0,130,131,
  	5,86,0,0,131,30,1,0,0,0,132,133,5,91,0,0,133,32,1,0,0,0,134,135,5,93,
  	0,0,135,34,1,0,0,0,136,137,5,64,0,0,137,36,1,0,0,0,138,139,5,45,0,0,139,
  	140,5,62,0,0,140,38,1,0,0,0,141,142,5,95,0,0,142,40,1,0,0,0,143,144,5,
  	102,0,0,144,145,5,110,0,0,145,42,1,0,0,0,146,147,5,108,0,0,147,148,5,
  	101,0,0,148,149,5,116,0,0,149,44,1,0,0,0,150,151,5,112,0,0,151,152,5,
  	117,0,0,152,153,5,98,0,0,153,154,5,108,0,0,154,155,5,105,0,0,155,156,
  	5,99,0,0,156,46,1,0,0,0,157,158,5,112,0,0,158,159,5,114,0,0,159,160,5,
  	105,0,0,160,161,5,118,0,0,161,162,5,97,0,0,162,163,5,116,0,0,163,164,
  	5,101,0,0,164,48,1,0,0,0,165,166,5,105,0,0,166,167,5,109,0,0,167,168,
  	5,112,0,0,168,169,5,111,0,0,169,170,5,114,0,0,170,171,5,116,0,0,171,50,
  	1,0,0,0,172,173,5,114,0,0,173,174,5,101,0,0,174,175,5,116,0,0,175,176,
  	5,117,0,0,176,177,5,114,0,0,177,178,5,110,0,0,178,52,1,0,0,0,179,180,
  	5,116,0,0,180,181,5,111,0,0,181,54,1,0,0,0,182,183,5,105,0,0,183,184,
  	5,110,0,0,184,185,5,116,0,0,185,56,1,0,0,0,186,187,5,99,0,0,187,188,5,
  	104,0,0,188,189,5,97,0,0,189,190,5,114,0,0,190,58,1,0,0,0,191,192,5,102,
  	0,0,192,193,5,108,0,0,193,194,5,111,0,0,194,195,5,97,0,0,195,196,5,116,
  	0,0,196,60,1,0,0,0,197,198,5,115,0,0,198,199,5,116,0,0,199,200,5,114,
  	0,0,200,201,5,105,0,0,201,202,5,110,0,0,202,203,5,103,0,0,203,62,1,0,
  	0,0,204,205,5,98,0,0,205,206,5,111,0,0,206,207,5,111,0,0,207,208,5,108,
  	0,0,208,209,5,101,0,0,209,210,5,97,0,0,210,211,5,110,0,0,211,64,1,0,0,
  	0,212,213,5,100,0,0,213,214,5,111,0,0,214,215,5,117,0,0,215,216,5,98,
  	0,0,216,217,5,108,0,0,217,218,5,101,0,0,218,66,1,0,0,0,219,220,5,118,
  	0,0,220,221,5,111,0,0,221,222,5,105,0,0,222,223,5,100,0,0,223,68,1,0,
  	0,0,224,225,5,99,0,0,225,226,5,97,0,0,226,227,5,115,0,0,227,228,5,116,
  	0,0,228,70,1,0,0,0,229,230,5,99,0,0,230,231,5,97,0,0,231,232,5,108,0,
  	0,232,233,5,108,0,0,233,72,1,0,0,0,234,236,5,45,0,0,235,234,1,0,0,0,235,
  	236,1,0,0,0,236,238,1,0,0,0,237,239,7,0,0,0,238,237,1,0,0,0,239,240,1,
  	0,0,0,240,238,1,0,0,0,240,241,1,0,0,0,241,242,1,0,0,0,242,244,5,46,0,
  	0,243,245,7,0,0,0,244,243,1,0,0,0,245,246,1,0,0,0,246,244,1,0,0,0,246,
  	247,1,0,0,0,247,257,1,0,0,0,248,250,7,1,0,0,249,251,7,2,0,0,250,249,1,
  	0,0,0,250,251,1,0,0,0,251,253,1,0,0,0,252,254,7,0,0,0,253,252,1,0,0,0,
  	254,255,1,0,0,0,255,253,1,0,0,0,255,256,1,0,0,0,256,258,1,0,0,0,257,248,
  	1,0,0,0,257,258,1,0,0,0,258,260,1,0,0,0,259,261,7,3,0,0,260,259,1,0,0,
  	0,260,261,1,0,0,0,261,74,1,0,0,0,262,264,5,45,0,0,263,262,1,0,0,0,263,
  	264,1,0,0,0,264,266,1,0,0,0,265,267,7,0,0,0,266,265,1,0,0,0,267,268,1,
  	0,0,0,268,266,1,0,0,0,268,269,1,0,0,0,269,76,1,0,0,0,270,271,5,116,0,
  	0,271,272,5,114,0,0,272,273,5,117,0,0,273,280,5,101,0,0,274,275,5,102,
  	0,0,275,276,5,97,0,0,276,277,5,108,0,0,277,278,5,115,0,0,278,280,5,101,
  	0,0,279,270,1,0,0,0,279,274,1,0,0,0,280,78,1,0,0,0,281,285,5,34,0,0,282,
  	284,8,4,0,0,283,282,1,0,0,0,284,287,1,0,0,0,285,283,1,0,0,0,285,286,1,
  	0,0,0,286,288,1,0,0,0,287,285,1,0,0,0,288,289,5,34,0,0,289,80,1,0,0,0,
  	290,294,7,5,0,0,291,293,7,6,0,0,292,291,1,0,0,0,293,296,1,0,0,0,294,292,
  	1,0,0,0,294,295,1,0,0,0,295,82,1,0,0,0,296,294,1,0,0,0,297,299,5,13,0,
  	0,298,297,1,0,0,0,298,299,1,0,0,0,299,300,1,0,0,0,300,301,5,10,0,0,301,
  	302,1,0,0,0,302,303,6,41,0,0,303,84,1,0,0,0,304,306,7,7,0,0,305,304,1,
  	0,0,0,306,307,1,0,0,0,307,305,1,0,0,0,307,308,1,0,0,0,308,309,1,0,0,0,
  	309,310,6,42,0,0,310,86,1,0,0,0,15,0,235,240,246,250,255,257,260,263,
  	268,279,285,294,298,307,1,6,0,0
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
