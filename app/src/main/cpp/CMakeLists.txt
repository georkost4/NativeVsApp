cmake_minimum_required(VERSION 3.22.1)
project("ndkversusapp")

# Use relative include directory correctly
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/openssl/include)

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp
        sha256.c
)

# Add OpenSSL static library (prebuilt)
add_library(crypto STATIC IMPORTED)

# Set the path to the .a file for the current ABI
set_target_properties(crypto PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/openssl/libs/${ANDROID_ABI}/libcrypto.a
)

find_library(log-lib log)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        crypto
)