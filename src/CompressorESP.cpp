#include "Arduino.h"
#include "CompressorESP.h"

// Create a compressor object, with user input
Compressor::Compressor(uint8_t contactor_pin, uint8_t unloader_pin,
                       uint8_t tank_drain_pin, bool ext_tank_drain,
                       int max_pressure, int start_pressure, int max_temp,
                       int min_temp) 
    : contactor_pin{contactor_pin}
    , unloader_pin{unloader_pin}
    , tank_drain_pin{tank_drain_pin}
    , ext_tank_drain{ext_tank_drain}
    , max_pressure{max_pressure}
    , start_pressure{start_pressure}
    , max_temp{max_temp}
    , min_temp{min_temp}
{
}