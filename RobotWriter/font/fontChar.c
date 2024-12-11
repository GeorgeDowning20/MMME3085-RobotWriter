/**
 * @file fontChar.c
 * @brief Implementation of fontCharacter_t construction, stroke appending, and memory management.
 * @details
 * This file provides the functionallity to store and manage font characters as a series of strokes. It inludes
 * functions to append and free character strokes as well as a constructor to create a new font character.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#include "fontChar.h"

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DECLARATIONS                     //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Appends a single stroke to a fontCharacter_t object.
 * @param[in,out] self   Pointer to the fontCharacter_t structure to modify.
 * @param[in]     stroke The stroke to append.
 * @return SUCCESS on success, or an appropriate error code:
 *         - ERROR_NULL_POINTER if `self` is NULL.
 *         - ERROR_OUT_OF_BOUNDS if no more strokes can be appended.
 */
static errorCode_t _appendStroke(fontCharacter_t *const self, const stroke_t stroke);

/**
 * @brief Frees the memory allocated for a fontCharacter_t object.
 * @param[in,out] self Pointer to the fontCharacter_t to free.
 * @return SUCCESS on success, or ERROR_NULL_POINTER if `self` is NULL.
 */
static errorCode_t _free(fontCharacter_t *self);


///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

/**
 * @details
 * This function allocates memory for a fontCharacter_t structure, initializes its
 * fields, and allocates memory for the specified number of strokes. If memory
 * allocation fails, an error is reported, and NULL is returned. The caller must
 * eventually call the `free` function pointer within the structure to properly
 * deallocate the memory.
 */
fontCharacter_t *fontCharConstuctor(const char asciiKey, const uint8_t numStrokes)
{
    // Allocate memory for fontCharacter_t
    fontCharacter_t *font_char = malloc(sizeof(fontCharacter_t)); // Allocate memory for fontCharacter_t
    if (!font_char)                                               // Check if memory allocation failed
    {
        ErrorHandler(ERROR_MEMORY_ALLOCATION_FAILED); // Handle error
        return NULL;                                  // Return NULL
    }

    // Initialize fontCharacter_t fields
    font_char->asciiKey = asciiKey;                             // Set ASCII key
    font_char->numStrokes = numStrokes;                         // Set number of strokes
    font_char->strokeIdx = 1;                                   // Set stroke index to 1
    font_char->strokes = malloc(numStrokes * sizeof(stroke_t)); // Allocate memory for strokes
    if (!font_char->strokes)                                    // Check if memory allocation failed
    {
        free(font_char);                              // Avoid memory leak
        ErrorHandler(ERROR_MEMORY_ALLOCATION_FAILED); // Handle error
        return NULL;                                  // Return NULL
    }

    // Set function pointers
    font_char->appendStroke = _appendStroke; // Function pointer to append stroke
    font_char->free = _free;                 // Function pointer to free font character

    return font_char; // Return fontCharacter_t
}

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DEFINITIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @details
 * Checks the validity of the fontCharacter_t instance and ensures that there
 * is space left to append the provided stroke. If successful, the stroke is
 * appended and the stroke index is incremented.
 */
static errorCode_t _appendStroke(fontCharacter_t *const self, const stroke_t stroke)
{
    if (!self)                                   // Check if self is NULL
        return ErrorHandler(ERROR_NULL_POINTER); // Handle error

    if (self->strokeIdx > self->numStrokes)       // Check if stroke index is out of bounds
        return ErrorHandler(ERROR_OUT_OF_BOUNDS); // Handle error

    self->strokes[self->strokeIdx++] = stroke; // Append stroke and increment stroke index

    return SUCCESS; // Return success
}

/**
 * @details
 * Deallocates the memory allocated for the strokes and the fontCharacter_t
 * instance itself. After calling this function, the pointer to fontCharacter_t
 * should no longer be used.
 */
static errorCode_t _free(fontCharacter_t *self)
{
    if (!self)                                   // Check if self is NULL
        return ErrorHandler(ERROR_NULL_POINTER); // Handle error

    free(self->strokes); // Free strokes
    free(self);          // Free fontCharacter_t

    return SUCCESS; // Return success
}
