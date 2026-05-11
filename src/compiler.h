#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <vector>
#include <memory>

class Lexer;
class Parser;

class Compiler {
public:
    Compiler();
    ~Compiler();
    
    bool compile(const std::string& inputFile, const std::string& outputFile);
    
private:
    std::unique_ptr<Lexer> lexer;
    std::unique_ptr<Parser> parser;
    
    bool readSourceFile(const std::string& filename, std::string& content);
    bool writeOutputFile(const std::string& filename, const std::string& content);
};

#endif // COMPILER_H
