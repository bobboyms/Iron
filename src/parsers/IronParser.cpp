
// Generated from Iron.g4 by ANTLR 4.13.2


#include "IronListener.h"

#include "IronParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct IronParserStaticData final {
  IronParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IronParserStaticData(const IronParserStaticData&) = delete;
  IronParserStaticData(IronParserStaticData&&) = delete;
  IronParserStaticData& operator=(const IronParserStaticData&) = delete;
  IronParserStaticData& operator=(IronParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ironParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<IronParserStaticData> ironParserStaticData = nullptr;

void ironParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ironParserStaticData != nullptr) {
    return;
  }
#else
  assert(ironParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<IronParserStaticData>(
    std::vector<std::string>{
      "program", "importStatement", "qualifiedName", "statementList", "returnStatement", 
      "formatStatement", "formatArguments", "formatArgument", "externBlock", 
      "externFunctionDeclaration", "externFunctionArgs", "externFunctionArg", 
      "cTypes", "functionDeclaration", "arrowFunctionInline", "arrowFunctionBlock", 
      "functionSignature", "functionReturnType", "functionArgs", "functionArg", 
      "functionCall", "functionCallArgs", "functionCallArg", "varDeclaration", 
      "assignment", "varAssignment", "ifBlock", "ifStatement", "elseStatement", 
      "boolExpr", "expr", "number", "dataFormat", "varTypes"
    },
    std::vector<std::string>{
      "", "'f'('", "'extern'", "'...'", "", "", "','", "':'", "'='", "';'", 
      "'.'", "'*'", "'{'", "'}'", "'('", "')'", "'+'", "'-'", "'/'", "'['", 
      "']'", "'->'", "'and'", "'or'", "'not'", "'=='", "'!='", "'<'", "'<='", 
      "'>'", "'>='", "'if'", "'fn'", "'let'", "'else'", "'public'", "'import'", 
      "'return'", "'int'", "'char'", "'float'", "'string'", "'boolean'", 
      "'double'", "'void'"
    },
    std::vector<std::string>{
      "", "", "", "", "LINE_COMMENT", "BLOCK_COMMENT", "COMMA", "COLON", 
      "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", "R_CURLY", "L_PAREN", 
      "R_PAREN", "PLUS", "MINUS", "DIV", "L_BRACKET", "R_BRACKET", "ARROW", 
      "AND", "OR", "NOT", "EQEQ", "NEQ", "LT", "LTE", "GT", "GTE", "IF", 
      "FUNCTION", "LET", "ELSE", "PUBLIC", "IMPORT", "RETURN", "TYPE_INT", 
      "TYPE_CHAR", "TYPE_FLOAT", "TYPE_STRING", "TYPE_BOOLEAN", "TYPE_DOUBLE", 
      "TYPE_VOID", "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", 
      "IDENTIFIER", "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,361,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,1,0,5,0,70,8,0,10,
  	0,12,0,73,9,0,1,0,3,0,76,8,0,1,0,5,0,79,8,0,10,0,12,0,82,9,0,1,0,1,0,
  	1,1,1,1,1,1,1,1,3,1,90,8,1,1,2,1,2,1,2,5,2,95,8,2,10,2,12,2,98,9,2,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,107,8,3,10,3,12,3,110,9,3,1,4,1,4,1,4,1,
  	4,1,4,3,4,117,8,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,5,6,128,8,6,10,
  	6,12,6,131,9,6,1,7,1,7,1,7,1,7,1,7,3,7,138,8,7,1,8,1,8,1,8,1,8,4,8,144,
  	8,8,11,8,12,8,145,5,8,148,8,8,10,8,12,8,151,9,8,1,8,1,8,1,9,1,9,1,9,1,
  	9,3,9,159,8,9,1,9,1,9,3,9,163,8,9,1,9,1,9,3,9,167,8,9,1,10,1,10,1,10,
  	5,10,172,8,10,10,10,12,10,175,9,10,1,11,1,11,1,11,3,11,180,8,11,1,11,
  	1,11,1,12,1,12,1,13,3,13,187,8,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,3,16,208,
  	8,16,1,16,1,16,3,16,212,8,16,1,17,1,17,1,17,1,18,1,18,1,18,5,18,220,8,
  	18,10,18,12,18,223,9,18,1,19,1,19,1,19,1,19,3,19,229,8,19,1,19,3,19,232,
  	8,19,1,20,1,20,1,20,3,20,237,8,20,1,20,1,20,1,21,1,21,1,21,5,21,244,8,
  	21,10,21,12,21,247,9,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,
  	257,8,22,1,23,1,23,1,23,1,23,1,23,3,23,264,8,23,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,3,24,274,8,24,1,25,1,25,1,25,1,25,1,25,1,25,3,25,282,
  	8,25,1,26,1,26,3,26,286,8,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,27,3,27,297,8,27,1,28,1,28,3,28,301,8,28,1,29,1,29,1,29,1,29,1,29,1,
  	29,1,29,1,29,1,29,1,29,1,29,1,29,3,29,315,8,29,1,29,1,29,1,29,1,29,1,
  	29,1,29,5,29,323,8,29,10,29,12,29,326,9,29,1,30,1,30,1,30,1,30,1,30,1,
  	30,1,30,1,30,3,30,336,8,30,1,30,1,30,1,30,3,30,341,8,30,1,30,1,30,1,30,
  	1,30,3,30,347,8,30,1,30,5,30,350,8,30,10,30,12,30,353,9,30,1,31,1,31,
  	1,32,1,32,1,33,1,33,1,33,0,2,58,60,34,0,2,4,6,8,10,12,14,16,18,20,22,
  	24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,0,6,
  	2,0,38,40,42,44,1,0,22,23,1,0,25,30,1,0,45,46,1,0,45,48,2,0,32,32,38,
  	43,394,0,71,1,0,0,0,2,85,1,0,0,0,4,91,1,0,0,0,6,108,1,0,0,0,8,111,1,0,
  	0,0,10,118,1,0,0,0,12,124,1,0,0,0,14,137,1,0,0,0,16,139,1,0,0,0,18,154,
  	1,0,0,0,20,168,1,0,0,0,22,176,1,0,0,0,24,183,1,0,0,0,26,186,1,0,0,0,28,
  	195,1,0,0,0,30,199,1,0,0,0,32,205,1,0,0,0,34,213,1,0,0,0,36,216,1,0,0,
  	0,38,224,1,0,0,0,40,233,1,0,0,0,42,240,1,0,0,0,44,248,1,0,0,0,46,258,
  	1,0,0,0,48,265,1,0,0,0,50,275,1,0,0,0,52,283,1,0,0,0,54,289,1,0,0,0,56,
  	300,1,0,0,0,58,314,1,0,0,0,60,335,1,0,0,0,62,354,1,0,0,0,64,356,1,0,0,
  	0,66,358,1,0,0,0,68,70,3,2,1,0,69,68,1,0,0,0,70,73,1,0,0,0,71,69,1,0,
  	0,0,71,72,1,0,0,0,72,75,1,0,0,0,73,71,1,0,0,0,74,76,3,16,8,0,75,74,1,
  	0,0,0,75,76,1,0,0,0,76,80,1,0,0,0,77,79,3,26,13,0,78,77,1,0,0,0,79,82,
  	1,0,0,0,80,78,1,0,0,0,80,81,1,0,0,0,81,83,1,0,0,0,82,80,1,0,0,0,83,84,
  	5,0,0,1,84,1,1,0,0,0,85,86,5,36,0,0,86,89,3,4,2,0,87,88,5,10,0,0,88,90,
  	5,11,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,3,1,0,0,0,91,96,5,49,0,0,92,93,
  	5,10,0,0,93,95,5,49,0,0,94,92,1,0,0,0,95,98,1,0,0,0,96,94,1,0,0,0,96,
  	97,1,0,0,0,97,5,1,0,0,0,98,96,1,0,0,0,99,107,3,46,23,0,100,107,3,40,20,
  	0,101,107,3,50,25,0,102,107,3,60,30,0,103,107,3,58,29,0,104,107,3,54,
  	27,0,105,107,3,8,4,0,106,99,1,0,0,0,106,100,1,0,0,0,106,101,1,0,0,0,106,
  	102,1,0,0,0,106,103,1,0,0,0,106,104,1,0,0,0,106,105,1,0,0,0,107,110,1,
  	0,0,0,108,106,1,0,0,0,108,109,1,0,0,0,109,7,1,0,0,0,110,108,1,0,0,0,111,
  	116,5,37,0,0,112,117,3,64,32,0,113,117,5,49,0,0,114,117,3,40,20,0,115,
  	117,3,60,30,0,116,112,1,0,0,0,116,113,1,0,0,0,116,114,1,0,0,0,116,115,
  	1,0,0,0,117,9,1,0,0,0,118,119,5,1,0,0,119,120,5,48,0,0,120,121,5,6,0,
  	0,121,122,3,12,6,0,122,123,5,15,0,0,123,11,1,0,0,0,124,129,3,14,7,0,125,
  	126,5,6,0,0,126,128,3,14,7,0,127,125,1,0,0,0,128,131,1,0,0,0,129,127,
  	1,0,0,0,129,130,1,0,0,0,130,13,1,0,0,0,131,129,1,0,0,0,132,138,3,64,32,
  	0,133,138,5,49,0,0,134,138,3,40,20,0,135,138,3,60,30,0,136,138,5,48,0,
  	0,137,132,1,0,0,0,137,133,1,0,0,0,137,134,1,0,0,0,137,135,1,0,0,0,137,
  	136,1,0,0,0,138,15,1,0,0,0,139,140,5,2,0,0,140,141,5,49,0,0,141,149,5,
  	12,0,0,142,144,3,18,9,0,143,142,1,0,0,0,144,145,1,0,0,0,145,143,1,0,0,
  	0,145,146,1,0,0,0,146,148,1,0,0,0,147,143,1,0,0,0,148,151,1,0,0,0,149,
  	147,1,0,0,0,149,150,1,0,0,0,150,152,1,0,0,0,151,149,1,0,0,0,152,153,5,
  	13,0,0,153,17,1,0,0,0,154,155,5,32,0,0,155,156,5,49,0,0,156,158,5,14,
  	0,0,157,159,3,20,10,0,158,157,1,0,0,0,158,159,1,0,0,0,159,162,1,0,0,0,
  	160,161,5,6,0,0,161,163,5,3,0,0,162,160,1,0,0,0,162,163,1,0,0,0,163,164,
  	1,0,0,0,164,166,5,15,0,0,165,167,3,34,17,0,166,165,1,0,0,0,166,167,1,
  	0,0,0,167,19,1,0,0,0,168,173,3,22,11,0,169,170,5,6,0,0,170,172,3,22,11,
  	0,171,169,1,0,0,0,172,175,1,0,0,0,173,171,1,0,0,0,173,174,1,0,0,0,174,
  	21,1,0,0,0,175,173,1,0,0,0,176,177,5,49,0,0,177,179,5,7,0,0,178,180,5,
  	11,0,0,179,178,1,0,0,0,179,180,1,0,0,0,180,181,1,0,0,0,181,182,3,24,12,
  	0,182,23,1,0,0,0,183,184,7,0,0,0,184,25,1,0,0,0,185,187,5,35,0,0,186,
  	185,1,0,0,0,186,187,1,0,0,0,187,188,1,0,0,0,188,189,5,32,0,0,189,190,
  	5,49,0,0,190,191,3,32,16,0,191,192,5,12,0,0,192,193,3,6,3,0,193,194,5,
  	13,0,0,194,27,1,0,0,0,195,196,3,32,16,0,196,197,5,21,0,0,197,198,3,60,
  	30,0,198,29,1,0,0,0,199,200,3,32,16,0,200,201,5,21,0,0,201,202,5,12,0,
  	0,202,203,3,6,3,0,203,204,5,13,0,0,204,31,1,0,0,0,205,207,5,14,0,0,206,
  	208,3,36,18,0,207,206,1,0,0,0,207,208,1,0,0,0,208,209,1,0,0,0,209,211,
  	5,15,0,0,210,212,3,34,17,0,211,210,1,0,0,0,211,212,1,0,0,0,212,33,1,0,
  	0,0,213,214,5,7,0,0,214,215,3,66,33,0,215,35,1,0,0,0,216,221,3,38,19,
  	0,217,218,5,6,0,0,218,220,3,38,19,0,219,217,1,0,0,0,220,223,1,0,0,0,221,
  	219,1,0,0,0,221,222,1,0,0,0,222,37,1,0,0,0,223,221,1,0,0,0,224,225,5,
  	49,0,0,225,228,5,7,0,0,226,229,3,66,33,0,227,229,3,32,16,0,228,226,1,
  	0,0,0,228,227,1,0,0,0,229,231,1,0,0,0,230,232,3,48,24,0,231,230,1,0,0,
  	0,231,232,1,0,0,0,232,39,1,0,0,0,233,234,5,49,0,0,234,236,5,14,0,0,235,
  	237,3,42,21,0,236,235,1,0,0,0,236,237,1,0,0,0,237,238,1,0,0,0,238,239,
  	5,15,0,0,239,41,1,0,0,0,240,245,3,44,22,0,241,242,5,6,0,0,242,244,3,44,
  	22,0,243,241,1,0,0,0,244,247,1,0,0,0,245,243,1,0,0,0,245,246,1,0,0,0,
  	246,43,1,0,0,0,247,245,1,0,0,0,248,249,5,49,0,0,249,256,5,7,0,0,250,257,
  	3,64,32,0,251,257,5,49,0,0,252,257,3,40,20,0,253,257,3,10,5,0,254,257,
  	3,28,14,0,255,257,3,30,15,0,256,250,1,0,0,0,256,251,1,0,0,0,256,252,1,
  	0,0,0,256,253,1,0,0,0,256,254,1,0,0,0,256,255,1,0,0,0,257,45,1,0,0,0,
  	258,259,5,33,0,0,259,260,5,49,0,0,260,261,5,7,0,0,261,263,3,66,33,0,262,
  	264,3,48,24,0,263,262,1,0,0,0,263,264,1,0,0,0,264,47,1,0,0,0,265,273,
  	5,8,0,0,266,274,3,28,14,0,267,274,3,30,15,0,268,274,5,49,0,0,269,274,
  	3,64,32,0,270,274,3,40,20,0,271,274,3,60,30,0,272,274,3,58,29,0,273,266,
  	1,0,0,0,273,267,1,0,0,0,273,268,1,0,0,0,273,269,1,0,0,0,273,270,1,0,0,
  	0,273,271,1,0,0,0,273,272,1,0,0,0,274,49,1,0,0,0,275,276,5,49,0,0,276,
  	281,5,8,0,0,277,282,3,28,14,0,278,282,3,30,15,0,279,282,3,64,32,0,280,
  	282,3,60,30,0,281,277,1,0,0,0,281,278,1,0,0,0,281,279,1,0,0,0,281,280,
  	1,0,0,0,282,51,1,0,0,0,283,285,5,12,0,0,284,286,3,6,3,0,285,284,1,0,0,
  	0,285,286,1,0,0,0,286,287,1,0,0,0,287,288,5,13,0,0,288,53,1,0,0,0,289,
  	290,5,31,0,0,290,291,5,14,0,0,291,292,3,58,29,0,292,293,5,15,0,0,293,
  	296,3,52,26,0,294,295,5,34,0,0,295,297,3,56,28,0,296,294,1,0,0,0,296,
  	297,1,0,0,0,297,55,1,0,0,0,298,301,3,54,27,0,299,301,3,52,26,0,300,298,
  	1,0,0,0,300,299,1,0,0,0,301,57,1,0,0,0,302,303,6,29,-1,0,303,315,3,62,
  	31,0,304,315,5,49,0,0,305,306,5,14,0,0,306,307,3,58,29,0,307,308,5,15,
  	0,0,308,315,1,0,0,0,309,310,5,24,0,0,310,315,3,58,29,4,311,315,5,47,0,
  	0,312,315,3,40,20,0,313,315,3,60,30,0,314,302,1,0,0,0,314,304,1,0,0,0,
  	314,305,1,0,0,0,314,309,1,0,0,0,314,311,1,0,0,0,314,312,1,0,0,0,314,313,
  	1,0,0,0,315,324,1,0,0,0,316,317,10,9,0,0,317,318,7,1,0,0,318,323,3,58,
  	29,10,319,320,10,8,0,0,320,321,7,2,0,0,321,323,3,58,29,9,322,316,1,0,
  	0,0,322,319,1,0,0,0,323,326,1,0,0,0,324,322,1,0,0,0,324,325,1,0,0,0,325,
  	59,1,0,0,0,326,324,1,0,0,0,327,328,6,30,-1,0,328,336,3,62,31,0,329,336,
  	3,40,20,0,330,336,5,49,0,0,331,332,5,14,0,0,332,333,3,60,30,0,333,334,
  	5,15,0,0,334,336,1,0,0,0,335,327,1,0,0,0,335,329,1,0,0,0,335,330,1,0,
  	0,0,335,331,1,0,0,0,336,351,1,0,0,0,337,340,10,6,0,0,338,341,5,11,0,0,
  	339,341,5,18,0,0,340,338,1,0,0,0,340,339,1,0,0,0,341,342,1,0,0,0,342,
  	350,3,60,30,7,343,346,10,5,0,0,344,347,5,16,0,0,345,347,5,17,0,0,346,
  	344,1,0,0,0,346,345,1,0,0,0,347,348,1,0,0,0,348,350,3,60,30,6,349,337,
  	1,0,0,0,349,343,1,0,0,0,350,353,1,0,0,0,351,349,1,0,0,0,351,352,1,0,0,
  	0,352,61,1,0,0,0,353,351,1,0,0,0,354,355,7,3,0,0,355,63,1,0,0,0,356,357,
  	7,4,0,0,357,65,1,0,0,0,358,359,7,5,0,0,359,67,1,0,0,0,40,71,75,80,89,
  	96,106,108,116,129,137,145,149,158,162,166,173,179,186,207,211,221,228,
  	231,236,245,256,263,273,281,285,296,300,314,322,324,335,340,346,349,351
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ironParserStaticData = std::move(staticData);
}

}

IronParser::IronParser(TokenStream *input) : IronParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

IronParser::IronParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  IronParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ironParserStaticData->atn, ironParserStaticData->decisionToDFA, ironParserStaticData->sharedContextCache, options);
}

