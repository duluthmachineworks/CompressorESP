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
    , pump_state{pump_state}
    , unloader_state{unloader_state}
{
}

// --------------------- Private Functions --------------------- //

void Compressor::openUnloader() {
  unloader_state = Open;
  unloader_start_time = millis();
  digitalWrite(unloader_pin, HIGH);
}

void Compressor::closeUnloader() {
  unloader_state = Closed;
  unloader_start_time = 0;
  digitalWrite(unloader_pin, LOW);
}

void Compressor::compressorOn() {
  pump_state = Running;
  pump_start_time = millis();
  digitalWrite(contactor_pin, HIGH);
}

void Compressor::compressorOff() {
  pump_state = Off;
  pump_start_time = 0;
  digitalWrite(contactor_pin, LOW);
}

// --------------------- Public Functions --------------------- //
void Compressor::begin() {
  //Sets each of the utilized pins to output
  pinMode(contactor_pin, OUTPUT);
  pinMode(unloader_pin, OUTPUT);
  pinMode(tank_drain_pin, OUTPUT);
}

void Compressor::startCompressor() {
  pump_state = Running;//need to chancge **************************************************************************************
};

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

//Operates the state machine for each compressor object. Is called with no arguments every loop().
PumpState previous_operation_state;
UlState previous_unloader_state;
unsigned long current_op_time;

void Compressor::run() { //Stopped here for the night. This needs to change to two separate FSMs, one for the pump, and one for the unloader.
/*
  switch (pump_state) {
  case Off: {
    if (previous_operation_state != pump_state) {
      compressorOff();
    }
  }
    break;

  case Unloading: {
    current_op_time = millis();
    if (current_op_time >= ((unload_time * 1000) + unloader_start_time)) {
      closeUnloader();
    }
  }
    break;

  case Starting:
    break;

  case Running:
    break;

  default:
    break;
  }


previous_operation_state = operation_state;
previous_unloader_state = unloader_state;*/
}
