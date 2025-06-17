#ifndef TOTP_H
#define TOTP_H

#include <iostream>
#include <stdint.h>
#include <string.h>
#include <string>
#include <time.h>

/* ==== SHA1 ==== */

#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20

typedef struct {
  uint32_t h[5];
  uint64_t len;
  uint8_t block[64];
  uint32_t blkused;
} SHA1_CTX;

// Function declarations
uint32_t sha1_rol(uint32_t val, int bits);
void sha1_init(SHA1_CTX *ctx);
void sha1_block(SHA1_CTX *ctx);
void sha1_update(SHA1_CTX *ctx, const uint8_t *data, uint32_t len);
void sha1_final(SHA1_CTX *ctx, uint8_t *digest);

/* ==== HMAC-SHA1 ==== */
void hmac_sha1(const uint8_t *key, uint32_t key_len, const uint8_t *msg, uint32_t msg_len, uint8_t *out);

/* ==== TOTP ==== */
uint32_t generate_totp(const uint8_t *key, uint32_t key_len, uint64_t time, uint32_t interval);
int verify_totp(const uint8_t *key, int key_len, uint32_t input_otp, time_t current_time, uint32_t interval);
void generate_user_secret(const uint8_t* master_secret, uint32_t master_len, const std::string &user_id, uint8_t out[20]);

#endif   // TOTP_H
