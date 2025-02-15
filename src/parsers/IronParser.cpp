
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
      "boolExpr", "primary", "expr", "number", "dataFormat", "varTypes"
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
  	4,1,51,374,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,1,0,5,
  	0,72,8,0,10,0,12,0,75,9,0,1,0,3,0,78,8,0,1,0,5,0,81,8,0,10,0,12,0,84,
  	9,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,92,8,1,1,2,1,2,1,2,5,2,97,8,2,10,2,12,
  	2,100,9,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,109,8,3,10,3,12,3,112,9,3,1,
  	4,1,4,1,4,1,4,1,4,3,4,119,8,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,5,6,
  	130,8,6,10,6,12,6,133,9,6,1,7,1,7,1,7,1,7,1,7,3,7,140,8,7,1,8,1,8,1,8,
  	1,8,4,8,146,8,8,11,8,12,8,147,5,8,150,8,8,10,8,12,8,153,9,8,1,8,1,8,1,
  	9,1,9,1,9,1,9,3,9,161,8,9,1,9,1,9,3,9,165,8,9,1,9,1,9,3,9,169,8,9,1,10,
  	1,10,1,10,5,10,174,8,10,10,10,12,10,177,9,10,1,11,1,11,1,11,3,11,182,
  	8,11,1,11,1,11,1,12,1,12,1,13,3,13,189,8,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,
  	3,16,210,8,16,1,16,1,16,3,16,214,8,16,1,17,1,17,1,17,1,18,1,18,1,18,5,
  	18,222,8,18,10,18,12,18,225,9,18,1,19,1,19,1,19,1,19,3,19,231,8,19,1,
  	19,3,19,234,8,19,1,20,1,20,1,20,3,20,239,8,20,1,20,1,20,1,21,1,21,1,21,
  	5,21,246,8,21,10,21,12,21,249,9,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,
  	1,22,3,22,259,8,22,1,23,1,23,1,23,1,23,1,23,3,23,266,8,23,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,3,24,276,8,24,1,25,1,25,1,25,1,25,1,25,1,
  	25,3,25,284,8,25,1,26,1,26,3,26,288,8,26,1,26,1,26,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,3,27,299,8,27,1,28,1,28,3,28,303,8,28,1,29,1,29,1,29,1,
  	29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,3,29,317,8,29,1,29,1,29,1,
  	29,1,29,1,29,1,29,5,29,325,8,29,10,29,12,29,328,9,29,1,30,1,30,1,30,1,
  	30,1,30,1,30,1,30,1,30,1,30,3,30,339,8,30,1,31,1,31,1,31,1,31,1,31,1,
  	31,1,31,1,31,3,31,349,8,31,1,31,1,31,1,31,3,31,354,8,31,1,31,1,31,1,31,
  	1,31,3,31,360,8,31,1,31,5,31,363,8,31,10,31,12,31,366,9,31,1,32,1,32,
  	1,33,1,33,1,34,1,34,1,34,0,2,58,62,35,0,2,4,6,8,10,12,14,16,18,20,22,
  	24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,
  	0,6,2,0,38,40,42,44,1,0,22,23,1,0,25,30,1,0,45,46,1,0,45,48,2,0,32,32,
  	38,43,411,0,73,1,0,0,0,2,87,1,0,0,0,4,93,1,0,0,0,6,110,1,0,0,0,8,113,
  	1,0,0,0,10,120,1,0,0,0,12,126,1,0,0,0,14,139,1,0,0,0,16,141,1,0,0,0,18,
  	156,1,0,0,0,20,170,1,0,0,0,22,178,1,0,0,0,24,185,1,0,0,0,26,188,1,0,0,
  	0,28,197,1,0,0,0,30,201,1,0,0,0,32,207,1,0,0,0,34,215,1,0,0,0,36,218,
  	1,0,0,0,38,226,1,0,0,0,40,235,1,0,0,0,42,242,1,0,0,0,44,250,1,0,0,0,46,
  	260,1,0,0,0,48,267,1,0,0,0,50,277,1,0,0,0,52,285,1,0,0,0,54,291,1,0,0,
  	0,56,302,1,0,0,0,58,316,1,0,0,0,60,338,1,0,0,0,62,348,1,0,0,0,64,367,
  	1,0,0,0,66,369,1,0,0,0,68,371,1,0,0,0,70,72,3,2,1,0,71,70,1,0,0,0,72,
  	75,1,0,0,0,73,71,1,0,0,0,73,74,1,0,0,0,74,77,1,0,0,0,75,73,1,0,0,0,76,
  	78,3,16,8,0,77,76,1,0,0,0,77,78,1,0,0,0,78,82,1,0,0,0,79,81,3,26,13,0,
  	80,79,1,0,0,0,81,84,1,0,0,0,82,80,1,0,0,0,82,83,1,0,0,0,83,85,1,0,0,0,
  	84,82,1,0,0,0,85,86,5,0,0,1,86,1,1,0,0,0,87,88,5,36,0,0,88,91,3,4,2,0,
  	89,90,5,10,0,0,90,92,5,11,0,0,91,89,1,0,0,0,91,92,1,0,0,0,92,3,1,0,0,
  	0,93,98,5,49,0,0,94,95,5,10,0,0,95,97,5,49,0,0,96,94,1,0,0,0,97,100,1,
  	0,0,0,98,96,1,0,0,0,98,99,1,0,0,0,99,5,1,0,0,0,100,98,1,0,0,0,101,109,
  	3,46,23,0,102,109,3,40,20,0,103,109,3,50,25,0,104,109,3,62,31,0,105,109,
  	3,58,29,0,106,109,3,54,27,0,107,109,3,8,4,0,108,101,1,0,0,0,108,102,1,
  	0,0,0,108,103,1,0,0,0,108,104,1,0,0,0,108,105,1,0,0,0,108,106,1,0,0,0,
  	108,107,1,0,0,0,109,112,1,0,0,0,110,108,1,0,0,0,110,111,1,0,0,0,111,7,
  	1,0,0,0,112,110,1,0,0,0,113,118,5,37,0,0,114,119,3,66,33,0,115,119,5,
  	49,0,0,116,119,3,40,20,0,117,119,3,62,31,0,118,114,1,0,0,0,118,115,1,
  	0,0,0,118,116,1,0,0,0,118,117,1,0,0,0,119,9,1,0,0,0,120,121,5,1,0,0,121,
  	122,5,48,0,0,122,123,5,6,0,0,123,124,3,12,6,0,124,125,5,15,0,0,125,11,
  	1,0,0,0,126,131,3,14,7,0,127,128,5,6,0,0,128,130,3,14,7,0,129,127,1,0,
  	0,0,130,133,1,0,0,0,131,129,1,0,0,0,131,132,1,0,0,0,132,13,1,0,0,0,133,
  	131,1,0,0,0,134,140,3,66,33,0,135,140,5,49,0,0,136,140,3,40,20,0,137,
  	140,3,62,31,0,138,140,5,48,0,0,139,134,1,0,0,0,139,135,1,0,0,0,139,136,
  	1,0,0,0,139,137,1,0,0,0,139,138,1,0,0,0,140,15,1,0,0,0,141,142,5,2,0,
  	0,142,143,5,49,0,0,143,151,5,12,0,0,144,146,3,18,9,0,145,144,1,0,0,0,
  	146,147,1,0,0,0,147,145,1,0,0,0,147,148,1,0,0,0,148,150,1,0,0,0,149,145,
  	1,0,0,0,150,153,1,0,0,0,151,149,1,0,0,0,151,152,1,0,0,0,152,154,1,0,0,
  	0,153,151,1,0,0,0,154,155,5,13,0,0,155,17,1,0,0,0,156,157,5,32,0,0,157,
  	158,5,49,0,0,158,160,5,14,0,0,159,161,3,20,10,0,160,159,1,0,0,0,160,161,
  	1,0,0,0,161,164,1,0,0,0,162,163,5,6,0,0,163,165,5,3,0,0,164,162,1,0,0,
  	0,164,165,1,0,0,0,165,166,1,0,0,0,166,168,5,15,0,0,167,169,3,34,17,0,
  	168,167,1,0,0,0,168,169,1,0,0,0,169,19,1,0,0,0,170,175,3,22,11,0,171,
  	172,5,6,0,0,172,174,3,22,11,0,173,171,1,0,0,0,174,177,1,0,0,0,175,173,
  	1,0,0,0,175,176,1,0,0,0,176,21,1,0,0,0,177,175,1,0,0,0,178,179,5,49,0,
  	0,179,181,5,7,0,0,180,182,5,11,0,0,181,180,1,0,0,0,181,182,1,0,0,0,182,
  	183,1,0,0,0,183,184,3,24,12,0,184,23,1,0,0,0,185,186,7,0,0,0,186,25,1,
  	0,0,0,187,189,5,35,0,0,188,187,1,0,0,0,188,189,1,0,0,0,189,190,1,0,0,
  	0,190,191,5,32,0,0,191,192,5,49,0,0,192,193,3,32,16,0,193,194,5,12,0,
  	0,194,195,3,6,3,0,195,196,5,13,0,0,196,27,1,0,0,0,197,198,3,32,16,0,198,
  	199,5,21,0,0,199,200,3,62,31,0,200,29,1,0,0,0,201,202,3,32,16,0,202,203,
  	5,21,0,0,203,204,5,12,0,0,204,205,3,6,3,0,205,206,5,13,0,0,206,31,1,0,
  	0,0,207,209,5,14,0,0,208,210,3,36,18,0,209,208,1,0,0,0,209,210,1,0,0,
  	0,210,211,1,0,0,0,211,213,5,15,0,0,212,214,3,34,17,0,213,212,1,0,0,0,
  	213,214,1,0,0,0,214,33,1,0,0,0,215,216,5,7,0,0,216,217,3,68,34,0,217,
  	35,1,0,0,0,218,223,3,38,19,0,219,220,5,6,0,0,220,222,3,38,19,0,221,219,
  	1,0,0,0,222,225,1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,37,1,0,0,
  	0,225,223,1,0,0,0,226,227,5,49,0,0,227,230,5,7,0,0,228,231,3,68,34,0,
  	229,231,3,32,16,0,230,228,1,0,0,0,230,229,1,0,0,0,231,233,1,0,0,0,232,
  	234,3,48,24,0,233,232,1,0,0,0,233,234,1,0,0,0,234,39,1,0,0,0,235,236,
  	5,49,0,0,236,238,5,14,0,0,237,239,3,42,21,0,238,237,1,0,0,0,238,239,1,
  	0,0,0,239,240,1,0,0,0,240,241,5,15,0,0,241,41,1,0,0,0,242,247,3,44,22,
  	0,243,244,5,6,0,0,244,246,3,44,22,0,245,243,1,0,0,0,246,249,1,0,0,0,247,
  	245,1,0,0,0,247,248,1,0,0,0,248,43,1,0,0,0,249,247,1,0,0,0,250,251,5,
  	49,0,0,251,258,5,7,0,0,252,259,3,66,33,0,253,259,5,49,0,0,254,259,3,40,
  	20,0,255,259,3,10,5,0,256,259,3,28,14,0,257,259,3,30,15,0,258,252,1,0,
  	0,0,258,253,1,0,0,0,258,254,1,0,0,0,258,255,1,0,0,0,258,256,1,0,0,0,258,
  	257,1,0,0,0,259,45,1,0,0,0,260,261,5,33,0,0,261,262,5,49,0,0,262,263,
  	5,7,0,0,263,265,3,68,34,0,264,266,3,48,24,0,265,264,1,0,0,0,265,266,1,
  	0,0,0,266,47,1,0,0,0,267,275,5,8,0,0,268,276,3,28,14,0,269,276,3,30,15,
  	0,270,276,5,49,0,0,271,276,3,66,33,0,272,276,3,40,20,0,273,276,3,62,31,
  	0,274,276,3,58,29,0,275,268,1,0,0,0,275,269,1,0,0,0,275,270,1,0,0,0,275,
  	271,1,0,0,0,275,272,1,0,0,0,275,273,1,0,0,0,275,274,1,0,0,0,276,49,1,
  	0,0,0,277,278,5,49,0,0,278,283,5,8,0,0,279,284,3,28,14,0,280,284,3,30,
  	15,0,281,284,3,66,33,0,282,284,3,62,31,0,283,279,1,0,0,0,283,280,1,0,
  	0,0,283,281,1,0,0,0,283,282,1,0,0,0,284,51,1,0,0,0,285,287,5,12,0,0,286,
  	288,3,6,3,0,287,286,1,0,0,0,287,288,1,0,0,0,288,289,1,0,0,0,289,290,5,
  	13,0,0,290,53,1,0,0,0,291,292,5,31,0,0,292,293,5,14,0,0,293,294,3,58,
  	29,0,294,295,5,15,0,0,295,298,3,52,26,0,296,297,5,34,0,0,297,299,3,56,
  	28,0,298,296,1,0,0,0,298,299,1,0,0,0,299,55,1,0,0,0,300,303,3,54,27,0,
  	301,303,3,52,26,0,302,300,1,0,0,0,302,301,1,0,0,0,303,57,1,0,0,0,304,
  	305,6,29,-1,0,305,306,5,14,0,0,306,307,3,58,29,0,307,308,5,15,0,0,308,
  	317,1,0,0,0,309,310,5,24,0,0,310,317,3,58,29,8,311,317,5,47,0,0,312,317,
  	3,64,32,0,313,317,5,49,0,0,314,317,3,40,20,0,315,317,3,62,31,0,316,304,
  	1,0,0,0,316,309,1,0,0,0,316,311,1,0,0,0,316,312,1,0,0,0,316,313,1,0,0,
  	0,316,314,1,0,0,0,316,315,1,0,0,0,317,326,1,0,0,0,318,319,10,7,0,0,319,
  	320,7,1,0,0,320,325,3,58,29,8,321,322,10,6,0,0,322,323,7,2,0,0,323,325,
  	3,58,29,7,324,318,1,0,0,0,324,321,1,0,0,0,325,328,1,0,0,0,326,324,1,0,
  	0,0,326,327,1,0,0,0,327,59,1,0,0,0,328,326,1,0,0,0,329,339,3,64,32,0,
  	330,339,5,49,0,0,331,339,5,47,0,0,332,339,3,40,20,0,333,334,5,14,0,0,
  	334,335,3,58,29,0,335,336,5,15,0,0,336,339,1,0,0,0,337,339,3,62,31,0,
  	338,329,1,0,0,0,338,330,1,0,0,0,338,331,1,0,0,0,338,332,1,0,0,0,338,333,
  	1,0,0,0,338,337,1,0,0,0,339,61,1,0,0,0,340,341,6,31,-1,0,341,349,3,64,
  	32,0,342,349,3,40,20,0,343,349,5,49,0,0,344,345,5,14,0,0,345,346,3,62,
  	31,0,346,347,5,15,0,0,347,349,1,0,0,0,348,340,1,0,0,0,348,342,1,0,0,0,
  	348,343,1,0,0,0,348,344,1,0,0,0,349,364,1,0,0,0,350,353,10,6,0,0,351,
  	354,5,11,0,0,352,354,5,18,0,0,353,351,1,0,0,0,353,352,1,0,0,0,354,355,
  	1,0,0,0,355,363,3,62,31,7,356,359,10,5,0,0,357,360,5,16,0,0,358,360,5,
  	17,0,0,359,357,1,0,0,0,359,358,1,0,0,0,360,361,1,0,0,0,361,363,3,62,31,
  	6,362,350,1,0,0,0,362,356,1,0,0,0,363,366,1,0,0,0,364,362,1,0,0,0,364,
  	365,1,0,0,0,365,63,1,0,0,0,366,364,1,0,0,0,367,368,7,3,0,0,368,65,1,0,
  	0,0,369,370,7,4,0,0,370,67,1,0,0,0,371,372,7,5,0,0,372,69,1,0,0,0,41,
  	73,77,82,91,98,108,110,118,131,139,147,151,160,164,168,175,181,188,209,
  	213,223,230,233,238,247,258,265,275,283,287,298,302,316,324,326,338,348,
  	353,359,362,364
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
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::IMPORT) {
      setState(70);
      importStatement();
      setState(75);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(77);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::T__1) {
      setState(76);
      externBlock();
    }
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::FUNCTION

    || _la == IronParser::PUBLIC) {
      setState(79);
      functionDeclaration();
      setState(84);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(85);
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
    setState(87);
    match(IronParser::IMPORT);
    setState(88);
    qualifiedName();
    setState(91);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::DOT) {
      setState(89);
      match(IronParser::DOT);
      setState(90);
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
    setState(93);
    match(IronParser::IDENTIFIER);
    setState(98);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(94);
        match(IronParser::DOT);
        setState(95);
        match(IronParser::IDENTIFIER); 
      }
      setState(100);
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
    setState(110);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 809388751208448) != 0)) {
      setState(108);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(101);
        varDeclaration();
        break;
      }

      case 2: {
        setState(102);
        functionCall();
        break;
      }

      case 3: {
        setState(103);
        varAssignment();
        break;
      }

      case 4: {
        setState(104);
        expr(0);
        break;
      }

      case 5: {
        setState(105);
        boolExpr(0);
        break;
      }

      case 6: {
        setState(106);
        ifStatement();
        break;
      }

      case 7: {
        setState(107);
        returnStatement();
        break;
      }

      default:
        break;
      }
      setState(112);
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
    setState(113);
    match(IronParser::RETURN);
    setState(118);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(114);
      dataFormat();
      break;
    }

    case 2: {
      setState(115);
      antlrcpp::downCast<ReturnStatementContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(116);
      functionCall();
      break;
    }

    case 4: {
      setState(117);
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
    setState(120);
    match(IronParser::T__0);
    setState(121);
    match(IronParser::STRING_LITERAL);
    setState(122);
    match(IronParser::COMMA);

    setState(123);
    formatArguments();
    setState(124);
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
    setState(126);
    formatArgument();
    setState(131);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(127);
      match(IronParser::COMMA);
      setState(128);
      formatArgument();
      setState(133);
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
    setState(139);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(134);
      dataFormat();
      break;
    }

    case 2: {
      setState(135);
      antlrcpp::downCast<FormatArgumentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(136);
      functionCall();
      break;
    }

    case 4: {
      setState(137);
      expr(0);
      break;
    }

    case 5: {
      setState(138);
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
    setState(141);
    match(IronParser::T__1);
    setState(142);
    antlrcpp::downCast<ExternBlockContext *>(_localctx)->language = match(IronParser::IDENTIFIER);
    setState(143);
    match(IronParser::L_CURLY);
    setState(151);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::FUNCTION) {
      setState(145); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(144);
                externFunctionDeclaration();
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(147); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(153);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(154);
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
    setState(156);
    match(IronParser::FUNCTION);
    setState(157);
    antlrcpp::downCast<ExternFunctionDeclarationContext *>(_localctx)->exterFunctionName = match(IronParser::IDENTIFIER);
    setState(158);
    match(IronParser::L_PAREN);
    setState(160);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(159);
      externFunctionArgs();
    }
    setState(164);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COMMA) {
      setState(162);
      match(IronParser::COMMA);
      setState(163);
      antlrcpp::downCast<ExternFunctionDeclarationContext *>(_localctx)->varied = match(IronParser::T__2);
    }
    setState(166);
    match(IronParser::R_PAREN);
    setState(168);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COLON) {
      setState(167);
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
    setState(170);
    externFunctionArg();
    setState(175);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(171);
        match(IronParser::COMMA);
        setState(172);
        externFunctionArg(); 
      }
      setState(177);
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
    setState(178);
    antlrcpp::downCast<ExternFunctionArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(179);
    match(IronParser::COLON);
    setState(181);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::STAR) {
      setState(180);
      antlrcpp::downCast<ExternFunctionArgContext *>(_localctx)->ptr = match(IronParser::STAR);
    }
    setState(183);
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
    setState(185);
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
    setState(188);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::PUBLIC) {
      setState(187);
      match(IronParser::PUBLIC);
    }
    setState(190);
    match(IronParser::FUNCTION);
    setState(191);
    antlrcpp::downCast<FunctionDeclarationContext *>(_localctx)->functionName = match(IronParser::IDENTIFIER);
    setState(192);
    functionSignature();
    setState(193);
    match(IronParser::L_CURLY);
    setState(194);
    statementList();
    setState(195);
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
    setState(197);
    functionSignature();
    setState(198);
    match(IronParser::ARROW);
    setState(199);
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
    setState(201);
    functionSignature();
    setState(202);
    match(IronParser::ARROW);
    setState(203);
    match(IronParser::L_CURLY);
    setState(204);
    statementList();
    setState(205);
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
    setState(207);
    match(IronParser::L_PAREN);
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(208);
      functionArgs();
    }
    setState(211);
    match(IronParser::R_PAREN);
    setState(213);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COLON) {
      setState(212);
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
    setState(215);
    match(IronParser::COLON);
    setState(216);
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
    setState(218);
    functionArg();
    setState(223);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(219);
      match(IronParser::COMMA);
      setState(220);
      functionArg();
      setState(225);
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
    setState(226);
    antlrcpp::downCast<FunctionArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(227);
    match(IronParser::COLON);
    setState(230);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::FUNCTION:
      case IronParser::TYPE_INT:
      case IronParser::TYPE_CHAR:
      case IronParser::TYPE_FLOAT:
      case IronParser::TYPE_STRING:
      case IronParser::TYPE_BOOLEAN:
      case IronParser::TYPE_DOUBLE: {
        setState(228);
        varTypes();
        break;
      }

      case IronParser::L_PAREN: {
        setState(229);
        functionSignature();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(233);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::EQ) {
      setState(232);
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
    setState(235);
    antlrcpp::downCast<FunctionCallContext *>(_localctx)->functionName = match(IronParser::IDENTIFIER);
    setState(236);
    match(IronParser::L_PAREN);
    setState(238);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(237);
      functionCallArgs();
    }
    setState(240);
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
    setState(242);
    functionCallArg();
    setState(247);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(243);
      match(IronParser::COMMA);
      setState(244);
      functionCallArg();
      setState(249);
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
    setState(250);
    antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(251);
    match(IronParser::COLON);
    setState(258);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(252);
      dataFormat();
      break;
    }

    case 2: {
      setState(253);
      antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->anotherVarName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(254);
      functionCall();
      break;
    }

    case 4: {
      setState(255);
      formatStatement();
      break;
    }

    case 5: {
      setState(256);
      arrowFunctionInline();
      break;
    }

    case 6: {
      setState(257);
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
    setState(260);
    match(IronParser::LET);
    setState(261);
    antlrcpp::downCast<VarDeclarationContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(262);
    match(IronParser::COLON);
    setState(263);
    varTypes();
    setState(265);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::EQ) {
      setState(264);
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
    setState(267);
    match(IronParser::EQ);
    setState(275);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      setState(268);
      arrowFunctionInline();
      break;
    }

    case 2: {
      setState(269);
      arrowFunctionBlock();
      break;
    }

    case 3: {
      setState(270);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 4: {
      setState(271);
      dataFormat();
      break;
    }

    case 5: {
      setState(272);
      functionCall();
      break;
    }

    case 6: {
      setState(273);
      expr(0);
      break;
    }

    case 7: {
      setState(274);
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
    setState(277);
    antlrcpp::downCast<VarAssignmentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(278);
    match(IronParser::EQ);
    setState(283);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      setState(279);
      arrowFunctionInline();
      break;
    }

    case 2: {
      setState(280);
      arrowFunctionBlock();
      break;
    }

    case 3: {
      setState(281);
      dataFormat();
      break;
    }

    case 4: {
      setState(282);
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
    setState(285);
    match(IronParser::L_CURLY);
    setState(287);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      setState(286);
      statementList();
      break;
    }

    default:
      break;
    }
    setState(289);
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
    setState(291);
    match(IronParser::IF);
    setState(292);
    match(IronParser::L_PAREN);
    setState(293);
    boolExpr(0);
    setState(294);
    match(IronParser::R_PAREN);
    setState(295);
    ifBlock();
    setState(298);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::ELSE) {
      setState(296);
      match(IronParser::ELSE);
      setState(297);
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
    setState(302);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::IF: {
        enterOuterAlt(_localctx, 1);
        setState(300);
        ifStatement();
        break;
      }

      case IronParser::L_CURLY: {
        enterOuterAlt(_localctx, 2);
        setState(301);
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

IronParser::NumberContext* IronParser::BoolExprContext::number() {
  return getRuleContext<IronParser::NumberContext>(0);
}

tree::TerminalNode* IronParser::BoolExprContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
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
    setState(316);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      setState(305);
      match(IronParser::L_PAREN);
      setState(306);
      boolExpr(0);
      setState(307);
      match(IronParser::R_PAREN);
      break;
    }

    case 2: {
      setState(309);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->not_ = match(IronParser::NOT);
      setState(310);
      boolExpr(8);
      break;
    }

    case 3: {
      setState(311);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->booleanValue = match(IronParser::BOOLEAN_VALUE);
      break;
    }

    case 4: {
      setState(312);
      number();
      break;
    }

    case 5: {
      setState(313);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 6: {
      setState(314);
      functionCall();
      break;
    }

    case 7: {
      setState(315);
      expr(0);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(326);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(324);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(318);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(319);
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
          setState(320);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(321);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(322);
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
          setState(323);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(7);
          break;
        }

        default:
          break;
        } 
      }
      setState(328);
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

