#include <Wire.h>      //

#define uvPin A0        //H
#define ambPin A1        //H

int timer_f = 0;        //EE
int uvRaw = 0;          //
int ambRaw = 0;        //
byte uvEE = 0;        //    
byte ambEE = 0;        //  
int storedcount = 0;      //

//initial eeprom address
int ee_address = 0x02;    //H

//address format: 1 0 1 0 A2 A1 B0 R/W. (R/W = 1 for read, 0 for write)
int eeprom_cntrl = 0x50;  //A2 = 0; A1 = 0; B0 = 0.    //H
/******TODO: WILL NEED TO IMPLEMENT THIS FOR TWO BLOCKS******/

void setup(){
  /***I2C SETUP***/
  //join bus as Master
  Wire.begin();
  delay(150);
  
  /***TIMER INTERRUPTS***/
  //stop interrupts 
  cli();
  //set timer1 interrupt at 0.25Hz
  TCCR1A = 0;    //set entire TCCR1A register to 0
  TCCR1B = 0;    //same for TCCR1B
  TCNT1  = 0;    //initialize counter value to 0
  //set compare match register for 0.25hz increments
  OCR1A = 62499; // = (16*10^6) / (0.25*1024) - 1 (must be <65536)
  //turn on CTC mode
  TCCR1B |= (1 << WGM12);
  //Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  //enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  //allow interrupts
  sei();
  
  //Pin setup
  pinMode(uvPin, INPUT);
  pinMode(ambPin, INPUT);
  
}

//timer interrupt
ISR(TIMER1_COMPA_vect){
  if(timer_f == 0){
     timer_f = 1;
   }
}

//writes one byte of data to stated address in memory
void EepromWrite(int address, byte data){
  
  //split new 16 bit address into high and low bytes
  byte add_lo = address;
  byte add_hi = (address >> 8);
  
  //start transmission & send control byte
  Wire.beginTransmission(eeprom_cntrl);
  //send address high byte
  Wire.write(add_hi);
  //send address low byte
  Wire.write(add_lo);
  //send data byte
  Wire.write(data);
  //end transmission
  Wire.endTransmission();
  delay(5);
  
} 

//reads one byte of data from stated address in memory
byte EepromRead(int address){
  
  //split 16 bit address into high and low bytes
  byte add_lo = address;
  byte add_hi = (address >> 8);
    
  
  //start transmission & send control byte
  Wire.beginTransmission(eeprom_cntrl);
  //send address high byte
  Wire.write(add_hi);
  //send address low byte
  Wire.write(add_lo);
  //end write
  Wire.endTransmission();
  delay(5);
  //read one byte from eeprom
  Wire.requestFrom(eeprom_cntrl, 1);
  //wait for receipt
  while(Wire.available() == 0);
  //assign value
  byte receivedValue = Wire.read();
  
  return receivedValue;
}

/**USE THIS FUNCTION TO WRITE DATA TO EEPROM**/
void StoreData(int address, int data){

  //scale value from adc from 10 bits to 8 bits
  unsigned long int scaledData = (data/4);
  byte newdata = (byte)scaledData;
  
  EepromWrite(address, newdata);    //Tx data_hi byte
  ee_address++;                        //increment eeprom address
  storedcount++;                    //increment global storedcount
  
  //update counter value stored in eeprom
  UpdateCounter();
}

void UpdateCounter(){
  /* function for keeping track of number of 
  *  values in eeprom and writing that value into 
  *  first 2 memory locations in eeprom        */
  
  //split storedcount int into two 8 bit values
  byte count_lo = storedcount;
  byte count_hi = (storedcount >> 8);
  
  //Update Counter Value in eeprom addresses 0x00 and 0x01
  EepromWrite(0x00, count_hi);    //tx count_hi byte
  EepromWrite(0x01, count_lo);    //tx count_lo byte

}

void ReadAllData(){
  /* function for reading all of eeprom */
  byte receivedValue = 0;
  byte receivedBuffer[1024];
  
  //get count bytes from eeprom and convert to integer
  byte count_hi = EepromRead(0x00);
  byte count_lo = EepromRead(0x01);
  int count = count_lo | (count_hi << 8);
  
  /*READ storedcount NUMBER OF VALUES FROM EEPROM
    AND STORE SEQUENTIALLY IN A BUFFER*/
  
  int address = 0x03;        //start at first address
  int y = 0;
  for (y=0; y<count; y++){
    
    receivedValue = EepromRead(address);    //read hi data value
    address++;                                 //increment eeprom address
    
    //convert to int and store in buffer
    receivedBuffer[y] = receivedValue;
    
  }

  storedcount = 0;        //reset global storedcount
  ee_address = 0x02;      //reset global eeprom address
  
}
  
//main
void loop(){
  if (timer_f==1){
    timer_f=0;
    
    uvRaw = analogRead(uvPin);
    StoreData(0x03, uvRaw);
    ambRaw = analogRead(ambPin);
    StoreData(0x04, ambRaw);
    
    uvEE = EepromRead(0x03);
    ambEE = EepromRead(0x04);
  }
}