IronParser::~IronParser() {
  delete _interpreter;
}

const atn::ATN& IronParser::getATN() const {
  return *ironParserStaticData->atn;
}

std::string IronParser::getGrammarFileName() const {
  return "Iron.g4";
}

const std::vector<std::string>& IronParser::getRuleNames() const {
  return ironParserStaticData->ruleNames;
}

const dfa::Vocabulary& IronParser::getVocabulary() const {
  return ironParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IronParser::getSerializedATN() const {
  return ironParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

IronParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ProgramContext::EOF() {
  return getToken(IronParser::EOF, 0);
}

std::vector<IronParser::ImportStatementContext *> IronParser::ProgramContext::importStatement() {
  return getRuleContexts<IronParser::ImportStatementContext>();
}

IronParser::ImportStatementContext* IronParser::ProgramContext::importStatement(size_t i) {
  return getRuleContext<IronParser::ImportStatementContext>(i);
}

IronParser::ExternBlockContext* IronParser::ProgramContext::externBlock() {
  return getRuleContext<IronParser::ExternBlockContext>(0);
}

std::vector<IronParser::FunctionDeclarationContext *> IronParser::ProgramContext::functionDeclaration() {
  return getRuleContexts<IronParser::FunctionDeclarationContext>();
}

IronParser::FunctionDeclarationContext* IronParser::ProgramContext::functionDeclaration(size_t i) {
  return getRuleContext<IronParser::FunctionDeclarationContext>(i);
}


size_t IronParser::ProgramContext::getRuleIndex() const {
  return IronParser::RuleProgram;
}

void IronParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void IronParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

IronParser::ProgramContext* IronParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, IronParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::IMPORT) {
      setState(68);
      importStatement();
      setState(73);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(75);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::T__1) {
      setState(74);
      externBlock();
    }
    setState(80);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::FUNCTION

    || _la == IronParser::PUBLIC) {
      setState(77);
      functionDeclaration();
      setState(82);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(83);
    match(IronParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

IronParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ImportStatementContext::IMPORT() {
  return getToken(IronParser::IMPORT, 0);
}

IronParser::QualifiedNameContext* IronParser::ImportStatementContext::qualifiedName() {
  return getRuleContext<IronParser::QualifiedNameContext>(0);
}

tree::TerminalNode* IronParser::ImportStatementContext::DOT() {
  return getToken(IronParser::DOT, 0);
}

tree::TerminalNode* IronParser::ImportStatementContext::STAR() {
  return getToken(IronParser::STAR, 0);
}


size_t IronParser::ImportStatementContext::getRuleIndex() const {
  return IronParser::RuleImportStatement;
}

void IronParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void IronParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}

IronParser::ImportStatementContext* IronParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 2, IronParser::RuleImportStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(IronParser::IMPORT);
    setState(86);
    qualifiedName();
    setState(89);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::DOT) {
      setState(87);
      match(IronParser::DOT);
      setState(88);
      match(IronParser::STAR);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedNameContext ------------------------------------------------------------------

IronParser::QualifiedNameContext::QualifiedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> IronParser::QualifiedNameContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::QualifiedNameContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> IronParser::QualifiedNameContext::DOT() {
  return getTokens(IronParser::DOT);
}

tree::TerminalNode* IronParser::QualifiedNameContext::DOT(size_t i) {
  return getToken(IronParser::DOT, i);
}


size_t IronParser::QualifiedNameContext::getRuleIndex() const {
  return IronParser::RuleQualifiedName;
}

void IronParser::QualifiedNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualifiedName(this);
}

