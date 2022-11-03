#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t i2cAddr = 0x27;       //Defining the screen's I2C address
const uint8_t rowNo = 2;            //The number of rows for the LCD screen
const uint8_t colNo = 16;           //The number of columns for the LCD screen

LiquidCrystal_I2C lcd(i2cAddr, colNo, rowNo);     //LCD class constructor

/*
This function finds the devices connected to the I2C bus.

@params: None
returns: None
*/
void I2C_find(){
  while(!Serial);             //Don't print to Serial if the monitor isn't opened.
  Serial.println("I2C Scanner. Scanning for devices...");   //GUI
  byte count = 0;             //The number of devices connected in the bus.

  Wire.begin();                           //Beginning serial communication in the I2C bus.
  for(byte i = 8; i < 120; i++){
    Wire.beginTransmission(i);              //Begins transmission in address i. If the transmission is ended, a unit has been found. The address is thus printed.
    if(!Wire.endTransmission()){
      Serial.print("Found address: ");
      Serial.print(i, DEC);
      Serial.print(" (0x");                 //Address is printed 
      Serial.print(i, HEX);
      Serial.println(")");
      count++;
      delay(1);
    }
  }
  // After the scan is finished, show number of devices found
  Serial.println("Scan finished.");
  Serial.print("Found ");
  Serial.print(count, DEC);
  Serial.println(" device(s).");
}

void setup() {
  Serial.begin(9600);
  I2C_find();             //Find the screen
  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("I2C LCD Tutorial");
  lcd.setCursor(0, 1);
  lcd.print("*Ardumotive.com");
}

void loop() {
  if(Serial.available()){
    delay(100);
    lcd.clear();
    while(Serial.available() > 0){
      lcd.write(Serial.read());
    }
  }
}