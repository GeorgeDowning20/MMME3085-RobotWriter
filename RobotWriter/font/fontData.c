/**
 * @file fontData.c
 * @brief Implementation of font data handling, including hashing, insertion, lookup, scaling, and parsing.
 * @details
 * This file provides the functionality to store and manage font characters inside a hash table.
 * Each font character is associated with an ASCII key and is stored as a series of strokes.
 * The hash table uses chaining to handle collisions, allowing multiple font characters with
 * the same hash to be stored as a linked list of nodes.
 *
 * Functions are provided to insert and look up font characters, scale the strokes of all font
 * characters by a given factor, parse a font file to populate the hash table, and free all
 * allocated resources.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#include "fontData.h"

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DECLARATIONS                     //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Node in the hash table for storing font characters.
 * @details Each hash node contains:
 * - A character key (ASCII key for the font character).
 * - A pointer to a fontCharacter_t object.
 * - A pointer to the next node in the chain (for handling collisions).
 */
typedef struct hashNode_s
{
    char key;                   /**< ASCII key for the character. */
    fontCharacter_t *character; /**< Pointer to the font character. */
    struct hashNode_s *next;    /**< Pointer to the next node in the chain. */
} hashNode_t;

/**
 * @brief Inserts a font character into the hash table.
 * @param[in,out] self       Pointer to the fontData_t instance.
 * @param[in]     character  Pointer to the font character to insert.
 * @return SUCCESS on success, or an appropriate error code:
 *         - ERROR_NULL_POINTER if `self` or `character` is NULL.
 *         - ERROR_MEMORY_ALLOCATION_FAILED if memory allocation for the node fails.
 */
static errorCode_t _insert(fontData_t *const self, fontCharacter_t *const character);

/**
 * @brief Looks up a font character in the hash table by ASCII key.
 * @param[in] self      Pointer to the fontData_t instance.
 * @param[in] asciiKey  ASCII key of the font character to retrieve.
 * @return Pointer to the corresponding fontCharacter_t on success, or NULL if not found or
 *         if `self` is NULL.
 */
static const fontCharacter_t *_lookup(const fontData_t *const self, const char asciiKey);

/**
 * @brief Scales all strokes in the font data by a given factor.
 * @param[in,out] fontData Pointer to the fontData_t instance.
 * @param[in]     scale    The factor by which to scale the font strokes.
 * @return SUCCESS on success, or ERROR_NULL_POINTER if `fontData` is NULL.
 */
static errorCode_t _scale(fontData_t *const self, double scale);

/**
 * @brief Hash function for converting a character key into an index.
 * @param[in] key The ASCII character key to hash.
 * @return An unsigned integer in [0,127] representing the hash table index.
 */
static inline unsigned int _hash_function(char key);

/**
 * @brief Parses the font file and populates the hash table with font characters.
 * @param[in,out] fontData Pointer to the fontData_t instance to populate.
 * @param[in]     filename Name of the font file to parse.
 * @return SUCCESS on success, or an appropriate error code:
 *         - ERROR_NULL_POINTER if `fontData` or `filename` is NULL.
 *         - ERROR_OPEN_FILE if the file cannot be opened.
 *         - ERROR_MEMORY_ALLOCATION_FAILED if memory allocation for font characters fails.
 */
static errorCode_t _parse(fontData_t *const self, const char *const filename);

/**
 * @brief Frees all memory allocated for the font data, including the hash table and its contents.
 * @param[in,out] self Pointer to the fontData_t instance to free.
 * @return SUCCESS on success, or ERROR_NULL_POINTER if `self` is NULL.
 */
static errorCode_t _free(fontData_t *self);

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

/**
 @details Allocates memory for the fontData_t structure, sets the function pointers, and
 * initializes the hash table to NULL. This structure can then be used to insert, lookup,
 * scale, and parse font characters, and finally be freed when no longer needed.
 */
fontData_t *fontDataConstructor(void)
{
    fontData_t *fontData = malloc(sizeof(fontData_t)); // Allocate memory for fontData_t
    if (!fontData)                                     // Check if memory allocation failed
    {
        ErrorHandler(ERROR_MEMORY_ALLOCATION_FAILED); // Handle error
        return NULL;                                  // Return NULL
    }

    fontData->free = _free;     // Function pointer to free the font data
    fontData->lookup = _lookup; // Function pointer to look up a font character
    fontData->insert = _insert; // Function pointer to insert a font character
    fontData->scale = _scale;   // Function pointer to scale the font data
    fontData->parse = _parse;   // Function pointer to parse a font file

    for (int i = 0; i < ASCII_CHARACTERS; i++) // Initialize hash table to NULL
    {
        fontData->table[i] = NULL; // Set each element to NULL
    }
    return fontData; // Return the fontData_t structure
}

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DEFINITIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @details
 * Allocates a new hash node and places it in the hash table at the index computed by
 * the hash function. In the event of a collision, the new node is linked into the existing chain.
 */
