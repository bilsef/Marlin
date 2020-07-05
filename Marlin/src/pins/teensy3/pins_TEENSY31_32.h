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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Teensy 3.1 (MK20DX256) and Teensy 3.2 (MK20DX256) Breadboard pin assignments
 * Requires the Teensyduino software with Teensy 3.1 or Teensy 3.2 selected in Arduino IDE!
 * http://www.pjrc.com/teensy/teensyduino.html
 */

/*********************************************************************************************************
plan for Teensy3.2:
                                                     USB
                                          GND |-----#####-----| VIN 5V
      E1_DIR              MOSI1   RX1       0 |     #####     | Analog GND
      E1_STEP             MISO1   TX1       1 |               | 3.3V
      X_STOP                                2 |         AREF* | 23  A9 PWM               TEMP_BED (VACUUM)
      X_DIR                    CAN0TX  PWM  3 |          A10* | 22  A8 PWM               E0_ENABLE
      X_STEP                   CAN0RX  PWM  4 |          A11* | 21  A7 PWM  CS0          HEATER_BED (VAC_PUMP)
      X_ENABLE            MISO1   TX1  PWM  5 |      * *      | 20  A6 PWM  CS0          TEMP0 (LEFT_VAC)
      E1_ENABLE                        PWM  6 |      * *      | 19  A5            SCL0   TEMP1 (RIGHT_VAC)
      E0_DIR              MOSI0   RX3       7 |      * *      | 18  A4            SDA0   SOL1 (RIGHT_VALVE)
      E0_STEP             MISO0   TX3       8 |      * *      | 17  A3            SDA0   SOL0 (LEFT_VALVE)
      Y_STOP              CS0     RX2  PWM  9 |      * *      | 16  A2            SCL0   Z_ENABLE
      Y_DIR               CS0     TX2  PWM 10 |      * *      | 15  A1      CS0          Z_STEP
      Y_STEP              MOSI0            11 |      * *      | 14  A0      CS0   SCK0   Z_DIR
      Y_ENABLE            MISO0            12 |___*_*_*_*_*___| 13 LED            SCK0   Z_STOP
                                                          |
                                                          |_____   A14  DAC              LIGHT_CONTROL   

          Interior pins:
                                                 A12 * * 5A13
                                                 GND * * 3.3V
                                                  24 * * 33   
                                       PWM        25 * * 32        PWM
                                       RX2  A15   26 * * 31   A20       TX2  
                                            A16   27 * * 30   A19            SDA1
                                            A17   28 * * 29   A18            SCL1


*********************************************************************************************************/

#if !IS_32BIT_TEENSY
  #error "Oops! Select 'Teensy 3.1' or 'Teensy 3.2' in 'Tools > Board.'"
#endif

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "Teensy3.2"
#endif

#define AT90USB 1286   // Disable MarlinSerial etc.
#define USBCON //1286  // Disable MarlinSerial etc.

//
// Limit Switches
//
#define X_STOP_PIN          2
#define Y_STOP_PIN          9
#define Z_STOP_PIN          28 //13

//
// Steppers
//
#define X_STEP_PIN          4
#define X_DIR_PIN           3
#define X_ENABLE_PIN        5

#define Y_STEP_PIN          11
#define Y_DIR_PIN           10
#define Y_ENABLE_PIN        12

#define Z_STEP_PIN          15
#define Z_DIR_PIN           14
#define Z_ENABLE_PIN        16

#define E0_STEP_PIN         8
#define E0_DIR_PIN          7
#define E0_ENABLE_PIN       22

#define E1_STEP_PIN         1
#define E1_DIR_PIN          0
#define E1_ENABLE_PIN       8

//
// Heaters / Fans
//
#define HEATER_0_PIN       29  // Not used
#define HEATER_1_PIN       30  // Not used
#define HEATER_BED_PIN     21  // Vacuum pump
#define HEATER_BED_INVERTING false

#ifndef FAN_PIN
  #define FAN_PIN          28  // Not used
#endif

//
// Temperature Sensors
//
#define TEMP_0_PIN         6    // Analog Input - A6 -> Left Vacuum
#define TEMP_1_PIN         5    // Analog Input - A5 -> Right Vacuum
#define TEMP_BED_PIN       9    // Analog Input - A9 -> Pump Vacuum

//#ifndef FILWIDTH_PIN
//  #define FILWIDTH_PIN      6   // Analog Input
//#endif

//
// Misc. Functions
//

//#define SDSS               16   // 8
#define LED_PIN            13

#define SOL0_PIN           17
#define SOL1_PIN           18

//#define SERVO_PIN          32  // DAC pin A14 -> LED Light


//
// LCD / Controller
//

//#define SCK_PIN            13
//#define MISO_PIN           12
//#define MOSI_PIN           11

/*
#if HAS_SPI_LCD
  #define LCD_PINS_RS      40
  #define LCD_PINS_ENABLE  41
  #define LCD_PINS_D4      42
  #define LCD_PINS_D5      43
  #define LCD_PINS_D6      44
  #define LCD_PINS_D7      45
  #define BTN_EN1          46
  #define BTN_EN2          47
  #define BTN_ENC          48
#endif
*/
