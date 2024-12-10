/**
 * @file fontChar.h
 * @brief Declarations and definitions related to the fontCharacter_t structure and its operations.
 * @details
 * This header file provides the declarations for the fontCharacter_t structure and its associated
 * functions. The fontCharacter_t represents a font character defined by a sequence of strokes.
 * Each stroke indicates a movement of the pen (with pen up or pen down states) to draw the character.
 * The file also declares the fontCharConstructor function which creates and initializes a
 * fontCharacter_t instance.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */
#pragma once

#include "../robot/cursor.h"
#include "../misc/coord.h"
#include <stdlib.h>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DECLARATIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @brief A 2D vector type defined as Coord2D_t.
 */
typedef Coord2D_t Vect2d_t;

/**
 * @brief Structure representing a single stroke of a character.
 * @details A stroke consists of a vector (defining direction and length) and a pen state.
 * The pen state indicates whether the pen is down (drawing) or up (not drawing) as it moves
 * along the specified vector.
 */
typedef struct stroke_s
{
    Vect2d_t vec;   /**< 2D vector representing the direction and length of the stroke. */
    bool pen_state; /**< Pen state: true = pen down (drawing), false = pen up (moving without drawing). */
} stroke_t;

/**
 * @brief Structure representing a font character.
 * @details This structure stores all the strokes that form a single character. It keeps track of:
 * - The ASCII character it represents.
 * - The total number of strokes.
 * - The current stroke index (to which new strokes can be appended).
 * - A dynamically allocated array of strokes.
 *
 * It also provides function pointers to:
 * - Append a new stroke to the character.
 * - Free all associated resources when the character is no longer needed.
 */
typedef struct fontCharacter_s
{
    char asciiKey;      /**< ASCII character this font character represents. */
    uint8_t numStrokes; /**< Total number of strokes that define the character. */
    uint8_t strokeIdx;  /**< Current stroke index, indicating how many strokes have been appended. */
    stroke_t *strokes;  /**< Dynamically allocated array of strokes defining the character. */

    /**
     * @brief Function pointer to append a stroke to the font character.
     * @param[in,out] self   Pointer to the fontCharacter_t structure.
     * @param[in]     stroke The stroke to be appended.
     * @return SUCCESS on success, or an appropriate error code.
     */
    errorCode_t (*appendStroke)(struct fontCharacter_s *const self, const stroke_t stroke);

    /**
     * @brief Function pointer to free the font character and its resources.
     * @param[in,out] self Pointer to the fontCharacter_t structure.
     * @return SUCCESS on success, or ERROR_NULL_POINTER if `self` is NULL.
     */
    errorCode_t (*free)(struct fontCharacter_s *self);
} fontCharacter_t;

/**
 * @brief Constructs and initializes a new fontCharacter_t object.
 * @param[in] asciiKey    The ASCII character key that this font character represents.
 * @param[in] numStrokes  The number of strokes that will be associated with this font character.
 * @return A pointer to the newly created fontCharacter_t object, or NULL if allocation fails.
 */
fontCharacter_t *fontCharConstuctor(const char asciiKey, const uint8_t numStrokes);
