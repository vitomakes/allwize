/*

Allwize - Module Info Example

This example prints out the configuration settings stored
in the module non-volatile memory.

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

#include "Allwize.h"
Allwize * allwize;

#ifdef ARDUINO_AVR_UNO
    #define RX_PIN      8
    #define TX_PIN      9
    #include <SoftwareSerial.h>
    SoftwareSerial module(RX_PIN, TX_PIN);
#endif

#ifdef ARDUINO_AVR_LEONARDO
    #define module      Serial1
#endif

#ifdef ARDUINO_ARCH_ESP8266
    #define RX_PIN      12
    #define TX_PIN      13
    #include <SoftwareSerial.h>
    SoftwareSerial module(RX_PIN, TX_PIN);
#endif

#define COLUMN_PAD  20

void format(const char * name, const char * value) {
    Serial.print(name);
    for (uint8_t i=0; i<COLUMN_PAD-strlen(name); i++) Serial.print(" ");
    Serial.println(value);
}

void format(const char * name, String value) {
    Serial.print(name);
    for (uint8_t i=0; i<COLUMN_PAD-strlen(name); i++) Serial.print(" ");
    Serial.println(value);
}

void format(const char * name, int value) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", value);
    format(name, buffer);
}

void setup() {

    Serial.begin(115200);
    while (!Serial);

    module.begin(19200);
    module.setTimeout(2000);
    allwize = new Allwize(module);
    allwize->setTimeout(2000);

    Serial.println();
    Serial.println("Allwize - Module Memory Dump");
    Serial.println();

    if (!allwize->ready()) {
        Serial.println("Module not ready");
        return;
    }

    format("Property", "Value");
    Serial.println("------------------------------");

    format("Channel", allwize->getChannel());
    format("Power", allwize->getPower());
    format("MBUS Mode", allwize->getMBusMode());
    format("Sleep Mode", allwize->getSleepMode());
    format("Control Field", allwize->getControlField());

    format("Manufacturer ID", allwize->getMID());
    format("Unique ID", allwize->getUID());
    format("Version", allwize->getVersion());
    format("Device", allwize->getDevice());
    format("Temperature (C)", allwize->getTemperature());
    format("Voltage (mV)", allwize->getVoltage());

}

void loop() {}
