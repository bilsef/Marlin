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
#ifdef __IMXRT1062__

#include "../../core/serial.h"
#include "../../inc/MarlinConfigPre.h"

#if ENABLED(ETHERNETSUPPORT)

#include <NativeEthernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

EthernetServer server(23);

EthernetClient telnetClient;

enum linkStates {UNLINKED, LINKING, LINKED, CONNECTING, CONNECTED, NO_HARDWARE} linkState;

void ethernet_init() {

  SERIAL_ECHO_MSG("Starting network...");

  // initialize the Ethernet device
  Ethernet.begin(mac);  // use DHCP
  //Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    SERIAL_ERROR_MSG("Ethernet hardware was not found.  Sorry, can't run without hardware. :(");
    linkState = NO_HARDWARE;
    return;
  }

  linkState = UNLINKED;

  if (Ethernet.linkStatus() == LinkOFF) {
    SERIAL_ERROR_MSG("Ethernet cable is not connected.");
    //delay(500);
    return;
  }

  delay(100);

  server.begin();

  linkState = LINKING;
}

bool newClient=0;
void ethernet_check() {

  switch (linkState) {
    case NO_HARDWARE:
      break;

    case UNLINKED:
      if (Ethernet.linkStatus() == LinkOFF) {
        break;
      }
      SERIAL_ECHOLN("Ethernet cable connected");
      server.begin();
      linkState = LINKING;
      break;

    case LINKING:
      if (!Ethernet.localIP()) break;

      SERIAL_ECHO("Successfully started telnet server with IP ");
      SERIAL_ECHO((Ethernet.localIP()) & 0xFF);
      SERIAL_ECHOPAIR(":", (Ethernet.localIP()>>8) & 0xFF);
      SERIAL_ECHOPAIR(":", (Ethernet.localIP()>>16) & 0xFF);
      SERIAL_ECHOLNPAIR(":", (Ethernet.localIP()>>24) & 0xFF);

      linkState = LINKED;
      break;

    case LINKED:
      if (Ethernet.linkStatus() == LinkOFF) {
        SERIAL_ERROR_MSG("Ethernet cable is not connected.");
        linkState = UNLINKED;
        break;
      }
      telnetClient = server.accept();
      if (telnetClient) {
        SERIAL_ECHOLN("Client connected");
        linkState = CONNECTING;
      }
      break;

    case CONNECTING:
      telnetClient.println("Marlin " SHORT_BUILD_VERSION);
      #if defined(STRING_DISTRIBUTION_DATE) && defined(STRING_CONFIG_H_AUTHOR)
        telnetClient.println(
          " Last Updated: " STRING_DISTRIBUTION_DATE
          " | Author: " STRING_CONFIG_H_AUTHOR
        );
      #endif
      telnetClient.println("Compiled: " __DATE__);
      linkState = CONNECTED;
      break;

    case CONNECTED:
      if (telnetClient && !telnetClient.connected()) {
        SERIAL_ECHOLN("Client disconnected");
        telnetClient.stop();
        linkState = LINKED;
      }
      if (Ethernet.linkStatus() == LinkOFF) {
        SERIAL_ERROR_MSG("Ethernet cable is not connected.");
        if (telnetClient) telnetClient.stop();
        linkState = UNLINKED;
      }
      break;

    default:
      break;
  }
    return;
}

#endif // ETHERNETSUPPORT
#endif // __IMXRT1062__
