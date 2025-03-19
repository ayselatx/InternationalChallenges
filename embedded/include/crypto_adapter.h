#pragma once

// custom headers
#include "constants.h"
#include "data_types.h"

// esp8266 osapi lib
#include "osapi.h"

// arduino libs
#include <AES.h>
#include <CTR.h>
#include <SHA256.h>

// std libs
#include <algorithm>

enum class encrypt_error : uint8_t { OK, BAD_DATA_LENGTH };
enum class decrypt_error : uint8_t { OK, BAD_DATA_LENGTH, WRONG_HASH };

// maybe use ed25519 for key exchange
// https://rweather.github.io/arduinolibs/classEd25519.html
class CryptoAdapter {
private:
  // https://rweather.github.io/arduinolibs/classCBC.html
  // https://rweather.github.io/arduinolibs/classAESCommon.html
  CTR<AES256> _ctr;
  // https://rweather.github.io/arduinolibs/classSHA256.html
  SHA256 _sha;
  uint8_t _hmac_key[HMAC_KEY_SIZE];

public:
  CryptoAdapter(node_config *config);

  bool isCorrectDataLength(uint32_t length);

  void updateConfig(const node_config *config);

  // every message needs to be divisible by the block size
  static constexpr uint32_t getBlockSize() {
    return std::max(AES_BLOCK_SIZE, SHA_BLOCK_SIZE);
  }

  static constexpr uint32_t toValidSize(uint32_t size) {
    uint32_t blockSize = CryptoAdapter::getBlockSize();
    return size + (blockSize - size % blockSize) % blockSize;
  }

  encrypt_error encryptData(uint8_t *output_data, const uint8_t *input_data,
                            uint32_t data_length, uint8_t iv[IV_LENGTH]);

  decrypt_error decryptData(uint8_t *output_data, const uint8_t *input_data,
                            uint32_t data_length, uint8_t iv[IV_LENGTH]);

  encrypt_error computeHash(const uint8_t *data, uint32_t data_length,
                            uint8_t output_hash[SHA_HASH_SIZE]);

  encrypt_error encryptMessage(const uint8_t *input, uint8_t *output,
                               uint32_t data_length);

  decrypt_error decryptMessage(const uint8_t *input, uint8_t *output,
                               uint32_t data_length);
};
