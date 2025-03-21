#pragma once

#include "constants.h"

#include <cstddef>
#include <cstdint>
#include <cstring>

struct node_config {
  uint8_t aes_key[AES_KEY_SIZE];
  uint8_t hmac_key[HMAC_KEY_SIZE];
  node_config(uint8_t aes_k[AES_KEY_SIZE], uint8_t hmac_k[HMAC_KEY_SIZE]) {
    memcpy(aes_key, aes_k, AES_KEY_SIZE);
    memcpy(hmac_key, hmac_k, HMAC_KEY_SIZE);
  }
};

#pragma pack(push, 1)
struct key_exchange_send {
  uint32_t k;
};

struct key_exchange_accept {
  uint8_t accept; // 0 or 1
};

struct dht_config {
  int delay;
};

struct dht_measurement {
  int temperature;
  int humidity;
};

struct bmp_config {
  int delay;
};

struct bmp_measurement {
  int pressure;
};

enum command_type : uint8_t {
  DHT_MEASUREMENT = 0,
  BMP_MEASUREMENT = 1,
  DHT_CONFIG = 2,
  BMP_CONFIG = 3,
  KEY_EXCHANGE_SEND = 4,
  KEY_EXCHANGE_ACCEPT = 5
};

struct send_message {
  // iv and sha256 need to be readable without the encryption
  uint8_t iv[IV_LENGTH];
  uint8_t hash[SHA_HASH_SIZE];
  // the encrypted data (of type message_data)
  uint8_t data[];
};

struct message_data {
  command_type command;
  uint8_t data[];
};

#pragma pack(pop)
