//e-ink---------------------------------------------------------------
#include "GxEPD.h"
// select the display class to use, only one
#include <GxGDEP015OC1/GxGDEP015OC1.h> // 1.54" b/w
// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

GxIO_Class io(SPI, /*CS=5*/ SS, /*DC=*/17, /*RST=*/16);
GxEPD_Class display(io, /*RST=*/16, /*BUSY=*/4);

#define UPDATE_SCREEN_EVERY_S 5

//Button configuration------------------------------------------------
#define BUTTON_1 38
#define BUTTON_2 37
#define BUTTON_3 39
#define BUTTON_NUM 3
const int buttons[] = {BUTTON_1, BUTTON_2, BUTTON_3};

//Version check parameters--------------------------------------------
#define READ_ANALOG_EVERY_MS 100

void setup()
{
  //Serial---------------------
  Serial.begin(115200);
  Serial.println("Hello world!");
  //Button---------------------
  //Activate pullup for buttons
  for (int i = 0; i < BUTTON_NUM; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  //Display--------------------
  display.init(); // enable diagnostic output on Serial
  display.setRotation(3);
}
void loop()
{
  testButtons();
  testVersion();
  displayTest();
}

void showFont(const char name[], const GFXfont *f)
{
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
  display.update();
}

/**
 * @brief Show text on screem
 * 
 */
void displayTest()
{
  static uint32_t lastUpdate = millis();
  if (millis() - lastUpdate > ((uint32_t)UPDATE_SCREEN_EVERY_S * 1000))
  {
    //showFont("FreeMonoBold9pt7b", &FreeMonoBold9pt7b);
    showFont("FreeMonoBold12pt7b", &FreeMonoBold12pt7b);
    //showFont("FreeMonoBold24pt7b", &FreeMonoBold24pt7b);
    lastUpdate=millis();
  }
}
/**
 * @brief Checks button and write on serial when pressed
 * 
 */
void testButtons()
{
  for (int i = 0; i < BUTTON_NUM; i++)
  {
    if (digitalRead(buttons[i]) == LOW)
    {
      Serial.print("Pressed button ");
      Serial.println(i + 1);
    }
  }
}

/**
 * @brief Dumps analog value of pin 25 and 33
 * 
 * Check by touching the GPIO, if first value reacts you have v1.0 if it's the second on the version is 1.2
 * 
 */
void testVersion()
{
  static uint32_t lastRead = millis();
  if (millis() - lastRead > READ_ANALOG_EVERY_MS)
  {
    Serial.print(analogRead(25));
    Serial.print(", ");
    Serial.print(analogRead(33));
    Serial.println();
    lastRead = millis();
  }
}