// native-lib.cpp
#include <jni.h>
#include <string>
#include <chrono>
#include "sha256.h"  // your SHA-256 implementation
#include <sha.h> // OpenSSL

extern "C"
JNIEXPORT jlong JNICALL
Java_gr_george_axd_ndkversusapp_MainActivity_nativeSha256(
        JNIEnv *env,
        jobject /* this */,
        jbyteArray input) {

    jsize len = env->GetArrayLength(input);
    jbyte *data = (jbyte *)env->GetPrimitiveArrayCritical(input, nullptr);

    uint8_t hash[32];

    auto start = std::chrono::high_resolution_clock::now();
    sha256((uint8_t*)data, len, hash);
    auto end = std::chrono::high_resolution_clock::now();

    env->ReleasePrimitiveArrayCritical(input, data, JNI_ABORT);

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

extern "C"
JNIEXPORT jlong JNICALL
Java_gr_george_axd_ndkversusapp_MainActivity_nativeSha256OpenSSL(
        JNIEnv *env, jobject, jbyteArray input) {

    jsize len = env->GetArrayLength(input);
    jbyte *data = (jbyte *) env->GetPrimitiveArrayCritical(input, nullptr);

    uint8_t hash[SHA256_DIGEST_LENGTH];
    auto start = std::chrono::high_resolution_clock::now();
    SHA256((const unsigned char*)data, len, hash);  // OpenSSL SHA256
    auto end = std::chrono::high_resolution_clock::now();

    env->ReleasePrimitiveArrayCritical(input, data, JNI_ABORT);

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

extern "C" JNIEXPORT jlong JNICALL
Java_gr_george_axd_ndkversusapp_MainActivity_nativeSimpleComputation(
        JNIEnv *env, jobject, jbyteArray input) {

    jsize len = env->GetArrayLength(input);
    jbyte *data = (jbyte *) env->GetPrimitiveArrayCritical(input, nullptr);

    volatile long long sum = 0; // Use volatile to prevent compiler optimizing away the loop completely
    auto start = std::chrono::high_resolution_clock::now();

    // Simple computation example: sum up byte values
    for (jsize i = 0; i < len; ++i) {
        sum += data[i]; // Or data[i] ^ (i % 256) for more "computation"
    }

    auto end = std::chrono::high_resolution_clock::now();
    env->ReleasePrimitiveArrayCritical(input, data, JNI_ABORT);

    // Return sum or time, whatever you want to benchmark
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}