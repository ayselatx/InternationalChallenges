#pragma once

#include <AES.h>
#include <Crypto.h>
#include <cstdint>
#include <string>

#pragma pack(push, 1)
struct node_config {
  uint8_t aesKey[32];
  void setAesFromString(const uint8_t key[32]) {}
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

enum command_type {
  DHT_MEASUREMENT = 0,
  BMP_MEASUREMENT = 1,
  DHT_CONFIG = 2,
  BMP_CONFIG = 3,
  NODE_CONFIG = 4
};

struct send_message {
  command_type command;
  union {
    dht_measurement dht_meas;
    bmp_measurement bmp_meas;
    dht_config dht_cfg;
    bmp_config bmp_cfg;
    node_config node_cfg;
  };
};
#pragma pack(pop)
