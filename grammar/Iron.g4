grammar Iron;

// ---------------------------------
// Regras do Lexer (Tokens)
// ---------------------------------

// Símbolos
COLON      : ':' ;
EQ         : '=' ;
SEMICOLON  : ';' ;
DOT        : '.' ;
STAR       : '*' ;
L_CURLY    : '{' ;
R_CURLY    : '}' ;
L_BRACKET  : '[' ;
R_BRACKET  : ']' ;
L_PAREN    : '(' ;
R_PAREN    : ')' ;

// Palavras reservadas
FUNCTION   : 'fn' ;
LET        : 'let' ;
PUBLIC     : 'public' ;
IMPORT     : 'import' ;

// Tipos de dados
TYPE_INT       : 'int' ;
TYPE_CHAR      : 'char' ;
TYPE_FLOAT     : 'float' ;
TYPE_STRING    : 'string' ;
TYPE_BOOLEAN   : 'boolean' ;
TYPE_DOUBLE    : 'double' ;

// Literais
REAL_NUMBER    : '-'? [0-9]+ '.' [0-9]+ ([eE] [+-]? [0-9]+)? ;
INT_NUMBER     : '-'? [0-9]+ ;
BOOLEAN_VALUE  : 'true' | 'false' ;
STRING_LITERAL : '"' ~["\r\n]* '"' ;

// Identificador
IDENTIFIER : [a-zA-Z_] [a-zA-Z0-9_]* ;

// Ignorar espaços em branco e quebras de linha como tokens separados
NEWLINE : '\r'? '\n' ;
WS      : [ \t]+ -> skip ;

// ---------------------------------
// Regras do Parser
// ---------------------------------

// Ponto de entrada da gramática
program
    : importStatement* body entryPoint? NEWLINE? EOF
    ;

// Declaração de importação
importStatement
    : IMPORT qualifiedName (DOT STAR)? NEWLINE
    ;

// Nome qualificado para importação (ex.: module.casa.janela)
qualifiedName
    : IDENTIFIER (DOT IDENTIFIER)*
    ;

// Ponto de entrada principal
entryPoint
    : '@main' '(' argVar=IDENTIFIER ')' L_CURLY (statement | NEWLINE)* R_CURLY NEWLINE? EOF?
    ;

// Corpo do programa
body
    : (statement | functionDeclaration | NEWLINE)*
    ;

// Declaração de função
functionDeclaration
    : PUBLIC? FUNCTION functionName=IDENTIFIER L_PAREN R_PAREN L_CURLY NEWLINE? R_CURLY NEWLINE?
    ;

// Declarações dentro do @main
statement
    : varDeclaration
    ;

// Declaração de variável
varDeclaration
    : LET varName=IDENTIFIER COLON varTypes (EQ dataFormat)? NEWLINE
    ;

// Formato de dados para inicializadores
dataFormat
    : REAL_NUMBER
    | INT_NUMBER
    | BOOLEAN_VALUE
    | STRING_LITERAL
    ;

// Tipos de variáveis permitidos
varTypes
    : TYPE_BOOLEAN
    | TYPE_CHAR
    | TYPE_DOUBLE
    | TYPE_FLOAT
    | TYPE_INT
    | TYPE_STRING
    ;
