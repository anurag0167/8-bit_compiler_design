/* SimpleLang Grammar in EBNF notation */

/* Program Structure */
program        ::= statement_list

/* Statement Types */
statement_list ::= statement | statement statement_list
statement      ::= declaration_statement
                 | assignment_statement
                 | conditional_statement

/* Declarations */
declaration_statement ::= "int" IDENTIFIER ";"

/* Assignments */
assignment_statement  ::= IDENTIFIER "=" expression ";"

/* Expressions */
expression     ::= term
                 | expression "+" term
                 | expression "-" term

term           ::= factor

factor         ::= IDENTIFIER
                 | NUMBER
                 | "(" expression ")"

/* Conditionals */
conditional_statement ::= "if" "(" condition ")" "{" statement_list "}"

condition      ::= expression "==" expression

/* Terminals */
IDENTIFIER     ::= LETTER (LETTER | DIGIT)*
NUMBER         ::= DIGIT+
LETTER         ::= "a" | "b" | ... | "z" | "A" | "B" | ... | "Z"
DIGIT          ::= "0" | "1" | ... | "9"

/* Comments */
comment        ::= "//" (any character except newline)* newline