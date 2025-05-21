// Firmware_Teensy_AiO-NG-v6 is copyright 2025 by the AOG Group
// Firmware_Teensy_AiO-NG-v6 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Firmware_Teensy_AiO-NG-v6 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
// Like most Arduino code, portions of this are based on other open source Arduino code with a compatiable license.

#ifndef CONFIGFUNCS_H
#define CONFIGFUNCS_H

#include "Arduino.h"
#include "mongoose_glue.h"

// Write default IP to EEPROM
void save_default_net()
{
    // IP stored in 300
    EEPROM.put(ipStore, defaultNet);
}

void save_default_GPS()
{
    EEPROM.put(gpsStore, defaultGPS);
}

void save_default_kwas()
{
    EEPROM.put(kwasStore, defaultKwas);
}

void save_default_ins()
{
    EEPROM.put(insStore, defaultIns);
}

// Write current IP to EEPROM
void save_current_net()
{
    // IP stored in 300
    netConfig.gatewayIP[0] = netConfig.currentIP[0];
    netConfig.gatewayIP[1] = netConfig.currentIP[1];
    netConfig.gatewayIP[2] = netConfig.currentIP[2];
    netConfig.gatewayIP[3] = 1;

    netConfig.broadcastIP[0] = netConfig.currentIP[0];
    netConfig.broadcastIP[1] = netConfig.currentIP[1];
    netConfig.broadcastIP[2] = netConfig.currentIP[2];
    netConfig.broadcastIP[3] = 255; // same subnet as module's IP but use broadcast

    EEPROM.put(ipStore, netConfig);
}

// Load current IP from EEPROM
void load_current_net()
{
    // IP loaded from 300
    EEPROM.get(ipStore, netConfig);
}

// Save GPS settings to EEPROM
void save_gps()
{
    // GPS saved to 400
    EEPROM.put(gpsStore, gpsConfig);
}

// load GPS settings from EEPROM
void load_gps()
{
    // GPS read from 400
    EEPROM.get(gpsStore, gpsConfig);
}

// Save KWAS data
void save_kwas()
{
    // Save KWAS to 600
    EEPROM.put(kwasStore, kwasCfg);
}

// Load KWAS data
void load_kwas()
{
    // Load KWAS to 600
    EEPROM.get(kwasStore, kwasCfg);
}

// Save INS data
void save_ins()
{
    // Save UM981 to 700
    EEPROM.put(insStore, insCfg);
}

// Load INS data
void load_ins()
{
    // Load UM981 to 700
    EEPROM.get(insStore, insCfg);
}

// Load the IP address from EEPROM
void storedCfgSetup()
{
    uint16_t eth_ee_read;
    EEPROM.get(eeVersionStore, eth_ee_read);

    if (eth_ee_read != EE_ver)
    { // if EE is out of sync, write defaults to EE
        EEPROM.put(eeVersionStore, EE_ver);
        save_default_net();
        load_current_net();
        Serial.print("\r\n\nWriting IP address defaults to EEPROM\r\n");

        save_default_GPS();
        Serial.print("\r\n\nWriting GPS defaults to EEPROM\r\n");
        load_gps();

        save_default_kwas();
        Serial.print("\r\n\nWriting KWAS defaults to EEPROM\r\n");
        load_kwas();

        save_default_ins();
        Serial.print("\r\n\nWriting INS defaults to EEPROM\r\n");
        load_ins();
    }
    else
    {
        load_current_net();
        Serial.print("\r\n\nLoaded IP address from EEPROM\r\n");

        load_gps();
        Serial.print("\r\n\nLoaded GPS settings from EEPROM\r\n");

        load_kwas();
        Serial.print("\r\n\nLoaded KWAS settings from EEPROM\r\n");

        load_ins();
        Serial.print("\r\n\nLoaded INS settings from EEPROM\r\n");
    }
}

