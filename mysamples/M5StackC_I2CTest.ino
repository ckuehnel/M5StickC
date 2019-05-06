/************************************************************************

  M5StackC I2C Scanner

  based on:

  The M5StackFire has a connector for I2C devices. 
  This program scans the addresses 1-127 continuosly and shows 
  the devices found on the TFT.

  The M5Stack fire has two internal I2C devices at address 0x68 and 0x75.
  
  October 2018, ChrisMicro

  adaptions 2019-05-05 by Claus Kühnel (info@ckuehnel.ch) 

************************************************************************/
#include <M5StickC.h>
#include <i2cdetect.h>

#define INFO 1
#define DEBUG 1
#define BAUDRATE 115200

void setup() 
{
  Serial.begin(BAUDRATE);
  delay(2000);              // wait for serial monitor
  if (INFO)  printInfo();
  if (DEBUG) Serial.println(F("Initializing..."));

  Wire.begin();
  M5.Lcd.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(YELLOW);  
  M5.Lcd.setTextSize(1);
  M5.Lcd.fillScreen( BLACK );
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("M5StickC I2C Tester");
    
  delay(3000);
  M5.Lcd.fillScreen( BLACK );
  if (DEBUG) Serial.println(F("Running...")); //last line in setup()
}

int textColor=YELLOW;

void loop() 
{
  int address;
  int error;
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("scanning Address [HEX]");
  
  for(address = 1; address < 127; address++ ) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if(error==0)
    {
      M5.Lcd.print(address,HEX);M5.Lcd.print(" ");
    }
    else M5.Lcd.print(".");

    delay(10);
  }

  if(textColor==YELLOW) textColor=GREEN;
  else textColor=YELLOW;
  M5.Lcd.setTextColor(textColor,BLACK);  

  if (DEBUG) i2cdetect();  // default range from 0x03 to 0x77
  delay(1000);
}

/*--------------------------------------------------------------*/

void printInfo()
{
  // Compile file path (internal file of compilation proccess)
  Serial.print("File "); Serial.println(__FILE__);
  
  String s1 = __DATE__;
  String s2 = __TIME__;
}
