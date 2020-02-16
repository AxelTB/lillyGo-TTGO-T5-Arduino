#include "eink.h"

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
  init_e_ink();
}
void loop()
{
  test_buttons();
  test_version();
  test_display();
}


/**
 * @brief Checks button and write on serial when pressed
 * 
 */
void test_buttons()
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
void test_version()
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