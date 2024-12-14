grammar Iron;

// Simbolos
COLON: ':' ;
EQ: '=' ;

// Palavras reservadas
LET: 'let';

// Tipos
TYPE_INT: 'int';
TYPE_FLOAT: 'float';
TYPE_STRING: 'string';
TYPE_BOOLEAN: 'boolean';
TYPE_DOUBLE: 'double';
TYPE_CHAR: 'char';

// Formato dos dados
INT_NUMBER: [0-9]+;
REAL_NUMBER: [0-9]+ '.' [0-9]+;
STRING_LITERAL: '"' (~["\\] | '\\' .)* '"';
BOOLEAN_VALUE: 'true' | 'false';

// Ignorar espaços em branco
WS: [ \t]+ -> skip;
NEWLINE: '\r'? '\n';
IDENTIFIER: ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*;

// Rules

dataFormat:
    INT_NUMBER
    | REAL_NUMBER
    | STRING_LITERAL
    | BOOLEAN_VALUE
    ;

varTypes:
    TYPE_BOOLEAN
    | TYPE_CHAR
    | TYPE_DOUBLE
    | TYPE_FLOAT
    | TYPE_INT
    | TYPE_STRING
    ;

finalInstruction:
            (NEWLINE | EOF)
            ;

varDeclaration:
    LET IDENTIFIER COLON varTypes (EQ dataFormat)? finalInstruction
    ;

// Nova regra para linhas vazias
emptyLine:
    NEWLINE
    ;

program:
    (varDeclaration | emptyLine)* EOF
    ;
