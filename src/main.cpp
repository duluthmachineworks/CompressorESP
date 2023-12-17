#include <Arduino.h>
#include <CompressorESP.h>

// Relay pins for LILYGO T-Relay Board
#define RELAY_PIN_1 21 // Pump 1 contactor
#define RELAY_PIN_2 19 // Pump 1 unloader
#define TEMP_PIN_1  34 // Pump 1 temp sensor
#define RELAY_PIN_3 18 // Pump 2 contactor
#define RELAY_PIN_4 5  // Pump 2 unloader
#define TEMP_PIN_2 34  // Pump 2 temp sensor
#define LED_PIN 25     // Onboard status LED
#define SWITCH_PIN 34  // Pin for a test button

Compressor pump1(RELAY_PIN_1, RELAY_PIN_2, TEMP_PIN_1);
Compressor pump2(RELAY_PIN_3, RELAY_PIN_4, TEMP_PIN_2);

//variables for testing
int buttonState = 0;
int lastButtonState = 0;
int startup_time;
int startup_run = 0;

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


  delay(500);
  startup_time = millis();
}

void loop() {
  pump1.run();
  pump2.run();

//Run through a sequence for testing
//does a run cycle on both pump 1 and 2, staggered, starts a new run cycle on pump 1, and then e-stops both.
if ((millis() >= startup_time + 3000) && startup_run == 0){
  pump1.startCompressor();
  Serial.println("Starting compressor 1");
  Serial.print("Error state: ");
  Serial.println(pump1.getErrorState());
  startup_run = 1;
}

if ((millis() >= startup_time + 4000) && startup_run == 1){
  pump2.startCompressor();
  Serial.println("Starting compressor 2");
  Serial.print("Error state: ");
  Serial.println(pump1.getErrorState());
  startup_run = 2;
}

if ((millis() >= startup_time + 7000) && startup_run == 2){
  pump1.stopCompressor();
  Serial.println("Stopping compressor 1");
  Serial.print("Error state: ");
  Serial.println(pump1.getErrorState());
  startup_run = 3;
}

if((millis() >= startup_time + 9000) && startup_run == 3) {
  pump2.stopCompressor();
  pump1.startCompressor();
  Serial.println("Stopping compressor 2");
  Serial.println("Re-starting compressor 1");
  Serial.print("Error state: ");
  Serial.println(pump1.getErrorState());
  startup_run = 4;
}
if ((millis() >= startup_time + 16000) && startup_run == 4) {
  pump1.eStop();
  pump2.eStop();
  Serial.println("E-stop all pumps");
  Serial.print("Error state: ");
  Serial.println(pump1.getErrorState());
  startup_run = 5;
}
 
}