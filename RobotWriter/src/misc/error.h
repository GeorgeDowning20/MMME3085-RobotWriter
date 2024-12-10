/**
 * @file error.h
 * @brief Defines error codes and a function to handle and log these errors.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#pragma once

#include <stdio.h>

#define PRINT_ERROR_CODES /**< Enable printing of error codes for debugging. */

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DECLARATIONS                      //
///////////////////////////////////////////////////////////////////////


/**
 * @enum errorCode_e
 * @brief Defines various error codes returned by functions within the application.
 *
 * These error codes indicate the type of failure encountered during operation.
 * Functions returning these error codes should document the conditions under which
 * each error can occur.
 *
 * @var errorCode_e::SUCCESS
 * Indicates that the operation completed successfully.
 *
 * @var errorCode_e::ERROR_OPEN_FILE
 * Indicates that opening a text file failed.
 *
 * @var errorCode_e::ERROR_INVALID_SCALE_INPUT
 * Indicates that the provided scale input was invalid.
 *
 * @var errorCode_e::ERROR_NO_TEXT_FILE
 * Indicates that no text file was found.
 *
 * @var errorCode_e::ERROR_NO_FONT_DATA
 * Indicates that no font data was available.
 *
 * @var errorCode_e::CURSOR_OUT_OF_BOUNDS
 * Indicates that the cursor position is outside the allowed bounds.
 *
 * @var errorCode_e::FONT_CHARACTER_NOT_FOUND
 * Indicates that a required font character was not found in the font data.
 *
 * @var errorCode_e::ERROR_MEMORY_ALLOCATION_FAILED
 * Indicates a failure in memory allocation.
 *
 * @var errorCode_e::ERROR_NULL_POINTER
 * Indicates that a null pointer was encountered where a valid pointer was expected.
 *
 * @var errorCode_e::ERROR_UNABLE_TO_OPEN_COM_PORT
 * Indicates that the COM port could not be opened.
 *
 * @var errorCode_e::ERROR_OUT_OF_BOUNDS
 * Indicates a generic out-of-bounds condition occurred.
 *
 * @var errorCode_e::WORD_TOO_LONG
 * Indicates that the provided word exceeds the maximum allowed length.
 *
 * @var errorCode_e::ERROR_INVALID_INPUT
 * Indicates that an invalid input was provided to a function.
 *
 * @var errorCode_e::ERROR_INVALID_FILE
 * Indicates that the file being processed is invalid.
 *
 * @var errorCode_e::ERROR_INVALID_FONT_FILE
 * Indicates that the font file is invalid.
 *
 * @var errorCode_e::ERROR_INVALID_FONT_CHARACTER
 * Indicates that the font file contains an invalid character definition.
 *
 * @var errorCode_e::ERROR_INVALID_FONT_STROKE
 * Indicates that a font stroke definition in the font file is invalid.
 *
 * @var errorCode_e::ERROR_INVALID_FONT_STROKE_VEC
 * Indicates that a font stroke vector definition is invalid.
 *
 * @var errorCode_e::ERROR_INSERT_CHARACTER
 * Indicates that inserting a character into the data structure failed.
 *
 * @var errorCode_e::ERROR_APPEND_STROKE
 * Indicates that appending a stroke to a character failed.
 *
 * @var errorCode_e::ERROR_PARSE_STROKE
 * Indicates that parsing a stroke definition failed.
 *
 * @var errorCode_e::ERROR_UNEXPECTED_EOF
 * Indicates that an unexpected end-of-file was encountered.
 *
 * @var errorCode_e::ERROR_PARSE_CHARACTER
 * Indicates that parsing a character definition failed.
 */
typedef enum errorCode_e
{
    SUCCESS = 0,                    /**< Operation completed successfully. */
    ERROR_OPEN_FILE,                /**< Error opening text file. */
    ERROR_INVALID_SCALE_INPUT,      /**< Invalid scale input (out of allowed range). */
    ERROR_NO_TEXT_FILE,             /**< No text file found. */
    ERROR_NO_FONT_DATA,             /**< No font data available. */
    CURSOR_OUT_OF_BOUNDS,           /**< Cursor position is outside the valid range. */
    FONT_CHARACTER_NOT_FOUND,       /**< Required font character not found in data. */
    ERROR_MEMORY_ALLOCATION_FAILED, /**< Memory allocation failure. */
    ERROR_NULL_POINTER,             /**< Null pointer encountered. */
    ERROR_UNABLE_TO_OPEN_COM_PORT,  /**< Unable to open the COM port. */
    ERROR_OUT_OF_BOUNDS,            /**< Out-of-bounds error (generic). */
    WORD_TOO_LONG,                  /**< Provided word is too long. */
    ERROR_INVALID_INPUT,            /**< Invalid input provided. */
    ERROR_INVALID_FILE,             /**< Invalid file. */
    ERROR_INVALID_FONT_FILE,        /**< Invalid font file. */
    ERROR_INVALID_FONT_CHARACTER,   /**< Invalid font character definition. */
    ERROR_INVALID_FONT_STROKE,      /**< Invalid font stroke definition. */
    ERROR_INVALID_FONT_STROKE_VEC,  /**< Invalid font stroke vector. */
    ERROR_INSERT_CHARACTER,         /**< Error inserting character into data structure. */
    ERROR_APPEND_STROKE,            /**< Error appending stroke to character. */
    ERROR_PARSE_STROKE,             /**< Error parsing stroke definition. */
    ERROR_UNEXPECTED_EOF,           /**< Unexpected end-of-file encountered. */
    ERROR_PARSE_CHARACTER           /**< Error parsing character definition. */
} errorCode_t;

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Handles and logs the given error code.
 *
 * This function prints an error message to stderr corresponding to the provided
 * error code if `PRINT_ERROR_CODES` is defined. This helps in debugging by
 * providing information about why a particular operation failed.
 *
 * @param[in] error The error code to handle.
 * @return The same error code passed in.
 */
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
        /* No action for SUCCESS or unspecified errors. */
        break;
    }
#endif

    return error;
}
