#include "Arduino.h"
#include "CompressorESP.h"
//#define START_LAG 3;

// Create a compressor object, with user input
Compressor::Compressor(uint8_t contactor_pin, uint8_t unloader_pin,
             uint8_t temp_sensor_pin, int high_pressure,
             int low_pressure, int duty_cycle, int max_temp,
             int min_temp, int unload_time)
    //copy to local variables
    : contactor_pin{contactor_pin}
    , unloader_pin{unloader_pin}
    , temp_sensor_pin{temp_sensor_pin}
    , high_pressure{high_pressure}
    , low_pressure{low_pressure}
    , duty_cycle{duty_cycle}
    , max_temp{max_temp}
    , min_temp{min_temp}
    , unload_time{unload_time}
    , pump_state{pump_state}
    , unloader_state{unloader_state}
    , error_state{error_state}
{
}

// --------------------- Private Functions --------------------- //

//Direct control functions. These directly start and stop equipment
void Compressor::openUnloader() {
  unloader_state = Open;
  unloader_start_time = current_millis;
  digitalWrite(unloader_pin, HIGH);
}

void Compressor::closeUnloader() {
  unloader_state = Closed;
  unloader_start_time = 0;
  digitalWrite(unloader_pin, LOW);
}

void Compressor::compressorOn() {
  pump_state = Running;
  pump_start_time = current_millis;
  digitalWrite(contactor_pin, HIGH);
}

void Compressor::compressorOff() {
  pump_state = Online;
  pump_start_time = 0;
  digitalWrite(contactor_pin, LOW);
}

bool Compressor::stateIsChanged() {
  if (pump_state != previous_pump_state && unloader_state != previous_unloader_state) {
    return true;
  } else {
    return false;
  }
}

// --------------------- Public Functions --------------------- //
void Compressor::begin() {
  //Called during setup(), Sets each of the utilized pins to output
  pinMode(contactor_pin, OUTPUT);
  pinMode(unloader_pin, OUTPUT);
  pinMode(temp_sensor_pin, INPUT);
}

void Compressor::takeOnline() {
  //Do not allow compressor to become online without clearing errors
  switch (error_state) {
    case None: {
      pump_state = Online;
    } break;

    default:
    break;
  }
}

void Compressor::takeOffline() {
  stopCompressor();
  pump_state = Offline;
}

void Compressor::startCompressor() {
  switch (pump_state) {

  case Offline: {
    error_state = Offline_err;
  } break;

  case Online: {
    unloadPump();
    compressorOn();
  }
  default:
    break;
  }
};

void Compressor::stopCompressor(){
  compressorOff();
  unloadPump();
}

void Compressor::eStop() {
  compressorOff();
  openUnloader();
  pump_state = Offline;
  error_state = EStop_err;
}

void Compressor::unloadPump() {
  unloader_state = Unloading;
  unloader_start_time = current_millis;
  digitalWrite(unloader_pin, HIGH);
}

void Compressor::drainTank() {
 return;
}

// ---- Setter functions ---- //
void Compressor::setUnloadTime(int s_unload_time) {
  unload_time = s_unload_time;
}

void Compressor::clearErrorCode() {
  error_state = None;
}

// ---- Getter functions ---- //
PumpState Compressor::getPumpState() {
  return pump_state;
}

UlState Compressor::getUnloaderState() {
  return unloader_state;
}

// run() operates the state machine for each compressor object. Is called with no arguments every loop().

void Compressor::run() {
  // Called in the loop() function. This handles the state management for
  // compressor objects

  // Get the current time to sync all functions
  current_millis = millis();

  //  *** Pump state machine *** //
  switch (pump_state) {
  case Offline: {
    //Do something
  }

  case Online: {
    // Do something
  }

  

  case Running: {
    // Do something
  }

  default:
    break;
  }

  // *** Unloader state machine *** //
  switch (unloader_state) {

  case Closed: {
    // Do something
  }

  case Open: {
    // Do something
  } break;

  case Unloading: {
    if (current_millis >= (unloader_start_time + (unload_time * 1000))) {
     closeUnloader();
    }
  } break;

  default:
    break;
  }

 
  // Save current state for the next loop() run
  previous_pump_state = pump_state;
  previous_unloader_state = unloader_state;
}
