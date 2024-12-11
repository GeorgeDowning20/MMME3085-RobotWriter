/**
 * @file fontData.h
 * @brief Declarations for managing font data, including a hash table for storing font characters.
 * @details
 * This header defines the fontData_t structure and related components for storing and managing
 * font characters in a hash table. Each entry in the hash table corresponds to an ASCII character
 * and its associated fontCharacter_t object. The fontData_t structure provides function pointers
 * for operations such as inserting, looking up, scaling, parsing from a file, and freeing the entire
 * font data structure.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#pragma once

#include "../misc/error.h"
#include "fontChar.h"

#define ASCII_CHARACTERS 128

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DECLARATIONS                      //
///////////////////////////////////////////////////////////////////////


/**
 * @brief Opaque structure representing a hash node for storing font characters.
 */
typedef struct hashNode_s hashNode_t;

/**
 * @brief Structure representing font data, including a hash table.
 * @details
 * The fontData_t structure stores:
 * - A hash table of font characters indexed by ASCII code.
 * - A font scaling factor used to scale all character strokes.
 * - Function pointers for managing the font data, including insertion, lookup, scaling, parsing,
 *   and freeing resources.
 */
typedef struct fontData_s
{
    double fontScale;                    /**< Scaling factor for the font. */
    hashNode_t *table[ASCII_CHARACTERS]; /**< Hash table for storing font characters, indexed by ASCII value. */

    /**
     * @brief Frees all memory associated with the font data, including the hash table and its characters.
     * @param[in,out] self Pointer to the fontData_t instance.
     * @return SUCCESS on success, or ERROR_NULL_POINTER if `self` is NULL.
     */
    errorCode_t (*free)(struct fontData_s *self);

    /**
     * @brief Looks up a font character in the hash table by ASCII key.
     * @param[in] self Pointer to the fontData_t instance.
     * @param[in] ascii_key The ASCII key of the character to look up.
     * @return Pointer to the corresponding fontCharacter_t, or NULL if not found.
     */
    const fontCharacter_t *(*lookup)(const struct fontData_s *const self, const char ascii_key);

    /**
     * @brief Scales all the font characters by the given factor.
     * @param[in,out] self Pointer to the fontData_t instance.
     * @param[in] scale The factor by which to scale the font.
     * @return SUCCESS on success, or ERROR_NULL_POINTER if `self` is NULL.
     */
    errorCode_t (*scale)(struct fontData_s *const self, double scale);

    /**
     * @brief Inserts a font character into the hash table.
     * @param[in,out] self Pointer to the fontData_t instance.
     * @param[in] character Pointer to the font character to insert.
     * @return SUCCESS on success, or an appropriate error code on failure.
     */
    errorCode_t (*insert)(struct fontData_s *const self, fontCharacter_t *const character);

    /**
     * @brief Parses a font file and populates the hash table with font characters.
     * @param[in,out] self Pointer to the fontData_t instance.
     * @param[in] filename The name of the font file to parse.
     * @return SUCCESS on success, or an appropriate error code if parsing fails.
     */
    errorCode_t (*parse)(struct fontData_s *const self, const char *filename);
} fontData_t;

/**
 * @brief Constructs and initializes a new fontData_t object.
 * @return A pointer to the newly created fontData_t object, or NULL if allocation fails.
 */
fontData_t *fontDataConstructor(void);
