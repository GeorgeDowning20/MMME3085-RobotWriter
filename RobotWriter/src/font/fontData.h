#pragma once

#include "../misc/error.h"
#include "fontChar.h"

#define ASCII_CHARACTERS 128

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DECLARATIONS                      //
///////////////////////////////////////////////////////////////////////

//opaqe type for hashtable
typedef struct hashNode_s hashNode_t;

/**
 * @brief Structure representing font data, including a hash table.
 * 
 */
typedef struct fontData_s
{
    double fontScale;                    /**< Scaling factor for the font. */
    hashNode_t *table[ASCII_CHARACTERS]; /**< Hash table for storing font characters. */
    errorCode_t (*free)(struct fontData_s *self);
    const fontCharacter_t *(*lookup)(const struct fontData_s *const self, const char ascii_key);
    errorCode_t (*scale)(struct fontData_s *const self, double scale);
    errorCode_t (*insert)(struct fontData_s *const self, fontCharacter_t *const character);
    errorCode_t (*parse)(struct fontData_s *const self, const char *filename);
} fontData_t;

fontData_t *fontDataConstructor(void);
