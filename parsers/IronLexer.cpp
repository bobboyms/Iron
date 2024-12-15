
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
      "T__0", "COLON", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", "R_CURLY", 
      "L_BRACKET", "R_BRACKET", "L_PAREN", "R_PAREN", "FUNCTION", "LET", 
      "PUBLIC", "IMPORT", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", "TYPE_STRING", 
      "TYPE_BOOLEAN", "TYPE_DOUBLE", "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", 
      "STRING_LITERAL", "IDENTIFIER", "NEWLINE", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'@main'", "':'", "'='", "';'", "'.'", "'*'", "'{'", "'}'", "'['", 
      "']'", "'('", "')'", "'fn'", "'let'", "'public'", "'import'", "'int'", 
      "'char'", "'float'", "'string'", "'boolean'", "'double'"
    },
    std::vector<std::string>{
      "", "", "COLON", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", "R_CURLY", 
      "L_BRACKET", "R_BRACKET", "L_PAREN", "R_PAREN", "FUNCTION", "LET", 
      "PUBLIC", "IMPORT", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", "TYPE_STRING", 
      "TYPE_BOOLEAN", "TYPE_DOUBLE", "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", 
      "STRING_LITERAL", "IDENTIFIER", "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,29,217,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,
  	1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,
  	13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,
  	15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,18,1,
  	18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,
  	20,1,20,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,22,3,
  	22,147,8,22,1,22,4,22,150,8,22,11,22,12,22,151,1,22,1,22,4,22,156,8,22,
  	11,22,12,22,157,1,22,1,22,3,22,162,8,22,1,22,4,22,165,8,22,11,22,12,22,
  	166,3,22,169,8,22,1,23,3,23,172,8,23,1,23,4,23,175,8,23,11,23,12,23,176,
  	1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,188,8,24,1,25,1,25,
  	5,25,192,8,25,10,25,12,25,195,9,25,1,25,1,25,1,26,1,26,5,26,201,8,26,
  	10,26,12,26,204,9,26,1,27,3,27,207,8,27,1,27,1,27,1,28,4,28,212,8,28,
  	11,28,12,28,213,1,28,1,28,0,0,29,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,
  	9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,
  	21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,1,0,7,1,0,48,57,2,
  	0,69,69,101,101,2,0,43,43,45,45,3,0,10,10,13,13,34,34,3,0,65,90,95,95,
  	97,122,4,0,48,57,65,90,95,95,97,122,2,0,9,9,32,32,229,0,1,1,0,0,0,0,3,
  	1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,
  	0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,
  	1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,
  	0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,
  	0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,
  	1,0,0,0,1,59,1,0,0,0,3,65,1,0,0,0,5,67,1,0,0,0,7,69,1,0,0,0,9,71,1,0,
  	0,0,11,73,1,0,0,0,13,75,1,0,0,0,15,77,1,0,0,0,17,79,1,0,0,0,19,81,1,0,
  	0,0,21,83,1,0,0,0,23,85,1,0,0,0,25,87,1,0,0,0,27,90,1,0,0,0,29,94,1,0,
  	0,0,31,101,1,0,0,0,33,108,1,0,0,0,35,112,1,0,0,0,37,117,1,0,0,0,39,123,
  	1,0,0,0,41,130,1,0,0,0,43,138,1,0,0,0,45,146,1,0,0,0,47,171,1,0,0,0,49,
  	187,1,0,0,0,51,189,1,0,0,0,53,198,1,0,0,0,55,206,1,0,0,0,57,211,1,0,0,
  	0,59,60,5,64,0,0,60,61,5,109,0,0,61,62,5,97,0,0,62,63,5,105,0,0,63,64,
  	5,110,0,0,64,2,1,0,0,0,65,66,5,58,0,0,66,4,1,0,0,0,67,68,5,61,0,0,68,
  	6,1,0,0,0,69,70,5,59,0,0,70,8,1,0,0,0,71,72,5,46,0,0,72,10,1,0,0,0,73,
  	74,5,42,0,0,74,12,1,0,0,0,75,76,5,123,0,0,76,14,1,0,0,0,77,78,5,125,0,
  	0,78,16,1,0,0,0,79,80,5,91,0,0,80,18,1,0,0,0,81,82,5,93,0,0,82,20,1,0,
  	0,0,83,84,5,40,0,0,84,22,1,0,0,0,85,86,5,41,0,0,86,24,1,0,0,0,87,88,5,
  	102,0,0,88,89,5,110,0,0,89,26,1,0,0,0,90,91,5,108,0,0,91,92,5,101,0,0,
  	92,93,5,116,0,0,93,28,1,0,0,0,94,95,5,112,0,0,95,96,5,117,0,0,96,97,5,
  	98,0,0,97,98,5,108,0,0,98,99,5,105,0,0,99,100,5,99,0,0,100,30,1,0,0,0,
  	101,102,5,105,0,0,102,103,5,109,0,0,103,104,5,112,0,0,104,105,5,111,0,
  	0,105,106,5,114,0,0,106,107,5,116,0,0,107,32,1,0,0,0,108,109,5,105,0,
  	0,109,110,5,110,0,0,110,111,5,116,0,0,111,34,1,0,0,0,112,113,5,99,0,0,
  	113,114,5,104,0,0,114,115,5,97,0,0,115,116,5,114,0,0,116,36,1,0,0,0,117,
  	118,5,102,0,0,118,119,5,108,0,0,119,120,5,111,0,0,120,121,5,97,0,0,121,
  	122,5,116,0,0,122,38,1,0,0,0,123,124,5,115,0,0,124,125,5,116,0,0,125,
  	126,5,114,0,0,126,127,5,105,0,0,127,128,5,110,0,0,128,129,5,103,0,0,129,
  	40,1,0,0,0,130,131,5,98,0,0,131,132,5,111,0,0,132,133,5,111,0,0,133,134,
  	5,108,0,0,134,135,5,101,0,0,135,136,5,97,0,0,136,137,5,110,0,0,137,42,
  	1,0,0,0,138,139,5,100,0,0,139,140,5,111,0,0,140,141,5,117,0,0,141,142,
  	5,98,0,0,142,143,5,108,0,0,143,144,5,101,0,0,144,44,1,0,0,0,145,147,5,
  	45,0,0,146,145,1,0,0,0,146,147,1,0,0,0,147,149,1,0,0,0,148,150,7,0,0,
  	0,149,148,1,0,0,0,150,151,1,0,0,0,151,149,1,0,0,0,151,152,1,0,0,0,152,
  	153,1,0,0,0,153,155,5,46,0,0,154,156,7,0,0,0,155,154,1,0,0,0,156,157,
  	1,0,0,0,157,155,1,0,0,0,157,158,1,0,0,0,158,168,1,0,0,0,159,161,7,1,0,
  	0,160,162,7,2,0,0,161,160,1,0,0,0,161,162,1,0,0,0,162,164,1,0,0,0,163,
  	165,7,0,0,0,164,163,1,0,0,0,165,166,1,0,0,0,166,164,1,0,0,0,166,167,1,
  	0,0,0,167,169,1,0,0,0,168,159,1,0,0,0,168,169,1,0,0,0,169,46,1,0,0,0,
  	170,172,5,45,0,0,171,170,1,0,0,0,171,172,1,0,0,0,172,174,1,0,0,0,173,
  	175,7,0,0,0,174,173,1,0,0,0,175,176,1,0,0,0,176,174,1,0,0,0,176,177,1,
  	0,0,0,177,48,1,0,0,0,178,179,5,116,0,0,179,180,5,114,0,0,180,181,5,117,
  	0,0,181,188,5,101,0,0,182,183,5,102,0,0,183,184,5,97,0,0,184,185,5,108,
  	0,0,185,186,5,115,0,0,186,188,5,101,0,0,187,178,1,0,0,0,187,182,1,0,0,
  	0,188,50,1,0,0,0,189,193,5,34,0,0,190,192,8,3,0,0,191,190,1,0,0,0,192,
  	195,1,0,0,0,193,191,1,0,0,0,193,194,1,0,0,0,194,196,1,0,0,0,195,193,1,
  	0,0,0,196,197,5,34,0,0,197,52,1,0,0,0,198,202,7,4,0,0,199,201,7,5,0,0,
  	200,199,1,0,0,0,201,204,1,0,0,0,202,200,1,0,0,0,202,203,1,0,0,0,203,54,
  	1,0,0,0,204,202,1,0,0,0,205,207,5,13,0,0,206,205,1,0,0,0,206,207,1,0,
  	0,0,207,208,1,0,0,0,208,209,5,10,0,0,209,56,1,0,0,0,210,212,7,6,0,0,211,
  	210,1,0,0,0,212,213,1,0,0,0,213,211,1,0,0,0,213,214,1,0,0,0,214,215,1,
  	0,0,0,215,216,6,28,0,0,216,58,1,0,0,0,14,0,146,151,157,161,166,168,171,
  	176,187,193,202,206,213,1,6,0,0
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
