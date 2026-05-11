#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <memory>
#include <vector>

// Абстрактное синтаксическое дерево (AST)
struct ASTNode {
    virtual ~ASTNode() = default;
};

struct Program : public ASTNode {
    std::vector<std::unique_ptr<ASTNode>> declarations;
};

class Parser {
public:
    Parser();
    ~Parser();
    
    std::unique_ptr<Program> parse(const std::vector<Token>& tokens);
    
private:
    std::vector<Token> tokens;
    size_t position;
    
    const Token& current() const;
    const Token& peek(size_t offset = 1) const;
    void advance();
    bool match(TokenType type);
    
    std::unique_ptr<ASTNode> parseDeclaration();
    std::unique_ptr<ASTNode> parseFunction();
};

#endif // PARSER_H
