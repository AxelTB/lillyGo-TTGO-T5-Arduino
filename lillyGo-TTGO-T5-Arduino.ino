
#define BUTTON_1 38
#define BUTTON_2 37
#define BUTTON_3 39

void IRAM_ATTR ButtonISR() {
    Serial.println("Button");
}

int pins[]={BUTTON_1,BUTTON_2,BUTTON_3};
void setup()
{
    //Serial usb test
    Serial.begin(115200);
    Serial.println("Hello world!");
    //Button ISR
    attachInterrupt(BUTTON_1, ButtonISR, FALLING);

}

void loop()
{
    Serial.println("Loop");
    dumpStatuses(pins,3);
    delay(1000);
}

void dumpStatuses(int *pins, int len){
    for(int i=0; i<len; i++){
        Serial.print(digitalRead(pins[i])==HIGH ? "H":"L");
    }
    Serial.println();
}