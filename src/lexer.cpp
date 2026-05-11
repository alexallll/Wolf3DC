#include "lexer.h"
#include <cctype>
#include <unordered_map>

static std::unordered_map<std::string, TokenType> keywords = {
    {"int", TokenType::KW_INT},
    {"char", TokenType::KW_CHAR},
    {"void", TokenType::KW_VOID},
    {"if", TokenType::KW_IF},
    {"else", TokenType::KW_ELSE},
    {"for", TokenType::KW_FOR},
    {"while", TokenType::KW_WHILE},
    {"return", TokenType::KW_RETURN},
    {"struct", TokenType::KW_STRUCT},
};

Lexer::Lexer() : position(0), line(1), column(1) {}

Lexer::~Lexer() {}

std::vector<Token> Lexer::tokenize(const std::string& src) {
    source = src;
    position = 0;
    line = 1;
    column = 1;
    
    std::vector<Token> tokens;
    
    while (position < source.length()) {
        skipWhitespace();
        
        if (position >= source.length()) break;
        
        // Проверяем на комментарии
        if (current() == '/' && peek() == '/') {
            skipComment();
            continue;
        }
        
        char ch = current();
        
        if (std::isalpha(ch) || ch == '_') {
            tokens.push_back(readIdentifierOrKeyword());
        } else if (std::isdigit(ch)) {
            tokens.push_back(readNumber());
        } else if (ch == '"') {
            tokens.push_back(readString());
        } else if (ch == ';') {
            tokens.push_back({TokenType::SEMICOLON, ";", line, column});
            advance();
        } else if (ch == ',') {
            tokens.push_back({TokenType::COMMA, ",", line, column});
            advance();
        } else if (ch == '.') {
            tokens.push_back({TokenType::DOT, ".", line, column});
            advance();
        } else if (ch == '(') {
            tokens.push_back({TokenType::LPAREN, "(", line, column});
            advance();
        } else if (ch == ')') {
            tokens.push_back({TokenType::RPAREN, ")", line, column});
            advance();
        } else if (ch == '{') {
            tokens.push_back({TokenType::LBRACE, "{", line, column});
            advance();
        } else if (ch == '}') {
            tokens.push_back({TokenType::RBRACE, "}", line, column});
            advance();
        } else if (ch == '[') {
            tokens.push_back({TokenType::LBRACKET, "[", line, column});
            advance();
        } else if (ch == ']') {
            tokens.push_back({TokenType::RBRACKET, "]", line, column});
            advance();
        } else {
            tokens.push_back(readOperator());
        }
    }
    
    tokens.push_back({TokenType::EOF_TOKEN, "", line, column});
    return tokens;
}

char Lexer::current() {
    if (position >= source.length()) return '\0';
    return source[position];
}

char Lexer::peek(size_t offset) {
    if (position + offset >= source.length()) return '\0';
    return source[position + offset];
}

void Lexer::advance() {
    if (position < source.length()) {
        if (source[position] == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        position++;
    }
}

void Lexer::skipWhitespace() {
    while (position < source.length() && std::isspace(current())) {
        advance();
    }
}

void Lexer::skipComment() {
    // Пропускаем //
    advance();
    advance();
    
    // Пропускаем до конца строки
    while (position < source.length() && current() != '\n') {
        advance();
    }
    if (current() == '\n') {
        advance();
    }
}

Token Lexer::readIdentifierOrKeyword() {
    int startLine = line;
    int startCol = column;
    std::string value;
    
    while (position < source.length() && (std::isalnum(current()) || current() == '_')) {
        value += current();
        advance();
    }
    
    TokenType type = TokenType::IDENTIFIER;
    if (keywords.find(value) != keywords.end()) {
        type = keywords[value];
    }
    
    return {type, value, startLine, startCol};
}

Token Lexer::readNumber() {
    int startLine = line;
    int startCol = column;
    std::string value;
    
    while (position < source.length() && std::isdigit(current())) {
        value += current();
        advance();
    }
    
    return {TokenType::NUMBER, value, startLine, startCol};
}

Token Lexer::readString() {
    int startLine = line;
    int startCol = column;
    std::string value;
    
    advance(); // Пропускаем открывающую кавычку
    
    while (position < source.length() && current() != '"') {
        if (current() == '\\') {
            advance();
            if (position < source.length()) {
                value += current();
                advance();
            }
        } else {
            value += current();
            advance();
        }
    }
    
    if (current() == '"') {
        advance(); // Пропускаем закрывающую кавычку
    }
    
    return {TokenType::STRING, value, startLine, startCol};
}

Token Lexer::readOperator() {
    int startLine = line;
    int startCol = column;
    char ch = current();
    
    advance();
    
    // Двухсимвольные операторы
    if (ch == '+') {
        return {TokenType::PLUS, "+", startLine, startCol};
    } else if (ch == '-') {
        return {TokenType::MINUS, "-", startLine, startCol};
    } else if (ch == '*') {
        return {TokenType::STAR, "*", startLine, startCol};
    } else if (ch == '/') {
        return {TokenType::SLASH, "/", startLine, startCol};
    } else if (ch == '%') {
        return {TokenType::PERCENT, "%", startLine, startCol};
    } else if (ch == '=') {
        if (current() == '=') {
            advance();
            return {TokenType::EQ, "==", startLine, startCol};
        }
        return {TokenType::ASSIGN, "=", startLine, startCol};
    } else if (ch == '!') {
        if (current() == '=') {
            advance();
            return {TokenType::NEQ, "!=", startLine, startCol};
        }
    } else if (ch == '<') {
        if (current() == '=') {
            advance();
            return {TokenType::LTE, "<=", startLine, startCol};
        }
        return {TokenType::LT, "<", startLine, startCol};
    } else if (ch == '>') {
        if (current() == '=') {
            advance();
            return {TokenType::GTE, ">=", startLine, startCol};
        }
        return {TokenType::GT, ">", startLine, startCol};
    }
    
    return {TokenType::UNKNOWN, std::string(1, ch), startLine, startCol};
}
