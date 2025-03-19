#include <SPI.h>
#include <LoRa.h>

#define SS 15      // D8 (GPIO15)
#define RST 16     // D0 (GPIO16)
#define DIO0 5     // D1 (GPIO5)

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing LoRa Reciever...");

  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa module initialized successfully!");
  delay(1000); // Give LoRa module time to initialize
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.println("Received packet");
    //Serial.println("{");
    // read packet
    while (LoRa.available()) {
      Serial.print( (char)LoRa.read());
    }

    // print RSSI of packet
    //Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());
    //Serial.print(" SNR: ");
    Serial.println(LoRa.packetSnr());
    //Serial.println("}");
  }
}
