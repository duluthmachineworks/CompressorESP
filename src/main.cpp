#include <Arduino.h>
#include <CompressorESP.h>

//Relay pins for LILYGO T-Relay Board
#define RELAY_PIN_1 21 //Pump 1 contactor
#define RELAY_PIN_2 19 //Pump 1 unloader
#define RELAY_PIN_3 18 //Pump 2 contactor
#define RELAY_PIN_4 5 //Pump 2 unloader
#define LED_PIN     25

Compressor pump1(RELAY_PIN_1, RELAY_PIN_2);
Compressor pump2(RELAY_PIN_3, RELAY_PIN_4);


void setup() {
    pump1.begin();
    pump2.begin();
}

void loop() {
    pump1.unloadPump();
    delay(500);
    pump2.unloadPump();
    delay(500);
}