#ifndef ANDROID_SUPPORT_H
#define ANDROID_SUPPORT_H

#include <string>
#include <vector>

namespace AndroidSupport {
    // Целевые платформы для Android
    enum class AndroidArch {
        ARM,       // ARMv7
        ARM64,     // ARM64/ARMv8
        X86,       // Intel x86
        X86_64     // Intel x86-64
    };
    
    // Конфиг для Android
    struct AndroidConfig {
        AndroidArch arch;
        int minApiLevel;  // Минимальный API level (21+)
        std::string packageName;
        std::string appName;
    };
    
    // Функции для трансляции на Android
    std::string translateToAndroid(const std::string& dosCode);
    std::string generateAndroidManifest(const AndroidConfig& config);
    std::string generateJNI(const std::string& code);
    std::string generateOpenGLES(const std::string& renderCode);
    
    // Получить подходящую архитектуру
    AndroidArch getDefaultArch();
}

#endif // ANDROID_SUPPORT_H
