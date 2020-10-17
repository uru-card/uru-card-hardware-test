#include<Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

Adafruit_MPR121 cap = Adafruit_MPR121();

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    delay(2000);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        while (1)
            ;
    }
    Serial.println("SSD1306 found!");

    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("URUCard");
    display.display();

    // Default address is 0x5A, if tied to 3.3V its 0x5B
    // If tied to SDA its 0x5C and if SCL then 0x5D
    if (!cap.begin(0x5A))
    {
        Serial.println("MPR121 not found, check wiring?");
        while (1)
            ;
    }
    Serial.println("MPR121 found!");
}

void loop()
{
    delay(1000);
}