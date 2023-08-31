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

#include "Arduino.h"
#ifndef CompressorESP_h
#define CompressorESP_h

class Compressor {
private:
  uint8_t contactor_pin;
  uint8_t unloader_pin;
  uint8_t tank_drain_pin;
  bool ext_tank_drain = false;
  int set_high_pressure;
  int set_low_pressure;
  int set_max_temp;
  int set_min_temp;

public:
  Compressor(uint8_t contactor_pin, uint8_t unloader_pin,
             uint8_t tank_drain_pin = NULL, bool ext_tank_drain = false,
             int max_pressure = 120, int start_pressure = 100, int max_temp = 175,
             int min_temp = 32);
  void startCompressor();
  void stopCompressor();
  void unloadPump();
  void drainTank();
};

#endif