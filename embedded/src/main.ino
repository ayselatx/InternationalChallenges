#include <Arduino.h>
#include <DHT11.h>
#include <LoRa.h>

#include "data_types.h"

DHT11 dht11(2);
constexpr uint8_t default_key[32] = {141, 198, 196, 133, 18,  103, 218, 248,
                                     196, 236, 212, 40,  76,  12,  15,  122,
                                     15,  17,  25,  138, 162, 48};
Crypto crypto;

node_config current_config;

uint8_t *tmpData1;
uint8_t *tmpData2;
uint32_t tmpDataLen;

void setup() {
  Serial.begin(115200);
  delay(2000);
  bool done = crypto.setKey(default_key);
  if (done) {
    Serial.println("YES KEY");
  } else {
    Serial.println("NO KEY");
  }
  tmpDataLen = sizeof(send_message) % crypto.getBlockSize() == 0
                   ? sizeof(send_message)
                   : sizeof(send_message) + crypto.getBlockSize() -
                         sizeof(send_message) % crypto.getBlockSize();

  Serial.println("DATALEN: ");
  Serial.println(tmpDataLen);
  Serial.println("blockSize: ");
  Serial.println(crypto.getBlockSize());
  Serial.println("DATALEN MOD BLOCKSIZE ");
  Serial.println(tmpDataLen % crypto.getBlockSize());

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
  curr_mess.command = command_type::DHT_MEASUREMENT;
  curr_mess.dht_meas = meas;

  // copy the data to the tmp buffer
  memcpy((void *)tmpData1, (void *)&curr_mess, sizeof(send_message));
  Serial.println("buff1 b4:");
  for (int i = 0; i < tmpDataLen; i++) {
    Serial.printf("0x%02x ", tmpData1[i]);
  }
  Serial.println("");
  memset(tmpData2, 0, tmpDataLen);
  bool done = crypto.encryptData(tmpData2, tmpData1, tmpDataLen);
  if (done) {
    Serial.println("YES ENCRPTED");
  } else {
    Serial.println("NO ENCRPTED");
  }
  memset(tmpData1, 0, tmpDataLen);

  Serial.println("buff2 after:");
  for (int i = 0; i < tmpDataLen; i++) {
    Serial.printf("0x%02x ", tmpData2[i]);
  }
  Serial.println("");

  done = crypto.decryptData(tmpData1, tmpData2, tmpDataLen);
  if (done) {
    Serial.println("YES DECRPTED");
  } else {
    Serial.println("NO DECRPTED");
  }

  // copy the data back from the tmp buffer
  memcpy((void *)&curr_mess, (void *)tmpData1, sizeof(send_message));
  Serial.printf("H: %d\nT: %d\n", curr_mess.dht_meas.humidity,
                curr_mess.dht_meas.temperature);
  delay(1000);
}