void IronParser::QualifiedNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualifiedName(this);
}

IronParser::QualifiedNameContext* IronParser::qualifiedName() {
  QualifiedNameContext *_localctx = _tracker.createInstance<QualifiedNameContext>(_ctx, getState());
  enterRule(_localctx, 4, IronParser::RuleQualifiedName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(IronParser::IDENTIFIER);
    setState(96);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(92);
        match(IronParser::DOT);
        setState(93);
        match(IronParser::IDENTIFIER); 
      }
      setState(98);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementListContext ------------------------------------------------------------------

IronParser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::VarDeclarationContext *> IronParser::StatementListContext::varDeclaration() {
  return getRuleContexts<IronParser::VarDeclarationContext>();
}

IronParser::VarDeclarationContext* IronParser::StatementListContext::varDeclaration(size_t i) {
  return getRuleContext<IronParser::VarDeclarationContext>(i);
}

std::vector<IronParser::FunctionCallContext *> IronParser::StatementListContext::functionCall() {
  return getRuleContexts<IronParser::FunctionCallContext>();
}

IronParser::FunctionCallContext* IronParser::StatementListContext::functionCall(size_t i) {
  return getRuleContext<IronParser::FunctionCallContext>(i);
}

std::vector<IronParser::VarAssignmentContext *> IronParser::StatementListContext::varAssignment() {
  return getRuleContexts<IronParser::VarAssignmentContext>();
}

IronParser::VarAssignmentContext* IronParser::StatementListContext::varAssignment(size_t i) {
  return getRuleContext<IronParser::VarAssignmentContext>(i);
}

std::vector<IronParser::ExprContext *> IronParser::StatementListContext::expr() {
  return getRuleContexts<IronParser::ExprContext>();
}

IronParser::ExprContext* IronParser::StatementListContext::expr(size_t i) {
  return getRuleContext<IronParser::ExprContext>(i);
}

std::vector<IronParser::BoolExprContext *> IronParser::StatementListContext::boolExpr() {
  return getRuleContexts<IronParser::BoolExprContext>();
}

IronParser::BoolExprContext* IronParser::StatementListContext::boolExpr(size_t i) {
  return getRuleContext<IronParser::BoolExprContext>(i);
}

std::vector<IronParser::IfStatementContext *> IronParser::StatementListContext::ifStatement() {
  return getRuleContexts<IronParser::IfStatementContext>();
}

IronParser::IfStatementContext* IronParser::StatementListContext::ifStatement(size_t i) {
  return getRuleContext<IronParser::IfStatementContext>(i);
}

std::vector<IronParser::ReturnStatementContext *> IronParser::StatementListContext::returnStatement() {
  return getRuleContexts<IronParser::ReturnStatementContext>();
}

IronParser::ReturnStatementContext* IronParser::StatementListContext::returnStatement(size_t i) {
  return getRuleContext<IronParser::ReturnStatementContext>(i);
}


size_t IronParser::StatementListContext::getRuleIndex() const {
  return IronParser::RuleStatementList;
}

void IronParser::StatementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementList(this);
}

