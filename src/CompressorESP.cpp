#include "Arduino.h"
#include "CompressorESP.h"

// Create a compressor object, with user input
Compressor::Compressor(uint8_t contactor_pin, uint8_t unloader_pin,
                       uint8_t tank_drain_pin, bool ext_tank_drain, bool ext_tank_drain_func = NULL,
                       int high_pressure, int low_pressure, int max_temp,
                       int min_temp, int unload_time = 2, int drain_time = 5) 
    : contactor_pin{contactor_pin}
    , unloader_pin{unloader_pin}
    , tank_drain_pin{tank_drain_pin}
    , ext_tank_drain{ext_tank_drain}
    , ext_tank_drain_func{ext_tank_drain_func}
    , high_pressure{high_pressure}
    , low_pressure{low_pressure}
    , max_temp{max_temp}
    , min_temp{min_temp}
    , unload_time{unload_time}
    , drain_time{drain_time}
{
}

void startCompressor();
void stopCompressor();

bool Compressor::unloadPump() {
  digitalWrite(unloader_pin, HIGH);
  delay(unload_time * 1000);
  digitalWrite(unloader_pin, LOW);

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