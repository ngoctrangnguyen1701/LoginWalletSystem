// https://github.com/B-Con/crypto-algorithms

/*********************************************************************
* Filename:   sha256.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding SHA1 implementation.
*********************************************************************/

#ifndef SHA256_H
#define SHA256_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/
typedef unsigned char MY_BYTE;             // 8-bit byte
typedef unsigned int  MY_WORD;             // 32-bit word, change to "long" for 16-bit machines

typedef struct {
	MY_BYTE data[64];
	MY_WORD datalen;
	unsigned long long bitlen;
	MY_WORD state[8];
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const MY_BYTE data[], size_t len);
void sha256_final(SHA256_CTX *ctx, MY_BYTE hash[]);

#endif   // SHA256_H
