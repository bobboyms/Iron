grammar HightLavelIR;

// --------------------------------- Regras do Lexer (Tokens) ---------------------------------

// Símbolos
COLON: ':';
COMMA: ',';
EQ: '=';
SEMICOLON: ';'; // Mantido caso seja necessário no futuro
DOT: '.';
STAR: '*';
L_CURLY: '{';
R_CURLY: '}';
L_PAREN: '(';
R_PAREN: ')';
MULT: 'MULT';
PLUS: 'PLUS';
MINUS: 'MINUS';
DIV: 'DIV';
L_BRACKET: '[';
R_BRACKET: ']';
AT: '@';
ARROW: '->';
UNDERSCORE: '_';

// Palavras reservadas
FUNCTION: 'fn';
LET: 'let';
PUBLIC: 'public';
PRIVATE: 'private';
IMPORT: 'import';
RETURN: 'return';

// Tipos de dados
TO: 'to';
TYPE_INT: 'int';
TYPE_CHAR: 'char';
TYPE_FLOAT: 'float';
TYPE_STRING: 'string';
TYPE_BOOLEAN: 'boolean';
TYPE_DOUBLE: 'double';
VOID: 'void';

CAST: 'cast';
CALL: 'call';
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
program: importStatement* ( functionDeclaration)* EOF;

// Declaração de importação
importStatement: IMPORT qualifiedName (DOT STAR)?;

// Nome qualificado para importação (ex.: module.casa.janela)
qualifiedName: IDENTIFIER (DOT IDENTIFIER)*;

// Lista de declarações dentro do ponto de entrada ou função
statementList: (expr | functionCall)*;

// Declaração de função
functionDeclaration: (PRIVATE | PUBLIC)? FUNCTION functionName = IDENTIFIER functionSignature
		L_CURLY statementList R_CURLY;

functionSignature:
	L_PAREN functionArgs? R_PAREN functionReturnType?;

// Tipo de retorno da função
functionReturnType: COLON (varTypes | VOID);

// Argumentos da função
functionArgs: functionArg (',' functionArg)*;

// Argumento da função
functionArg:
	varName = IDENTIFIER COLON (varTypes | functionSignature);

// Chamada de função
functionCall:
	//call i32 @add(i32 10, i32 20)
	CALL varTypes functionName = IDENTIFIER L_PAREN functionCallArgs? R_PAREN;

// Argumentos da chamada de função
functionCallArgs: functionCallArg (',' functionCallArg)*;

// Argumento da chamada de função
functionCallArg:
	varName = IDENTIFIER COLON varTypes (
		dataFormat
		| functionCall
		| anotherVarName = IDENTIFIER
	);

op: (varName = IDENTIFIER | number);
opRight: op;
opLeft: op;

typeRight: varTypes;
typeLeft: varTypes;

cast: anotherVarName = IDENTIFIER typeLeft TO typeRight;

mathOp: ( MULT | DIV | PLUS | MINUS) opLeft COMMA opRight;

expr:
	LET varName = IDENTIFIER COLON varTypes EQ (
		mathOp
		| functionCall
		| cast
		| number
		| functionPtr
		| assignment
	);

assignment: anotherVarName = IDENTIFIER;
functionPtr: 'fptr' functionName = IDENTIFIER;

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
	| FUNCTION
	| VOID;