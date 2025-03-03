#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

// void printTokens(Token* tokens, size_t tokenCount)
// {
//     for (size_t i = 0; i < tokenCount; i++)
//     {
//         printf("Token value %s, \t Token Number &d\n", tokens[i].value, tokens[i].type);
//     }
// }

// int main()
// {
//     FILE *inputFile = fopen("input.simp", "r");
//     FILE *outputFile = fopen("output.asm", "w");

//     if (!outputFile)
//     {
//         fprintf(stderr, "Output file not open! \n");
//         return 1;
//     }

//     fseek(inputFile, 0, SEEK_END);
//     long fileSize = ftell(inputFile);
//     fseek(inputFile, 0, SEEK_SET);
//     char *sourceCode = (char *)malloc(fileSize + 1);
//     fread(sourceCode, 1, fileSize, inputFile);
//     sourceCode[fileSize] = '\0';
//     fclose(inputFile);

//     // Create lexer and tokenize the source code
//     Lexer* lexer = lexer_create(sourceCode);
//     size_t tokenCount = 0;
//     Token* tokens = lexer_tokenize(lexer, &tokenCount);

//     // Print tokens
//     printTokens(tokens, tokenCount);

//     // Free memory
//     free(tokens);
//     free(sourceCode);
//     lexer_destroy(lexer);
// }

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
