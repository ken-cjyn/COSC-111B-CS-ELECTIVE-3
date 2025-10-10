#define THERMISTOR_PIN A0
#define LDR_PIN A2
#define ALERT_PIN 12 

const int TEMP_THRESHOLD = 50;   
const int LIGHT_THRESHOLD = 220; 

const float SERIES_RESISTOR = 10; 
const float BETA = 3950.0;
const float ROOM_TEMP = 298.15;  

void setup() {
  pinMode(ALERT_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float temp = getTemp();
  int light = analogRead(LDR_PIN);

 Serial.print("T: "); Serial.print(temp);
  Serial.print(" °C | L: "); Serial.println(light);

  if (temp >= TEMP_THRESHOLD && light >= LIGHT_THRESHOLD) {
    digitalWrite(ALERT_PIN, HIGH);
    delay(100);
    digitalWrite(ALERT_PIN, LOW);
    delay(100);
  } else {
    digitalWrite(ALERT_PIN, LOW);
  }
}

float getTemp() {
  int adc = analogRead(THERMISTOR_PIN);
  float t = BETA / (log((1025 * SERIES_RESISTOR / adc - SERIES_RESISTOR)/ SERIES_RESISTOR) + BETA /ROOM_TEMP);
  return t - 273.15;
}


