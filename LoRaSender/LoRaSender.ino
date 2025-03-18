#include <SPI.h>
#include <Wire.h>
#include <LoRa.h>
#include <DHT11.h>
#include <Adafruit_BMP280.h>

#define SS 15      // D8 (GPIO15)
#define RST 16     // D0 (GPIO16)
#define DIO0 5     // D1 (GPIO5)
#define SDA_PIN D3  // GPIO4
#define SCL_PIN D2  // GPIO5

// DHT11 sensor
DHT11 dht11(2);
int temperature;
int humidity;
// BMP280 sensor
Adafruit_BMP280 bmp; // Use I2C interface
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN); 
  unsigned status = bmp.begin(0x76);

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
  // Read from sensors
  ReadFromSensors();
  Serial.println("Sending packet");
  Serial.println("{");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  sensors_event_t pressure_event;
  bmp_pressure->getEvent(&pressure_event);
  Serial.print(F("Pressure: "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");
  Serial.println("}");

  LoRa.beginPacket();
  LoRa.print("Temperature: ");
  LoRa.print(temperature);
  LoRa.println(" °C");
  LoRa.print("Humidity: ");
  LoRa.print(humidity);
  LoRa.println(" %");
  LoRa.print("Pressure: ");
  LoRa.print(pressure_event.pressure);
  LoRa.println(" hPa");
  LoRa.endPacket();

  delay(3000);
}

void ReadFromSensors(){
  int result = dht11.readTemperatureHumidity(temperature, humidity);
}