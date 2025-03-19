#pragma once

#include <AES.h>
#include <Arduino.h>
#include <Crypto.h>
#include <cstdint>
#include <string>

#pragma pack(push, 1)
struct node_config {
  uint8_t aesKey[32];
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

class Crypto {
private:
  AES256 aes;

  bool checkCorrectDataLength(int length) {
    if (length < aes.blockSize()) {
      // the data is too small
      return false;
    }
    if (length % aes.blockSize() != 0) {
      // the data needs to be padded to match the block size
      return false;
    }
    return true;
  }

public:
  bool setKey(const uint8_t aesKey[32]) { return aes.setKey(aesKey, 32); }

  uint32_t getBlockSize() { return aes.blockSize(); }

  bool encryptData(uint8_t *output, const uint8_t *input, int length) {
    if (!checkCorrectDataLength(length))
      return false;
    for (int i = 0; i < length % aes.blockSize(); i++) {
      bool done = aes.encryptBlock(&output[i * aes.blockSize()],
                                   &input[i * aes.blockSize()]);
      if (!done)
        return false;
    }
    return true;
  };

  bool decryptData(uint8_t *output, const uint8_t *input, int length) {
    if (!checkCorrectDataLength(length))
      return false;
    for (int i = 0; i < length % aes.blockSize(); i++) {
      bool done = aes.decryptBlock(&output[i * aes.blockSize()],
                                   &input[i * aes.blockSize()]);
      if (!done)
        return false;
    }
    return true;
  }
};
