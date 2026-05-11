#ifndef DOS_SUPPORT_H
#define DOS_SUPPORT_H

#include <string>
#include <vector>

namespace DosSupport {
    // DOS режимы
    enum class DosMode {
        REAL_MODE,      // 16-bit real mode
        PROTECTED_MODE, // 32-bit protected mode
        FLAT_MODEL      // Flat memory model
    };
    
    // Структура для DOS конфига
    struct DosConfig {
        DosMode mode;
        bool useExtender;  // DOS Extender (для protected mode)
        bool useVesa;      // VESA для видео
        uint16_t memoryLimit; // Максимальная память
    };
    
    // Функции для обработки DOS кода
    std::string translateDosCode(const std::string& sourceCode);
    std::string generateDosHeader(const DosConfig& config);
    std::string optimizeForDos(const std::string& code);
    
    // Поддержка DOS прерываний
    struct DosInterrupt {
        uint8_t number;
        std::string name;
        std::string description;
    };
    
    std::vector<DosInterrupt> getSupportedInterrupts();
}

#endif // DOS_SUPPORT_H
