/**
 * @file main.c
 * @brief Entry point for the robot text drawing application.
 * @details
 * This program initializes the robot, parses font data from a specified font file,
 * and allows the user to specify a text height and input file containing the text to be drawn.
 * It then processes the input text, converts it into G-code, and sends the commands to the robot
 * to draw the text. Finally, it frees allocated resources and concludes the operation.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#include "main.h"

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

/**
 * @details
 * This function flushes the standard input, requests a text height from the user,
 * and validates that it falls within the permitted range. If valid, the height is
 * converted into a scale factor based on the default character space.
 */
errorCode_t GetUserScale(double *scale)
{
    double height;                                       // Desired text height in millimeters
    fflush(stdin);                                       // Flush standard input
    printf("Enter the desired text height (4-10 mm): "); // Prompt user for text height

    if (scanf("%lf", &height) != 1 || height < MINIMUM_TEXT_HEIGHT_MM || height > MAXIMUM_TEXT_HEIGHT_MM) // Check if input is valid
        return ErrorHandler(ERROR_INVALID_SCALE_INPUT);                                                   // Handle error

    *scale = height / CHARACTER_SPACE_MM; // Calculate scale factor
    return SUCCESS;                       // Return success
}

/**
 * @details
 * This function flushes the standard input, requests a file name from the user, and
 * tries to open the specified file in read mode. If successful, it returns a pointer
 * to the opened file.
 */
errorCode_t GetUserFile(FILE **file)
{
    char filename[100];                  // Buffer to hold file name
    fflush(stdin);                       // Flush standard input
    printf("Enter file name to read: "); // Prompt user for file name
    scanf("%s", filename);               // Read file name

    *file = fopen(filename, "r");             // Open file
    if (!*file)                               // Check if file cannot be opened
        return ErrorHandler(ERROR_OPEN_FILE); // Handle error

    return SUCCESS; // Return success
}

///////////////////////////////////////////////////////////////////////
//                       MAIN PROGRAM ENTRY                          //
///////////////////////////////////////////////////////////////////////

int main(void)
{
    fontData_t *fontData = fontDataConstructor();

    // Start up the robot
    if (StartUpRobot() != SUCCESS)
        exit(EXIT_FAILURE);

    // Parse the font file
    if (fontData->parse(fontData, FONT_FILE) != SUCCESS)
        exit(EXIT_FAILURE);

    // Ask the user for the desired text height
    double scale;
    while (GetUserScale(&scale) != SUCCESS)
        ;

    // Scale the font data
    if (fontData->scale(fontData, scale) != SUCCESS)
        exit(EXIT_FAILURE);

    // Process the text file
    FILE *file = NULL;
    while (GetUserFile(&file) != SUCCESS)
        ;

    // Process the text file
    if (process_text_file(fontData, file) != SUCCESS)
        exit(EXIT_FAILURE);

    fclose(file);

    // Free the font data
    if (fontData->free(fontData) != SUCCESS)
        exit(EXIT_FAILURE);

    return 0;
}
