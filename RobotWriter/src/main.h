/**
 * @file main.h
 * @brief Main configuration header for setting up the robot and font data environment.
 * @details
 * This header file consolidates the necessary includes and defines for controlling the robot and
 * processing font data. It includes references to the RS232 and serial communication libraries,
 * the font data structures and functions, the G-code generation utilities, and the robot control
 * functionality. It also defines the default baud rate for communication with the robot.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */
#pragma once

#include "../lib/rs232.h"
#include "../lib/serial.h"

#include "font/fontData.h"
#include "robot/gcode.h"
#include "robot/robot.h"
#include "misc/error.h"

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DECLARATIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Prompts the user to enter a desired text height and converts it into a scale factor.
 * @param[out] scale Pointer to a double where the computed scale factor will be stored.
 * @return SUCCESS if a valid scale is obtained, or ERROR_INVALID_SCALE_INPUT if the input is invalid.
 */
errorCode_t GetUserScale(double *scale);

/**
 * @brief Prompts the user for a file name and attempts to open it for reading.
 * @param[out] file Pointer to a FILE* where the opened file pointer will be stored.
 * @return SUCCESS on successfully opening the file, or ERROR_OPEN_FILE if the file cannot be opened.
 */
errorCode_t GetUserFile(FILE **file);