void insWritePoll()
{
    if (insCfgStart)
    {
        Serial.printf("\r\nINS Cfg Writing: %d\r\n", insCfgCtr);
        Serial.println(insCfg[insCfgCtr]);
        SerialGPS1.println(insCfg[insCfgCtr]);
        //Serial.printf("Comand Status0: %d\r\n", insCmdStat);
        if (insCfgCtr == 17)
        {
            insCfgStart = false;
            insCfgCtr = 0;
        }
        insCfgCtr++;
    }
}

// static uint32_t ipv4str(const char *str)
// {
//     struct mg_addr a = {};
//     mg_aton(mg_str(str), &a);
//     return *(uint32_t *)&a.ip;
// }

void checkUM98x()
{
    uint32_t baudrate = 0;
    for (uint32_t i = 0; i < nrBaudrates; i++)
    {
        baudrate = baudrates[i];
        Serial.print("Checking for UM98x at baudrate: ");
        Serial.println(baudrate);
        SerialGPS1.begin(baudrate);
        // Increase the size of the serial buffer to hold longer UM981 config messages
        SerialGPS1.addMemoryForRead(tmpGPSrxbuffer, tmp_serial_buffer_size);
        SerialGPS1.addMemoryForWrite(tmpGPStxbuffer, tmp_serial_buffer_size);
        delay(100);
        SerialGPS1.write("VERSION\r\n");
        delay(100);
        while (SerialGPS1.available())
        {
            char incoming[tmp_serial_buffer_size];
            SerialGPS1.readBytesUntil('\n', incoming, tmp_serial_buffer_size);
            if (strstr(incoming, "UM981") != NULL) // Got a UM981 version line
            {
                Serial.print("UM981 VERSION: ");
                Serial.println(incoming);
                gotUM981 = true;
                if (baudrate != 460800)
                {
                    Serial.println("UM981 baudrate wrong for AOG. Setting to 460800 bps for AOG");
                    SerialGPS1.write("CONFIG COM1 460800\r\n");
                    delay(100);
                    SerialGPS1.write("CONFIG COM2 460800\r\n");
                    delay(100);
                    SerialGPS1.write("CONFIG COM3 460800\r\n");
                    delay(100);
                    SerialGPS1.begin(baudGPS);
                    SerialGPS1.addMemoryForRead(GPS1rxbuffer, sizeof(GPS1rxbuffer));
                    SerialGPS1.addMemoryForWrite(GPS1txbuffer, sizeof(GPS1txbuffer));
                    delay(100);
                    SerialGPS1.write("SAVECONFIG\r\n");
                }

                break;
            }
            if (gotUM981)
            {
                break;
            }
            if (strstr(incoming, "UM982") != NULL) // Got a UM982 version line
            {
                Serial.print("UM982 VERSION: ");
                Serial.println(incoming);
                gotUM982 = true;
                if (baudrate != 460800)
                {
                    Serial.println("UM982 baudrate wrong for AOG. Setting to 460800 bps for AOG");
                    SerialGPS1.write("CONFIG COM1 460800\r\n");
                    delay(100);
                    SerialGPS1.write("CONFIG COM2 460800\r\n");
                    delay(100);
                    SerialGPS1.write("CONFIG COM3 460800\r\n");
                    delay(100);
                    SerialGPS1.begin(baudGPS);
                    SerialGPS1.addMemoryForRead(GPS1rxbuffer, sizeof(GPS1rxbuffer));
                    SerialGPS1.addMemoryForWrite(GPS1txbuffer, sizeof(GPS1txbuffer));
                    delay(100);
                    SerialGPS1.write("SAVECONFIG\r\n");
                }
                break;
            }
            if (gotUM982)
            {
                break;
            }
        }
        if (gotUM981 || gotUM982)
        {
            break;
        }
    }
}

static uint32_t ipv4ary(const uint8_t input[])
{
    char buf[16];
    mg_snprintf(buf, sizeof(buf), "%d.%d.%d.%d", input[0], input[1], input[2], input[3]);
    struct mg_addr a = {};
    mg_aton(mg_str(buf), &a);
    return *(uint32_t *)&a.ip;
}

#endif