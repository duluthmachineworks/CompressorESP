#include <Arduino.h>
#include <CompressorESP.h>

// Relay pins for LILYGO T-Relay Board
#define RELAY_PIN_1 21 // Pump 1 contactor
#define RELAY_PIN_2 19 // Pump 1 unloader
#define RELAY_PIN_3 18 // Pump 2 contactor
#define RELAY_PIN_4 5  // Pump 2 unloader
#define LED_PIN 25
#define SWITCH_PIN 34

Compressor pump1(RELAY_PIN_1, RELAY_PIN_2, RELAY_PIN_1);
Compressor pump2(RELAY_PIN_3, RELAY_PIN_4, RELAY_PIN_3);

int buttonState = 0;
int lastButtonState = 0;

void setup() {
  // Init serial
  Serial.begin(9600);
  delay(100);
  Serial.println();
  Serial.println("setup");

  // Init button - for testing
  pinMode(SWITCH_PIN, INPUT);
  // Init LED - for testing
  pinMode(LED_PIN, OUTPUT);

  // Init compressor objects
  pump1.begin();
  pump2.begin();

  if (pump1.unloadPump()) {
    Serial.println("Pump 1 Unloaded");
  }
  delay(500);
  if (pump2.unloadPump()) {
    Serial.println("Pump 2 Unloaded");
  }
  delay(500);
}

void loop() {
  
  
  //Implement button to test features
  buttonState = digitalRead(SWITCH_PIN);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      Serial.println("pressed");
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }
  lastButtonState = buttonState;




  delay(25);
}