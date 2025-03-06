#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ASTNode ASTNode;
typedef struct NumberNode NumberNode;
typedef struct VariableNode VariableNode;
typedef struct VariableDec VariableDec;
typedef struct BinaryOpNode BinaryOpNode;
typedef struct ConditionalNode ConditionalNode;
typedef struct BlockNode BlockNode;
typedef struct Parser Parser;

// ASTNode structure definition
struct ASTNode {
    void (*generateCode)(ASTNode* node, FILE* out);
    void (*generateL)(ASTNode* node, FILE* out);
    void (*generateR)(ASTNode* node, FILE* out);
};

// NumberNode structure definition
struct NumberNode {
    ASTNode base; // Inheritance simulation by including the base ASTNode structure
    int val;
};

NumberNode* numberNode_create(int val);
void numberNode_generateCode(NumberNode* node, FILE* out);
void numberNode_generateL(NumberNode* node, FILE* out);
void numberNode_generateR(NumberNode* node, FILE* out);

// VariableNode structure definition
struct VariableNode {
    ASTNode base;
    char* name;
    int id;
};

VariableNode* variableNode_create(char* name);
void variableNode_generateCode(VariableNode* node, FILE* out);
void variableNode_generateL(VariableNode* node, FILE* out);
void variableNode_generateR(VariableNode* node, FILE* out);

// VariableDec structure definition
struct VariableDec {
    VariableNode base;
    char* varN;
    ASTNode* val; // Use pointer to ASTNode for value
};

VariableDec* variableDec_create(char* varN, ASTNode* val);
void variableDec_generateCode(VariableDec* node, FILE* out);
void variableDec_generateL(VariableDec* node, FILE* out);
void variableDec_generateR(VariableDec* node, FILE* out);

// BinaryOpNode structure definition
struct BinaryOpNode {
    ASTNode base;
    ASTNode* l;
    ASTNode* r;
    char op;
};

BinaryOpNode* binaryOpNode_create(ASTNode* l, char op, ASTNode* r);
void binaryOpNode_generateCode(BinaryOpNode* node, FILE* out);
void binaryOpNode_generateL(BinaryOpNode* node, FILE* out);
void binaryOpNode_generateR(BinaryOpNode* node, FILE* out);

// ConditionalNode structure definition
struct ConditionalNode {
    ASTNode base;
    ASTNode* cond;
    ASTNode* then_br;
    ASTNode* else_br;
};

ConditionalNode* conditionalNode_create(ASTNode* cond, ASTNode* then_br, ASTNode* else_br);
void conditionalNode_generateCode(ConditionalNode* node, FILE* out);
void conditionalNode_generateL(ConditionalNode* node, FILE* out);
void conditionalNode_generateR(ConditionalNode* node, FILE* out);

// BlockNode structure definition
struct BlockNode {
    ASTNode base;
    ASTNode** statements;
    size_t statement_count;
};

BlockNode* blockNode_create();
void blockNode_addStat(BlockNode* block, ASTNode* statement);
void blockNode_generateCode(BlockNode* node, FILE* out);
void blockNode_generateL(BlockNode* node, FILE* out);
void blockNode_generateR(BlockNode* node, FILE* out);

// Parser structure definition
struct Parser {
    Token* tokens;
    size_t pos;
};

Parser* parser_create(Token* tokens);
ASTNode* parser_parse(Parser* parser);

// Parser helper functions
ASTNode* parseExp(Parser* parser);
ASTNode* parseExpStat(Parser* parser);
ASTNode* parsePrim(Parser* parser);
ASTNode* parseStat(Parser* parser);
ASTNode* parseVarDec(Parser* parser);
ASTNode* parseVarAssign(Parser* parser);
ASTNode* parseCond(Parser* parser);
ASTNode* parseBlock(Parser* parser);

// Utility functions for the parser
bool match(Parser* parser, Tokentype* types, size_t num_types);
bool isAtEnd(Parser* parser);
bool check(Parser* parser, Tokentype type);
void advance(Parser* parser);
Token previous(Parser* parser);
void consume(Parser* parser, Tokentype type, const char* error_msg);

#endif
