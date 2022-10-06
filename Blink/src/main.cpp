#include <Arduino.h>

#define LED_PIN 12
#define BUTTON_PIN 8

// Vise fram antall ganger knappen har blitt trykket på.
unsigned int antall = 0;

// Tilstandsvariabel
unsigned long prevMillis = 0;
bool state = false;

//Start Serial

// Setup sets the pin modes
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  prevMillis = millis();
}

// Loop for button control
void loop() {
  if(!digitalRead(BUTTON_PIN)){
    digitalWrite(LED_PIN, LOW);
    state = false;
  } else {
    digitalWrite(LED_PIN, HIGH);
    while((millis() - prevMillis > 1000) || !state){
      antall++;
      Serial.println(antall);
      prevMillis = millis();
      state = true;
    }
  }
}