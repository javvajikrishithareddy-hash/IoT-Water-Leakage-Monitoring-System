#define WATER_SENSOR 34

void setup() {
  Serial.begin(115200);
}

void loop() {
  int value = analogRead(WATER_SENSOR);
  Serial.print("Water Sensor Value: ");
  Serial.println(value);
  delay(500);
}