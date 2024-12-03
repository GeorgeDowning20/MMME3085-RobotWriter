#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#else
#include <Windows.h>
// #define sleep(x) Sleep(x)ß
#endif

#include "../lib/rs232.h"
#include "../lib/serial.h"

#define bdrate 115200               /* 115200 baud */

/**
 * @brief Structure representing a single stroke of a character.
 */
typedef struct stroke_s {
    double x;           /**< X-coordinate of the stroke. */
    double y;           /**< Y-coordinate of the stroke. */
    bool pen_state;     /**< State of the pen (true = down, false = up). */
} stroke_t;

/**
 * @brief Structure representing a font character.
 */
typedef struct fontCharacter_s {
    char ascii_key;          /**< ASCII key for the character. */
    uint8_t num_strokes;     /**< Number of strokes in the character. */
    stroke_t *strokes;       /**< Array of strokes that define the character. */
} fontCharacter_t;

/**
 * @brief Structure representing the cursor position.
 */
typedef struct cursor_s {
    double x;    /**< X-coordinate of the cursor. */
    double y;    /**< Y-coordinate of the cursor. */
} cursor_t;

/**
 * @brief Node in the hash table for storing font characters.
 */
typedef struct hashNode_s {
    char key;                    /**< ASCII key for the character. */
    fontCharacter_t *character;  /**< Pointer to the font character. */
    struct hashNode_s *next;     /**< Pointer to the next node in the chain. */
} hashNode_t;

/**
 * @brief Structure representing font data, including a hash table.
 */
typedef struct fontData_s {
    double scale;                  /**< Scaling factor for the font. */
    hashNode_t *table[128];        /**< Hash table for storing font characters. */
} fontData_t;

/**
 * @brief Inserts a font character into the hash table.
 * @param hash_table Pointer to the hash table.
 * @param ascii_key ASCII key for the font character.
 * @param character Pointer to the font character to insert.
 * @return 0 on success, -1 on failure.
 */
int hash_table_insert(fontData_t *hash_table, const char ascii_key, fontCharacter_t *character);

/**
 * @brief Looks up a font character in the hash table by ASCII key.
 * @param hash_table Pointer to the hash table.
 * @param ascii_key ASCII key of the font character to retrieve.
 * @return Pointer to the corresponding fontCharacter_t, or NULL if not found.
 */
const fontCharacter_t *hash_table_lookup(const fontData_t *hash_table, const char ascii_key);

/**
 * @brief Parses the font file and populates a hash table with font characters.
 * @param font_data Pointer to the font data to populate.
 * @param filename Name of the font file to parse.
 */
void parse_font_file(fontData_t *font_data, const char *filename);

/**
 * @brief Scales the font data by a given factor.
 * @param font_data Pointer to the font data to scale.
 */
void scale_font_data(fontData_t *font_data);

/**
 * @brief Processes a text file and generates G-code for the text.
 * @param font_data Pointer to the font data to use.
 */
void process_text_file(const fontData_t *font_data);

/**
 * @brief Generates G-code for a given text string.
 * @param font_data Pointer to the font data to use.
 * @param text Text string (single word) to generate G-code for.
 */
void generate_gcode(const fontData_t *font_data, const char *text);
