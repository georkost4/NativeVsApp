/*********************************************************************
* Filename:   sha256.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding SHA256 implementation.
*********************************************************************/

#ifndef SHA256_H
#define SHA256_H

#ifdef __cplusplus
extern "C" {
#endif

/*************************** HEADER FILES ***************************/
#include <stddef.h>
#include <stdint.h>  // needed for uint8_t

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned int  WORD;             // 32-bit word, change to "long" for 16-bit machines

typedef struct {
    BYTE data[64];
    WORD datalen;
    unsigned long long bitlen;
    WORD state[8];
} MY_SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
// Convenience wrapper: hash entire input at once
void sha256(const uint8_t *data, size_t len, uint8_t hash[32]);

#ifdef __cplusplus
}
#endif

#endif   // SHA256_H