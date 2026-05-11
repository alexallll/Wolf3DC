#include "compiler.h"
#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "W3D Compiler - Wolfenstein 3D C to C++ Compiler\n";
        std::cout << "Usage: w3d_compiler <input.c> <output.cpp> [options]\n\n";
        std::cout << "Options:\n";
        std::cout << "  --target dos         Compile for DOS\n";
        std::cout << "  --target android     Compile for Android\n";
        std::cout << "  --mode real          DOS real mode (16-bit)\n";
        std::cout << "  --mode protected     DOS protected mode (32-bit)\n";
        std::cout << "  --vesa               Enable VESA video support (DOS)\n";
        std::cout << "  --arch arm           Android ARM architecture\n";
        std::cout << "  --arch arm64         Android ARM64 architecture\n";
        std::cout << "  --optimize O2        Optimization level (O0-O3, Os)\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::string target = "native";
    std::string dosMode = "protected";
    std::string androidArch = "arm64";
    std::string optimLevel = "O2";
    bool useVesa = false;

    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--target") == 0 && i + 1 < argc) {
            target = argv[++i];
        }
        else if (strcmp(argv[i], "--mode") == 0 && i + 1 < argc) {
            dosMode = argv[++i];
        }
        else if (strcmp(argv[i], "--arch") == 0 && i + 1 < argc) {
            androidArch = argv[++i];
        }
        else if (strcmp(argv[i], "--vesa") == 0) {
            useVesa = true;
        }
        else if (strcmp(argv[i], "--optimize") == 0 && i + 1 < argc) {
            optimLevel = argv[++i];
        }
    }

    Compiler compiler;

    std::cout << "W3D Compiler v1.0\n";
    std::cout << "Input:  " << inputFile << "\n";
    std::cout << "Output: " << outputFile << "\n";
    std::cout << "Target: " << target << "\n";

    if (target == "dos") {
        std::cout << "DOS Mode: " << dosMode << "\n";
        if (useVesa) {
            std::cout << "VESA: Enabled\n";
        }
    }
    else if (target == "android") {
        std::cout << "Android Arch: " << androidArch << "\n";
    }

    std::cout << "Optimization: " << optimLevel << "\n";
    std::cout << "\nCompiling...\n";

    if (compiler.compile(inputFile, outputFile)) {
        std::cout << "Compilation successful!\n";
        return 0;
    }
    else {
        std::cerr << "Compilation failed!\n";
        return 1;
    }
}
