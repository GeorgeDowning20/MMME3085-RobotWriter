#include "cursor.h"
#include "robot.h"

static inline bool _iswithinBounds(const cursor_t *const self);
static errorCode_t _set(cursor_t *const self, const Coord2D_t position);
static errorCode_t _move(cursor_t *const self, const Coord2D_t delta);
static errorCode_t _newline(cursor_t *const self);
static errorCode_t _update(cursor_t *const self);
static errorCode_t _carriagereturn(cursor_t *const self);
static inline bool _testWordOverflow(const cursor_t *const self, const char *word);

cursor_t cursorConstructor(double scale)
{
    cursor_t cursor;
    cursor.scale = scale;
    cursor.posisiton.x = MIN_X_VALUE_MM;
    cursor.posisiton.y = MAX_Y_VALUE_MM - (CHARACTER_SPACE_MM * cursor.scale);
    cursor.homePosition.x = HOME_X_VALUE_MM;
    cursor.homePosition.y = HOME_Y_VALUE_MM;
    cursor.maxPosition.x = MAX_X_VALUE_MM - (CHARACTER_SPACE_MM * cursor.scale);
    cursor.maxPosition.y = MAX_Y_VALUE_MM - (CHARACTER_SPACE_MM * cursor.scale);
    cursor.minPosition.x = MIN_X_VALUE_MM;
    cursor.minPosition.y = MIN_Y_VALUE_MM;
    cursor.lineSpace = (CHARACTER_SPACE_MM * cursor.scale) + LINE_SPACE_MM;
    cursor.characterSpace = CHARACTER_SPACE_MM * cursor.scale;
    cursor.init = true;
    cursor.set = _set;
    cursor.move = _move;
    cursor.newline = _newline;
    cursor.carriagereturn = _carriagereturn;
    cursor.update = _update;
    cursor.testWordOverflow = _testWordOverflow;
    return cursor;
}

static inline bool _testWordOverflow(const cursor_t *const self, const char *const word)
{
    const int length = strlen(word) - 1;
    if ((self->posisiton.x + ((length)*self->characterSpace)) > self->maxPosition.x)
        return true;
    return false;
}

static inline bool _iswithinBounds(const cursor_t *const self)
{
    if (self->posisiton.x > self->maxPosition.x ||
        self->posisiton.x < self->minPosition.x ||
        self->posisiton.y > self->maxPosition.y ||
        self->posisiton.y < self->minPosition.y)
        return false;

    return true;
}

static errorCode_t _set(cursor_t *const self, const Coord2D_t position)
{
    self->posisiton = position;

    if (!_iswithinBounds(self))
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS);

    return SUCCESS;
}

static errorCode_t _move(cursor_t *const self, const Coord2D_t delta)
{
    self->posisiton = AddCoord2D(self->posisiton, delta);

    if (!_iswithinBounds(self))
        self->newline(self);

    if (!_iswithinBounds(self))
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS);

    return SUCCESS;
}

static errorCode_t _newline(cursor_t *const self)
{
    const Coord2D_t pos = {self->minPosition.x, self->posisiton.y - self->lineSpace};
    self->set(self, pos);

    if (!_iswithinBounds(self))
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS);
    return SUCCESS;
}

static errorCode_t _carriagereturn(cursor_t *const self)
{
    const Coord2D_t pos = {self->minPosition.x, self->posisiton.y};
    self->set(self, pos);

    if (!_iswithinBounds(self))
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS);
    return SUCCESS;
}

static errorCode_t _update(cursor_t *const self)
{
    const Coord2D_t delta = {self->characterSpace, 0.0};
    self->move(self, delta);

    if (!_iswithinBounds(self))
        self->newline(self);

    if (!_iswithinBounds(self))
        return ErrorHandler(CURSOR_OUT_OF_BOUNDS);

    return SUCCESS;
}
