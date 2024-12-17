
// Generated from Iron.g4 by ANTLR 4.13.2


#include "IronLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct IronLexerStaticData final {
  IronLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IronLexerStaticData(const IronLexerStaticData&) = delete;
  IronLexerStaticData(IronLexerStaticData&&) = delete;
  IronLexerStaticData& operator=(const IronLexerStaticData&) = delete;
  IronLexerStaticData& operator=(IronLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag ironlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<IronLexerStaticData> ironlexerLexerStaticData = nullptr;

void ironlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ironlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(ironlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<IronLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "COLON", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", 
      "R_CURLY", "L_PAREN", "R_PAREN", "PLUS", "MINUS", "DIV", "L_BRACKET", 
      "R_BRACKET", "ARROW", "FUNCTION", "LET", "PUBLIC", "IMPORT", "RETURN", 
      "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", "TYPE_STRING", "TYPE_BOOLEAN", 
      "TYPE_DOUBLE", "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", 
      "IDENTIFIER", "NEWLINE", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'@main'", "','", "':'", "'='", "';'", "'.'", "'*'", "'{'", "'}'", 
      "'('", "')'", "'+'", "'-'", "'/'", "'['", "']'", "'->'", "'fn'", "'let'", 
      "'public'", "'import'", "'return'", "'int'", "'char'", "'float'", 
      "'string'", "'boolean'", "'double'"
    },
    std::vector<std::string>{
      "", "", "", "COLON", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", 
      "R_CURLY", "L_PAREN", "R_PAREN", "PLUS", "MINUS", "DIV", "L_BRACKET", 
      "R_BRACKET", "ARROW", "FUNCTION", "LET", "PUBLIC", "IMPORT", "RETURN", 
      "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", "TYPE_STRING", "TYPE_BOOLEAN", 
      "TYPE_DOUBLE", "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", 
      "IDENTIFIER", "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,35,249,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,1,0,
  	1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,
  	7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,
  	14,1,15,1,15,1,16,1,16,1,16,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,21,1,
  	21,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,23,1,
  	23,1,24,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,
  	26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,27,1,
  	27,1,28,3,28,177,8,28,1,28,4,28,180,8,28,11,28,12,28,181,1,28,1,28,4,
  	28,186,8,28,11,28,12,28,187,1,28,1,28,3,28,192,8,28,1,28,4,28,195,8,28,
  	11,28,12,28,196,3,28,199,8,28,1,29,3,29,202,8,29,1,29,4,29,205,8,29,11,
  	29,12,29,206,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,3,30,218,8,
  	30,1,31,1,31,5,31,222,8,31,10,31,12,31,225,9,31,1,31,1,31,1,32,1,32,5,
  	32,231,8,32,10,32,12,32,234,9,32,1,33,3,33,237,8,33,1,33,1,33,1,33,1,
  	33,1,34,4,34,244,8,34,11,34,12,34,245,1,34,1,34,0,0,35,1,1,3,2,5,3,7,
  	4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,
  	17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,
  	57,29,59,30,61,31,63,32,65,33,67,34,69,35,1,0,7,1,0,48,57,2,0,69,69,101,
  	101,2,0,43,43,45,45,3,0,10,10,13,13,34,34,3,0,65,90,95,95,97,122,4,0,
  	48,57,65,90,95,95,97,122,2,0,9,9,32,32,261,0,1,1,0,0,0,0,3,1,0,0,0,0,
  	5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,
  	0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,
  	0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,
  	1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,
  	0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,
  	0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,
  	1,0,0,0,1,71,1,0,0,0,3,77,1,0,0,0,5,79,1,0,0,0,7,81,1,0,0,0,9,83,1,0,
  	0,0,11,85,1,0,0,0,13,87,1,0,0,0,15,89,1,0,0,0,17,91,1,0,0,0,19,93,1,0,
  	0,0,21,95,1,0,0,0,23,97,1,0,0,0,25,99,1,0,0,0,27,101,1,0,0,0,29,103,1,
  	0,0,0,31,105,1,0,0,0,33,107,1,0,0,0,35,110,1,0,0,0,37,113,1,0,0,0,39,
  	117,1,0,0,0,41,124,1,0,0,0,43,131,1,0,0,0,45,138,1,0,0,0,47,142,1,0,0,
  	0,49,147,1,0,0,0,51,153,1,0,0,0,53,160,1,0,0,0,55,168,1,0,0,0,57,176,
  	1,0,0,0,59,201,1,0,0,0,61,217,1,0,0,0,63,219,1,0,0,0,65,228,1,0,0,0,67,
  	236,1,0,0,0,69,243,1,0,0,0,71,72,5,64,0,0,72,73,5,109,0,0,73,74,5,97,
  	0,0,74,75,5,105,0,0,75,76,5,110,0,0,76,2,1,0,0,0,77,78,5,44,0,0,78,4,
  	1,0,0,0,79,80,5,58,0,0,80,6,1,0,0,0,81,82,5,61,0,0,82,8,1,0,0,0,83,84,
  	5,59,0,0,84,10,1,0,0,0,85,86,5,46,0,0,86,12,1,0,0,0,87,88,5,42,0,0,88,
  	14,1,0,0,0,89,90,5,123,0,0,90,16,1,0,0,0,91,92,5,125,0,0,92,18,1,0,0,
  	0,93,94,5,40,0,0,94,20,1,0,0,0,95,96,5,41,0,0,96,22,1,0,0,0,97,98,5,43,
  	0,0,98,24,1,0,0,0,99,100,5,45,0,0,100,26,1,0,0,0,101,102,5,47,0,0,102,
  	28,1,0,0,0,103,104,5,91,0,0,104,30,1,0,0,0,105,106,5,93,0,0,106,32,1,
  	0,0,0,107,108,5,45,0,0,108,109,5,62,0,0,109,34,1,0,0,0,110,111,5,102,
  	0,0,111,112,5,110,0,0,112,36,1,0,0,0,113,114,5,108,0,0,114,115,5,101,
  	0,0,115,116,5,116,0,0,116,38,1,0,0,0,117,118,5,112,0,0,118,119,5,117,
  	0,0,119,120,5,98,0,0,120,121,5,108,0,0,121,122,5,105,0,0,122,123,5,99,
  	0,0,123,40,1,0,0,0,124,125,5,105,0,0,125,126,5,109,0,0,126,127,5,112,
  	0,0,127,128,5,111,0,0,128,129,5,114,0,0,129,130,5,116,0,0,130,42,1,0,
  	0,0,131,132,5,114,0,0,132,133,5,101,0,0,133,134,5,116,0,0,134,135,5,117,
  	0,0,135,136,5,114,0,0,136,137,5,110,0,0,137,44,1,0,0,0,138,139,5,105,
  	0,0,139,140,5,110,0,0,140,141,5,116,0,0,141,46,1,0,0,0,142,143,5,99,0,
  	0,143,144,5,104,0,0,144,145,5,97,0,0,145,146,5,114,0,0,146,48,1,0,0,0,
  	147,148,5,102,0,0,148,149,5,108,0,0,149,150,5,111,0,0,150,151,5,97,0,
  	0,151,152,5,116,0,0,152,50,1,0,0,0,153,154,5,115,0,0,154,155,5,116,0,
  	0,155,156,5,114,0,0,156,157,5,105,0,0,157,158,5,110,0,0,158,159,5,103,
  	0,0,159,52,1,0,0,0,160,161,5,98,0,0,161,162,5,111,0,0,162,163,5,111,0,
  	0,163,164,5,108,0,0,164,165,5,101,0,0,165,166,5,97,0,0,166,167,5,110,
  	0,0,167,54,1,0,0,0,168,169,5,100,0,0,169,170,5,111,0,0,170,171,5,117,
  	0,0,171,172,5,98,0,0,172,173,5,108,0,0,173,174,5,101,0,0,174,56,1,0,0,
  	0,175,177,5,45,0,0,176,175,1,0,0,0,176,177,1,0,0,0,177,179,1,0,0,0,178,
  	180,7,0,0,0,179,178,1,0,0,0,180,181,1,0,0,0,181,179,1,0,0,0,181,182,1,
  	0,0,0,182,183,1,0,0,0,183,185,5,46,0,0,184,186,7,0,0,0,185,184,1,0,0,
  	0,186,187,1,0,0,0,187,185,1,0,0,0,187,188,1,0,0,0,188,198,1,0,0,0,189,
  	191,7,1,0,0,190,192,7,2,0,0,191,190,1,0,0,0,191,192,1,0,0,0,192,194,1,
  	0,0,0,193,195,7,0,0,0,194,193,1,0,0,0,195,196,1,0,0,0,196,194,1,0,0,0,
  	196,197,1,0,0,0,197,199,1,0,0,0,198,189,1,0,0,0,198,199,1,0,0,0,199,58,
  	1,0,0,0,200,202,5,45,0,0,201,200,1,0,0,0,201,202,1,0,0,0,202,204,1,0,
  	0,0,203,205,7,0,0,0,204,203,1,0,0,0,205,206,1,0,0,0,206,204,1,0,0,0,206,
  	207,1,0,0,0,207,60,1,0,0,0,208,209,5,116,0,0,209,210,5,114,0,0,210,211,
  	5,117,0,0,211,218,5,101,0,0,212,213,5,102,0,0,213,214,5,97,0,0,214,215,
  	5,108,0,0,215,216,5,115,0,0,216,218,5,101,0,0,217,208,1,0,0,0,217,212,
  	1,0,0,0,218,62,1,0,0,0,219,223,5,34,0,0,220,222,8,3,0,0,221,220,1,0,0,
  	0,222,225,1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,226,1,0,0,0,225,
  	223,1,0,0,0,226,227,5,34,0,0,227,64,1,0,0,0,228,232,7,4,0,0,229,231,7,
  	5,0,0,230,229,1,0,0,0,231,234,1,0,0,0,232,230,1,0,0,0,232,233,1,0,0,0,
  	233,66,1,0,0,0,234,232,1,0,0,0,235,237,5,13,0,0,236,235,1,0,0,0,236,237,
  	1,0,0,0,237,238,1,0,0,0,238,239,5,10,0,0,239,240,1,0,0,0,240,241,6,33,
  	0,0,241,68,1,0,0,0,242,244,7,6,0,0,243,242,1,0,0,0,244,245,1,0,0,0,245,
  	243,1,0,0,0,245,246,1,0,0,0,246,247,1,0,0,0,247,248,6,34,0,0,248,70,1,
  	0,0,0,14,0,176,181,187,191,196,198,201,206,217,223,232,236,245,1,6,0,
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
  ironlexerLexerStaticData = std::move(staticData);
}

}

IronLexer::IronLexer(CharStream *input) : Lexer(input) {
  IronLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *ironlexerLexerStaticData->atn, ironlexerLexerStaticData->decisionToDFA, ironlexerLexerStaticData->sharedContextCache);
}

IronLexer::~IronLexer() {
  delete _interpreter;
}

std::string IronLexer::getGrammarFileName() const {
  return "Iron.g4";
}

const std::vector<std::string>& IronLexer::getRuleNames() const {
  return ironlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& IronLexer::getChannelNames() const {
  return ironlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& IronLexer::getModeNames() const {
  return ironlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& IronLexer::getVocabulary() const {
  return ironlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IronLexer::getSerializedATN() const {
  return ironlexerLexerStaticData->serializedATN;
}

const atn::ATN& IronLexer::getATN() const {
  return *ironlexerLexerStaticData->atn;
}




void IronLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ironlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(ironlexerLexerOnceFlag, ironlexerLexerInitialize);
#endif
}
