#ifndef TOTP_H
#define TOTP_H

#include <stdint.h>
#include <string>

uint32_t generate_totp(const uint8_t *key, uint32_t key_len, uint64_t time, uint32_t interval);
uint32_t generate_totp_with_counter(const uint8_t *key, uint32_t key_len, uint64_t counter);
bool verify_totp(const uint8_t *key, int key_len, uint32_t input_otp, time_t current_time, uint32_t interval);
void generate_user_secret(const uint8_t* master_secret, uint32_t master_len, const std::string &user_id, uint8_t out[20]);

#endif