#include "gcode.h"

/**
 * @brief Generate G-code for a given text string.
 */
errorCode_t generate_gcode(const fontData_t *const fontData, const char *text)
{
    static cursor_t cursor;
    if (!cursor.init)
        cursor = cursorConstructor(fontData->fontScale);

    if (cursor.testWordOverflow(&cursor, text))
        cursor.newline(&cursor);

    while (*text != '\0')
    {
        switch (*text)
        {
        case ' ':
            if (cursor.update(&cursor) != SUCCESS)
                return CURSOR_OUT_OF_BOUNDS;
            break;
        case '\n':
            if (cursor.newline(&cursor) != SUCCESS)
                return CURSOR_OUT_OF_BOUNDS;
            break;
        case '\r':
            if (cursor.carriagereturn(&cursor) != SUCCESS)
                return CURSOR_OUT_OF_BOUNDS;
            break;
        default:
        {
            const fontCharacter_t *const fontChar = fontData->lookup(fontData, *text);
            if (!fontChar)
            {
                ErrorHandler(FONT_CHARACTER_NOT_FOUND);
                break;
            }

            for (uint8_t i = 0; i < fontChar->numStrokes; i++)
                SendStoke(&cursor, fontChar->strokes[i]);

            if (cursor.update(&cursor) != SUCCESS)
                return CURSOR_OUT_OF_BOUNDS;
            break;
        }
        }
        text++;
    }
    return SUCCESS;
}

/**
 * @brief Process a text file word by word and generate G-code.
 */
errorCode_t process_text_file(const fontData_t *const fontData, FILE *const file)
{

    if (!fontData)
        return ErrorHandler(ERROR_NO_FONT_DATA);

    if (!file)
        return ErrorHandler(ERROR_NO_TEXT_FILE);

    char buff[256]; // Buffer to hold each word
    int ch;
    int index = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        buff[index++] = ch;

        if (ch == ' ' || ch == '\n' || ch == '\r')
        {
            buff[index] = '\0';
            errorCode_t error = generate_gcode(fontData, buff);
            if (error != SUCCESS)
                return ErrorHandler(error);
            index = 0;
        }
    }

    if (index > 0)
    {
        buff[index] = '\0';
        errorCode_t error = generate_gcode(fontData, buff);
        if (error != SUCCESS)
            return ErrorHandler(error);
    }

    fclose(file);
    HomeRobot();

    return SUCCESS;
}
