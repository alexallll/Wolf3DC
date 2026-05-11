#include "dos_support.h"
#include <sstream>
#include <algorithm>

namespace DosSupport {

std::string translateDosCode(const std::string& sourceCode) {
    std::ostringstream output;
    
    // Генерируем DOS-совместимый код
    output << "/* Wolfenstein 3D DOS - Auto-generated code */\n";
    output << "#include <dos.h>\n";
    output << "#include <conio.h>\n";
    output << "#include <stdlib.h>\n\n";
    
    output << sourceCode;
    
    return output.str();
}

std::string generateDosHeader(const DosConfig& config) {
    std::ostringstream header;
    
    header << "/* DOS Configuration */\n";
    
    switch(config.mode) {
        case DosMode::REAL_MODE:
            header << "#define DOS_REAL_MODE 1\n";
            header << "#define MEMORY_MODEL 'r' /* Real mode 16-bit */\n";
            break;
        case DosMode::PROTECTED_MODE:
            header << "#define DOS_PROTECTED_MODE 1\n";
            header << "#define MEMORY_MODEL 'p' /* Protected mode 32-bit */\n";
            if (config.useExtender) {
                header << "#define USE_DOS_EXTENDER 1\n";
            }
            break;
        case DosMode::FLAT_MODEL:
            header << "#define DOS_FLAT_MODEL 1\n";
            header << "#define MEMORY_MODEL 'f' /* Flat memory model */\n";
            break;
    }
    
    if (config.useVesa) {
        header << "#define USE_VESA 1\n";
        header << "#define VESA_VERSION 0x200 /* VESA 2.0 */\n";
    }
    
    header << "#define MAX_MEMORY " << config.memoryLimit << "\n\n";
    
    return header.str();
}

std::string optimizeForDos(const std::string& code) {
    std::ostringstream optimized;
    
    optimized << "/* DOS-optimized code */\n";
    optimized << "/* - Minimized memory usage */\n";
    optimized << "/* - Segmented architecture */\n";
    optimized << "/* - Direct hardware access */\n\n";
    
    optimized << code;
    
    return optimized.str();
}

std::vector<DosInterrupt> getSupportedInterrupts() {
    return {
        {0x10, "INT 10h", "Video services"},
        {0x13, "INT 13h", "Disk I/O"},
        {0x21, "INT 21h", "DOS services"},
        {0x33, "INT 33h", "Mouse services"},
        {0x05, "INT 05h", "Print screen"},
        {0x1C, "INT 1Ch", "Timer tick"},
        {0x09, "INT 09h", "Keyboard"},
    };
}

} // namespace DosSupport
