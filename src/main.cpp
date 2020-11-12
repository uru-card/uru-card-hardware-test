#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_MPR121.h>

#include <SparkFun_ATECCX08a_Arduino_Library.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

bool screen_available = false;

Adafruit_MPR121 cap = Adafruit_MPR121();

bool keyboard_available = false;

ATECCX08A atecc;

bool security_available = false;

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

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        screen_available = true;
        print_status("URU Card", "HW Test");
    }

    if (cap.begin(0x5A))
    {
        keyboard_available = true;
    }

    security_available = atecc.begin();

    delay(3000);
}

String getTouched()
{
    static uint16_t lasttouched = 0;
    uint16_t currtouched = cap.touched();
    uint8_t index = 0;
    static const String keystrokes[] = {"", "1", "2", "3", "4", "5", "6", "7", "8", "9", "C", "0", "Ok"};

    for (uint8_t i = 0; i < 12; i++)
    {
        // it if *is* touched and *wasnt* touched before, alert!
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)))
        {
            index = i + 1;
        }
    }

    // reset our state
    lasttouched = currtouched;

    return keystrokes[index];
}

void loop()
{
    static uint mode = 1;
    static uint modeTick = 0;

    modeTick += 1;
    if (modeTick >= 40)
    {
        modeTick = 0;

        // Rotate display modes
        mode += 1;
        if (mode > 3)
        {
            mode = 1;
        }

        switch (mode)
        {
        case 1:
            print_status("SSD1306", screen_available ? "Ok" : "Error!");
            break;
        case 2:
            print_status("MPR121", keyboard_available ? "Ok" : "Error!");
            break;
        case 3:
            print_status("ATECC508A", security_available ? "Ok" : "Error!");
            break;
        }
    }

    String touched = getTouched();
    if (!touched.isEmpty())
    {
        mode = 0;
        modeTick = 0;

        print_status("Touched", touched.c_str());
    }

    delay(50);
}