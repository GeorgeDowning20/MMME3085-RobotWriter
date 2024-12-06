#pragma once

#include "../robot/cursor.h"
#include "../misc/coord.h"
#include <stdlib.h>
#include <stdint.h>

typedef Coord2D_t Vect2d_t;

/**
 * @brief Structure representing a single stroke of a character.
 */
typedef struct stroke_s
{
    Vect2d_t vec;
    bool pen_state; /**< State of the pen (true = down, false = up). */
} stroke_t;

/**
 * @brief Structure representing a font character.
 */
typedef struct fontCharacter_s
{
    char asciiKey;      /**< ASCII key for the character. */
    uint8_t numStrokes; /**< Number of strokes in the character. */
    uint8_t strokeIdx; /**< Index of the current stroke. */
    stroke_t *strokes;  /**< Array of strokes that define the character. */
    errorCode_t (*appendStroke)(struct fontCharacter_s *const self, const stroke_t stroke);
    errorCode_t (*free)(struct fontCharacter_s *self);
} fontCharacter_t;

fontCharacter_t *fontCharConstuctor(const char asciiKey, const uint8_t numStrokes);