void IronParser::StatementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementList(this);
}

IronParser::StatementListContext* IronParser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 6, IronParser::RuleStatementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 809388751208448) != 0)) {
      setState(106);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(99);
        varDeclaration();
        break;
      }

      case 2: {
        setState(100);
        functionCall();
        break;
      }

      case 3: {
        setState(101);
        varAssignment();
        break;
      }

      case 4: {
        setState(102);
        expr(0);
        break;
      }

      case 5: {
        setState(103);
        boolExpr(0);
        break;
      }

      case 6: {
        setState(104);
        ifStatement();
        break;
      }

      case 7: {
        setState(105);
        returnStatement();
        break;
      }

      default:
        break;
      }
      setState(110);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

IronParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ReturnStatementContext::RETURN() {
  return getToken(IronParser::RETURN, 0);
}

IronParser::DataFormatContext* IronParser::ReturnStatementContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::FunctionCallContext* IronParser::ReturnStatementContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ExprContext* IronParser::ReturnStatementContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

tree::TerminalNode* IronParser::ReturnStatementContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}


size_t IronParser::ReturnStatementContext::getRuleIndex() const {
  return IronParser::RuleReturnStatement;
}

void IronParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void IronParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}

IronParser::ReturnStatementContext* IronParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 8, IronParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    match(IronParser::RETURN);
    setState(116);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(112);
      dataFormat();
      break;
    }

    case 2: {
      setState(113);
      antlrcpp::downCast<ReturnStatementContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(114);
      functionCall();
      break;
    }

    case 4: {
      setState(115);
      expr(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormatStatementContext ------------------------------------------------------------------

IronParser::FormatStatementContext::FormatStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FormatStatementContext::STRING_LITERAL() {
  return getToken(IronParser::STRING_LITERAL, 0);
}

tree::TerminalNode* IronParser::FormatStatementContext::COMMA() {
  return getToken(IronParser::COMMA, 0);
}

tree::TerminalNode* IronParser::FormatStatementContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

IronParser::FormatArgumentsContext* IronParser::FormatStatementContext::formatArguments() {
  return getRuleContext<IronParser::FormatArgumentsContext>(0);
}


size_t IronParser::FormatStatementContext::getRuleIndex() const {
  return IronParser::RuleFormatStatement;
}

void IronParser::FormatStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormatStatement(this);
}

void IronParser::FormatStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormatStatement(this);
}

IronParser::FormatStatementContext* IronParser::formatStatement() {
  FormatStatementContext *_localctx = _tracker.createInstance<FormatStatementContext>(_ctx, getState());
  enterRule(_localctx, 10, IronParser::RuleFormatStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    match(IronParser::T__0);
    setState(119);
    match(IronParser::STRING_LITERAL);
    setState(120);
    match(IronParser::COMMA);

    setState(121);
    formatArguments();
    setState(122);
    match(IronParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormatArgumentsContext ------------------------------------------------------------------

IronParser::FormatArgumentsContext::FormatArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::FormatArgumentContext *> IronParser::FormatArgumentsContext::formatArgument() {
  return getRuleContexts<IronParser::FormatArgumentContext>();
}

IronParser::FormatArgumentContext* IronParser::FormatArgumentsContext::formatArgument(size_t i) {
  return getRuleContext<IronParser::FormatArgumentContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::FormatArgumentsContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::FormatArgumentsContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::FormatArgumentsContext::getRuleIndex() const {
  return IronParser::RuleFormatArguments;
}

void IronParser::FormatArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormatArguments(this);
}

void IronParser::FormatArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormatArguments(this);
}

IronParser::FormatArgumentsContext* IronParser::formatArguments() {
  FormatArgumentsContext *_localctx = _tracker.createInstance<FormatArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 12, IronParser::RuleFormatArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    formatArgument();
    setState(129);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(125);
      match(IronParser::COMMA);
      setState(126);
      formatArgument();
      setState(131);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormatArgumentContext ------------------------------------------------------------------

IronParser::FormatArgumentContext::FormatArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::DataFormatContext* IronParser::FormatArgumentContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::FunctionCallContext* IronParser::FormatArgumentContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ExprContext* IronParser::FormatArgumentContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

tree::TerminalNode* IronParser::FormatArgumentContext::STRING_LITERAL() {
  return getToken(IronParser::STRING_LITERAL, 0);
}

tree::TerminalNode* IronParser::FormatArgumentContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}


size_t IronParser::FormatArgumentContext::getRuleIndex() const {
  return IronParser::RuleFormatArgument;
}

void IronParser::FormatArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormatArgument(this);
}

void IronParser::FormatArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormatArgument(this);
}

IronParser::FormatArgumentContext* IronParser::formatArgument() {
  FormatArgumentContext *_localctx = _tracker.createInstance<FormatArgumentContext>(_ctx, getState());
  enterRule(_localctx, 14, IronParser::RuleFormatArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(132);
      dataFormat();
      break;
    }

    case 2: {
      setState(133);
      antlrcpp::downCast<FormatArgumentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(134);
      functionCall();
      break;
    }

    case 4: {
      setState(135);
      expr(0);
      break;
    }

    case 5: {
      setState(136);
      match(IronParser::STRING_LITERAL);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternBlockContext ------------------------------------------------------------------

IronParser::ExternBlockContext::ExternBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ExternBlockContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

tree::TerminalNode* IronParser::ExternBlockContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

tree::TerminalNode* IronParser::ExternBlockContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

std::vector<IronParser::ExternFunctionDeclarationContext *> IronParser::ExternBlockContext::externFunctionDeclaration() {
  return getRuleContexts<IronParser::ExternFunctionDeclarationContext>();
}

IronParser::ExternFunctionDeclarationContext* IronParser::ExternBlockContext::externFunctionDeclaration(size_t i) {
  return getRuleContext<IronParser::ExternFunctionDeclarationContext>(i);
}


size_t IronParser::ExternBlockContext::getRuleIndex() const {
  return IronParser::RuleExternBlock;
}

void IronParser::ExternBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternBlock(this);
}

void IronParser::ExternBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternBlock(this);
}

IronParser::ExternBlockContext* IronParser::externBlock() {
  ExternBlockContext *_localctx = _tracker.createInstance<ExternBlockContext>(_ctx, getState());
  enterRule(_localctx, 16, IronParser::RuleExternBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(139);
    match(IronParser::T__1);
    setState(140);
    antlrcpp::downCast<ExternBlockContext *>(_localctx)->language = match(IronParser::IDENTIFIER);
    setState(141);
    match(IronParser::L_CURLY);
    setState(149);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::FUNCTION) {
      setState(143); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(142);
                externFunctionDeclaration();
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(145); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(151);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(152);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternFunctionDeclarationContext ------------------------------------------------------------------

IronParser::ExternFunctionDeclarationContext::ExternFunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::FUNCTION() {
  return getToken(IronParser::FUNCTION, 0);
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::ExternFunctionArgsContext* IronParser::ExternFunctionDeclarationContext::externFunctionArgs() {
  return getRuleContext<IronParser::ExternFunctionArgsContext>(0);
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::COMMA() {
  return getToken(IronParser::COMMA, 0);
}

IronParser::FunctionReturnTypeContext* IronParser::ExternFunctionDeclarationContext::functionReturnType() {
  return getRuleContext<IronParser::FunctionReturnTypeContext>(0);
}


size_t IronParser::ExternFunctionDeclarationContext::getRuleIndex() const {
  return IronParser::RuleExternFunctionDeclaration;
}

void IronParser::ExternFunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternFunctionDeclaration(this);
}

void IronParser::ExternFunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternFunctionDeclaration(this);
}

IronParser::ExternFunctionDeclarationContext* IronParser::externFunctionDeclaration() {
  ExternFunctionDeclarationContext *_localctx = _tracker.createInstance<ExternFunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 18, IronParser::RuleExternFunctionDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    match(IronParser::FUNCTION);
    setState(155);
    antlrcpp::downCast<ExternFunctionDeclarationContext *>(_localctx)->exterFunctionName = match(IronParser::IDENTIFIER);
    setState(156);
    match(IronParser::L_PAREN);
    setState(158);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(157);
      externFunctionArgs();
    }
    setState(162);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COMMA) {
      setState(160);
      match(IronParser::COMMA);
      setState(161);
      antlrcpp::downCast<ExternFunctionDeclarationContext *>(_localctx)->varied = match(IronParser::T__2);
    }
    setState(164);
    match(IronParser::R_PAREN);
    setState(166);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COLON) {
      setState(165);
      functionReturnType();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternFunctionArgsContext ------------------------------------------------------------------

IronParser::ExternFunctionArgsContext::ExternFunctionArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::ExternFunctionArgContext *> IronParser::ExternFunctionArgsContext::externFunctionArg() {
  return getRuleContexts<IronParser::ExternFunctionArgContext>();
}

IronParser::ExternFunctionArgContext* IronParser::ExternFunctionArgsContext::externFunctionArg(size_t i) {
  return getRuleContext<IronParser::ExternFunctionArgContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::ExternFunctionArgsContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::ExternFunctionArgsContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::ExternFunctionArgsContext::getRuleIndex() const {
  return IronParser::RuleExternFunctionArgs;
}

void IronParser::ExternFunctionArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternFunctionArgs(this);
}

void IronParser::ExternFunctionArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternFunctionArgs(this);
}

