/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/Users/leonard_lo/OneDrive/dev/particleproj/bme-280/src/bme-280.ino"
/*
 * Project bme-280
 * Description:
 * Author:
 * Date:
 */

#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

void setup();
void loop();
#line 11 "/Users/leonard_lo/OneDrive/dev/particleproj/bme-280/src/bme-280.ino"
#define BME_SCK D1

#define BME_MOSI D0


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);


double temp;
double humidity;

// -----------------------------------------------------------
void setup() {
  Particle.variable("temp", temp);
  Particle.variable("humidity", humidity);

  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  // if (!bme.begin(0x76)) {
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  Serial.println("Loop");
  float t = bme.readTemperature(); // *C
  float h = bme.readHumidity(); // %
  //float p = bme.readPressure() / 100.0F; // hPa
  //float a = bme.readAltitude(SEALEVELPRESSURE_HPA);
  
  temp = (t*9/5) + 32.00; //Celsius to Fahrenheit conversion
  humidity = h;

  //formatting sensor data into string message
  String data = String::format("%.2f",temp) + " degrees F, " + "humidity "+ String::format("%.2f",h) + "%";

  // Publish data to Particle Cloud
  Particle.publish("data", data,PRIVATE);

  delay(5000);
}