
#define BUTTON_1 38
#define BUTTON_2 37
#define BUTTON_3 39
#define BUTTON_NUM 3

#define READ_ANALOG_EVERY_MS 100

const int buttons[]={BUTTON_1,BUTTON_2,BUTTON_3};
void setup()
{
    //Serial usb
    Serial.begin(115200);
    Serial.println("Hello world!");
    //Button
    //Activate pullup for buttons
    for(int i=0; i<BUTTON_NUM; i++){
        pinMode(buttons[i], INPUT_PULLUP);
    }

}

void loop()
{
    testButtons();
    testVersion();
}
/**
 * @brief Checks button and write on serial when pressed
 * 
 */
void testButtons(){
    for (int i=0; i<BUTTON_NUM; i++){
        if(digitalRead(buttons[i])== LOW){
            Serial.print("Pressed button ");
            Serial.println(i+1);
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
    static uint32_t lastRead=millis();
    if(millis()-lastRead > READ_ANALOG_EVERY_MS){
    Serial.print(analogRead(25));
    Serial.print(", ");
    Serial.print(analogRead(33));
    Serial.println();
    lastRead=millis();
    }
}