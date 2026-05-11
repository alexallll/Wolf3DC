#include "parser.h"
#include <iostream>

Parser::Parser() : position(0) {}

Parser::~Parser() {}

std::unique_ptr<Program> Parser::parse(const std::vector<Token>& src) {
    tokens = src;
    position = 0;
    
    auto program = std::make_unique<Program>();
    
    while (current().type != TokenType::EOF_TOKEN) {
        auto decl = parseDeclaration();
        if (decl) {
            program->declarations.push_back(std::move(decl));
        }
    }
    
    return program;
}

const Token& Parser::current() const {
    if (position >= tokens.size()) {
        static Token eof = {TokenType::EOF_TOKEN, "", 0, 0};
        return eof;
    }
    return tokens[position];
}

const Token& Parser::peek(size_t offset) const {
    if (position + offset >= tokens.size()) {
        static Token eof = {TokenType::EOF_TOKEN, "", 0, 0};
        return eof;
    }
    return tokens[position + offset];
}

void Parser::advance() {
    if (position < tokens.size()) {
        position++;
    }
}

bool Parser::match(TokenType type) {
    if (current().type == type) {
        advance();
        return true;
    }
    return false;
}

std::unique_ptr<ASTNode> Parser::parseDeclaration() {
    // Для простоты пропускаем неизвестные токены
    if (current().type == TokenType::EOF_TOKEN) {
        return nullptr;
    }
    
    advance();
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::parseFunction() {
    // Заглушка для парсинга функций
    return nullptr;
}
