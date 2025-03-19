#pragma once

#include "constants.h"

#include <cstddef>
#include <cstdint>

#pragma pack(push, 1)
struct node_config {
  uint8_t aes_key[AES_KEY_SIZE];
  uint8_t hmac_key[HMAC_KEY_SIZE];
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
  NODE_CONFIG = 4
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