IronParser::ExternFunctionArgsContext* IronParser::externFunctionArgs() {
  ExternFunctionArgsContext *_localctx = _tracker.createInstance<ExternFunctionArgsContext>(_ctx, getState());
  enterRule(_localctx, 20, IronParser::RuleExternFunctionArgs);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(168);
    externFunctionArg();
    setState(173);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(169);
        match(IronParser::COMMA);
        setState(170);
        externFunctionArg(); 
      }
      setState(175);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternFunctionArgContext ------------------------------------------------------------------

IronParser::ExternFunctionArgContext::ExternFunctionArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ExternFunctionArgContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

IronParser::CTypesContext* IronParser::ExternFunctionArgContext::cTypes() {
  return getRuleContext<IronParser::CTypesContext>(0);
}

tree::TerminalNode* IronParser::ExternFunctionArgContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::ExternFunctionArgContext::STAR() {
  return getToken(IronParser::STAR, 0);
}


size_t IronParser::ExternFunctionArgContext::getRuleIndex() const {
  return IronParser::RuleExternFunctionArg;
}

void IronParser::ExternFunctionArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternFunctionArg(this);
}

void IronParser::ExternFunctionArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternFunctionArg(this);
}

IronParser::ExternFunctionArgContext* IronParser::externFunctionArg() {
  ExternFunctionArgContext *_localctx = _tracker.createInstance<ExternFunctionArgContext>(_ctx, getState());
  enterRule(_localctx, 22, IronParser::RuleExternFunctionArg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    antlrcpp::downCast<ExternFunctionArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(177);
    match(IronParser::COLON);
    setState(179);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::STAR) {
      setState(178);
      antlrcpp::downCast<ExternFunctionArgContext *>(_localctx)->ptr = match(IronParser::STAR);
    }
    setState(181);
    cTypes();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CTypesContext ------------------------------------------------------------------

IronParser::CTypesContext::CTypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_BOOLEAN() {
  return getToken(IronParser::TYPE_BOOLEAN, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_CHAR() {
  return getToken(IronParser::TYPE_CHAR, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_DOUBLE() {
  return getToken(IronParser::TYPE_DOUBLE, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_FLOAT() {
  return getToken(IronParser::TYPE_FLOAT, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_INT() {
  return getToken(IronParser::TYPE_INT, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_VOID() {
  return getToken(IronParser::TYPE_VOID, 0);
}


size_t IronParser::CTypesContext::getRuleIndex() const {
  return IronParser::RuleCTypes;
}

void IronParser::CTypesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCTypes(this);
}

void IronParser::CTypesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCTypes(this);
}

IronParser::CTypesContext* IronParser::cTypes() {
  CTypesContext *_localctx = _tracker.createInstance<CTypesContext>(_ctx, getState());
  enterRule(_localctx, 24, IronParser::RuleCTypes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 32710470926336) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

IronParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::FUNCTION() {
  return getToken(IronParser::FUNCTION, 0);
}

IronParser::FunctionSignatureContext* IronParser::FunctionDeclarationContext::functionSignature() {
  return getRuleContext<IronParser::FunctionSignatureContext>(0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

IronParser::StatementListContext* IronParser::FunctionDeclarationContext::statementList() {
  return getRuleContext<IronParser::StatementListContext>(0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::PUBLIC() {
  return getToken(IronParser::PUBLIC, 0);
}


size_t IronParser::FunctionDeclarationContext::getRuleIndex() const {
  return IronParser::RuleFunctionDeclaration;
}

void IronParser::FunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDeclaration(this);
}

void IronParser::FunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDeclaration(this);
}

IronParser::FunctionDeclarationContext* IronParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 26, IronParser::RuleFunctionDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::PUBLIC) {
      setState(185);
      match(IronParser::PUBLIC);
    }
    setState(188);
    match(IronParser::FUNCTION);
    setState(189);
    antlrcpp::downCast<FunctionDeclarationContext *>(_localctx)->functionName = match(IronParser::IDENTIFIER);
    setState(190);
    functionSignature();
    setState(191);
    match(IronParser::L_CURLY);
    setState(192);
    statementList();
    setState(193);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionInlineContext ------------------------------------------------------------------

IronParser::ArrowFunctionInlineContext::ArrowFunctionInlineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::FunctionSignatureContext* IronParser::ArrowFunctionInlineContext::functionSignature() {
  return getRuleContext<IronParser::FunctionSignatureContext>(0);
}

tree::TerminalNode* IronParser::ArrowFunctionInlineContext::ARROW() {
  return getToken(IronParser::ARROW, 0);
}

IronParser::ExprContext* IronParser::ArrowFunctionInlineContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}


size_t IronParser::ArrowFunctionInlineContext::getRuleIndex() const {
  return IronParser::RuleArrowFunctionInline;
}

void IronParser::ArrowFunctionInlineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunctionInline(this);
}

void IronParser::ArrowFunctionInlineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunctionInline(this);
}

IronParser::ArrowFunctionInlineContext* IronParser::arrowFunctionInline() {
  ArrowFunctionInlineContext *_localctx = _tracker.createInstance<ArrowFunctionInlineContext>(_ctx, getState());
  enterRule(_localctx, 28, IronParser::RuleArrowFunctionInline);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    functionSignature();
    setState(196);
    match(IronParser::ARROW);
    setState(197);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionBlockContext ------------------------------------------------------------------

IronParser::ArrowFunctionBlockContext::ArrowFunctionBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::FunctionSignatureContext* IronParser::ArrowFunctionBlockContext::functionSignature() {
  return getRuleContext<IronParser::FunctionSignatureContext>(0);
}

tree::TerminalNode* IronParser::ArrowFunctionBlockContext::ARROW() {
  return getToken(IronParser::ARROW, 0);
}

tree::TerminalNode* IronParser::ArrowFunctionBlockContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

IronParser::StatementListContext* IronParser::ArrowFunctionBlockContext::statementList() {
  return getRuleContext<IronParser::StatementListContext>(0);
}

tree::TerminalNode* IronParser::ArrowFunctionBlockContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}


size_t IronParser::ArrowFunctionBlockContext::getRuleIndex() const {
  return IronParser::RuleArrowFunctionBlock;
}

void IronParser::ArrowFunctionBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunctionBlock(this);
}

void IronParser::ArrowFunctionBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunctionBlock(this);
}

IronParser::ArrowFunctionBlockContext* IronParser::arrowFunctionBlock() {
  ArrowFunctionBlockContext *_localctx = _tracker.createInstance<ArrowFunctionBlockContext>(_ctx, getState());
  enterRule(_localctx, 30, IronParser::RuleArrowFunctionBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    functionSignature();
    setState(200);
    match(IronParser::ARROW);
    setState(201);
    match(IronParser::L_CURLY);
    setState(202);
    statementList();
    setState(203);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionSignatureContext ------------------------------------------------------------------

IronParser::FunctionSignatureContext::FunctionSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionSignatureContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

tree::TerminalNode* IronParser::FunctionSignatureContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

IronParser::FunctionArgsContext* IronParser::FunctionSignatureContext::functionArgs() {
  return getRuleContext<IronParser::FunctionArgsContext>(0);
}

IronParser::FunctionReturnTypeContext* IronParser::FunctionSignatureContext::functionReturnType() {
  return getRuleContext<IronParser::FunctionReturnTypeContext>(0);
}


size_t IronParser::FunctionSignatureContext::getRuleIndex() const {
  return IronParser::RuleFunctionSignature;
}

void IronParser::FunctionSignatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionSignature(this);
}

void IronParser::FunctionSignatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionSignature(this);
}

IronParser::FunctionSignatureContext* IronParser::functionSignature() {
  FunctionSignatureContext *_localctx = _tracker.createInstance<FunctionSignatureContext>(_ctx, getState());
  enterRule(_localctx, 32, IronParser::RuleFunctionSignature);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(205);
    match(IronParser::L_PAREN);
    setState(207);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(206);
      functionArgs();
    }
    setState(209);
    match(IronParser::R_PAREN);
    setState(211);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COLON) {
      setState(210);
      functionReturnType();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionReturnTypeContext ------------------------------------------------------------------

IronParser::FunctionReturnTypeContext::FunctionReturnTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionReturnTypeContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

IronParser::VarTypesContext* IronParser::FunctionReturnTypeContext::varTypes() {
  return getRuleContext<IronParser::VarTypesContext>(0);
}


size_t IronParser::FunctionReturnTypeContext::getRuleIndex() const {
  return IronParser::RuleFunctionReturnType;
}

void IronParser::FunctionReturnTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionReturnType(this);
}

void IronParser::FunctionReturnTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionReturnType(this);
}

IronParser::FunctionReturnTypeContext* IronParser::functionReturnType() {
  FunctionReturnTypeContext *_localctx = _tracker.createInstance<FunctionReturnTypeContext>(_ctx, getState());
  enterRule(_localctx, 34, IronParser::RuleFunctionReturnType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(213);
    match(IronParser::COLON);
    setState(214);
    varTypes();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionArgsContext ------------------------------------------------------------------

IronParser::FunctionArgsContext::FunctionArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::FunctionArgContext *> IronParser::FunctionArgsContext::functionArg() {
  return getRuleContexts<IronParser::FunctionArgContext>();
}

IronParser::FunctionArgContext* IronParser::FunctionArgsContext::functionArg(size_t i) {
  return getRuleContext<IronParser::FunctionArgContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::FunctionArgsContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::FunctionArgsContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::FunctionArgsContext::getRuleIndex() const {
  return IronParser::RuleFunctionArgs;
}

void IronParser::FunctionArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArgs(this);
}

void IronParser::FunctionArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArgs(this);
}

IronParser::FunctionArgsContext* IronParser::functionArgs() {
  FunctionArgsContext *_localctx = _tracker.createInstance<FunctionArgsContext>(_ctx, getState());
  enterRule(_localctx, 36, IronParser::RuleFunctionArgs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
    functionArg();
    setState(221);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(217);
      match(IronParser::COMMA);
      setState(218);
      functionArg();
      setState(223);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionArgContext ------------------------------------------------------------------

IronParser::FunctionArgContext::FunctionArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionArgContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

tree::TerminalNode* IronParser::FunctionArgContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::VarTypesContext* IronParser::FunctionArgContext::varTypes() {
  return getRuleContext<IronParser::VarTypesContext>(0);
}

IronParser::FunctionSignatureContext* IronParser::FunctionArgContext::functionSignature() {
  return getRuleContext<IronParser::FunctionSignatureContext>(0);
}

IronParser::AssignmentContext* IronParser::FunctionArgContext::assignment() {
  return getRuleContext<IronParser::AssignmentContext>(0);
}


size_t IronParser::FunctionArgContext::getRuleIndex() const {
  return IronParser::RuleFunctionArg;
}

void IronParser::FunctionArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArg(this);
}

void IronParser::FunctionArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArg(this);
}

IronParser::FunctionArgContext* IronParser::functionArg() {
  FunctionArgContext *_localctx = _tracker.createInstance<FunctionArgContext>(_ctx, getState());
  enterRule(_localctx, 38, IronParser::RuleFunctionArg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(224);
    antlrcpp::downCast<FunctionArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(225);
    match(IronParser::COLON);
    setState(228);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::FUNCTION:
      case IronParser::TYPE_INT:
      case IronParser::TYPE_CHAR:
      case IronParser::TYPE_FLOAT:
      case IronParser::TYPE_STRING:
      case IronParser::TYPE_BOOLEAN:
      case IronParser::TYPE_DOUBLE: {
        setState(226);
        varTypes();
        break;
      }

      case IronParser::L_PAREN: {
        setState(227);
        functionSignature();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(231);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::EQ) {
      setState(230);
      assignment();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

IronParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionCallContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

tree::TerminalNode* IronParser::FunctionCallContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::FunctionCallContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::FunctionCallArgsContext* IronParser::FunctionCallContext::functionCallArgs() {
  return getRuleContext<IronParser::FunctionCallArgsContext>(0);
}


size_t IronParser::FunctionCallContext::getRuleIndex() const {
  return IronParser::RuleFunctionCall;
}

void IronParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void IronParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}

IronParser::FunctionCallContext* IronParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 40, IronParser::RuleFunctionCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(233);
    antlrcpp::downCast<FunctionCallContext *>(_localctx)->functionName = match(IronParser::IDENTIFIER);
    setState(234);
    match(IronParser::L_PAREN);
    setState(236);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(235);
      functionCallArgs();
    }
    setState(238);
    match(IronParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallArgsContext ------------------------------------------------------------------

IronParser::FunctionCallArgsContext::FunctionCallArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::FunctionCallArgContext *> IronParser::FunctionCallArgsContext::functionCallArg() {
  return getRuleContexts<IronParser::FunctionCallArgContext>();
}

IronParser::FunctionCallArgContext* IronParser::FunctionCallArgsContext::functionCallArg(size_t i) {
  return getRuleContext<IronParser::FunctionCallArgContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::FunctionCallArgsContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::FunctionCallArgsContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::FunctionCallArgsContext::getRuleIndex() const {
  return IronParser::RuleFunctionCallArgs;
}

void IronParser::FunctionCallArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallArgs(this);
}

void IronParser::FunctionCallArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallArgs(this);
}

IronParser::FunctionCallArgsContext* IronParser::functionCallArgs() {
  FunctionCallArgsContext *_localctx = _tracker.createInstance<FunctionCallArgsContext>(_ctx, getState());
  enterRule(_localctx, 42, IronParser::RuleFunctionCallArgs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(240);
    functionCallArg();
    setState(245);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(241);
      match(IronParser::COMMA);
      setState(242);
      functionCallArg();
      setState(247);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallArgContext ------------------------------------------------------------------

IronParser::FunctionCallArgContext::FunctionCallArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionCallArgContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

std::vector<tree::TerminalNode *> IronParser::FunctionCallArgContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::FunctionCallArgContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}

IronParser::DataFormatContext* IronParser::FunctionCallArgContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::FunctionCallContext* IronParser::FunctionCallArgContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::FormatStatementContext* IronParser::FunctionCallArgContext::formatStatement() {
  return getRuleContext<IronParser::FormatStatementContext>(0);
}

IronParser::ArrowFunctionInlineContext* IronParser::FunctionCallArgContext::arrowFunctionInline() {
  return getRuleContext<IronParser::ArrowFunctionInlineContext>(0);
}

IronParser::ArrowFunctionBlockContext* IronParser::FunctionCallArgContext::arrowFunctionBlock() {
  return getRuleContext<IronParser::ArrowFunctionBlockContext>(0);
}


size_t IronParser::FunctionCallArgContext::getRuleIndex() const {
  return IronParser::RuleFunctionCallArg;
}

void IronParser::FunctionCallArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallArg(this);
}

void IronParser::FunctionCallArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallArg(this);
}

IronParser::FunctionCallArgContext* IronParser::functionCallArg() {
  FunctionCallArgContext *_localctx = _tracker.createInstance<FunctionCallArgContext>(_ctx, getState());
  enterRule(_localctx, 44, IronParser::RuleFunctionCallArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(248);
    antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(249);
    match(IronParser::COLON);
    setState(256);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(250);
      dataFormat();
      break;
    }

    case 2: {
      setState(251);
      antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->anotherVarName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(252);
      functionCall();
      break;
    }

    case 4: {
      setState(253);
      formatStatement();
      break;
    }

    case 5: {
      setState(254);
      arrowFunctionInline();
      break;
    }

    case 6: {
      setState(255);
      arrowFunctionBlock();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclarationContext ------------------------------------------------------------------

IronParser::VarDeclarationContext::VarDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::VarDeclarationContext::LET() {
  return getToken(IronParser::LET, 0);
}

tree::TerminalNode* IronParser::VarDeclarationContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

IronParser::VarTypesContext* IronParser::VarDeclarationContext::varTypes() {
  return getRuleContext<IronParser::VarTypesContext>(0);
}

tree::TerminalNode* IronParser::VarDeclarationContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::AssignmentContext* IronParser::VarDeclarationContext::assignment() {
  return getRuleContext<IronParser::AssignmentContext>(0);
}


size_t IronParser::VarDeclarationContext::getRuleIndex() const {
  return IronParser::RuleVarDeclaration;
}

void IronParser::VarDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDeclaration(this);
}

void IronParser::VarDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDeclaration(this);
}

IronParser::VarDeclarationContext* IronParser::varDeclaration() {
  VarDeclarationContext *_localctx = _tracker.createInstance<VarDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 46, IronParser::RuleVarDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
    match(IronParser::LET);
    setState(259);
    antlrcpp::downCast<VarDeclarationContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(260);
    match(IronParser::COLON);
    setState(261);
    varTypes();
    setState(263);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::EQ) {
      setState(262);
      assignment();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

IronParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::AssignmentContext::EQ() {
  return getToken(IronParser::EQ, 0);
}

IronParser::ArrowFunctionInlineContext* IronParser::AssignmentContext::arrowFunctionInline() {
  return getRuleContext<IronParser::ArrowFunctionInlineContext>(0);
}

IronParser::ArrowFunctionBlockContext* IronParser::AssignmentContext::arrowFunctionBlock() {
  return getRuleContext<IronParser::ArrowFunctionBlockContext>(0);
}

IronParser::DataFormatContext* IronParser::AssignmentContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::FunctionCallContext* IronParser::AssignmentContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ExprContext* IronParser::AssignmentContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

IronParser::BoolExprContext* IronParser::AssignmentContext::boolExpr() {
  return getRuleContext<IronParser::BoolExprContext>(0);
}

tree::TerminalNode* IronParser::AssignmentContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}


size_t IronParser::AssignmentContext::getRuleIndex() const {
  return IronParser::RuleAssignment;
}

void IronParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void IronParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}

IronParser::AssignmentContext* IronParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 48, IronParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(265);
    match(IronParser::EQ);
    setState(273);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      setState(266);
      arrowFunctionInline();
      break;
    }

    case 2: {
      setState(267);
      arrowFunctionBlock();
      break;
    }

    case 3: {
      setState(268);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 4: {
      setState(269);
      dataFormat();
      break;
    }

    case 5: {
      setState(270);
      functionCall();
      break;
    }

    case 6: {
      setState(271);
      expr(0);
      break;
    }

    case 7: {
      setState(272);
      boolExpr(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarAssignmentContext ------------------------------------------------------------------

IronParser::VarAssignmentContext::VarAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::VarAssignmentContext::EQ() {
  return getToken(IronParser::EQ, 0);
}

tree::TerminalNode* IronParser::VarAssignmentContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::ArrowFunctionInlineContext* IronParser::VarAssignmentContext::arrowFunctionInline() {
  return getRuleContext<IronParser::ArrowFunctionInlineContext>(0);
}

IronParser::ArrowFunctionBlockContext* IronParser::VarAssignmentContext::arrowFunctionBlock() {
  return getRuleContext<IronParser::ArrowFunctionBlockContext>(0);
}

IronParser::DataFormatContext* IronParser::VarAssignmentContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::ExprContext* IronParser::VarAssignmentContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}


size_t IronParser::VarAssignmentContext::getRuleIndex() const {
  return IronParser::RuleVarAssignment;
}

void IronParser::VarAssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarAssignment(this);
}

void IronParser::VarAssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarAssignment(this);
}

IronParser::VarAssignmentContext* IronParser::varAssignment() {
  VarAssignmentContext *_localctx = _tracker.createInstance<VarAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 50, IronParser::RuleVarAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275);
    antlrcpp::downCast<VarAssignmentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(276);
    match(IronParser::EQ);
    setState(281);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      setState(277);
      arrowFunctionInline();
      break;
    }

    case 2: {
      setState(278);
      arrowFunctionBlock();
      break;
    }

    case 3: {
      setState(279);
      dataFormat();
      break;
    }

    case 4: {
      setState(280);
      expr(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfBlockContext ------------------------------------------------------------------

IronParser::IfBlockContext::IfBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::IfBlockContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

tree::TerminalNode* IronParser::IfBlockContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

IronParser::StatementListContext* IronParser::IfBlockContext::statementList() {
  return getRuleContext<IronParser::StatementListContext>(0);
}


size_t IronParser::IfBlockContext::getRuleIndex() const {
  return IronParser::RuleIfBlock;
}

void IronParser::IfBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfBlock(this);
}

void IronParser::IfBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfBlock(this);
}

IronParser::IfBlockContext* IronParser::ifBlock() {
  IfBlockContext *_localctx = _tracker.createInstance<IfBlockContext>(_ctx, getState());
  enterRule(_localctx, 52, IronParser::RuleIfBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(283);
    match(IronParser::L_CURLY);
    setState(285);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      setState(284);
      statementList();
      break;
    }

    default:
      break;
    }
    setState(287);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

IronParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::IfStatementContext::IF() {
  return getToken(IronParser::IF, 0);
}

tree::TerminalNode* IronParser::IfStatementContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

IronParser::BoolExprContext* IronParser::IfStatementContext::boolExpr() {
  return getRuleContext<IronParser::BoolExprContext>(0);
}

tree::TerminalNode* IronParser::IfStatementContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

IronParser::IfBlockContext* IronParser::IfStatementContext::ifBlock() {
  return getRuleContext<IronParser::IfBlockContext>(0);
}

tree::TerminalNode* IronParser::IfStatementContext::ELSE() {
  return getToken(IronParser::ELSE, 0);
}

IronParser::ElseStatementContext* IronParser::IfStatementContext::elseStatement() {
  return getRuleContext<IronParser::ElseStatementContext>(0);
}


size_t IronParser::IfStatementContext::getRuleIndex() const {
  return IronParser::RuleIfStatement;
}

void IronParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void IronParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}

IronParser::IfStatementContext* IronParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 54, IronParser::RuleIfStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(289);
    match(IronParser::IF);
    setState(290);
    match(IronParser::L_PAREN);
    setState(291);
    boolExpr(0);
    setState(292);
    match(IronParser::R_PAREN);
    setState(293);
    ifBlock();
    setState(296);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::ELSE) {
      setState(294);
      match(IronParser::ELSE);
      setState(295);
      elseStatement();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseStatementContext ------------------------------------------------------------------

IronParser::ElseStatementContext::ElseStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::IfStatementContext* IronParser::ElseStatementContext::ifStatement() {
  return getRuleContext<IronParser::IfStatementContext>(0);
}

IronParser::IfBlockContext* IronParser::ElseStatementContext::ifBlock() {
  return getRuleContext<IronParser::IfBlockContext>(0);
}


size_t IronParser::ElseStatementContext::getRuleIndex() const {
  return IronParser::RuleElseStatement;
}

void IronParser::ElseStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseStatement(this);
}

