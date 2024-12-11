/**
 * @file gcode.c
 * @brief Implementation of text processing functions that generate G-code from text using font data.
 * @details This file provides functions to process text from a file and to generate G-code
 *       instructions using a given font data set.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#include "gcode.h"

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

/**
 * @details
 * This function uses a static cursor to track the current drawing position. If the cursor
 * isn't initialized, it constructs a new cursor using the font data's scale factor. Before
 * processing the text, it checks if the word would overflow the current cursor line. If so,
 * it moves to a new line.
 *
 * It then iterates through the text:
 * - Spaces cause a cursor update.
 * - Newline ('\n') and carriage return ('\r') characters cause the cursor to adjust its position
 *   accordingly.
 * - Other characters are looked up in the font data. If found, their strokes are sent to the
 *   robot using `SendStoke()`. After drawing each character, the cursor is updated.
 */
errorCode_t generate_gcode(const fontData_t *const fontData, const char *text)
{
    static cursor_t cursor;                              // Static cursor to track position
    if (!cursor.init)                                    // Check if cursor is initialized
        cursor = cursorConstructor(fontData->fontScale); // Initialize cursor

    if (cursor.testWordOverflow(&cursor, text)) // Check if word would overflow
        cursor.newline(&cursor);                // Move to new line

    while (*text != '\0') // Iterate through text
    {
        switch (*text) // Check character
        {
        case ' ':                                  // Space
            if (cursor.update(&cursor) != SUCCESS) // Update cursor
                return CURSOR_OUT_OF_BOUNDS;       // Handle error
            break;
        case '\n':                                  // Newline
            if (cursor.newline(&cursor) != SUCCESS) // Move to new line
                return CURSOR_OUT_OF_BOUNDS;        // Handle error
            break;
        case '\r':                                         // Carriage return
            if (cursor.carriagereturn(&cursor) != SUCCESS) // Move to start of line
                return CURSOR_OUT_OF_BOUNDS;               // Handle error
            break;
        default:
        {
            const fontCharacter_t *const fontChar = fontData->lookup(fontData, *text); // Look up character
            if (!fontChar)                                                             // if no charater was found
            {
                ErrorHandler(FONT_CHARACTER_NOT_FOUND); // Handle error
                break;                                  // Break
            }

            for (uint8_t i = 0; i < fontChar->numStrokes; i++) // Iterate through strokes
                SendStoke(&cursor, fontChar->strokes[i]);      // Send stroke to robot

            if (cursor.update(&cursor) != SUCCESS) // Update cursor
                return CURSOR_OUT_OF_BOUNDS;       // Handle error
            break;
        }
        }
        text++; // Move to next character
    }
    return SUCCESS; // Return success
}

/**
 * @details
 * This function reads the text file character by character and accumulates characters into a buffer.
 * Once it encounters a space, newline, or carriage return, it treats the accumulated characters as
 * a complete "word" and calls `generate_gcode()` to generate G-code for that word.
 *
 * If the file ends and there are still accumulated characters, it processes those as the final word.
 * After processing the file, it closes the file and sends the robot to its home position.
 */
errorCode_t process_text_file(const fontData_t *const fontData, FILE *const file)
{

    if (!fontData)                               // Check if fontData is NULL
        return ErrorHandler(ERROR_NO_FONT_DATA); // Handle error

    if (!file)                                   // Check if file is NULL
        return ErrorHandler(ERROR_NO_TEXT_FILE); // Handle error

    char buff[256]; // Buffer to hold each word
    int ch;         // Current character
    int index = 0;  // Index in buffer

    while ((ch = fgetc(file)) != EOF) // Read characters until end of file
    {
        buff[index++] = ch; // Add character to buffer

        if (ch == ' ' || ch == '\n' || ch == '\r') // Check if character is space, newline, or carriage return
        {
            buff[index] = '\0';                                 // Null-terminate buffer
            errorCode_t error = generate_gcode(fontData, buff); // Generate G-code for word
            if (error != SUCCESS)                               // Check if error
                return ErrorHandler(error);                     // Handle error
            index = 0;                                          // Reset index
        }
    }

    if (index > 0) // Check if there are remaining characters
    {
        buff[index] = '\0';                                 // Null-terminate buffer
        errorCode_t error = generate_gcode(fontData, buff); // Generate G-code for word
        if (error != SUCCESS)                               // Check if error
            return ErrorHandler(error);                     // Handle error
    }

    fclose(file); // Close file
    HomeRobot();  // Send robot to home position

    return SUCCESS; // Return success
}
