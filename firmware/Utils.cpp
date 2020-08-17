#include "Utils.h"

uint8_t i2c_write(byte deviceAddr, uint8_t address, long data, uint8_t l) {
  Wire.beginTransmission(deviceAddr);
  Wire.write(byte(address)); // address specifier
  while (l > 0) {
    l--;
    Wire.write(byte(data >> (l * 8))); // value specifier
  }
  byte error = Wire.endTransmission();
  if (error != 0) {
    Serial.println(F("Error during write"));
    return 1;
  }
  delay(1);
  return 0;
}

long i2c_read(byte deviceAddr, uint8_t address, uint8_t l) {
  Wire.beginTransmission(deviceAddr);
  Wire.write(byte(address));
  Wire.endTransmission(false);//repeated start !! mandatory !!
  
 /* Serial.print(deviceAddr,HEX);
  Serial.println(" repeated start");*/
  
  Wire.requestFrom(deviceAddr, l);
  
 /* Serial.print(deviceAddr,HEX);
  Serial.println(" request");*/
  while (Wire.available() < l){
    delay(10);   
 /* Serial.print(Wire.available());
  Serial.println(" available"); */
  }
  //Serial.println(" available");
  long res = 0;
  for (uint8_t i = 0; i < l; i++) {
 /* Serial.print(deviceAddr,HEX);
  Serial.print(" request");*/
    uint8_t value = Wire.read();
 // Serial.println(" response");
    //if(address==REG_S1)Serial.println(value,HEX);
    res = (res << 8) + byte(value);
  }
  return res;
}
