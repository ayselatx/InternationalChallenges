#include <Arduino.h>
#include <DHT11.h>
#include <LoRa.h>

#include "data_types.h"

DHT11 dht11(2);
constexpr uint8_t default_key[32] = {};
Crypto crypto;

node_config current_config;

uint8_t *tmpData1;
uint8_t *tmpData2;
uint32_t tmpDataLen;

void setup() {
  Serial.begin(9600);
  crypto.setKey(default_key);
  tmpDataLen =
      sizeof(send_message) % crypto.getBlockSize() == 0
          ? sizeof(send_message)
          : sizeof(send_message) + sizeof(send_message) % crypto.getBlockSize();
  tmpData1 = (uint8_t *)malloc(tmpDataLen);
  tmpData2 = (uint8_t *)malloc(tmpDataLen);
}

void loop() {
  dht_measurement meas;
  meas.humidity = 10;
  meas.temperature = 20;

  send_message curr_mess;
  curr_mess.command = command_type::DHT_MEASUREMENT;
  curr_mess.dht_meas = meas;

  // copy the data to the tmp buffer
  memcpy((void *)tmpData1, (void *)&curr_mess, sizeof(send_message));
  crypto.encryptData(tmpData2, tmpData1, tmpDataLen);

  crypto.decryptData(tmpData1, tmpData2, tmpDataLen);

  // copy the data back from the tmp buffer
  memcpy((void *)&curr_mess, (void *)tmpData1, sizeof(send_message));
  Serial.printf("H: %d\nT: %d\n", curr_mess.dht_meas.humidity,
                curr_mess.dht_meas.temperature);
  delay(1);
}
