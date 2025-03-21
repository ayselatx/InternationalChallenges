#include <Arduino.h>
#include <DHT11.h>
#include <LoRa.h>

#include "constants.h"
#include "crypto_adapter.h"
#include "data_types.h"
#include "osapi.h"

DHT11 dht11(2);
uint8_t default_aes_key[AES_KEY_SIZE] = {141, 198, 196, 133, 18,  103, 218, 248,
                                         196, 236, 212, 40,  76,  12,  15,  122,
                                         15,  17,  25,  138, 162, 48};

uint8_t default_hmac_key[HMAC_KEY_SIZE] = {
    141, 198, 196, 133, 18,  103, 218, 248, 196, 236, 212, 40,  76,  12,  15,
    122, 15,  17,  25,  138, 162, 48,  141, 198, 196, 133, 18,  103, 218, 248,
    196, 236, 212, 40,  76,  12,  15,  122, 15,  17,  25,  138, 162, 48};

// TODO: this needs to be saveable in EEPROM so that the key changes are
// presistent
node_config *current_config =
    new node_config(default_aes_key, default_hmac_key);

CryptoAdapter *crypto = new CryptoAdapter(current_config);

size_t MAX_MESSAGE_SIZE = CryptoAdapter::toValidSize(
    sizeof(send_message) + // Base size of send_message (without data[])
    sizeof(message_data) + // Base size of message_data (without data[])
    sizeof(node_config));  // Max size of any payload (from the union)

size_t buffer_size = 2 * MAX_MESSAGE_SIZE;

send_message *in_message = (send_message *)malloc(buffer_size);
send_message *in_buff = (send_message *)malloc(buffer_size);
size_t in_msg_data_size;

send_message *out_message = (send_message *)malloc(buffer_size);
send_message *out_buff = (send_message *)malloc(buffer_size);
size_t out_msg_data_size;

void setup() {
  Serial.begin(115200);
  delay(2000);

  memset(in_message, 0, buffer_size);
  memset(in_buff, 0, buffer_size);

  memset(out_message, 0, buffer_size);
  memset(out_buff, 0, buffer_size);
}

void loop() {
  delay(1000);

  message_data *out_mess_data = (message_data *)out_message->data;
  {
    out_mess_data->command = DHT_MEASUREMENT;
    dht_measurement *meas = (dht_measurement *)out_mess_data->data;
    meas->humidity = os_random();
    meas->temperature = os_random();
    out_msg_data_size = CryptoAdapter::toValidSize(sizeof(message_data) +
                                                   sizeof(dht_measurement));

    Serial.printf("HUM BEFORE: %d, TEMP BEFORE: %d \n", meas->humidity,
                  meas->temperature);
  }

  // // logging
  // {
  //   Serial.println("OUT_BUFF BEFORE ENCRYPTION");
  //   for (int i = 0; i < out_msg_data_size; i++) {
  //     Serial.printf("0x02%x ", ((uint8_t *)out_mess_data)[i]);
  //   }
  //   Serial.println("OUT_BUFF BEFORE ENCRYPTION");
  // }

  // encryption
  {
    encrypt_error err =
        crypto->encryptMessage(out_buff, out_message, out_msg_data_size);
    if (err != encrypt_error::OK) {
      Serial.println("Error encrypting message.");
      return;
    }
    // TODO: SEND THE OUT_BUFF TO THE OTHER NODE
  }

  // // logging
  // {
  //   Serial.println("OUT_BUFF AFTER ENCRYPTION");
  //   for (int i = 0; i < out_msg_data_size; i++) {
  //     Serial.printf("0x02%x ", ((uint8_t *)out_mess_data)[i]);
  //   }
  //   Serial.println("OUT_BUFF AFTER ENCRYPTION");
  // }

  // decryption
  {
    in_msg_data_size = out_msg_data_size;
    // TODO: GET THE MESSAGE FROM THE OTHER NODE TO IN_BUFF

    decrypt_error err =
        crypto->decryptMessage(in_buff, out_message, in_msg_data_size);
    if (err != decrypt_error::OK) {
      Serial.println("Error decrypting message.");
      return;
    }
    Serial.println("GOD HELP ME MAKE THIS WORK");
    message_data *data = (message_data *)in_buff->data;
    dht_measurement *meas = (dht_measurement *)data->data;
    Serial.printf("HUM AFTER: %d, TEMP AFTER: %d \n", meas->humidity,
                  meas->temperature);
  }
}
