/*
    ENV Unit connected to M5StickC via Grove Connector
    
*/

#include <M5StickC.h>
#include "DHT12.h"
#include <Wire.h> //The DHT12 uses I2C comunication.
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>

#define INFO 1
#define DEBUG 1
#define BAUDRATE 115200

DHT12 dht12; //Preset scale CELSIUS and ID 0x5c.
Adafruit_BMP280 bme;

void setup() 
{
  Serial.begin(BAUDRATE);
  delay(2000);              // wait for serial monitor
  if (INFO)  printInfo();
  if (DEBUG) Serial.println(F("Initializing..."));

  M5.begin();
  M5.Lcd.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(GREEN);  
  M5.Lcd.setTextSize(1);
  M5.Lcd.fillScreen( BLACK );
   
  delay(3000);
  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("ENV Unit test...");
  
  if (DEBUG) Serial.println(F("Running...")); //last line in setup()
  
  Serial.println(F("ENV Unit(DHT12 and BMP280) test..."));
  
  Wire.begin(32,33);
  if (!bme.begin(0x76))
  {  
      Serial.println("Could not find a valid BMP280 sensor, check wiring!");
      while (1);
  }  
}

void loop() 
{
  Wire.begin(32,33);
  float tmp = dht12.readTemperature();
  float hum = dht12.readHumidity();
  float pressure = bme.readPressure();
  Serial.printf("Temperature: %2.1f *C  Humidity: %2.0f %%  Pressure: %2.0f Pa\r\n", tmp, hum, pressure);

  M5.Lcd.setCursor(0, 16);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.printf("Temp: %2.1f *C\r\nHumi: %2.0f %%\r\nPressure: %2.0f Pa\r\n", tmp, hum, pressure);

  Wire.begin(); // internal I2C Bus
  float vbat = M5.Axp.GetVbatData() * 1.1 / 1000;
  M5.Lcd.printf("\r\nVbat: %.3f V\r\n", vbat);
  int charge = M5.Axp.GetIchargeData() / 2;
  M5.Lcd.printf("Icharge: %d mA\r\n", charge);
  Serial.printf("Vbat: %.3f V  Icharge: %d mA\r\n",vbat, charge);
  
  delay(2500);
}

/*--------------------------------------------------------------*/

void printInfo()
{
  // Compile file path (internal file of compilation proccess)
  Serial.print("File "); Serial.println(__FILE__);
  
  String s1 = __DATE__;
  String s2 = __TIME__;

  // Date of compilation
  Serial.print("Compilation @ "); Serial.println(s1 + " " + s2);
  
  // Arduino IDE SW version
  Serial.print("ARDUINO IDE v"); Serial.println(ARDUINO);
  
  // Oscillator frequency
  Serial.print("CPU Clock in MHz: "); Serial.println(F_CPU/1E6);
}
