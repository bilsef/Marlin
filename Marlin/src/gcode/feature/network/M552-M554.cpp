/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../../inc/MarlinConfigPre.h"

#if ENABLED(ETHERNET_SUPPORT)

//#include "../../../feature/network/ethernet.h"
#include "../../../HAL/TEENSY40_41/ethernet.h"
#include "../../../core/serial.h"
#include "../../gcode.h"

//
// M552: Set IP address, enable/disable network interface
//      Pnnn IP address, 0.0.0.0 means acquire an IP address using DHCP
//      Snnn (optional) -1 = reset network interface, 0 = disable networking, 1 = enable networking as a client

void GcodeSuite::M552() {
    if (parser.seenval('P')) ip.fromString(parser.value_string());
    SERIAL_ECHO("ip address: ");
    if (Ethernet.linkStatus() == LinkON) {
        if (!serial_port_index) Ethernet.localIP().printTo(MYSERIAL0);
        if ( serial_port_index) Ethernet.localIP().printTo(MYSERIAL1);
    }
    else {
        if (!serial_port_index) ip.printTo(MYSERIAL0);
        if ( serial_port_index) ip.printTo(MYSERIAL1);
    }
    SERIAL_EOL();
}

//
// M553: Set Netmask
//      Pnnn Netmask
//

  void GcodeSuite::M553() {
    if (parser.seenval('P')) subnet.fromString(parser.value_string());
    SERIAL_ECHO("subnet mask: ");
    if (Ethernet.linkStatus() == LinkON) {
        if (!serial_port_index) Ethernet.subnetMask().printTo(MYSERIAL0);
        if ( serial_port_index) Ethernet.subnetMask().printTo(MYSERIAL1);
    }
    else {
        if (!serial_port_index) subnet.printTo(MYSERIAL0);
        if ( serial_port_index) subnet.printTo(MYSERIAL1);
    }
    SERIAL_EOL();
  }

//
// M554: Set Gateway
//      Pnnn Gatewway
//

  void GcodeSuite::M554() {
    if (parser.seenval('P')) gateway.fromString(parser.value_string());
    SERIAL_ECHO("gateway address: ");
    if (Ethernet.linkStatus() == LinkON) {
        if (!serial_port_index) Ethernet.gatewayIP().printTo(MYSERIAL0);
        if ( serial_port_index) Ethernet.gatewayIP().printTo(MYSERIAL1);
    }
    else {
        if (!serial_port_index) gateway.printTo(MYSERIAL0);
        if ( serial_port_index) gateway.printTo(MYSERIAL1);
    }
    SERIAL_EOL();
  }


#endif // ETHERNET_SUPPORT
