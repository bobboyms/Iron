grammar Iron;

// --------------------------------- Regras do Lexer (Tokens) ---------------------------------

// Comentário de linha: "//" seguido de qualquer coisa até a quebra de linha ou EOF
LINE_COMMENT: '//' ~[\r\n]* -> skip;

// Comentário de bloco: "/*" seguido de qualquer conteúdo até "*/"
BLOCK_COMMENT: '/*' .*? '*/' -> skip;

// Símbolos
COMMA: ',';
COLON: ':';
EQ: '=';
SEMICOLON: ';'; // Mantido caso seja necessário no futuro
DOT: '.';
STAR: '*';
L_CURLY: '{';
R_CURLY: '}';
L_PAREN: '(';
R_PAREN: ')';
PLUS: '+';
MINUS: '-';
DIV: '/';
MOD: '%';
L_BRACKET: '[';
R_BRACKET: ']';
ARROW: '->';

// Tokens para operadores lógicos e relacionais
AND: 'and';
OR: 'or';
NOT: 'not';
EQEQ: '==';
NEQ: '!=';
LT: '<';
LTE: '<=';
GT: '>';
GTE: '>=';

// Palavras reservadas
IF: 'if';
FUNCTION: 'fn';
LET: 'let';
MUT: 'mut';
ELSE: 'else';
PUBLIC: 'public';
IMPORT: 'import';
RETURN: 'return';
IN: 'in';
FOR: 'for';
WHILE: 'while';
REPEAT: 'repeat';
STRUCT: 'struct';
OPTIONS: 'options';
CONTINUE: 'continue';
BREAK: 'break';

// Tipos de dados
TYPE_INT: 'int';
TYPE_CHAR: 'char';
TYPE_FLOAT: 'float';
TYPE_STRING: 'string';
TYPE_BOOLEAN: 'boolean';
TYPE_DOUBLE: 'double';
TYPE_VOID: 'void';

