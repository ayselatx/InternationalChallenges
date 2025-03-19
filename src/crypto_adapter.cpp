// custom headers
#include "crypto_adapter.h"
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

CryptoAdapter::CryptoAdapter(node_config *config) {
  this->updateConfig(config);
}

bool CryptoAdapter::isCorrectDataLength(uint32_t length) {
  if (length < this->getBlockSize()) {
    // the data is too small
    return false;
  }
  if (length % this->getBlockSize() != 0) {
    // the data needs to be padded to match the block size
    return false;
  }
  return true;
}

void CryptoAdapter::updateConfig(const node_config *config) {
  _ctr.setKey(config->aes_key, AES_KEY_SIZE);
  memcpy(_hmac_key, config->hmac_key, HMAC_KEY_SIZE);
}

encrypt_error CryptoAdapter::encryptData(uint8_t *output_data,
                                         const uint8_t *input_data,
                                         uint32_t data_length,
                                         uint8_t iv[IV_LENGTH]) {
  if (!isCorrectDataLength(data_length))
    return encrypt_error::BAD_DATA_LENGTH;

  _ctr.setIV(iv, IV_LENGTH);
  _ctr.encrypt(output_data, input_data, data_length);

  return encrypt_error::OK;
};

decrypt_error CryptoAdapter::decryptData(uint8_t *output_data,
                                         const uint8_t *input_data,
                                         uint32_t data_length,
                                         uint8_t iv[IV_LENGTH]) {
  if (!isCorrectDataLength(data_length))
    return decrypt_error::BAD_DATA_LENGTH;

  _ctr.setIV(iv, IV_LENGTH);
  _ctr.decrypt(output_data, input_data, data_length);

  return decrypt_error::OK;
}

encrypt_error CryptoAdapter::computeHash(const uint8_t *data,
                                         uint32_t data_length,
                                         uint8_t output_hash[SHA_HASH_SIZE]) {
  if (!isCorrectDataLength(data_length))
    return encrypt_error::BAD_DATA_LENGTH;

  _sha.resetHMAC(_hmac_key, HMAC_KEY_SIZE);
  _sha.update(data, data_length);
  _sha.finalizeHMAC(_hmac_key, HMAC_KEY_SIZE, output_hash, SHA_HASH_SIZE);

  return encrypt_error::OK;
}

encrypt_error CryptoAdapter::encryptMessage(const uint8_t *input,
                                            uint8_t *output,
                                            uint32_t data_length) {
  if (!isCorrectDataLength(data_length))
    return encrypt_error::BAD_DATA_LENGTH;

  send_message *input_msg = (send_message *)input;
  send_message *output_msg = (send_message *)output;

  os_get_random(output_msg->iv, IV_LENGTH);
  this->encryptData(input_msg->data, output_msg->data, data_length,
                    output_msg->iv);
  this->computeHash(output_msg->data, data_length, output_msg->hash);

  return encrypt_error::OK;
}

decrypt_error CryptoAdapter::decryptMessage(const uint8_t *input,
                                            uint8_t *output,
                                            uint32_t data_length) {
  if (!isCorrectDataLength(data_length))
    return decrypt_error::BAD_DATA_LENGTH;

  send_message *input_msg = (send_message *)input;
  send_message *output_msg = (send_message *)output;
  this->decryptData(input_msg->data, output_msg->data, data_length,
                    output_msg->iv);

  uint8_t hash[SHA_HASH_SIZE];
  this->computeHash(input_msg->data, data_length, hash);

  if (memcmp(input_msg->hash, hash, SHA_HASH_SIZE) != 0) {
    return decrypt_error::WRONG_HASH;
  }

  return decrypt_error::OK;
}
