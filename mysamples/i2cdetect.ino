void i2cdetect()
{
  int address;
  int error;
    
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
}

void i2cdetect1()
{
  int address;
  int error;
    
  for(address = 1; address < 127; address++ ) 
  {
    Wire1.beginTransmission(address);
    error = Wire1.endTransmission();
    if(error==0)
    {
      M5.Lcd.print(address,HEX);M5.Lcd.print(" ");
    }
    else M5.Lcd.print(".");

    delay(10);
  }   
}
