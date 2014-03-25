/************************************EEPROM FUNCTIONS**************************/
/*                                                                            */
/******************************************************************************/

//Read the byte stored at address 'address'
byte EEPROM_Read(unsigned long address){
  byte address_low=address;
  byte address_high=address>>8;     //removed mid, changed from 16
  byte buffer;
  Wire.beginTransmission(EEPROM_address_R1);
  Wire.write(address_high);
  Wire.write(address_low);
  Wire.endTransmission();
  delay(5);
  //read one byte from eeprom - ***can we do more than 1 a time
  Wire.requestFrom(EEPROM_address_R1, 1);    //added r1
  //wait for receipt
  while(Wire.available() == 0);
  //assign value
  buffer= Wire.read();
  return buffer;
}  

//Write an array of data to the EEPROM
void EEPROM_Write(byte data[], unsigned long address, int ELEN){
  byte address_low=address;
  byte address_high=address>>8;
  Wire.beginTransmission(EEPROM_address_W1);
  Wire.write(address_high);
  Wire.write(address_low);
  int x;
  for(x=0; x<ELEN; x++){
    Wire.write(data[x]);
  }
  Wire.endTransmission();
  delay(5); //is this necessary? 
}