void IronParser::ElseStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseStatement(this);
}

IronParser::ElseStatementContext* IronParser::elseStatement() {
  ElseStatementContext *_localctx = _tracker.createInstance<ElseStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, IronParser::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(300);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::IF: {
        enterOuterAlt(_localctx, 1);
        setState(298);
        ifStatement();
        break;
      }

      case IronParser::L_CURLY: {
        enterOuterAlt(_localctx, 2);
        setState(299);
        ifBlock();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BoolExprContext ------------------------------------------------------------------

IronParser::BoolExprContext::BoolExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::NumberContext* IronParser::BoolExprContext::number() {
  return getRuleContext<IronParser::NumberContext>(0);
}

tree::TerminalNode* IronParser::BoolExprContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

std::vector<IronParser::BoolExprContext *> IronParser::BoolExprContext::boolExpr() {
  return getRuleContexts<IronParser::BoolExprContext>();
}

IronParser::BoolExprContext* IronParser::BoolExprContext::boolExpr(size_t i) {
  return getRuleContext<IronParser::BoolExprContext>(i);
}

tree::TerminalNode* IronParser::BoolExprContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::NOT() {
  return getToken(IronParser::NOT, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::BOOLEAN_VALUE() {
  return getToken(IronParser::BOOLEAN_VALUE, 0);
}

IronParser::FunctionCallContext* IronParser::BoolExprContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ExprContext* IronParser::BoolExprContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

tree::TerminalNode* IronParser::BoolExprContext::OR() {
  return getToken(IronParser::OR, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::AND() {
  return getToken(IronParser::AND, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::EQEQ() {
  return getToken(IronParser::EQEQ, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::NEQ() {
  return getToken(IronParser::NEQ, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::LT() {
  return getToken(IronParser::LT, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::LTE() {
  return getToken(IronParser::LTE, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::GT() {
  return getToken(IronParser::GT, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::GTE() {
  return getToken(IronParser::GTE, 0);
}


size_t IronParser::BoolExprContext::getRuleIndex() const {
  return IronParser::RuleBoolExpr;
}

void IronParser::BoolExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolExpr(this);
}

void IronParser::BoolExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolExpr(this);
}


IronParser::BoolExprContext* IronParser::boolExpr() {
   return boolExpr(0);
}

IronParser::BoolExprContext* IronParser::boolExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  IronParser::BoolExprContext *_localctx = _tracker.createInstance<BoolExprContext>(_ctx, parentState);
  IronParser::BoolExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, IronParser::RuleBoolExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(314);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      setState(303);
      number();
      break;
    }

    case 2: {
      setState(304);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(305);
      match(IronParser::L_PAREN);
      setState(306);
      boolExpr(0);
      setState(307);
      match(IronParser::R_PAREN);
      break;
    }

    case 4: {
      setState(309);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->not_ = match(IronParser::NOT);
      setState(310);
      boolExpr(4);
      break;
    }

    case 5: {
      setState(311);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->booleanValue = match(IronParser::BOOLEAN_VALUE);
      break;
    }

    case 6: {
      setState(312);
      functionCall();
      break;
    }

    case 7: {
      setState(313);
      expr(0);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(324);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(322);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(316);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(317);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == IronParser::AND

          || _la == IronParser::OR)) {
            antlrcpp::downCast<BoolExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(318);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(319);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(320);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 2113929216) != 0))) {
            antlrcpp::downCast<BoolExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(321);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(9);
          break;
        }

        default:
          break;
        } 
      }
      setState(326);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

IronParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::NumberContext* IronParser::ExprContext::number() {
  return getRuleContext<IronParser::NumberContext>(0);
}

IronParser::FunctionCallContext* IronParser::ExprContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

tree::TerminalNode* IronParser::ExprContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::ExprContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

std::vector<IronParser::ExprContext *> IronParser::ExprContext::expr() {
  return getRuleContexts<IronParser::ExprContext>();
}

IronParser::ExprContext* IronParser::ExprContext::expr(size_t i) {
  return getRuleContext<IronParser::ExprContext>(i);
}

tree::TerminalNode* IronParser::ExprContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::ExprContext::STAR() {
  return getToken(IronParser::STAR, 0);
}

tree::TerminalNode* IronParser::ExprContext::DIV() {
  return getToken(IronParser::DIV, 0);
}

tree::TerminalNode* IronParser::ExprContext::PLUS() {
  return getToken(IronParser::PLUS, 0);
}

tree::TerminalNode* IronParser::ExprContext::MINUS() {
  return getToken(IronParser::MINUS, 0);
}


size_t IronParser::ExprContext::getRuleIndex() const {
  return IronParser::RuleExpr;
}

void IronParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void IronParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


IronParser::ExprContext* IronParser::expr() {
   return expr(0);
}

IronParser::ExprContext* IronParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  IronParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  IronParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, IronParser::RuleExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(335);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      setState(328);
      number();
      break;
    }

    case 2: {
      setState(329);
      functionCall();
      break;
    }

    case 3: {
      setState(330);
      antlrcpp::downCast<ExprContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 4: {
      setState(331);
      match(IronParser::L_PAREN);
      setState(332);
      expr(0);
      setState(333);
      match(IronParser::R_PAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(351);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(349);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(337);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(340);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case IronParser::STAR: {
              setState(338);
              antlrcpp::downCast<ExprContext *>(_localctx)->mult = match(IronParser::STAR);
              break;
            }

            case IronParser::DIV: {
              setState(339);
              antlrcpp::downCast<ExprContext *>(_localctx)->div = match(IronParser::DIV);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(342);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(343);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(346);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case IronParser::PLUS: {
              setState(344);
              antlrcpp::downCast<ExprContext *>(_localctx)->plus = match(IronParser::PLUS);
              break;
            }

            case IronParser::MINUS: {
              setState(345);
              antlrcpp::downCast<ExprContext *>(_localctx)->minus = match(IronParser::MINUS);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(348);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(353);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

IronParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::NumberContext::REAL_NUMBER() {
  return getToken(IronParser::REAL_NUMBER, 0);
}

tree::TerminalNode* IronParser::NumberContext::INT_NUMBER() {
  return getToken(IronParser::INT_NUMBER, 0);
}


size_t IronParser::NumberContext::getRuleIndex() const {
  return IronParser::RuleNumber;
}

void IronParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void IronParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

IronParser::NumberContext* IronParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 62, IronParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(354);
    _la = _input->LA(1);
    if (!(_la == IronParser::REAL_NUMBER

    || _la == IronParser::INT_NUMBER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DataFormatContext ------------------------------------------------------------------

IronParser::DataFormatContext::DataFormatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::DataFormatContext::REAL_NUMBER() {
  return getToken(IronParser::REAL_NUMBER, 0);
}

tree::TerminalNode* IronParser::DataFormatContext::INT_NUMBER() {
  return getToken(IronParser::INT_NUMBER, 0);
}

tree::TerminalNode* IronParser::DataFormatContext::BOOLEAN_VALUE() {
  return getToken(IronParser::BOOLEAN_VALUE, 0);
}

tree::TerminalNode* IronParser::DataFormatContext::STRING_LITERAL() {
  return getToken(IronParser::STRING_LITERAL, 0);
}


size_t IronParser::DataFormatContext::getRuleIndex() const {
  return IronParser::RuleDataFormat;
}

void IronParser::DataFormatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDataFormat(this);
}

void IronParser::DataFormatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDataFormat(this);
}

IronParser::DataFormatContext* IronParser::dataFormat() {
  DataFormatContext *_localctx = _tracker.createInstance<DataFormatContext>(_ctx, getState());
  enterRule(_localctx, 64, IronParser::RuleDataFormat);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(356);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 527765581332480) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarTypesContext ------------------------------------------------------------------

IronParser::VarTypesContext::VarTypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_BOOLEAN() {
  return getToken(IronParser::TYPE_BOOLEAN, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_CHAR() {
  return getToken(IronParser::TYPE_CHAR, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_DOUBLE() {
  return getToken(IronParser::TYPE_DOUBLE, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_FLOAT() {
  return getToken(IronParser::TYPE_FLOAT, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_INT() {
  return getToken(IronParser::TYPE_INT, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_STRING() {
  return getToken(IronParser::TYPE_STRING, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::FUNCTION() {
  return getToken(IronParser::FUNCTION, 0);
}


size_t IronParser::VarTypesContext::getRuleIndex() const {
  return IronParser::RuleVarTypes;
}

void IronParser::VarTypesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarTypes(this);
}

void IronParser::VarTypesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarTypes(this);
}

IronParser::VarTypesContext* IronParser::varTypes() {
  VarTypesContext *_localctx = _tracker.createInstance<VarTypesContext>(_ctx, getState());
  enterRule(_localctx, 66, IronParser::RuleVarTypes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(358);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17321603104768) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool IronParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 29: return boolExprSempred(antlrcpp::downCast<BoolExprContext *>(context), predicateIndex);
    case 30: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool IronParser::boolExprSempred(BoolExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 9);
    case 1: return precpred(_ctx, 8);

  default:
    break;
  }
  return true;
}

bool IronParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

void IronParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ironParserInitialize();
#else
  ::antlr4::internal::call_once(ironParserOnceFlag, ironParserInitialize);
#endif
}
