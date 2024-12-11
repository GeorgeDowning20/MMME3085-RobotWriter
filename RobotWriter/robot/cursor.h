/**
 * @file cursor.h
 * @brief Declaration of the cursor_t structure and associated functions.
 * @details
 * This file provides the interface for managing the cursor position,
 * including setting, moving, and performing carriage returns and newlines.
 * It also includes functionality to detect when writing a word would overflow
 * the predefined boundaries.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#pragma once
#include <stdbool.h>

#include "../misc/coord.h"
#include "../misc/error.h"

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DECLARATIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Structure representing the cursor position and related settings.
 */
typedef struct cursor_s
{
    Coord2D_t posisiton;    /**< Current position of the cursor. */
    Coord2D_t homePosition; /**< The 'home' position from where the cursor starts. */
    Coord2D_t maxPosition;  /**< The maximum allowed position (bound) for the cursor. */
    Coord2D_t minPosition;  /**< The minimum allowed position (bound) for the cursor. */
    bool init;              /**< Initialization state of the cursor (true if initialized). */
    double scale;           /**< Scaling factor applied to cursor movements. */
    double lineSpace;       /**< The spacing between successive lines when newline is invoked. */
    double characterSpace;  /**< The spacing between successive characters. */

    /**
     * @brief Set the cursor position.
     * @param[in,out] self Pointer to the cursor structure.
     * @param[in] position The new position to set the cursor to.
     * @return SUCCESS on success, or an appropriate error code on failure.
     */
    errorCode_t (*set)(struct cursor_s *const self, const Coord2D_t position);

    /**
     * @brief Move the cursor by a given delta.
     * @param[in,out] self Pointer to the cursor structure.
     * @param[in] delta The delta by which to move the cursor.
     * @return SUCCESS on success, or an appropriate error code on failure.
     */
    errorCode_t (*move)(struct cursor_s *const self, const Coord2D_t delta);

    /**
     * @brief Move the cursor to a new line position.
     * @param[in,out] self Pointer to the cursor structure.
     * @return SUCCESS on success, or an appropriate error code on failure.
     */
    errorCode_t (*newline)(struct cursor_s *const self);

    /**
     * @brief Move the cursor to the start of the current line (carriage return).
     * @param[in,out] self Pointer to the cursor structure.
     * @return SUCCESS on success, or an appropriate error code on failure.
     */
    errorCode_t (*carriagereturn)(struct cursor_s *const self);

    /**
     * @brief Update the cursor state, for example after scaling or boundary changes.
     * @param[in,out] self Pointer to the cursor structure.
     * @return SUCCESS on success, or an appropriate error code on failure.
     */
    errorCode_t (*update)(struct cursor_s *const self);

    /**
     * @brief Check if writing a given word would overflow the allowed cursor area.
     * @param[in] self Pointer to the cursor structure.
     * @param[in] word Pointer to the word to test for overflow.
     * @return true if writing the word would cause overflow, false otherwise.
     */
    bool (*testWordOverflow)(const struct cursor_s *const self, const char *const word);
} cursor_t;

/**
 * @brief Constructs and initializes a new cursor_t object.
 * @param[in] scale The scaling factor to apply to the cursor's movements.
 * @return A cursor_t structure initialized with the given scale and default positions.
 */
cursor_t cursorConstructor(double scale);
