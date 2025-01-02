grammar Iron;

// ---------------------------------
// Regras do Lexer (Tokens)
// ---------------------------------

// Símbolos
COMMA: ',' ;
COLON      : ':' ;
EQ         : '=' ;
SEMICOLON  : ';' ; // Mantido caso seja necessário no futuro
DOT        : '.' ;
STAR       : '*' ;
L_CURLY    : '{' ;
R_CURLY    : '}' ;
L_PAREN    : '(' ;
R_PAREN    : ')' ;
PLUS       : '+' ;
MINUS      : '-' ;
DIV        : '/' ;
L_BRACKET: '[' ;
R_BRACKET: ']' ;
ARROW : '->' ;


// Palavras reservadas
FUNCTION   : 'fn' ;
LET        : 'let' ;
PUBLIC     : 'public' ;
IMPORT     : 'import' ;
RETURN     : 'return' ;

// Tipos de dados
TYPE_INT       : 'int' ;
TYPE_CHAR      : 'char' ;
TYPE_FLOAT     : 'float' ;
TYPE_STRING    : 'string' ;
TYPE_BOOLEAN   : 'boolean' ;
TYPE_DOUBLE    : 'double' ;

// Literais
REAL_NUMBER    : '-'? [0-9]+ '.' [0-9]+ ([eE] [+-]? [0-9]+)? [FD]?;
INT_NUMBER     : '-'? [0-9]+ ;
BOOLEAN_VALUE  : 'true' | 'false' ;
STRING_LITERAL : '"' ~["\r\n]* '"' ;

// Identificador
IDENTIFIER : [a-zA-Z_] [a-zA-Z0-9_]* ;

// Ignorar espaços em branco e quebras de linha como tokens separados
NEWLINE : '\r'? '\n' -> skip ;
WS      : [ \t]+ -> skip ;

// ---------------------------------
// Regras do Parser
// ---------------------------------

// Ponto de entrada da gramática
program
    : importStatement* (functionDeclaration | entryPoint)* EOF
    ;

// Declaração de importação
importStatement
    : IMPORT qualifiedName (DOT STAR)?
    ;

// Nome qualificado para importação (ex.: module.casa.janela)
qualifiedName
    : IDENTIFIER (DOT IDENTIFIER)*
    ;

// Ponto de entrada principal
entryPoint
    : '@main' '(' argVar=IDENTIFIER ')' L_CURLY statementList R_CURLY
    ;

// Lista de declarações dentro do ponto de entrada ou função
statementList
    : (varDeclaration | varAssignment | expr | functionCall | return)*
    ;

return:
    RETURN (expr | functionCall)
    ;

// Declaração de função
functionDeclaration
    : PUBLIC? FUNCTION functionName=IDENTIFIER functionSignature
        L_CURLY statementList R_CURLY
    ;

//(peso:float, idade:int):float -> peso * idade
arrowFunctionInline:
    functionSignature ARROW expr
;

arrowFunctionBlock:
    functionSignature ARROW
    L_CURLY statementList R_CURLY
;

functionSignature:
    L_PAREN functionArgs? R_PAREN functionReturnType?
;

// Tipo de retorno da função
functionReturnType
    : COLON varTypes
    ;

// Argumentos da função
functionArgs
    : functionArg (COMMA functionArg)*
    ;

// Argumento da função
functionArg
    : varName=IDENTIFIER COLON (varTypes | functionSignature) assignment?
    ;

// Chamada de função
functionCall
    : functionName=IDENTIFIER L_PAREN functionCallArgs? R_PAREN
    ;

// Argumentos da chamada de função
functionCallArgs
    : functionCallArg (COMMA functionCallArg)*
    ;

// Argumento da chamada de função
functionCallArg
    : varName=IDENTIFIER COLON (dataFormat | functionCall | arrowFunctionInline | arrowFunctionBlock | anotherVarName=IDENTIFIER)
    ;

// Declaração de variável
varDeclaration
    : LET varName=IDENTIFIER COLON varTypes assignment?
    ;

// Atribuição
assignment
    : EQ (arrowFunctionInline | arrowFunctionBlock | dataFormat | expr )
    ;

varAssignment
    : varName=IDENTIFIER EQ (arrowFunctionInline | arrowFunctionBlock | dataFormat | expr )
    ;

// Expressão matemática com precedência adequada
expr:   left=expr (mult='*'| div='/') right=expr
    |   left=expr (plus='+'|minus='-') right=expr
    |   number
    |   functionCall
    |   varName=IDENTIFIER
    |   L_PAREN expr R_PAREN
    ;

number:
     REAL_NUMBER
    | INT_NUMBER
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
    | FUNCTION
    ;
