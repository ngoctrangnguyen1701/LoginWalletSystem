#include "totp.h"

/* ==== SHA1 Implementation ==== */

// Ham xoay bit
uint32_t sha1_rol(uint32_t val, int bits) {
  return (val << bits) | (val >> (32 - bits));
}

// Khoi tao SHA1
void sha1_init(SHA1_CTX *ctx) {
  ctx->h[0] = 0x67452301;
  ctx->h[1] = 0xEFCDAB89;
  ctx->h[2] = 0x98BADCFE;
  ctx->h[3] = 0x10325476;
  ctx->h[4] = 0xC3D2E1F0;
  ctx->len = 0;
  ctx->blkused = 0;
}

// Xu li mot khoi du lieu
void sha1_block(SHA1_CTX *ctx) {
  uint32_t w[80], a, b, c, d, e, f, k, temp;
  int i;

  // Chuyen doi khoi du lieu thanh mang w
  for (i = 0; i < 16; i++) {
    w[i] = (ctx->block[i*4] << 24) | (ctx->block[i*4+1] << 16) |
           (ctx->block[i*4+2] << 8) | (ctx->block[i*4+3]);
  }
  for (i = 16; i < 80; i++) {
    w[i] = sha1_rol(w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16], 1);
  }

  // Khoi tao gia tri ban dau
  a = ctx->h[0];
  b = ctx->h[1];
  c = ctx->h[2];
  d = ctx->h[3];
  e = ctx->h[4];

  // Vong lap chinh
  for (i = 0; i < 80; i++) {
    if (i < 20) {
      f = (b & c) | ((~b) & d);
      k = 0x5A827999;
    } else if (i < 40) {
      f = b ^ c ^ d;
      k = 0x6ED9EBA1;
    } else if (i < 60) {
      f = (b & c) | (b & d) | (c & d);
      k = 0x8F1BBCDC;
    } else {
      f = b ^ c ^ d;
      k = 0xCA62C1D6;
    }
    temp = sha1_rol(a,5) + f + e + k + w[i];
    e = d;
    d = c;
    c = sha1_rol(b,30);
    b = a;
    a = temp;
  }

  // Cap nhat gia tri bam
  ctx->h[0] += a;
  ctx->h[1] += b;
  ctx->h[2] += c;
  ctx->h[3] += d;
  ctx->h[4] += e;
}

// Cap nhat du lieu vao SHA1
void sha1_update(SHA1_CTX *ctx, const uint8_t *data, uint32_t len) {
  while (len--) {
    ctx->block[ctx->blkused++] = *data++;
    ctx->len++;
    if (ctx->blkused == 64) {
      sha1_block(ctx);
      ctx->blkused = 0;
    }
  }
}

// Ket thuc SHA1 va lay ket qua
void sha1_final(SHA1_CTX *ctx, uint8_t *digest) {
  uint64_t total_bits = ctx->len * 8;
  sha1_update(ctx, (const uint8_t *)"\x80", 1);
  while (ctx->blkused != 56) {
    sha1_update(ctx, (const uint8_t *)"\x00", 1);
  }

  // Them do dai vao cuoi
  for (int i = 7; i >= 0; i--) {
    uint8_t byte = (total_bits >> (i*8)) & 0xFF;
    sha1_update(ctx, &byte, 1);
  }

  // Lay gia tri bam
  for (int i = 0; i < 5; i++) {
    digest[i*4+0] = (ctx->h[i] >> 24) & 0xFF;
    digest[i*4+1] = (ctx->h[i] >> 16) & 0xFF;
    digest[i*4+2] = (ctx->h[i] >> 8) & 0xFF;
    digest[i*4+3] = (ctx->h[i]) & 0xFF;
  }
}

/* ==== HMAC-SHA1 Implementation ==== */

// Tinh HMAC-SHA1
void hmac_sha1(const uint8_t *key, uint32_t key_len, const uint8_t *msg, uint32_t msg_len, uint8_t *out) {
  uint8_t k_ipad[64], k_opad[64];
  uint8_t tk[20];
  SHA1_CTX ctx;

  // Neu key dai hon 64 byte, bam no
  if (key_len > 64) {
    sha1_init(&ctx);
    sha1_update(&ctx, key, key_len);
    sha1_final(&ctx, tk);
    key = tk;
    key_len = 20;
  }

  // Chuan bi k_ipad va k_opad
  memset(k_ipad, 0x36, 64);
  memset(k_opad, 0x5c, 64);

  for (int i = 0; i < key_len; i++) {
    k_ipad[i] ^= key[i];
    k_opad[i] ^= key[i];
  }

  // Tinh HMAC
  sha1_init(&ctx);
  sha1_update(&ctx, k_ipad, 64);
  sha1_update(&ctx, msg, msg_len);
  sha1_final(&ctx, out);

  sha1_init(&ctx);
  sha1_update(&ctx, k_opad, 64);
  sha1_update(&ctx, out, 20);
  sha1_final(&ctx, out);
}

/* ==== TOTP Implementation ==== */

// Tinh ma TOTP
uint32_t generate_totp(const uint8_t *key, uint32_t key_len, uint64_t time, uint32_t interval) {
  uint64_t counter = time / interval;
  uint8_t msg[8];
  uint8_t hash[20];
  int i;

  // Chuyen doi counter thanh mang byte
  for (i = 7; i >= 0; i--) {
    msg[i] = counter & 0xFF;
    counter >>= 8;
  }

  // Tinh HMAC-SHA1
  hmac_sha1(key, key_len, msg, 8, hash);

  // Lay ma OTP tu hash
  int offset = hash[19] & 0x0F;
  uint32_t bin_code = (hash[offset] & 0x7F) << 24 |
                      (hash[offset+1] & 0xFF) << 16 |
                      (hash[offset+2] & 0xFF) << 8 |
                      (hash[offset+3] & 0xFF);

  return bin_code % 1000000; //Lay 6 chu so
}

int verify_totp(const uint8_t *key, int key_len, uint32_t input_otp, time_t current_time, uint32_t interval) {
  // chap nhan trong khoang t-1, t, t+1 (tuc ±30 giay)
  for (int i = -1; i <= 1; ++i) {
      // current_time + i * interval  // Cong ±60 giay (±1 time window)
      uint32_t otp = generate_totp(key, key_len, current_time + i, interval);
      // uint32_t otp = generate_totp(key, key_len, current_time + i * interval, interval);
      std::cout << "[DEBUG] Generated OTP (" << i << "): " << otp << std::endl;
      if (otp == input_otp)
          return 1; // hop le
  }
  return 0; // khong hop le
}

void generate_user_secret(const uint8_t* master_secret, uint32_t master_len, const std::string &user_id, uint8_t out[20]) {
    hmac_sha1(master_secret, master_len,
              (const uint8_t*)user_id.c_str(), user_id.size(), out);
}
