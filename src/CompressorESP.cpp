#include "Arduino.h"
#include "CompressorESP.h"
//#define START_LAG 3;

// Create a compressor object, with user input
Compressor::Compressor(uint8_t contactor_pin, uint8_t unloader_pin,
                       uint8_t tank_drain_pin, bool ext_tank_drain, bool ext_tank_drain_funcL,
                       int high_pressure, int low_pressure, int duty_cycle, int max_temp,
                       int min_temp, int unload_time, int drain_time) 
    : contactor_pin{contactor_pin}
    , unloader_pin{unloader_pin}
    , tank_drain_pin{tank_drain_pin}
    , ext_tank_drain{ext_tank_drain}
    , ext_tank_drain_func{ext_tank_drain_func}
    , high_pressure{high_pressure}
    , low_pressure{low_pressure}
    , duty_cycle{duty_cycle}
    , max_temp{max_temp}
    , min_temp{min_temp}
    , unload_time{unload_time}
    , drain_time{drain_time}
{
}

// --------------------- Private Functions --------------------- //

void Compressor::openUnloader() {
  digitalWrite(unloader_pin, HIGH);
}

void Compressor::closeUnloader() {
  digitalWrite(unloader_pin, LOW);
}

// --------------------- Public Functions --------------------- //
void Compressor::begin() {
  //Sets each of the utilized pins to output
  pinMode(contactor_pin, OUTPUT);
  pinMode(unloader_pin, OUTPUT);
  pinMode(tank_drain_pin, OUTPUT);
  
}

void Compressor::startCompressor() {
  openUnloader();
  delay(1000);
  digitalWrite(contactor_pin, HIGH);
  delay(2000);
  closeUnloader();
}

void Compressor::stopCompressor(){
  digitalWrite(contactor_pin, LOW);
  delay(1000);
  unloadPump();
}

bool Compressor::unloadPump() {
  openUnloader();
  delay(unload_time * 1000);
  closeUnloader();
  return true;
}

bool Compressor::drainTank() {
  if (ext_tank_drain) {
    return false;
    //Eventually will execute ext_tank_drain_func
  } else {
    digitalWrite(tank_drain_pin, HIGH);
    delay(drain_time * 1000);
    digitalWrite(tank_drain_pin, LOW);
  }

  return true; //do I want to do this?
}

void Compressor::setUnloadTime(int s_unload_time) {
  unload_time = s_unload_time;
}

void Compressor::setDrainTime(int s_drain_time) { 
    drain_time = s_drain_time; 
}