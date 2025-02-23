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
L_BRACKET: '[';
R_BRACKET: ']';
ARROW: '->';

// Tokens para operadores lógicos e relacionais (adicione esses tokens se ainda não existirem)
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
ELSE: 'else';
PUBLIC: 'public';
IMPORT: 'import';
RETURN: 'return';

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
	importStatement* externBlock? (functionDeclaration)* EOF;

// Declaração de importação
importStatement: IMPORT qualifiedName (DOT STAR)?;

// Nome qualificado para importação (ex.: module.casa.janela)
qualifiedName: IDENTIFIER (DOT IDENTIFIER)*;

// Ponto de entrada principal entryPoint: '@main' '(' argVar = IDENTIFIER ')' L_CURLY statementList
// R_CURLY;

// Lista de declarações dentro do ponto de entrada ou função
statementList: (
		varDeclaration
		| varAssignment
		| functionCall
		| expr
//		| boolExpr
		| ifStatement
		| returnStatement
	)*;

returnStatement:
	RETURN (
		dataFormat
		| varName = IDENTIFIER
		| functionCall
		| expr
	);


//forStatement
//    : 'for' forClause block
//    ;
//
//forClause
//    : forClassicClause            // Forma clássica com inicialização, condição e pós-execução
//    | forConditionClause          // Forma com apenas condição
//    |                             // Forma sem condição (loop infinito)
//    ;
//
//// Forma clássica: inicialização; condição; pós-execução
//forClassicClause
//    : '(' (varDeclaration | varAssignment | expr)? ';' expr? ';' expr? ')'
//    ;
//
//// Forma com apenas condição
//forConditionClause
//    : '(' boolExpr ')'
//    ;

// Bloco de código
//block
//    : '{' statementList '}'
//    ;

//printf("Taxa de aprovação: %d%%\n", 90);
// f"Nome: %s", maria
formatStatement:
    'f\'(' STRING_LITERAL COMMA (formatArguments) ')'
;

formatArguments: formatArgument (COMMA formatArgument)*;

formatArgument:
	(dataFormat | varName=IDENTIFIER | functionCall | expr | STRING_LITERAL);

//extern C function

externBlock:
	'extern' language = IDENTIFIER '{' (
		externFunctionDeclaration+
	)* '}';

externFunctionDeclaration:
	'fn' exterFunctionName = IDENTIFIER '(' externFunctionArgs? (',' varied = '...')? ')' functionReturnType?;

// Argumentos da função
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


//**********************

// Declaração de função
functionDeclaration:
	PUBLIC? FUNCTION functionName = IDENTIFIER functionSignature L_CURLY statementList R_CURLY;

//(peso:float, idade:int):float -> peso * idade
arrowFunctionInline: functionSignature ARROW expr;

arrowFunctionBlock:
	functionSignature ARROW L_CURLY statementList R_CURLY;

functionSignature:
	L_PAREN functionArgs? R_PAREN functionReturnType?;

// Tipo de retorno da função
functionReturnType: COLON varTypes;

// Argumentos da função
functionArgs: functionArg (COMMA functionArg)*;

// Argumento da função
functionArg:
	varName = IDENTIFIER COLON (varTypes | functionSignature) assignment?;

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
	);

// Declaração de variável
varDeclaration:
	LET varName = IDENTIFIER COLON varTypes assignment?;

// Atribuição
assignment:
	EQ (
		arrowFunctionInline
		| arrowFunctionBlock
		| varName = IDENTIFIER
		| dataFormat
		| functionCall
		| expr
		| boolExpr
	);

varAssignment:
	varName = IDENTIFIER EQ (
		arrowFunctionInline
		| arrowFunctionBlock
		| dataFormat
		| expr
	);

//if e else
ifBlock
    : L_CURLY statementList? R_CURLY
    ;

// ifStatement
ifStatement
    : IF L_PAREN boolExpr R_PAREN ifBlock (ELSE elseStatement)?
    ;

elseStatement
    : ifStatement
    | ifBlock
    ;

//expression
// : LPAREN expression RPAREN                       #parenExpression
// | NOT expression                                 #notExpression
// | left=expression op=comparator right=expression #comparatorExpression
// | left=expression op=binary right=expression     #binaryExpression
// | bool                                           #boolExpression
// | IDENTIFIER                                     #identifierExpression
// | DECIMAL                                        #decimalExpression
// ;

boolExpr

   : L_PAREN boolExpr R_PAREN
   | left=boolExpr op= ( EQEQ | NEQ | LT | LTE | GT | GTE) right=boolExpr
   | left=boolExpr op= AND right=boolExpr
   | left=boolExpr op= OR right=boolExpr
   | not = NOT boolExpr
   | booleanValue = BOOLEAN_VALUE
   | number
   | varName = IDENTIFIER
   | functionCall

   | expr;

primary
   : number
   | IDENTIFIER
   | BOOLEAN_VALUE
   | functionCall
   | L_PAREN boolExpr R_PAREN
   | expr
   ;

expr:
	left = expr (mult = '*' | mod= '%' | div = '/') right = expr
	| left = expr (plus = '+' | minus = '-') right = expr
	| number
	| functionCall
	| varName = IDENTIFIER
	| L_PAREN expr R_PAREN;

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