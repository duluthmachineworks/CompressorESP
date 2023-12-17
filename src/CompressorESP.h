// CompressorESP.h

/*This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

/***************************************************************************
* Create a class for compressor objects, using user selected values.
 ****************************************************************************/

#include "Arduino.h"
#ifndef CompressorESP_h
#define CompressorESP_h

// Enumerated States
enum PumpState { Offline, Online, Running };
enum UlState { Open, Unloading, Closed };
enum ErrorCode { None, Offline_err, EStop_err, Unload_err, Motor_err };

// Compressor class definition
class Compressor {
private:
  // Pins that must be specified
  const uint8_t contactor_pin;
  const uint8_t unloader_pin;
  const uint8_t temp_sensor_pin;

  // Set points
  int high_pressure;
  int low_pressure;
  int max_temp;
  int min_temp;
  int duty_cycle; // in min/hr
  int unload_time;

  // States
  PumpState pump_state;
  UlState unloader_state;
  PumpState previous_pump_state;
  UlState previous_unloader_state;

  // Time recording
  unsigned long pump_start_time;
  unsigned long unloader_start_time;
  unsigned long current_millis;

  // data recording
  unsigned long acc_run_time;
  ErrorCode error_state = None;


  // Private direct control functions
  void openUnloader();
  void closeUnloader();
  void compressorOn();
  void compressorOff();

  // Private helper functions
  bool stateIsChanged();

public:
  Compressor(uint8_t contactor_pin, uint8_t unloader_pin,
             uint8_t temp_sensor_pin, int high_pressure = 120,
             int low_pressure = 100, int duty_cycle = 30, int max_temp = 175,
             int min_temp = 32, int unload_time = 2);

  void begin();
  void run();
  void takeOnline();
  void takeOffline();

  void startCompressor();
  void stopCompressor();
  void eStop();

  void unloadPump();
  void drainTank();

  //Setter functions
  void setUnloadTime(int s_unload_time);
  void setDrainTime(int s_drain_time);
  void clearErrorCode();

  //Getter functions
  PumpState getPumpState();
  UlState getUnloaderState();
  int getErrorState();
};

#endif