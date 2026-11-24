#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define WATER_SENSOR 34
#define RED_LED 25
#define GREEN_LED 26
#define BUZZER 27

// Change if required after testing
#define THRESHOLD 300

void setup()
{
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BUZZER, LOW);

  Wire.begin(21,22);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED Failed");
    while(true);
  }

  display.clearDisplay();
  display.display();
}

void loop()
{
  int value = analogRead(WATER_SENSOR);

  Serial.print("Water Sensor Value : ");
  Serial.println(value);

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("WATER");

  display.setTextSize(1);

  if(value > THRESHOLD)
  {
    // Water Detected

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, HIGH);

    display.setCursor(0,30);
    display.println("STATUS:");
    display.println("LEAK DETECTED");
  }
  else
  {
    // Safe

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, LOW);

    display.setCursor(0,30);
    display.println("STATUS:");
    display.println("SAFE");
  }

  display.display();

  delay(300);
}