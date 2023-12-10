#include <Arduino.h>
#include <CompressorESP.h>

//Relay pins for LILYGO T-Relay Board
#define RELAY_PIN_1 21 //Pump 1 contactor
#define RELAY_PIN_2 19 //Pump 1 unloader
#define RELAY_PIN_3 18 //Pump 2 contactor
#define RELAY_PIN_4 5 //Pump 2 unloader
#define LED_PIN     25

Compressor pump1(RELAY_PIN_1, RELAY_PIN_2, RELAY_PIN_1);
Compressor pump2(RELAY_PIN_3, RELAY_PIN_4, RELAY_PIN_3);


void setup() {
    Serial.begin(9600);
    delay(100);
    Serial.println();
    Serial.println("setup");
    pump1.begin();
    pump2.begin();

    if(pump1.unloadPump()) {
        Serial.println("Pump 1 Unloaded");
    }
    delay(500);
    if(pump2.unloadPump()) {
        Serial.println("Pump 2 Unloaded");
    }
    delay(500);

    pump1.startCompressor();
    Serial.println("Pump 1 Started");
    delay(10000);
    pump2.startCompressor();
    Serial.println("Pump 2 started");
    delay(10000);
    pump1.stopCompressor();
    pump2.stopCompressor();
    Serial.println("All pumps stopped and unloaded");
}

void loop() {
    
}