#include "dos_support.h"
#include <algorithm>
#include <unordered_map>

namespace DosSupport {
    
    std::string translateDosCode(const std::string& sourceCode) {
        std::string output = sourceCode;
        
        // Заменяем DOS-специфичные функции
        std::unordered_map<std::string, std::string> dosReplacements = {
            {"int86", "dos_int86"},           // Вызов прерывания
            {"int86x", "dos_int86x"},         // Расширенный вызов
            {"geninterrupt", "dos_interrupt"}, // Прерывание
            {"_dos_open", "dos_file_open"},   // Открытие файла
            {"_dos_read", "dos_file_read"},   // Чтение файла
            {"_dos_write", "dos_file_write"}, // Запись файла
            {"outp", "dos_outport"},          // Вывод в порт
            {"inp", "dos_inport"},            // Ввод из порта
            {"peek", "dos_peek_mem"},         // Чтение памяти
            {"poke", "dos_poke_mem"}          // Запись в память
        };
        
        for (const auto& [old, replacement] : dosReplacements) {
            size_t pos = 0;
            while ((pos = output.find(old, pos)) != std::string::npos) {
                output.replace(pos, old.length(), replacement);
                pos += replacement.length();
            }
        }
        
        return output;
    }
    
    std::string generateDosHeader(const DosConfig& config) {
        std::string header;
        
        header += "// ===== DOS Configuration Header =====\n";
        header += "#pragma pack(1)\n";
        header += "#define DOS_REAL_MODE 0\n";
        header += "#define DOS_PROTECTED_MODE 1\n";
        header += "#define DOS_FLAT_MODEL 2\n\n";
        
        header += "// DOS Mode: ";
        switch (config.mode) {
            case DosMode::REAL_MODE:
                header += "Real Mode (16-bit)\n";
                break;
            case DosMode::PROTECTED_MODE:
                header += "Protected Mode (32-bit)\n";
                break;
            case DosMode::FLAT_MODEL:
                header += "Flat Model\n";
                break;
        }
        
        header += "// Memory Limit: " + std::to_string(config.memoryLimit) + " KB\n";
        header += "// VESA Support: " + std::string(config.useVesa ? "Enabled" : "Disabled") + "\n";
        header += "// DOS Extender: " + std::string(config.useExtender ? "Enabled" : "Disabled") + "\n\n";
        
        // Стандартные включения для DOS
        header += "#include <dos.h>\n";
        header += "#include <conio.h>\n";
        header += "#include <stdio.h>\n";
        header += "#include <stdlib.h>\n\n";
        
        return header;
    }
    
    std::string optimizeForDos(const std::string& code) {
        std::string optimized = code;
        
        // Удаляем C++ специфичные конструкции
        std::vector<std::string> cpp_keywords = {
            "std::", "class ", "template", "namespace", "using namespace"
        };
        
        for (const auto& keyword : cpp_keywords) {
            size_t pos = 0;
            while ((pos = optimized.find(keyword, pos)) != std::string::npos) {
                optimized.erase(pos, keyword.length());
            }
        }
        
        return optimized;
    }
    
    std::vector<DosInterrupt> getSupportedInterrupts() {
        std::vector<DosInterrupt> interrupts = {
            {0x10, "VIDEO", "Video BIOS interrupt"},
            {0x13, "DISK", "Disk BIOS interrupt"},
            {0x16, "KEYBOARD", "Keyboard BIOS interrupt"},
            {0x21, "DOS", "DOS interrupt"},
            {0x33, "MOUSE", "Mouse interrupt"},
            {0x1A, "TIME", "Time interrupt"}
        };
        return interrupts;
    }
}
