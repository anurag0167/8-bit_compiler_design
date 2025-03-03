#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
    INT,                // int 
    IDENTIFIER,         // identifier 
    ASSIGN,             // assign operator 
    NUMBER,             // number (countable variable)
    PLUS,               // add operator 
    MINUS,              // subtraction opeartor
    LPAREN,             // left (open) paranthesis
    RPAREN,             // right (close) paranthesis 
    IF,                 // using to handle if statement 
    ELSE,               // if else statement which is not handle throught if statement then go in else statement 
    EQ,                 // equal opeartor 
    LBRACE,             // left (open) bracket 
    RBRACE,             // right (close) bracket 
    SEMICOLON,          // semicolon 
    END,                // end it is a operator which is used to break the statement 
    EQUAL               // only one equal which is used to assign the variable 
} Tokentype;

// token structure which contain a token type and his name 
typedef struct {
    Tokentype type;
    char value[256];
} Token;

// lexer structure 
typedef struct {
    char* source;
    size_t pos;
} Lexer;

Lexer* lexer_create(char* source);
Token* lexer_tokenize(Lexer* lexer, size_t* token_count);
void lexer_destroy(Lexer* lexer);

#endif
