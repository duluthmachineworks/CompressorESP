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
enum PumpState { Offline, Online, Starting, Running, Stopping };
enum UlState { Open, Unloading, Closed };

//Compressor class definition
class Compressor {
private:
  // Pins that must be specified
  const uint8_t contactor_pin;
  const uint8_t unloader_pin;
  const uint8_t tank_drain_pin;

  //tank drain stuff, implement later
  const bool ext_tank_drain;
  const bool ext_tank_drain_func; // figure this out later

  // Set points
  int high_pressure;
  int low_pressure;
  int max_temp;
  int min_temp;

  // Other options
  int duty_cycle; // implement later
  int unload_time;
  int drain_time;
  int run_start_time; // In millis - later
  int run_end_time;   // in millis - later

  //States
  PumpState pump_state;
  UlState unloader_state;

  //Time recording
  unsigned long pump_start_time;
  unsigned long unloader_start_time;

  //Private direct control functions
  void openUnloader();
  void closeUnloader();
  void compressorOn();
  void compressorOff();

public:
  Compressor(uint8_t contactor_pin, uint8_t unloader_pin,
             uint8_t tank_drain_pin = -1, bool ext_tank_drain = false,
             bool ext_tank_drain_func = NULL, int high_pressure = 120,
             int low_pressure = 100, int duty_cycle = 25, int max_temp = 175,
             int min_temp = 32, int unload_time = 2, int drain_time = 5);

  void begin();
  void run();

  void startCompressor();
  void stopCompressor();

  bool unloadPump();
  bool drainTank();

  void setUnloadTime(int s_unload_time);
  void setDrainTime(int s_drain_time);
};

#endif