/*

Allwize - Module Info Example

Pretty-prints out the configuration settings stored in the module non-volatile memory.

Copyright (C) 2018 by Allwize <github@allwize.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

// -----------------------------------------------------------------------------
// Board definitions
// -----------------------------------------------------------------------------

#if defined(ARDUINO_AVR_UNO)
    #define RESET_PIN           7
    #define RX_PIN              8
    #define TX_PIN              9
    #define DEBUG_SERIAL        Serial
#endif // ARDUINO_AVR_UNO

#if defined(ARDUINO_AVR_LEONARDO)
    #define RESET_PIN           7
    #define HARDWARE_SERIAL     Serial1
    #define DEBUG_SERIAL        Serial
#endif // ARDUINO_AVR_LEONARDO

#if defined(ARDUINO_ARCH_SAMD)
    #define RESET_PIN           7
    #define HARDWARE_SERIAL     Serial1
    #define DEBUG_SERIAL        SerialUSB
#endif // ARDUINO_ARCH_SAMD

#if defined(ARDUINO_ARCH_ESP8266)
    #define RESET_PIN           14
    #define RX_PIN              12
    #define TX_PIN              13
    #define DEBUG_SERIAL        Serial
#endif // ARDUINO_ARCH_ESP8266

#if defined(ARDUINO_ARCH_ESP32)
    #define RESET_PIN           14
    #define RX_PIN              12
    #define TX_PIN              13
    #define DEBUG_SERIAL        Serial
#endif // ARDUINO_ARCH_ESP32

// -----------------------------------------------------------------------------
// Config & globals
// -----------------------------------------------------------------------------

#include "Allwize.h"
Allwize * allwize;

// -----------------------------------------------------------------------------
// Utils
// -----------------------------------------------------------------------------

#define COLUMN_PAD  20

void format(const char * name, const char * value) {
    DEBUG_SERIAL.print(name);
    for (uint8_t i=0; i<COLUMN_PAD-strlen(name); i++) DEBUG_SERIAL.print(" ");
    DEBUG_SERIAL.println(value);
}

void format(const char * name, String value) {
    DEBUG_SERIAL.print(name);
    for (uint8_t i=0; i<COLUMN_PAD-strlen(name); i++) DEBUG_SERIAL.print(" ");
    DEBUG_SERIAL.println(value);
}

void format(const char * name, int value) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", value);
    format(name, buffer);
}

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------

void setup() {

    DEBUG_SERIAL.begin(115200);
    while (!DEBUG_SERIAL && millis() < 5000);
    DEBUG_SERIAL.println();
    DEBUG_SERIAL.println("Allwize - Module Info");
    DEBUG_SERIAL.println();

    // Create and init AllWize object
    #if defined(HARDWARE_SERIAL)
        allwize = new Allwize(&HARDWARE_SERIAL, RESET_PIN);
    #else
        allwize = new Allwize(RX_PIN, TX_PIN, RESET_PIN);
    #endif
    allwize->begin();
    if (!allwize->waitForReady()) {
        DEBUG_SERIAL.println("Error connecting to the module, check your wiring!");
        while (true);
    }

    format("Property", "Value");
    DEBUG_SERIAL.println("------------------------------");

    format("Channel", allwize->getChannel());
    format("Power", allwize->getPower());
    format("MBUS Mode", allwize->getMBusMode());
    format("Sleep Mode", allwize->getSleepMode());
    format("Data Rate", allwize->getDataRate());
    format("Preamble Length", allwize->getPreamble());
    format("Sleep Mode", allwize->getSleepMode());
    format("Control Field", allwize->getControlField());
    format("Network Role", allwize->getNetworkRole());
    format("Install Mode", allwize->getInstallMode());

    format("Manufacturer ID", allwize->getMID());
    format("Unique ID", allwize->getUID());
    format("Version", allwize->getVersion());
    format("Device", allwize->getDevice());
    format("Part Number", allwize->getPartNumber());
    format("Hardware Version", allwize->getHardwareVersion());
    format("Firmware Version", allwize->getFirmwareVersion());
    format("Serial Number", allwize->getSerialNumber());

    format("Temperature (C)", allwize->getTemperature());
    format("Voltage (mV)", allwize->getVoltage());

}

void loop() {}
