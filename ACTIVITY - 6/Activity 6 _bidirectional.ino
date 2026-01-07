const int redLedPin    = 7;
const int greenLedPin  = 6;
const int blueLedPin   = 5;

const int redButtonPin    = 12;
const int greenButtonPin  = 11;
const int blueButtonPin   = 10;

int redLedStatus = LOW, greenLedStatus = LOW, blueLedStatus = LOW;
int lastRedBtn   = LOW, lastGreenBtn   = LOW, lastBlueBtn   = LOW;

void setup() {
    Serial.begin(9600);
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(blueLedPin, OUTPUT);
    pinMode(redButtonPin, INPUT);
    pinMode(greenButtonPin, INPUT);
    pinMode(blueButtonPin, INPUT);
}

void toggleHardware(int pin, int &status) {
    status = !status;
    digitalWrite(pin, status);
}

void loop() {
    int r = digitalRead(redButtonPin), 
        g = digitalRead(greenButtonPin),
        b = digitalRead(blueButtonPin);
    
    if (r && !lastRedBtn)   { Serial.println("R"); delay(50); } lastRedBtn = r;
    if (g && !lastGreenBtn) { Serial.println("G"); delay(50); } lastGreenBtn = g;
    if (b && !lastBlueBtn)  { Serial.println("B"); delay(50); } lastBlueBtn = b;

    if (Serial.available() > 0) {
        delay(30); 
        int charCount = 0;
        char firstChar = '\0';
        while (Serial.available() > 0) {
            char c = Serial.read();
            if (!isspace(c)) {
                if (charCount == 0) firstChar = c;
                charCount++;
            }
        }
        if (charCount == 1) {
            if      (firstChar == '1') toggleHardware(redLedPin, redLedStatus);
            else if (firstChar == '2') toggleHardware(greenLedPin, greenLedStatus);
            else if (firstChar == '3') toggleHardware(blueLedPin, blueLedStatus);
        } else if (charCount > 1) {
            Serial.println("ERROR: Single input only at a time!");
        }
    }
}