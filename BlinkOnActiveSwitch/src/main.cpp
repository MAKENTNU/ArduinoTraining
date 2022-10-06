#include <Arduino.h>

//#define LED_PIN 12
#define DELAY_TIME 200

const int ledPin = 12;
const int buttonPin = 8;

void Blink(const int &ledPin){
  digitalWrite(ledPin, LOW);
  delay(DELAY_TIME);
  digitalWrite(ledPin, HIGH);
  delay(DELAY_TIME);
}

// Setup sets the pin modes
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

// Loop for button control
void loop() {
  //1st case: Button not pressed, LED always on.
  if(!digitalRead(buttonPin)){
    digitalWrite(ledPin, HIGH);
  }
  //2nd case: Button pressed, LED blinks.
  else{
    Blink(ledPin);
  }
}