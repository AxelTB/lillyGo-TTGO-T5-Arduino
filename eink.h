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

void init_e_ink()
{
    display.init(); // enable diagnostic output on Serial
    display.setRotation(3);
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
void test_display()
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