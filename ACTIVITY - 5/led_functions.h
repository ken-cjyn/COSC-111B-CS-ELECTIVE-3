#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H

#include <Arduino.h>


const int RED_LED_PIN = 8;
const int GREEN_LED_PIN = 9;
const int BLUE_LED_PIN = 10;


extern bool redState;
extern bool greenState;
extern bool blueState;


void initializeLEDPins() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
}


void blinkBuiltinLED() {
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}


void toggleRedLED() {
  redState = !redState;
  digitalWrite(RED_LED_PIN, redState ? HIGH : LOW);
  Serial.print(">>> Red LED: ");
  Serial.println(redState ? "ON" : "OFF");
}


void toggleGreenLED() {
  greenState = !greenState;
  digitalWrite(GREEN_LED_PIN, greenState ? HIGH : LOW);
  Serial.print(">>> Green LED: ");
  Serial.println(greenState ? "ON" : "OFF");
}


void toggleBlueLED() {
  blueState = !blueState;
  digitalWrite(BLUE_LED_PIN, blueState ? HIGH : LOW);
  Serial.print(">>> Blue LED: ");
  Serial.println(blueState ? "ON" : "OFF");
}



  

  

void turnAllLEDsOn() {
  redState = true;
  greenState = true;
  blueState = true;
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  Serial.println(">>> All LEDs: ON");
}


void turnAllLEDsOff() {
  redState = false;
  greenState = false;
  blueState = false;
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  Serial.println(">>> All LEDs: OFF");
}


void printDebugInfo(char command) {
  Serial.print("Received command: ");
  Serial.print(command);
  Serial.print(" (ASCII: ");
  Serial.print((int)command);
  Serial.println(")");
}


void printUnknownCommandError(char command) {
  Serial.print("!!! Unknown command: '");
  Serial.print(command);
  Serial.print("' (ASCII: ");
  Serial.print((int)command);
  Serial.println(")");
}


void processSerialCommand(char command) {
  // Ignore whitespace characters
  if (command == '\n' || command == '\r' || command == ' ') {
    return;
  }
  
  // Convert to uppercase
  command = toupper(command);
  
  // Print debug info
  printDebugInfo(command);
  
  // Process command
  switch (command) {
    case 'R':
      toggleRedLED();
      break;
      
    case 'G':
      toggleGreenLED();
      break;
      
    case 'B':
      toggleBlueLED();
      break;
      
    case 'A':
      turnAllLEDsOn();
      break;
      
    case 'O':
      turnAllLEDsOff();
      break;
    

    case 'V':
      toggleRedLED();
      toggleBlueLED();
      break;
      
    default:
      printUnknownCommandError(command);
      break;
  }
}

#endif // LED_FUNCTIONS_H