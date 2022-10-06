#include <Arduino.h>

//Defining the delay time in milliseconds, as well as the switch idle time.
#define DELAY_TIME 200
#define SWITCH_IDLE_TIME 100000

//Defining the input and output pins
const int ledPin = 12;
const int buttonPin = 8;

//Defining a start flag and a memory cell for it
bool switchFlag = true;
bool switchFlagMem = true;

//Blink function
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
    //Switch flag controls whether the LED is on or off in this iteration.
    if(switchFlag){
      digitalWrite(ledPin, HIGH);
    } else{
      digitalWrite(ledPin, LOW);
    }
    //Logical hack in order to make the switch valid in the next case.
    switchFlagMem = switchFlag;
  }
  //2nd case: Button pressed, LED blinks.
  //Each time the button is pressed, we change the switch flag.
  //Thus, the LED will change state everytime you let go of the switch
  //In order to make sure that the switching isn't done continuously, a flag filter needs to be implemented.
  else{
    Blink(ledPin);
    if(switchFlag == switchFlagMem){
      switchFlag = !switchFlag;
    }
  }
}