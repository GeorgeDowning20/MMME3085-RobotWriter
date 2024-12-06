
#include "main.h"

errorCode_t GetUserScale(double *scale)
{
    double height;
    fflush(stdin);
    printf("Enter the desired text height (4-10 mm): ");

    if (scanf("%lf", &height) != 1 || height < MINIMUM_TEXT_HEIGHT_MM || height > MAXIMUM_TEXT_HEIGHT_MM)
        return ErrorHandler(ERROR_INVALID_SCALE_INPUT);

    *scale = height / CHARACTER_SPACE_MM;
    return SUCCESS;
}

errorCode_t GetUserFile(FILE **file)
{
    char filename[100];
    fflush(stdin);
    printf("Enter file name to read: ");

    scanf("%s", filename);

    *file = fopen(filename, "r");
    if (!*file)
        return ErrorHandler(ERROR_OPEN_FILE);

    return SUCCESS;
}

int main(void)
{
    fontData_t *fontData = fontDataConstructor();

    if (StartUpRobot() != SUCCESS)
        exit(EXIT_FAILURE);

    // Parse the font file
    if (fontData->parse(fontData, FONT_FILE) != SUCCESS)
        exit(EXIT_FAILURE);

    // Ask the user for the desired text height
    double scale;
    while (GetUserScale(&scale)!= SUCCESS);

    // Scale the font data
    if(fontData->scale(fontData, scale)!=SUCCESS)
        exit(EXIT_FAILURE);

    // Process the text file
    FILE *file = NULL;
    while (GetUserFile(&file)!= SUCCESS);

    // Process the text file
    if (process_text_file(fontData, file) != SUCCESS)
        exit(EXIT_FAILURE);

    fclose(file); 

    // Free the font data
    if(fontData->free(fontData)!=SUCCESS)
        exit(EXIT_FAILURE);

    return 0;
}