// Literais
REAL_NUMBER: '-'? [0-9]+ '.' [0-9]+ ([eE] [+-]? [0-9]+)? [FD]?;
INT_NUMBER: '-'? [0-9]+;
BOOLEAN_VALUE: 'true' | 'false';
STRING_LITERAL: '"' ~["\r\n]* '"';

// Identificador
IDENTIFIER: [a-zA-Z_] [a-zA-Z0-9_]*;

// Ignorar espaços em branco e quebras de linha como tokens separados
NEWLINE: '\r'? '\n' -> skip;
WS: [ \t]+ -> skip;

// --------------------------------- Regras do Parser ---------------------------------

// Ponto de entrada da gramática
program:
	importStatement* externBlock? (functionDeclaration | structStatement | optionsStatement)* EOF;

// Declaração de importação
importStatement: IMPORT qualifiedName (DOT STAR)?;

// Nome qualificado para importação (ex.: module.casa.janela)
qualifiedName: IDENTIFIER (DOT IDENTIFIER)*;

// Lista de declarações dentro do ponto de entrada ou função
statementList: (
        continueStatement
		| breakStatement
		| varDeclaration
		| varAssignment
		| functionCall
		| expr
		| ifStatement
		| whileStatement
		| repeatStatement
		| forStatement
		| returnStatement
		| formatStatement
	)*;

// Instruções de controle de fluxo
breakStatement: BREAK;
continueStatement: CONTINUE;

// Declarações de struct e options
structStatement:
    STRUCT structName = IDENTIFIER L_CURLY structBody (',' structBody)* R_CURLY
;

structBody:
   MUT? varName = IDENTIFIER COLON varTypes
;

structInit:
    structName = IDENTIFIER? L_CURLY structInitBody (',' structInitBody)* R_CURLY
;

structInitBody:
    varName = IDENTIFIER COLON (
    		dataFormat
    		| anotherVarName = IDENTIFIER
    		| functionCall
    		| arrowFunctionInline
    	)
;

optionsStatement:
     OPTIONS optionName = IDENTIFIER L_CURLY optionsBody (',' optionsBody)* R_CURLY
;

optionsBody:
    itemName = IDENTIFIER functionSignature?
;

// Instrução de retorno
returnStatement:
	RETURN (
		dataFormat
		| varName = IDENTIFIER
		| functionCall
		| expr
	)?;

// Estruturas de controle de loop
whileStatement:
    WHILE boolExpr L_CURLY statementList R_CURLY;

repeatStatement:
    REPEAT L_CURLY statementList R_CURLY WHILE boolExpr;

forStatement:
    FOR IDENTIFIER IN intervals L_CURLY statementList R_CURLY;

intervals:
    (firstNumber = INT_NUMBER | firstVarName = IDENTIFIER)
    '..'
    (secondNumber = INT_NUMBER | secondVarName = IDENTIFIER);

// Formato de string
formatStatement:
    'f\'(' STRING_LITERAL COMMA formatArguments ')'
;

formatArguments: formatArgument (COMMA formatArgument)*;

formatArgument:
	(dataFormat | varName=IDENTIFIER | functionCall | expr | STRING_LITERAL);

// Declarações de funções externas
externBlock:
	'extern' language = IDENTIFIER L_CURLY (
		externFunctionDeclaration+
	)* R_CURLY;

externFunctionDeclaration:
	FUNCTION exterFunctionName = IDENTIFIER L_PAREN externFunctionArgs? (',' varied = '...')? R_PAREN functionReturnType?;

// Argumentos da função externa
externFunctionArgs: externFunctionArg (COMMA externFunctionArg)*;

externFunctionArg:
	varName = IDENTIFIER COLON ptr = STAR? cTypes;

cTypes:
	TYPE_BOOLEAN
	| TYPE_CHAR
	| TYPE_DOUBLE
	| TYPE_FLOAT
	| TYPE_INT
	| TYPE_VOID
	;

// Declaração e chamada de função
functionDeclaration:
	PUBLIC? FUNCTION functionName = IDENTIFIER functionSignature L_CURLY statementList R_CURLY;

functionSignature:
	L_PAREN functionArgs? R_PAREN functionReturnType?;

// Tipo de retorno da função
functionReturnType: COLON varTypes;

// Argumentos da função
functionArgs: functionArg (COMMA functionArg)*;

// Argumento da função
functionArg:
	varName = IDENTIFIER COLON (fnsignature | varTypes) assignment?;

fnsignature:
    FUNCTION functionSignature
;

// Funções flecha (arrow functions)
arrowFunctionInline: 
    functionSignature ARROW (expr | L_CURLY statementList R_CURLY);

arrowFunctionBlock:
	functionSignature ARROW L_CURLY statementList R_CURLY;

// Chamada de função
functionCall:
	functionName = IDENTIFIER L_PAREN functionCallArgs? R_PAREN;

// Argumentos da chamada de função
functionCallArgs: functionCallArg (COMMA functionCallArg)*;

// Argumento da chamada de função
functionCallArg:
	varName = IDENTIFIER COLON (
		dataFormat
		| anotherVarName = IDENTIFIER
		| functionCall
		| formatStatement
		| arrowFunctionInline
		| arrowFunctionBlock
		| structInit
	);

// Declaração e atribuição de variáveis
varDeclaration:
	MUT? LET varName = IDENTIFIER COLON (varTypes | anotherType = IDENTIFIER) assignment?;

// Atribuição
assignment:
	EQ (
		arrowFunctionInline
		| arrowFunctionBlock
		| varName = IDENTIFIER
		| dataFormat
		| structInit
		| functionCall
		| expr
		| boolExpr
	);

varAssignment:
	varName = IDENTIFIER ('.' IDENTIFIER)* EQ (
		arrowFunctionInline
		| arrowFunctionBlock
		| anotherVarName = IDENTIFIER
		| dataFormat
		| structInit
		| functionCall
		| expr
		| boolExpr
	);

// Estruturas de controle if-else
ifBlock
    : L_CURLY statementList? R_CURLY
    ;

ifStatement
    : IF L_PAREN boolExpr R_PAREN ifBlock (ELSE elseStatement)?
    ;

elseStatement
    : ifStatement
    | ifBlock
    ;

// Expressões booleanas e aritméticas com prioridades claras
boolExpr
   : L_PAREN boolExpr R_PAREN                                  #parenBoolExpr
   | NOT boolExpr                                              #notExpr
   | left=boolExpr op=(AND|OR) right=boolExpr                 #logicalExpr
   | left=boolExpr op=(EQEQ|NEQ|LT|LTE|GT|GTE) right=boolExpr #comparisonExpr
   | BOOLEAN_VALUE                                             #booleanLiteral
   | number                                                    #numberExpr
   | IDENTIFIER                                                #identifierExpr
   | functionCall                                              #functionCallExpr
   | expr                                                      #arithmeticExpr
   ;

// Operadores matemáticos
math_op
   : PLUS 
   | MINUS 
   | STAR 
   | DIV 
   | MOD
   ;

// Expressões aritméticas com prioridade de operadores
expr
   : L_PAREN expr R_PAREN                           #parenExpr
   | left=expr op=(STAR|DIV|MOD) right=expr         #multExpr
   | left=expr op=(PLUS|MINUS) right=expr           #addExpr
   | number                                          #numberLiteral
   | functionCall                                    #functionCallLiteral
   | IDENTIFIER                                      #identifierLiteral
   ;

// Valores numéricos
number: REAL_NUMBER | INT_NUMBER;

// Formato de dados para inicializadores
dataFormat:
	REAL_NUMBER
	| INT_NUMBER
	| BOOLEAN_VALUE
	| STRING_LITERAL;

// Tipos de variáveis permitidos
varTypes:
	TYPE_BOOLEAN
	| TYPE_CHAR
	| TYPE_DOUBLE
	| TYPE_FLOAT
	| TYPE_INT
	| TYPE_STRING
	| FUNCTION;