#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    // Ключевые слова
    KW_INT,
    KW_CHAR,
    KW_VOID,
    KW_IF,
    KW_ELSE,
    KW_FOR,
    KW_WHILE,
    KW_RETURN,
    KW_STRUCT,
    
    // Операторы
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PERCENT,
    ASSIGN,
    EQ,
    NEQ,
    LT,
    GT,
    LTE,
    GTE,
    
    // Разделители
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,
    SEMICOLON,
    COMMA,
    DOT,
    
    // Литералы
    IDENTIFIER,
    NUMBER,
    STRING,
    
    // Конец файла
    EOF_TOKEN,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

class Lexer {
public:
    Lexer();
    ~Lexer();
    
    std::vector<Token> tokenize(const std::string& source);
    
private:
    std::string source;
    size_t position;
    int line;
    int column;
    
    char current();
    char peek(size_t offset = 1);
    void advance();
    void skipWhitespace();
    void skipComment();
    
    Token readIdentifierOrKeyword();
    Token readNumber();
    Token readString();
    Token readOperator();
};

#endif // LEXER_H
