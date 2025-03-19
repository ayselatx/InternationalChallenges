#include <Arduino.h>
#include <DHT11.h>
#include <LoRa.h>

#include "crypto_adapter.h"
#include "data_types.h"

DHT11 dht11(2);
uint8_t default_key[32] = {141, 198, 196, 133, 18,  103, 218, 248,
                           196, 236, 212, 40,  76,  12,  15,  122,
                           15,  17,  25,  138, 162, 48};
CryptoAdapter *crypto;
constexpr size_t MAX_MESSAGE_SIZE = CryptoAdapter::toValidSize(
    sizeof(send_message) + // Base size of send_message (without data[])
    sizeof(message_data) + // Base size of message_data (without data[])
    sizeof(node_config));  // Max size of any payload (from the union)

// this needs to be saveable in EEPROM so that the key changes are presistent
node_config current_config;

uint8_t *tmpData1;
uint8_t *tmpData2;
uint32_t tmpDataLen;

void setup() {
  Serial.begin(115200);
  delay(2000);
  tmpDataLen = CryptoAdapter::toValidSize(MAX_MESSAGE_SIZE);

  tmpData1 = (uint8_t *)malloc(tmpDataLen);
  memset(tmpData1, 0, tmpDataLen);
  tmpData2 = (uint8_t *)malloc(tmpDataLen);
  memset(tmpData2, 0, tmpDataLen);
}

void loop() {
  dht_measurement meas;
  meas.humidity = 100;
  meas.temperature = 30;

  send_message curr_mess;
  // curr_mess.command = command_type::DHT_MEASUREMENT;
  // curr_mess.dht_meas = meas;

  // copy the data to the tmp buffer
  memcpy((void *)tmpData1, (void *)&curr_mess, sizeof(send_message));
}