static errorCode_t _insert(fontData_t *const self, fontCharacter_t *const character)
{
    if (!character)                              // Check if character is NULL
        return ErrorHandler(ERROR_NULL_POINTER); // Handle error

    if (!self)                                   // Check if self is NULL
        return ErrorHandler(ERROR_NULL_POINTER); // Handle error

    unsigned int index = _hash_function(character->asciiKey); // Compute hash index
    hashNode_t *new_node = malloc(sizeof(hashNode_t));        // Allocate memory for new node
    if (!new_node)                                            // Check if memory allocation failed
        return ErrorHandler(ERROR_MEMORY_ALLOCATION_FAILED);  // Handle error

    new_node->key = character->asciiKey; // Set key to ASCII key
    new_node->character = character;     // Set character to font character
    new_node->next = self->table[index]; // Set next to current node at index
    self->table[index] = new_node;       // Set current node at index to new node

    return SUCCESS; // Return success
}

/**
 * @details
 * Computes the hash index for the given ASCII key and searches the chain at that index.
 * If the character is found, returns a pointer to the corresponding fontCharacter_t.
 */
static const fontCharacter_t *_lookup(const fontData_t *const self, const char asciiKey)
{
    if (!self)       // Check if self is NULL
        return NULL; // Return NULL

    unsigned int index = _hash_function(asciiKey); // Compute hash index
    hashNode_t *node = self->table[index];         // Get node at index
    while (node != NULL)                           // Iterate through chain
    {
        if (node->key == asciiKey) // Check if key matches
        {
            return node->character; // Return character
        }
        node = node->next; // Move to next node
    }
    return NULL; // Return NULL if not found
}

/**
 * @details
 * Iterates through each font character in the hash table and multiplies the x and y
 * components of each stroke by the given scale factor.
 */
static errorCode_t _scale(fontData_t *const self, double scale)
{
    if (!self)                               // Check if fontData is NULL
        return ErrorHandler(ERROR_NULL_POINTER); // Handle error

    self->fontScale = scale; // Set font scale to given scale

    for (int i = 0; i < ASCII_CHARACTERS; i++) // Iterate through hash table
    {
        hashNode_t *node = self->table[i]; // Get node at index
        while (node != NULL)                   // Iterate through chain
        {
            fontCharacter_t *fontChar = node->character;       // Get font character
            for (uint8_t j = 0; j < fontChar->numStrokes; j++) // Iterate through strokes
            {
                fontChar->strokes[j].vec.x *= scale; // Scale x component
                fontChar->strokes[j].vec.y *= scale; // Scale y component
            }
            node = node->next; // Move to next node
        }
    }

    return SUCCESS; // Return success
}

/**
 * @details
 * Returns the modulo of the ASCII value of the character by 128, ensuring an index in [0,127].
 */
static inline unsigned int _hash_function(char key)
{
    return (unsigned int)key % ASCII_CHARACTERS; // Return modulo of key by 128
}

/**
 * @details
 * Opens the specified file, reads font character definitions, constructs
 * fontCharacter_t objects, and inserts them into the hash table.
 */
static errorCode_t _parse(fontData_t *const self, const char *const filename)
{
    if (!self)                               // Check if fontData is NULL
        return ErrorHandler(ERROR_NULL_POINTER); // Handle error

    if (!filename)                               // Check if filename is NULL
        return ErrorHandler(ERROR_NULL_POINTER); // Handle error

    FILE *file = fopen(filename, "r");        // Open file
    if (!file)                                // Check if file cannot be opened
        return ErrorHandler(ERROR_NO_FONT_DATA); // Handle error

    char line[256];                         // Buffer for reading lines
    while (fgets(line, sizeof(line), file)) // Read lines from file
    {
        int id, numStrokes;                                   // Variables for ID and number of strokes
        if (sscanf(line, "999 %d %d", &id, &numStrokes) != 2) // Parse ID and number of strokes
            break;

        fontCharacter_t *fontChar = fontCharConstuctor((char)id, (uint8_t)numStrokes); // Construct font character
        if (!fontChar)                                                        // Check if font character is NULL
        {
            fclose(file);                                        // Close file
            return ErrorHandler(ERROR_MEMORY_ALLOCATION_FAILED); // Handle error
        }

        for (int i = 0; i < numStrokes; i++) // Iterate through strokes
        {
            if (!fgets(line, sizeof(line), file)) // Read line
                break;                            // Break if line cannot be read

            stroke_t stroke;                                                                             // Stroke structure
            if (sscanf(line, "%lf %lf %i", &stroke.vec.x, &stroke.vec.y, (int *)&stroke.pen_state) == 3) // Parse stroke
                fontChar->appendStroke(fontChar, stroke);                                                // Append stroke to font character
        }
        self->insert(self, fontChar); // Insert font character into hash table
    }

    fclose(file);   // Close file
    return SUCCESS; // Return success
}

/**
 * @details
 * Iterates over the hash table, frees all font characters and hash nodes, and then frees
 * the fontData_t structure itself.
 */
static errorCode_t _free(fontData_t *self)
{
    if (!self)                                   // Check if self is NULL
        return ErrorHandler(ERROR_NULL_POINTER); // Handle error

    for (int i = 0; i < ASCII_CHARACTERS; i++) // Iterate through hash table
    {
        hashNode_t *node = self->table[i]; // Get node at index
        while (node != NULL)               // Iterate through chain
        {
            hashNode_t *next_node = node->next;         // Get next node
            if (node->character)                        // Check if character is not NULL
                node->character->free(node->character); // Free character

            free(node);       // Free node
            node = next_node; // Move to next node
        }
        self->table[i] = NULL; // Set node at index to NULL
    }

    free(self); // Free fontData_t

    return SUCCESS; // Return success
}
