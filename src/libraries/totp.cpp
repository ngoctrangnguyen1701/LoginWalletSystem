#include "totp.h"
#include "sha1.h"

#include <iostream> // debug
#include <string.h> // memset (nếu dùng lại)
#include <time.h>   // time_t
#include <string>

/* ==== TOTP Implementation ==== */

// Tinh ma TOTP
uint32_t generate_totp(const uint8_t *key, uint32_t key_len, uint64_t time, uint32_t interval) {
  uint64_t counter = time / interval;
  uint8_t msg[8];
  uint8_t hash[20];
  int i;

  std::cout << "[DEBUG] generate_totp -> counter (" << counter << ")" << std::endl;


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

uint32_t generate_totp_with_counter(const uint8_t *key, uint32_t key_len, uint64_t counter) {
  // uint64_t counter = time / interval;
  uint8_t msg[8];
  uint8_t hash[20];
  int i;

  // std::cout << "[DEBUG] generate_totp_with_counter -> counter (" << counter << ")" << std::endl;


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

  return bin_code % 1000000;
}

bool verify_totp(const uint8_t *key, int key_len, uint32_t input_otp, time_t current_time, uint32_t interval) {
  // chap nhan trong khoang t-1, t, t+1 (tuc ±30 giay)
  uint64_t current_counter = current_time / interval;
  // time_t current_time_param = current_time + i * interval;
  for (int i = -1; i <= 1; ++i) {
      // current_time + i * interval  // Cong ±60 giay (±1 time window)
      // uint32_t otp = generate_totp(key, key_len, current_time + i, interval);
      // uint32_t otp = generate_totp(key, key_len, current_time + i * interval, interval);
      uint32_t otp = generate_totp_with_counter(key, key_len, current_counter + i);
      // std::cout << "[DEBUG] verify_totp (" << i << "): " << otp << std::endl;
      if (otp == input_otp)
          return true; // hop le
  }
  return false; // khong hop le
}

void generate_user_secret(const uint8_t* master_secret, uint32_t master_len, const std::string &user_id, uint8_t out[20]) {
    hmac_sha1(master_secret, master_len,
              (const uint8_t*)user_id.c_str(), user_id.size(), out);
}
