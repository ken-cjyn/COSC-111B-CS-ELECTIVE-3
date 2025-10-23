const int thermistorPin = A0;
const int ledPin = 8;

float temperature = 0;
bool isBlinking = false; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println("System ready. Monitoring temperature...");
}

void loop() {
  int analogValue = analogRead(thermistorPin);
  float resistance = (1023.0 / analogValue - 1) * 10000; 
  float temperatureC = 1 / (log(resistance / 10000.0) / 3950 + 1.0 / 298.15) - 273.15;

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  if (temperatureC >= 50) {
    isBlinking = true;  
  }


  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("stop")) {
      isBlinking = false;
      digitalWrite(ledPin, LOW);
      Serial.println("Blinking stopped.");
    }
  }

  if (isBlinking) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  } else {
    delay(500); 
  }
}
