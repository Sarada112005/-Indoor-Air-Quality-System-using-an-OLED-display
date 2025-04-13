#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define AIR_SENSOR_PIN 34  // Simulated Air Quality Sensor (Potentiometer)
#define GREEN_LED 26  // Good Air Quality
#define YELLOW_LED 27  // Moderate Air Quality
#define RED_LED 14  // Poor Air Quality
#define BUZZER 25  // Alarm for Poor Air Quality

void setup() {
    Serial.begin(115200);

    pinMode(AIR_SENSOR_PIN, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);

    // Initialize OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        for (;;);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Indoor Air Quality System");
    display.display();
    delay(2000);
}

void loop() {
    int airValue = analogRead(AIR_SENSOR_PIN);
    int airQuality = map(airValue, 0, 4095, 0, 500);  // AQI range from 0 to 500

    Serial.print("Air Quality Index: ");
    Serial.println(airQuality);

    // Update OLED Display
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("AQI: ");
    display.print(airQuality);

    // Air Quality Conditions
    if (airQuality < 100) {  // Good
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED, LOW);
        digitalWrite(BUZZER, LOW);
        display.println(" - Good 😊");
    } else if (airQuality >= 100 && airQuality < 200) {  // Moderate
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, HIGH);
        digitalWrite(RED_LED, LOW);
        digitalWrite(BUZZER, LOW);
        display.println(" - Moderate 😐");
    } else {  // Poor
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        digitalWrite(BUZZER, HIGH);
        display.println(" - Poor! ⚠️");
    }

    display.display();
    delay(2000);
}

