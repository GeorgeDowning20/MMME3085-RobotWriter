/**
 * @file cursor.c
 * @brief Implementation of the cursor_t structure and related operations.
 * @details This file manages the cursor position and movement within predefined boundaries,
 *       providing functions to set, move, return to a new line, handle carriage returns,
 *       update positioning, and check for word overflow conditions.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#include "cursor.h"
#include "robot.h"

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DECLARATIONS                     //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the given word would overflow the current cursor boundaries.
 * @param[in] self Pointer to the cursor structure.
 * @param[in] word The word to test for overflow.
 * @return true if writing the word would cause overflow, false otherwise.
 */
static inline bool _testWordOverflow(const cursor_t *const self, const char *const word);

/**
 * @brief Checks if the current cursor position is within defined boundaries.
 * @param[in] self Pointer to the cursor structure.
 * @return true if the cursor is within bounds, false otherwise.
 */
static inline bool _iswithinBounds(const cursor_t *const self);

/**
 * @brief Sets the cursor to a specified position.
 * @param[in,out] self Pointer to the cursor structure.
 * @param[in] position The new position to set the cursor to.
 * @return SUCCESS on success, or CURSOR_OUT_OF_BOUNDS if the position is invalid.
 */
static errorCode_t _set(cursor_t *const self, const Coord2D_t position);

/**
 * @brief Moves the cursor by a specified delta.
 * @param[in,out] self Pointer to the cursor structure.
 * @param[in] delta The delta by which to move the cursor.
 * @return SUCCESS on success, or CURSOR_OUT_OF_BOUNDS if the new position is invalid.
 */
static errorCode_t _move(cursor_t *const self, const Coord2D_t delta);

/**
 * @brief Moves the cursor to a new line.
 * @param[in,out] self Pointer to the cursor structure.
 * @return SUCCESS on success, or CURSOR_OUT_OF_BOUNDS if the new position is invalid.
 */
static errorCode_t _newline(cursor_t *const self);

/**
 * @brief Updates the cursor position after advancing by one character.
 * @param[in,out] self Pointer to the cursor structure.
 * @return SUCCESS on success, or CURSOR_OUT_OF_BOUNDS if the new position is invalid.
 */
static errorCode_t _update(cursor_t *const self);

/**
 * @brief Moves the cursor to the start of the current line (carriage return).
 * @param[in,out] self Pointer to the cursor structure.
 * @return SUCCESS on success, or CURSOR_OUT_OF_BOUNDS if the new position is invalid.
 */
static errorCode_t _carriagereturn(cursor_t *const self);

/**
 * @brief Constructs and initializes a new cursor_t object.
 * @param[in] scale The scaling factor to apply to the cursor's movements.
 * @return A cursor_t structure initialized with the given scale and default positions.
 */

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

/**
 * @details
 * This function initializes the cursor with a given scale factor, setting the initial position,
 * home position, minimum and maximum boundaries, as well as line and character spacing.
 * It also assigns function pointers to handle various cursor operations.
 */
cursor_t cursorConstructor(double scale)
{
    cursor_t cursor;                                                             // Declare cursor structure
    cursor.scale = scale;                                                        // Set scale to given scale
    cursor.posisiton.x = MIN_X_VALUE_MM;                                         // Set x position to minimum x value
    cursor.posisiton.y = MAX_Y_VALUE_MM - (CHARACTER_SPACE_MM * cursor.scale);   // Set y position to maximum y value
    cursor.homePosition.x = HOME_X_VALUE_MM;                                     // Set home position
    cursor.homePosition.y = HOME_Y_VALUE_MM;                                     // Set home position
    cursor.maxPosition.x = MAX_X_VALUE_MM - (CHARACTER_SPACE_MM * cursor.scale); // Set maximum x position
    cursor.maxPosition.y = MAX_Y_VALUE_MM - (CHARACTER_SPACE_MM * cursor.scale); // Set maximum y position
    cursor.minPosition.x = MIN_X_VALUE_MM;                                       // Set minimum x position
    cursor.minPosition.y = MIN_Y_VALUE_MM;                                       // Set minimum y position
    cursor.lineSpace = (CHARACTER_SPACE_MM * cursor.scale) + LINE_SPACE_MM;      // Set line space
    cursor.characterSpace = CHARACTER_SPACE_MM * cursor.scale;                   // Set character space
    cursor.init = true;                                                          // Set initialization state to true

    cursor.set = _set;                           // Set set function pointer
    cursor.move = _move;                         // Set move function pointer
    cursor.newline = _newline;                   // Set newline function pointer
    cursor.carriagereturn = _carriagereturn;     // Set carriage return function pointer
    cursor.update = _update;                     // Set update function pointer
    cursor.testWordOverflow = _testWordOverflow; // Set test word overflow function pointer
    return cursor;                               // Return cursor structure
}

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DEFINITIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @details
 * This function checks the length of the given word, calculates how much horizontal
 * space it would require (based on character spacing and cursor scale), and determines
 * if adding this word would exceed the maximum allowed X position.
 */
