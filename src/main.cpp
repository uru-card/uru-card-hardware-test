#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_MPR121.h>

#include <SparkFun_ATECCX08a_Arduino_Library.h> //Click here to get the library: http://librarymanager/All#SparkFun_ATECCX08a

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

bool screen_available = false;

Adafruit_MPR121 cap = Adafruit_MPR121();

bool keyboard_available = false;

ATECCX08A atecc;

bool security_available = false;

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    delay(2000);

    if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        screen_available = true;
    }

    if (cap.begin(0x5A))
    {
        keyboard_available = true;
    }

    security_available = atecc.begin();
}

void print_status(const char *label, const char *value)
{
    Serial.println(label);
    Serial.println(value);

    if (screen_available)
    {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println(label);
        display.setCursor(0, 16);
        display.println(value);
        display.display();
    }
}

void loop()
{
    print_status("URU Card", "HW Test");
    delay(3000);

    print_status("SSD1306", screen_available ? "Ok" : "Error!");
    delay(3000);

    print_status("MPR121", keyboard_available ? "Ok" : "Error!");
    delay(3000);

    print_status("ATECC508A", security_available ? "Ok" : "Error!");
    delay(3000);
}