#ifndef SHA1_H
#define SHA1_H

#include <stdint.h>

#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20

typedef struct {
    uint32_t h[5];
    uint64_t len;
    uint8_t block[64];
    uint32_t blkused;
} SHA1_CTX;

void sha1_init(SHA1_CTX *ctx);
void sha1_update(SHA1_CTX *ctx, const uint8_t *data, uint32_t len);
void sha1_final(SHA1_CTX *ctx, uint8_t *digest);
void hmac_sha1(const uint8_t *key, uint32_t key_len,
               const uint8_t *msg, uint32_t msg_len, uint8_t *out);

#endif
