#pragma once
#include <stdbool.h>

#include "../misc/coord.h"
#include "../misc/error.h"

/**
 * @brief Structure representing the cursor position.
 */
typedef struct cursor_s
{
    Coord2D_t posisiton;
    Coord2D_t homePosition;
    Coord2D_t maxPosition;
    Coord2D_t minPosition;
    bool init;
    double scale;
    double lineSpace;
    double characterSpace;
    errorCode_t (*set)(struct cursor_s *const self, const Coord2D_t position);
    errorCode_t (*move)(struct cursor_s *const self, const Coord2D_t delta);
    errorCode_t (*newline)(struct cursor_s *const self);
    errorCode_t (*carriagereturn)(struct cursor_s *const self);
    errorCode_t (*update)(struct cursor_s *const self);
    bool (*testWordOverflow)(const struct cursor_s *const self, const char *const word);
} cursor_t;

cursor_t cursorConstructor(double scale);