//----------------- PrimaryContext ------------------------------------------------------------------

IronParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::NumberContext* IronParser::PrimaryContext::number() {
  return getRuleContext<IronParser::NumberContext>(0);
}

tree::TerminalNode* IronParser::PrimaryContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::PrimaryContext::BOOLEAN_VALUE() {
  return getToken(IronParser::BOOLEAN_VALUE, 0);
}

IronParser::FunctionCallContext* IronParser::PrimaryContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

tree::TerminalNode* IronParser::PrimaryContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

IronParser::BoolExprContext* IronParser::PrimaryContext::boolExpr() {
  return getRuleContext<IronParser::BoolExprContext>(0);
}

tree::TerminalNode* IronParser::PrimaryContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

IronParser::ExprContext* IronParser::PrimaryContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}


size_t IronParser::PrimaryContext::getRuleIndex() const {
  return IronParser::RulePrimary;
}

void IronParser::PrimaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimary(this);
}

void IronParser::PrimaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimary(this);
}

IronParser::PrimaryContext* IronParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 60, IronParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(338);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(329);
      number();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(330);
      match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(331);
      match(IronParser::BOOLEAN_VALUE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(332);
      functionCall();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(333);
      match(IronParser::L_PAREN);
      setState(334);
      boolExpr(0);
      setState(335);
      match(IronParser::R_PAREN);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(337);
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
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, IronParser::RuleExpr, precedence);

    

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
    setState(348);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      setState(341);
      number();
      break;
    }

    case 2: {
      setState(342);
      functionCall();
      break;
    }

    case 3: {
      setState(343);
      antlrcpp::downCast<ExprContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 4: {
      setState(344);
      match(IronParser::L_PAREN);
      setState(345);
      expr(0);
      setState(346);
      match(IronParser::R_PAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(364);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(362);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(350);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(353);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case IronParser::STAR: {
              setState(351);
              antlrcpp::downCast<ExprContext *>(_localctx)->mult = match(IronParser::STAR);
              break;
            }

            case IronParser::DIV: {
              setState(352);
              antlrcpp::downCast<ExprContext *>(_localctx)->div = match(IronParser::DIV);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(355);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(356);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(359);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case IronParser::PLUS: {
              setState(357);
              antlrcpp::downCast<ExprContext *>(_localctx)->plus = match(IronParser::PLUS);
              break;
            }

            case IronParser::MINUS: {
              setState(358);
              antlrcpp::downCast<ExprContext *>(_localctx)->minus = match(IronParser::MINUS);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(361);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(366);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
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
  enterRule(_localctx, 64, IronParser::RuleNumber);
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
    setState(367);
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
  enterRule(_localctx, 66, IronParser::RuleDataFormat);
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
    setState(369);
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
  enterRule(_localctx, 68, IronParser::RuleVarTypes);
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
    setState(371);
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
    case 31: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool IronParser::boolExprSempred(BoolExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 6);

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
