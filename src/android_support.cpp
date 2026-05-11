#include "android_support.h"

namespace AndroidSupport {
    
    std::string translateToAndroid(const std::string& dosCode) {
        std::string output;
        
        output += "// Android JNI Bridge\n";
        output += "#include <jni.h>\n";
        output += "#include <android/log.h>\n";
        output += "#include <GLES2/gl2.h>\n\n";
        
        output += "#define LOG_TAG \"W3D\"\n";
        output += "#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)\n";
        output += "#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)\n";
        output += "#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)\n\n";
        
        // Заменяем DOS функции на Android эквиваленты
        output += "// DOS to Android mappings\n";
        output += "typedef int (*dos_interrupt_handler)(int interrupt_num);\n";
        output += "typedef void (*video_callback)();\n\n";
        
        // Добавляем JNI функции
        output += "extern \"C\" {\n";
        output += "    JNIEXPORT void JNICALL Java_com_w3d_Engine_nativeInit(JNIEnv* env, jobject obj);\n";
        output += "    JNIEXPORT void JNICALL Java_com_w3d_Engine_nativeRender(JNIEnv* env, jobject obj);\n";
        output += "    JNIEXPORT void JNICALL Java_com_w3d_Engine_nativeOnTouch(JNIEnv* env, jobject obj, jfloat x, jfloat y);\n";
        output += "}\n\n";
        
        // Интегрируем оригинальный код
        output += "// Original W3D code:\n";
        output += dosCode;
        
        return output;
    }
    
    std::string generateAndroidManifest(const AndroidConfig& config) {
        std::string manifest;
        
        manifest += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
        manifest += "<manifest xmlns:android=\"http://schemas.android.com/apk/res/android\"\n";
        manifest += "    package=\"" + config.packageName + "\">\n\n";
        
        manifest += "    <uses-permission android:name=\"android.permission.INTERNET\" />\n";
        manifest += "    <uses-permission android:name=\"android.permission.ACCESS_NETWORK_STATE\" />\n\n";
        
        manifest += "    <application\n";
        manifest += "        android:label=\"@string/app_name\">\n";
        manifest += "        <activity\n";
        manifest += "            android:name=\".MainActivity\"\n";
        manifest += "            android:screenOrientation=\"landscape\">\n";
        manifest += "            <intent-filter>\n";
        manifest += "                <action android:name=\"android.intent.action.MAIN\" />\n";
        manifest += "                <category android:name=\"android.intent.category.LAUNCHER\" />\n";
        manifest += "            </intent-filter>\n";
        manifest += "        </activity>\n";
        manifest += "    </application>\n";
        manifest += "</manifest>\n";
        
        return manifest;
    }
    
    std::string generateJNI(const std::string& code) {
        std::string jni;
        
        jni += "// Auto-generated JNI Bridge\n";
        jni += "#include <jni.h>\n";
        jni += "#include <android/log.h>\n\n";
        
        jni += "static bool initialized = false;\n\n";
        
        jni += "extern \"C\" {\n";
        jni += "    JNIEXPORT void JNICALL\n";
        jni += "    Java_com_w3d_Engine_nativeInit(JNIEnv* env, jobject obj) {\n";
        jni += "        __android_log_print(ANDROID_LOG_INFO, \"W3D\", \"Initializing engine...\");\n";
        jni += "        // Init code here\n";
        jni += "        initialized = true;\n";
        jni += "    }\n\n";
        
        jni += "    JNIEXPORT void JNICALL\n";
        jni += "    Java_com_w3d_Engine_nativeRender(JNIEnv* env, jobject obj) {\n";
        jni += "        if (initialized) {\n";
        jni += "            // Render code here\n";
        jni += "        }\n";
        jni += "    }\n";
        jni += "}\n";
        
        return jni;
    }
    
    std::string generateOpenGLES(const std::string& renderCode) {
        std::string gles;
        
        gles += "#include <GLES2/gl2.h>\n";
        gles += "#include <glm/glm.hpp>\n\n";
        
        gles += "// OpenGL ES 2.0 Shaders\n";
        gles += "const char* vertexShaderSource = R\"(\n";
        gles += "    #version 100\n";
        gles += "    uniform mat4 projection;\n";
        gles += "    attribute vec4 position;\n";
        gles += "    void main() {\n";
        gles += "        gl_Position = projection * position;\n";
        gles += "    }\n";
        gles += ")\";\n\n";
        
        gles += "const char* fragmentShaderSource = R\"(\n";
        gles += "    #version 100\n";
        gles += "    precision mediump float;\n";
        gles += "    uniform sampler2D texture;\n";
        gles += "    varying vec2 texCoord;\n";
        gles += "    void main() {\n";
        gles += "        gl_FragColor = texture2D(texture, texCoord);\n";
        gles += "    }\n";
        gles += ")\";\n";
        
        return gles;
    }
    
    AndroidArch getDefaultArch() {
        return AndroidArch::ARM64;
    }
}
