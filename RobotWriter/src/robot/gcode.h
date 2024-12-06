#pragma once

#include "robot.h"
#include "../font/fontData.h"
#include "../misc/error.h"

/**
 * @brief Processes a text file and generates G-code for the text.
 * @param fontData Pointer to the font data to use.
 */
errorCode_t process_text_file(const fontData_t *const fontData, FILE *const file);

/**
 * @brief Generates G-code for a given text string.
 * @param fontData Pointer to the font data to use.
 * @param text Text string (single word) to generate G-code for.
 */
errorCode_t generate_gcode(const fontData_t *const fontData, const char *text);
