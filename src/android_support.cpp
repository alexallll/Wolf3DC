#include "android_support.h"
#include <sstream>

namespace AndroidSupport {

std::string translateToAndroid(const std::string& dosCode) {
    std::ostringstream output;
    
    output << "/* Wolfenstein 3D Android - Auto-generated JNI code */\n";
    output << "#include <jni.h>\n";
    output << "#include <android/log.h>\n";
    output << "#include <GLES2/gl2.h>\n\n";
    
    output << "#define LOG_TAG \"W3D\"\n";
    output << "#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)\n";
    output << "#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)\n\n";
    
    output << dosCode;
    
    return output.str();
}

std::string generateAndroidManifest(const AndroidConfig& config) {
    std::ostringstream manifest;
    
    manifest << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    manifest << "<manifest xmlns:android=\"http://schemas.android.com/apk/res/android\"\n";
    manifest << "    package=\"" << config.packageName << "\"\n";
    manifest << "    android:versionCode=\"1\"\n";
    manifest << "    android:versionName=\"1.0\">\n\n";
    
    manifest << "    <uses-sdk\n";
    manifest << "        android:minSdkVersion=\"" << config.minApiLevel << "\"\n";
    manifest << "        android:targetSdkVersion=\"31\" />\n\n";
    
    manifest << "    <uses-permission android:name=\"android.permission.INTERNET\" />\n";
    manifest << "    <uses-permission android:name=\"android.permission.ACCESS_NETWORK_STATE\" />\n\n";
    
    manifest << "    <uses-feature android:name=\"android.hardware.gamepad\" android:required=\"false\" />\n";
    manifest << "    <uses-feature android:name=\"android.hardware.touchscreen\" />\n\n";
    
    manifest << "    <application\n";
    manifest << "        android:allowBackup=\"true\"\n";
    manifest << "        android:icon=\"@mipmap/ic_launcher\"\n";
    manifest << "        android:label=\"" << config.appName << "\"\n";
    manifest << "        android:supportsRtl=\"true\">\n\n";
    
    manifest << "        <activity android:name=\".MainActivity\"\n";
    manifest << "            android:screenOrientation=\"landscape\"\n";
    manifest << "            android:exported=\"true\">\n";
    manifest << "            <intent-filter>\n";
    manifest << "                <action android:name=\"android.intent.action.MAIN\" />\n";
    manifest << "                <category android:name=\"android.intent.category.LAUNCHER\" />\n";
    manifest << "            </intent-filter>\n";
    manifest << "        </activity>\n\n";
    
    manifest << "    </application>\n\n";
    manifest << "</manifest>\n";
    
    return manifest.str();
}

std::string generateJNI(const std::string& code) {
    std::ostringstream jni;
    
    jni << "/* JNI Native Library */\n";
    jni << "\nextern \"C\" {\n\n";
    
    jni << "JNIEXPORT void JNICALL\n";
    jni << "Java_com_wolf3d_game_GameEngine_init(JNIEnv* env, jobject obj,\n";
    jni << "                                      jint width, jint height) {\n";
    jni << "    LOGI(\"GameEngine init: %dx%d\", width, height);\n";
    jni << "}\n\n";
    
    jni << "JNIEXPORT void JNICALL\n";
    jni << "Java_com_wolf3d_game_GameEngine_render(JNIEnv* env, jobject obj) {\n";
    jni << "    // Render game frame\n";
    jni << "}\n\n";
    
    jni << "JNIEXPORT void JNICALL\n";
    jni << "Java_com_wolf3d_game_GameEngine_destroy(JNIEnv* env, jobject obj) {\n";
    jni << "    LOGI(\"GameEngine destroyed\");\n";
    jni << "}\n\n";
    
    jni << "}\n";
    
    return jni.str();
}

std::string generateOpenGLES(const std::string& renderCode) {
    std::ostringstream gles;
    
    gles << "/* OpenGL ES 2.0 Renderer */\n";
    gles << "\n#ifdef USE_OPENGL_ES\n";
    gles << "static GLuint shaderProgram;\n";
    gles << "static GLuint vertexBuffer;\n";
    gles << "static GLuint indexBuffer;\n\n";
    
    gles << "void initOpenGLES() {\n";
    gles << "    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);\n";
    gles << "    glEnable(GL_DEPTH_TEST);\n";
    gles << "    glEnable(GL_CULL_FACE);\n";
    gles << "}\n\n";
    
    gles << "void renderOpenGLES() {\n";
    gles << "    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);\n";
    gles << "    glUseProgram(shaderProgram);\n";
    gles << "    // Render geometry\n";
    gles << "}\n\n";
    
    gles << "#endif\n";
    
    return gles.str();
}

AndroidArch getDefaultArch() {
    // На практике определяется архитектурой хоста
    return AndroidArch::ARM64;
}

} // namespace AndroidSupport
