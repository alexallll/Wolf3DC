#include "compiler.h"
#include "lexer.h"
#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

Compiler::Compiler() 
    : lexer(std::make_unique<Lexer>()),
      parser(std::make_unique<Parser>()) {
}

Compiler::~Compiler() {}

bool Compiler::compile(const std::string& inputFile, const std::string& outputFile) {
    // Читаем исходный файл
    std::string sourceCode;
    if (!readSourceFile(inputFile, sourceCode)) {
        std::cerr << "Ошибка: не удалось прочитать файл " << inputFile << std::endl;
        return false;
    }

    std::cout << "1. Лексический анализ..." << std::endl;
    // Лексический анализ
    auto tokens = lexer->tokenize(sourceCode);
    std::cout << "   Найдено токенов: " << tokens.size() << std::endl;

    std::cout << "2. Синтаксический анализ..." << std::endl;
    // Синтаксический анализ
    auto ast = parser->parse(tokens);
    std::cout << "   AST построено успешно" << std::endl;

    std::cout << "3. Генерация кода..." << std::endl;
    // Генерируем выходной код (пока простой вывод)
    std::stringstream output;
    output << "// Скомпилировано из: " << inputFile << "\n";
    output << "// Автоматически сгенерированный код\n\n";
    output << "#include <iostream>\n";
    output << "#include <cstdint>\n\n";
    
    // TODO: добавить реальную генерацию кода из AST
    output << "// TODO: имплементация генерации кода\n";
    output << "// Было обработано " << tokens.size() << " токенов\n";

    std::cout << "   Код сгенерирован" << std::endl;

    std::cout << "4. Запись результата..." << std::endl;
    // Записываем результат
    if (!writeOutputFile(outputFile, output.str())) {
        std::cerr << "Ошибка: не удалось записать файл " << outputFile << std::endl;
        return false;
    }

    std::cout << "   Результат записан в " << outputFile << std::endl;
    return true;
}

bool Compiler::readSourceFile(const std::string& filename, std::string& content) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();
    file.close();

    return true;
}

bool Compiler::writeOutputFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << content;
    file.close();

    return true;
}
