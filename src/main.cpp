#include "compiler.h"
#include <iostream>
#include <fstream>
#include <sstream>

void printUsage(const char* programName) {
    std::cout << "Использование: " << programName << " <входной_файл> <выходной_файл>" << std::endl;
    std::cout << "Пример: " << programName << " input.c output.cpp" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Ошибка: неправильное количество аргументов!" << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::cout << "=== Компилятор Wolfenstein 3D DOS ===" << std::endl;
    std::cout << "Входной файл: " << inputFile << std::endl;
    std::cout << "Выходной файл: " << outputFile << std::endl;
    std::cout << std::endl;

    Compiler compiler;
    
    if (compiler.compile(inputFile, outputFile)) {
        std::cout << "✓ Компиляция успешно завершена!" << std::endl;
        return 0;
    } else {
        std::cerr << "✗ Ошибка при компиляции!" << std::endl;
        return 1;
    }
}