static inline bool _testWordOverflow(const cursor_t *const self, const char *const word)
{
    const int length = strlen(word) - 1;                                             // Get length of word
    if ((self->posisiton.x + ((length)*self->characterSpace)) > self->maxPosition.x) // Check if word would overflow
        return true;                                                                 // Return true if overflow
    return false;                                                                    // Return false if no overflow
}

/**
 * @details
 * Compares the current cursor position against the min and max boundaries.
 * If any coordinate is outside the defined limits, the cursor is considered out of bounds.
 */
static inline bool _iswithinBounds(const cursor_t *const self)
{
    if (self->posisiton.x > self->maxPosition.x || // Check if x is out of bounds
        self->posisiton.x < self->minPosition.x || // Check if x is out of bounds
        self->posisiton.y > self->maxPosition.y || // Check if y is out of bounds
        self->posisiton.y < self->minPosition.y)   // Check if y is out of bounds
        return false;                              // Return false if out of bounds

    return true; // Return true if within bounds
}

/**
 * @details
 * Assigns the given position to the cursor and then validates that the
 * cursor remains within boundaries. If not, an error is returned.
 */
static errorCode_t _set(cursor_t *const self, const Coord2D_t position)
{
    self->posisiton = position; // Set position to given position

    if (!_iswithinBounds(self))                    // Check if cursor is out of bounds
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS); // Handle error

    return SUCCESS; // Return success
}

/**
 * @details
 * Updates the cursor position by adding the given delta. If this position is out of
 * bounds, the function attempts to switch to a new line. If the position is still
 * invalid, it returns an error.
 */
static errorCode_t _move(cursor_t *const self, const Coord2D_t delta)
{
    self->posisiton = AddCoord2D(self->posisiton, delta); // Move cursor by delta

    if (!_iswithinBounds(self)) // Check if cursor is out of bounds
        self->newline(self);    // attempt to Move to new line

    if (!_iswithinBounds(self))                    // Check if cursor is out of bounds
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS); // Handle error

    return SUCCESS; // Return success
}

/**
 * @details
 * Moves the cursor down one line. This involves setting the x-position to the minimum
 * x-bound and decreasing the y-position by the line spacing. If the new position is invalid,
 * it returns an error.
 */
static errorCode_t _newline(cursor_t *const self)
{
    const Coord2D_t pos = {self->minPosition.x, self->posisiton.y - self->lineSpace}; // Set new position
    self->set(self, pos);                                                             // Set cursor to new position

    if (!_iswithinBounds(self))                    // Check if cursor is out of bounds
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS); // Handle error
    return SUCCESS;                                // Return success
}

/**
 * @details
 * Resets the x-position of the cursor to the minimum x-bound, emulating a carriage return.
 * If the updated position is out of bounds, it returns an error.
 */
static errorCode_t _carriagereturn(cursor_t *const self)
{
    const Coord2D_t pos = {self->minPosition.x, self->posisiton.y}; // Set new position
    self->set(self, pos);                                           // Set cursor to new position

    if (!_iswithinBounds(self))                    // Check if cursor is out of bounds
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS); // Handle error
    return SUCCESS;                                // Return success
}

/**
 * @details
 * Moves the cursor one character space to the right. If this results in an out-of-bounds
 * position, it attempts to move the cursor to a new line. If still out of bounds, it returns an error.
 */
static errorCode_t _update(cursor_t *const self)
{
    const Coord2D_t delta = {self->characterSpace, 0.0}; // Set delta to character space
    self->move(self, delta);                             // Move cursor by delta

    if (!_iswithinBounds(self)) // Check if cursor is out of bounds
        self->newline(self);    // attempt to Move to new line

    if (!_iswithinBounds(self))                    // Check if cursor is out of bounds
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS); // Handle error

    return SUCCESS; // Return success
}
