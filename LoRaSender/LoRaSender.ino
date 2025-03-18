#include <SPI.h>
#include <LoRa.h>
#include <DHT11.h>

#define SS 15      // D8 (GPIO15)
#define RST 16     // D0 (GPIO16)
#define DIO0 5     // D1 (GPIO5)

DHT11 dht11(2);
int counter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing LoRa Sender...");

  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa module failed to start!");
    while (1);  // Infinite loop if LoRa fails
  }

  Serial.println("LoRa module initialized successfully!");
  delay(1000); // Give LoRa module time to initialize
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
