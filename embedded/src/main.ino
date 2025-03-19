#include "Arduino.h"

#include "data_types.h"
#include <DHT11.h>

DHT11 dht11(2);

node_config current_config;

void setup() { Serial.begin(9600); }

void loop() {

  // current_config.setAesFromString("", ) ;
}
