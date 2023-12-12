
# CompressorESP
A small library for controlling an air compressor with an ESP32 board.

## What does it do?
This library is intended to provide an easy way to take control of an air compressor via an ESP32-powered relay board, such as the LILYGO T-Relay or other similar models. This allows the mechanical pressure control valve to be removed and replaced with a pressure sensor, and a contactor used to start the motor instead of the mechanical pressure switch.

## But why?
Mechanical pressure control switches are generally reliable and effective, but are insufficient for complicated, multi-compressor systems. This library is intended to work with larger projects intended to assemble multiple compressor units in to large parallel "compressor arrays". Digital compressor control could also be integrated in to various IOT style systems, allowing remote monitoring and start/stop of an air compressor system.

## How does it work?

This library allows creates a *compressor* object with the following features:
- The main contactor to control the motor
- A solenoid-controlled unloader valve which takes the place of a mechanical unloader valve
- A motor temperature sensor for thermal overload sensing
- A solenoid-controlled tank drain valve (optional)

Various preferences can be set upon creation of the *compressor* object, or via set functions:
- High/low pressure set points
- Max/min operating temperatures to prevent overheating or freezing
- Unload time required to entirely depressurize the line between the pump and tank
- Tank drain time, if using an automated tank drain
- Maximum start/stop frequency, in order to avoid overheating a capacitor-start motor
- Maximum duty cycle of the pump motor (minutes of run time per hour)

Assumptions include:
- That the compressor is controlled via a suitable contactor
- Pressure is monitored via a pressure sensor - this is outside of the scope of this library, although the accompanying *Baratron* library used in one of the examples can be used to interface with many types of sensors
- An appropriate solenoid valve is present to act as an unloader. This valve serves to depressurize the line between the tank check valve and the pump, allowing the pump to start under no load. 
- A temperature sensor is installed on or inside of the motor to get an acceptable thermal reading to protect from overload.
