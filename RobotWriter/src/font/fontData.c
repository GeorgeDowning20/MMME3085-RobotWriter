#include "fontData.h"

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DECLARATIONS                     //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Node in the hash table for storing font characters.
 */
typedef struct hashNode_s
{
    char key;                   /**< ASCII key for the character. */
    fontCharacter_t *character; /**< Pointer to the font character. */
    struct hashNode_s *next;    /**< Pointer to the next node in the chain. */
} hashNode_t;

/**
 * @brief Inserts a font character into the hash table.
 * @param hash_table Pointer to the hash table.
 * @param asciiKey ASCII key for the font character.
 * @param character Pointer to the font character to insert.
 * @return 0 on success, -1 on failure.
 */
static errorCode_t _insert(fontData_t *const self, fontCharacter_t *const character);

/**
 * @brief Looks up a font character in the hash table by ASCII key.
 * @param hash_table Pointer to the hash table.
 * @param asciiKey ASCII key of the font character to retrieve.
 * @return Pointer to the corresponding fontCharacter_t, or NULL if not found.
 */
static const fontCharacter_t *_lookup(const fontData_t *const self, const char asciiKey);

/**
 * @brief Scales the font data by a given factor.
 * @param fontData Pointer to the font data to scale.
 */
static errorCode_t _scale(fontData_t *const fontData, double scale);

/**
 * @brief Insert a font character into the hash table.
 */
static inline unsigned int _hash_function(char key)
{
    return (unsigned int)key % 128;
}

/**
 * @brief Parses the font file and populates a hash table with font characters.
 * @param fontData Pointer to the font data to populate.
 * @param filename Name of the font file to parse.
 */
static errorCode_t _parse(fontData_t *const fontData, const char *const filename);

/**
 * @brief Frees all memory allocated for font data, including the hash table and its contents.
 * @param self Pointer to the font data to free.
 */
static errorCode_t _free(fontData_t *self);

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

// cunstructors
fontData_t *fontDataConstructor(void)
{
    fontData_t *fontData = malloc(sizeof(fontData_t));
    fontData->free = _free;
    fontData->lookup = _lookup;
    fontData->insert = _insert;
    fontData->scale = _scale;
    fontData->parse = _parse;
    for (int i = 0; i < 128; i++)
    {
        fontData->table[i] = NULL;
    }
    return fontData;
}

///////////////////////////////////////////////////////////////////////
//                        PRIVATE   DEFINITIONS                      //
///////////////////////////////////////////////////////////////////////

static errorCode_t _insert(fontData_t *const self, fontCharacter_t *const character)
{
    if (!character)
        return ErrorHandler(ERROR_NULL_POINTER);

    if (!self)
        return ErrorHandler(ERROR_NULL_POINTER);

    unsigned int index = _hash_function(character->asciiKey);
    hashNode_t *new_node = malloc(sizeof(hashNode_t));
    if (!new_node)
        return ErrorHandler(ERROR_MEMORY_ALLOCATION_FAILED);

    new_node->key = character->asciiKey;
    new_node->character = character;
    new_node->next = self->table[index];
    self->table[index] = new_node;

    return SUCCESS;
}

/**
 * @brief Lookup a font character in the hash table by ASCII key.
 */
static const fontCharacter_t *_lookup(const fontData_t *const self, const char asciiKey)
{
    if (!self)
        return NULL;

    unsigned int index = _hash_function(asciiKey);
    hashNode_t *node = self->table[index];
    while (node != NULL)
    {
        if (node->key == asciiKey)
        {
            return node->character;
        }
        node = node->next;
    }
    return NULL;
}

/**
 * @brief Scale the font data by a given factor.
 */
static errorCode_t _scale(fontData_t *const fontData, double scale)
{

    if (!fontData)
        return ErrorHandler(ERROR_NULL_POINTER);

    fontData->fontScale = scale;

    for (int i = 0; i < 128; i++)
    {
        hashNode_t *node = fontData->table[i];
        while (node != NULL)
        {
            fontCharacter_t *fontChar = node->character;
            for (uint8_t j = 0; j < fontChar->numStrokes; j++)
            {
                fontChar->strokes[j].vec.x *= scale;
                fontChar->strokes[j].vec.y *= scale;
            }
            node = node->next;
        }
    }

    return SUCCESS;
}

/**
 * @brief Frees all memory allocated for font data, including the hash table and its contents.
 * @param fontData Pointer to the font data to free.
 */
static errorCode_t _free(fontData_t *self)
{
    if (!self) // Early exit for NULL pointer
                return ErrorHandler(ERROR_NULL_POINTER);


    for (int i = 0; i < ASCII_CHARACTERS; i++)
    {
        hashNode_t *node = self->table[i];
        while (node != NULL)
        {
            hashNode_t *next_node = node->next;

            // Free character strokes if present
            if (node->character)
                node->character->free(node->character);

            free(node); // Free the current hash node
            node = next_node;
        }
        self->table[i] = NULL; // Clear the hash table entry
    }

    free(self); // Free the parent structure

    return SUCCESS;
}

/**
 * @brief Parse the font file and populate the hash table.
 */
static errorCode_t _parse(fontData_t *const fontData, const char *const filename)
{
    if (!fontData)
        return ErrorHandler(ERROR_NULL_POINTER);

    FILE *file = fopen(filename, "r");
    if (!file)
        return ErrorHandler(ERROR_OPEN_FILE);

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int id, numStrokes;
        if (sscanf(line, "999 %d %d", &id, &numStrokes) != 2)
            break;

        fontCharacter_t *fontChar = fontCharConstuctor((char)id, numStrokes);
        if (!fontChar)
            return ErrorHandler(ERROR_MEMORY_ALLOCATION_FAILED);

        for (int i = 0; i < numStrokes; i++)
        {
            if (!fgets(line, sizeof(line), file))
                break;

            stroke_t stroke;
            if (sscanf(line, "%lf %lf %i", &stroke.vec.x, &stroke.vec.y, (int *)&stroke.pen_state) == 3)
                fontChar->appendStroke(fontChar, stroke);
        }
        fontData->insert(fontData, fontChar);
    }

    fclose(file);

    return SUCCESS;
}

