/**
 * @file gcode.h
 * @brief Declarations for text processing functions that utilize font data and robot movement.
 * @details This file provides functions to process text from a file and to generate G-code
 *       instructions using a given font data set.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#pragma once

#include "robot.h"
#include "../font/fontData.h"
#include "../misc/error.h"

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DECLARATIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Processes a text file using the provided font data.
 * @param[in] fontData Pointer to the fontData_t structure containing font information.
 * @param[in,out] file Pointer to the file from which text will be read and processed.
 * @return SUCCESS on successful processing, or an appropriate error code if processing fails.
 */
errorCode_t process_text_file(const fontData_t *const fontData, FILE *const file);

/**
 * @brief Generates G-code commands based on the provided text using the given font data.
 * @param[in] fontData Pointer to the fontData_t structure containing font information.
 * @param[in] text     Pointer to the text string for which G-code will be generated.
 * @return SUCCESS on successful G-code generation, or an appropriate error code if generation fails.
 */
errorCode_t generate_gcode(const fontData_t *const fontData, const char *text);
