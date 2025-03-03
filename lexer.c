#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

// // Token types
// typedef enum {
//     INT,
//     IF,
//     ELSE,
//     IDENTIFIER,
//     NUMBER,
//     EQ,
//     EQUAL,
//     PLUS,
//     MINUS,
//     LPAREN,
//     RPAREN,
//     LBRACE,
//     RBRACE,
//     SEMICOLON,
//     END
// } Tokentype;

// // Token structure
// typedef struct {
//     Tokentype type;
//     char value[256];  // To hold token value as a string (max 255 chars)
// } Token;

// // Lexer structure
// typedef struct {
//     char* source;
//     size_t pos;
// } Lexer;

// Function to create a new Lexer
Lexer* lexer_create(char* source) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->pos = 0;
    return lexer;
}

// Function to tokenize the input source code
Token* lexer_tokenize(Lexer* lexer, size_t* token_count) {
    size_t capacity = 10;  // Initial capacity for tokens
    Token* tokens = (Token*)malloc(capacity * sizeof(Token));
    *token_count = 0;
    char cur;

    while (lexer->source[lexer->pos] != '\0') {
        cur = lexer->source[lexer->pos];
        printf("Processing character: '%c' at position %zu\n", cur, lexer->pos);  // Debugging line
        // Skip whitespace
        if (isspace(cur)) {
            printf("Skipping whitespace: '%c'\n", cur);  // Debugging line
            lexer->pos++;
            continue;
        }

        // Handle identifiers and keywords
        if (isalpha(cur)) {
            char identifier[256];
            size_t idx = 0;

            while (isalnum(cur)) {
                identifier[idx++] = cur;
                lexer->pos++;
                cur = lexer->source[lexer->pos];
            }
            identifier[idx] = '\0';  // Null-terminate the string

            Token new_token;
            if (strcmp(identifier, "int") == 0) {
                new_token = (Token){INT, "int"};
            } else if (strcmp(identifier, "if") == 0) {
                new_token = (Token){IF, "if"};
            } else if (strcmp(identifier, "else") == 0) {
                new_token = (Token){ELSE, "else"};
            } else {
                strcpy(new_token.value, identifier);
                new_token.type = IDENTIFIER;
            }

            printf("Generated token: %s\n", new_token.value);  // Debugging line
            tokens[*token_count] = new_token;
            (*token_count)++;
        }
        // Handle numbers
        else if (isdigit(cur)) {
            char num[256];
            size_t idx = 0;

            while (isdigit(cur)) {
                num[idx++] = cur;
                lexer->pos++;
                cur = lexer->source[lexer->pos];
            }
            num[idx] = '\0';  // Null-terminate the string
            // tokens[*token_count] = (Token){NUMBER, ""};
            Token new_token = {NUMBER, *num};
            printf("Generated number token: %s\n", new_token.value);  // Debugging line

            strcpy(tokens[*token_count].value, num);
            (*token_count)++;
        }
        // Handle symbols (operators, parentheses, braces, etc.)
        else {
            Token new_token;
            switch (cur) {
                case '=':
                    lexer->pos++;
                    if (lexer->source[lexer->pos] == '=') {
                        new_token = (Token){EQ, "=="};
                    } else {
                        new_token = (Token){EQUAL, "="};
                        lexer->pos--;  // Rewind position if not '=='
                    }
                    break;
                case '+':
                    new_token = (Token){PLUS, "+"};
                    break;
                case '-':
                    new_token = (Token){MINUS, "-"};
                    break;
                case '(':
                    new_token = (Token){LPAREN, "("};
                    break;
                case ')':
                    new_token = (Token){RPAREN, ")"};
                    break;
                case '{':
                    new_token = (Token){LBRACE, "{"};
                    break;
                case '}':
                    new_token = (Token){RBRACE, "}"};
                    break;
                case ';':
                    new_token = (Token){SEMICOLON, ";"};
                    break;
                default:
                    fprintf(stderr, "Unknown character: '%c'\n", cur);
                    lexer->pos++;
                    continue;
            }
            tokens[*token_count] = new_token;
            (*token_count)++;
            lexer->pos++;
        }

        // Reallocate memory if needed
        if (*token_count >= capacity) {
            capacity *= 2;
            tokens = (Token*)realloc(tokens, capacity * sizeof(Token));
            if (tokens == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
        }
    }

    // Add the END token
    tokens[*token_count] = (Token){END, ""};
    (*token_count)++;

    return tokens;
}

// Function to free lexer memory
void lexer_destroy(Lexer* lexer) {
    free(lexer);
}

/*
// Function to print tokens
void printTokens(Token* tokens, size_t tokenCount) {
    for (size_t i = 0; i < tokenCount; i++) {
        printf("Token Value: %s, Token Number: %d\n", tokens[i].value, tokens[i].type);
    }
}

int main() {
    // Open the input file
    FILE* inputFile = fopen("input.simp", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file!\n");
        return 1;
    }
    else
    {
        printf("File is open !\n");
    }

    // Find the size of the file
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Allocate memory for the source code
    char* sourceCode = (char*)malloc(fileSize + 1);  // +1 for the null terminator
    fread(sourceCode, 1, fileSize, inputFile);
    sourceCode[fileSize] = '\0';  // Null-terminate the string
    fclose(inputFile);  // Close the file after reading

    // Create lexer and tokenize the source code
    Lexer* lexer = lexer_create(sourceCode);
    size_t tokenCount = 0;
    Token* tokens = lexer_tokenize(lexer, &tokenCount);

    // Print tokens
    printTokens(tokens, tokenCount);

    // Free memory
    free(tokens);
    free(sourceCode);
    lexer_destroy(lexer);

    return 0;
}
*/