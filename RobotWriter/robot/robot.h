/**
 * @file robot.h
 * @brief Declarations for robot control functions and related constants.
 * @details This file provides the interfaces for controlling the robot's position
 *       and movements. It includes functions to start up the robot, send strokes
 *       (pen movements) to it, and return it to a 'home' position, as well as
 *       defining various constants that govern its coordinate space and text
 *       dimensions.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#pragma once

#include "../lib/rs232.h"
#include "../lib/serial.h"
#include "../font/fontChar.h"
#include "../misc/error.h"
#include "cursor.h"

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

#define MAX_X_VALUE_MM 100.0   /**< Maximum X coordinate value in millimeters. */
#define MAX_Y_VALUE_MM 0       /**< Maximum Y coordinate value in millimeters. */
#define MIN_X_VALUE_MM 0       /**< Minimum X coordinate value in millimeters. */
#define MIN_Y_VALUE_MM -500.0 /**< Minimum Y coordinate value in millimeters. */

#define HOME_X_VALUE_MM 0.0 /**< Home position X coordinate in millimeters. */
#define HOME_Y_VALUE_MM 0.0 /**< Home position Y coordinate in millimeters. */

#define CHARACTER_SPACE_MM 18.0 /**< Default spacing in millimeters between characters. */
#define LINE_SPACE_MM 5.0       /**< Default line spacing in millimeters. */

#define MINIMUM_TEXT_HEIGHT_MM 4.0  /**< Minimum permissible text height in millimeters. */
#define MAXIMUM_TEXT_HEIGHT_MM 10.0 /**< Maximum permissible text height in millimeters. */

#define FONT_FILE "SingleStrokeFont.txt" /**< Default font file name. */

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DECLARATIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes and starts up the robot.
 * @return SUCCESS on successful startup, or an appropriate error code if startup fails.
 */
errorCode_t StartUpRobot(void);

/**
 * @brief Sends a stroke command to the robot based on the current cursor position.
 * @param[in] cursor Pointer to the cursor_t structure representing the robot's current position.
 * @param[in] stroke The stroke_t structure containing the vector and pen state to apply.
 * @return SUCCESS on success, or an appropriate error code if sending the stroke fails.
 */
errorCode_t SendStoke(const cursor_t *const cursor, const stroke_t stroke);

/**
 * @brief Moves the robot to its home position.
 * @return SUCCESS on success, or an appropriate error code if moving to home fails.
 */
errorCode_t HomeRobot(void);
