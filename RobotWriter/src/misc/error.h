#pragma once

#include <stdio.h>
#define PRINT_ERROR_CODES

typedef enum errorCode_e
{
    SUCCESS = 0,
    ERROR_OPEN_FILE,
    ERROR_INVALID_SCALE_INPUT,
    ERROR_NO_TEXT_FILE,
    ERROR_NO_FONT_DATA,
    CURSOR_OUT_OF_BOUNDS,
    FONT_CHARACTER_NOT_FOUND,
    ERROR_MEMORY_ALLOCATION_FAILED,
    ERROR_NULL_POINTER,
    ERROR_UNABLE_TO_OPEN_COM_PORT,
    ERROR_OUT_OF_BOUNDS,
    WORD_TOO_LONG,
    ERROR_INVALID_INPUT,
    ERROR_INVALID_FILE,
    ERROR_INVALID_FONT_FILE,
    ERROR_INVALID_FONT_CHARACTER,
    ERROR_INVALID_FONT_STROKE,
    ERROR_INVALID_FONT_STROKE_VEC,
    ERROR_INSERT_CHARACTER,
    ERROR_APPEND_STROKE,
    ERROR_PARSE_STROKE,
    ERROR_UNEXPECTED_EOF,
    ERROR_PARSE_CHARACTER,
} errorCode_t;

static inline errorCode_t ErrorHandler(const errorCode_t error)
{
#ifdef PRINT_ERROR_CODES
    switch (error)
    {
    case ERROR_OPEN_FILE:
        perror("Error opening text file\n");
        break;
    case ERROR_INVALID_SCALE_INPUT:
        perror("Invalid input. Height must be between 4 and 10 mm.\n");
        break;
    case ERROR_NO_TEXT_FILE:
        perror("Error no text file\n");
        break;
    case ERROR_NO_FONT_DATA:
        perror("Error no font data\n");
        break;
    case CURSOR_OUT_OF_BOUNDS:
        perror("Cursor out of bounds\n");
        break;
    case FONT_CHARACTER_NOT_FOUND:
        perror("Font character not found in data\n");
        break;
    case ERROR_MEMORY_ALLOCATION_FAILED:
        perror("Memory allocation failed\n");
        break;
    case ERROR_NULL_POINTER:
        perror("Null pointer\n");
        break;
    case ERROR_UNABLE_TO_OPEN_COM_PORT:
        perror("Unable to open COM port\n");
        break;
    case ERROR_OUT_OF_BOUNDS:
        perror("Out of bounds\n");
        break;
    case WORD_TOO_LONG:
        perror("Word too long\n");
        break;
    case ERROR_INVALID_INPUT:
        perror("Invalid input\n");
        break;
    case ERROR_INVALID_FILE:
        perror("Invalid file\n");
        break;
    case ERROR_INVALID_FONT_FILE:
        perror("Invalid font file\n");
        break;
    case ERROR_INVALID_FONT_CHARACTER:
        perror("Invalid font character\n");
        break;
    case ERROR_INVALID_FONT_STROKE:
        perror("Invalid font stroke\n");
        break;
    case ERROR_INVALID_FONT_STROKE_VEC:
        perror("Invalid font stroke vector\n");
        break;
    case ERROR_INSERT_CHARACTER:
        perror("Error inserting character\n");
        break;
    case ERROR_APPEND_STROKE:
        perror("Error appending stroke\n");
        break;
    case ERROR_PARSE_STROKE:
        perror("Error parsing stroke\n");
        break;
    case ERROR_UNEXPECTED_EOF:
        perror("Unexpected end of file\n");
        break;
    case ERROR_PARSE_CHARACTER:
        perror("Error parsing character\n");
        break;
    default:
        break;
    }
#endif

    return error;
}
