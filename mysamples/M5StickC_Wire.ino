/*
    Test the two i2c busses on M5StickC
    
*/

#include <M5StickC.h>
#include <Wire.h> 

#define INFO 1
#define DEBUG 1
#define BAUDRATE 115200

void setup() 
{
  Serial.begin(BAUDRATE);
  delay(3000);              // wait for serial monitor
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
  M5.Lcd.println("Test I2C Busses...");
  
  if (DEBUG) Serial.println(F("Running...")); //last line in setup()
  
  Serial.println(F("Test I2C Busses......")); 
}

void loop() 
{
  Wire.begin();
  M5.Lcd.setTextColor(YELLOW,BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Scanning internal I2C Bus");
  i2cdetect();
  delay(2000);
  M5.Lcd.fillScreen( BLACK );

  Wire1.begin(32,33);
  M5.Lcd.setTextColor(GREEN,BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Scanning I2C Bus@GROVE");
  i2cdetect1();
  delay(2000);
  M5.Lcd.fillScreen( BLACK );
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
