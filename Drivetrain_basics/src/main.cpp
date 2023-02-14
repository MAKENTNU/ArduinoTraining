#include <Arduino.h>

//Motor pins
const int EN1 = 9;
const int EN2 = 3;

const int IN[4] = {8, 4, 7, 2};

//Sensor pins
const int senseY = A0;
const int senseX = A1;

void motorDrive(const int &motorEnable, uint8_t &motorPWM){
  analogWrite(motorEnable, motorPWM);
  delay(10);
}

int *measureFunc(const int &joyXpin, const int &joyYpin){
  int measurement[2];
  int* measurePtr = measurement;
  measurement[0] = analogRead(joyYpin) - 512;
  measurement[1] = analogRead(joyXpin) - 512;
  Serial.print(measurement[0]);
  Serial.print(":\t");
  Serial.print(measurement[1]);
  Serial.print(":\t");
  return measurePtr;
}

void configThrottle(const int *motorInputs, const bool &moveForw){
  for(uint8_t i = 0; i < (sizeof(motorInputs)/sizeof(int)); i++){
    if(i < 2) digitalWrite(*(motorInputs + i), moveForw);
    else digitalWrite(*(motorInputs + i), !moveForw);
  }
}

uint8_t convertToMotorData(int *measurements, const int *motorInputs){
  uint8_t result;
  const bool forwDir = true;
  if(*measurements > 0){             //Move forward
    configThrottle(IN, forwDir);
    result = map(*measurements, 0, 512, 0, 255);
    Serial.println(result);
  } else {      //Move backward
    configThrottle(IN, !forwDir);
    result = map(*measurements, -512, 0, 255, 0);
    Serial.println(result);
  }
  return result;
}


void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  for(uint8_t i = 0; i < (sizeof(IN)/sizeof(int)); i++){
    pinMode(*(IN + i), OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int measurement[2];
  int* measurePtr = measurement;
  measurePtr = measureFunc(senseX, senseY);
  uint8_t motorSpeed = convertToMotorData(measurePtr, IN);
  motorDrive(EN1, motorSpeed);
  motorDrive(EN2, motorSpeed);
}