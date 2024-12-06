#include "fontChar.h"

static errorCode_t _appendStroke(fontCharacter_t *const self, const stroke_t stroke);

static errorCode_t _free(fontCharacter_t *self);

fontCharacter_t *fontCharConstuctor(const char asciiKey, const uint8_t numStrokes)
{
    // Allocate memory for fontCharacter_t
    fontCharacter_t *font_char = malloc(sizeof(fontCharacter_t));
    if (!font_char)
    {
        ErrorHandler(ERROR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }

    // Initialize fontCharacter_t fields
    font_char->asciiKey = asciiKey;
    font_char->numStrokes = numStrokes;
    font_char->strokeIdx = 1;
    font_char->strokes = malloc(numStrokes * sizeof(stroke_t));
    if (!font_char->strokes)
    {
        free(font_char); // Avoid memory leak
        ErrorHandler(ERROR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }

    // Set function pointers
    font_char->appendStroke = _appendStroke;
    font_char->free = _free;

    return font_char;
}

static errorCode_t _appendStroke(fontCharacter_t *const self, const stroke_t stroke)
{
    if (!self)
        return ErrorHandler(ERROR_NULL_POINTER);

    if (self->strokeIdx > self->numStrokes)
        return ErrorHandler(ERROR_OUT_OF_BOUNDS);

    self->strokes[self->strokeIdx++] = stroke;

    return SUCCESS;
}

static errorCode_t _free(fontCharacter_t *self)
{
    if (!self)
        return ErrorHandler(ERROR_NULL_POINTER);

    free(self->strokes);
    free(self);

    return SUCCESS;
}
