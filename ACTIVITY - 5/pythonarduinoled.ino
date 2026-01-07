#include "led_functions.h"


bool redState = false;
bool greenState = false;
bool blueState = false;

void setup() {

  Serial.begin(9600);
  
  
  initializeLEDPins();
  
  
  blinkBuiltinLED();
  
  
  Serial.println("Arduino 3-LED Controller Ready!");
  Serial.println("Waiting for commands (R, G, B, A, O, V)...");
}

void loop() {
  
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    processSerialCommand(command);
  }
}