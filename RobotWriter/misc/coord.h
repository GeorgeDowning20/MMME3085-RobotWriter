/**
 * @file coord.h
 * @brief Defines the Coord2D_t structure for representing 2D coordinates
 *        and provides inline functions for basic 2D vector operations.
 * @note View documentation at https://georgedowning20.github.io/MMME3085-RobotWriter/
 */

#pragma once

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DECLARATIONS                      //
///////////////////////////////////////////////////////////////////////

/**
 * @struct Coord2D_s
 * @brief Represents a point in 2D space.
 *
 * This structure contains two double precision floating-point numbers
 * representing the x and y coordinates of a point in 2D space.
 *
 * @var Coord2D_s::x
 * The x-coordinate of the point.
 *
 * @var Coord2D_s::y
 * The y-coordinate of the point.
 */
typedef struct Coord2D_s
{
    double x;
    double y;
} Coord2D_t;

///////////////////////////////////////////////////////////////////////
//                        PUBLIC   DEFINITIONS                       //
///////////////////////////////////////////////////////////////////////

/**
 * @brief Adds two 2D coordinates.
 *
 * @param[in] a The first 2D coordinate.
 * @param[in] b The second 2D coordinate.
 * @return The result of adding a and b.
 */
static inline Coord2D_t AddCoord2D(const Coord2D_t a, const Coord2D_t b)
{
    Coord2D_t result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

/**
 * @brief Subtracts one 2D coordinate from another.
 *
 * @param[in] a The 2D coordinate from which to subtract.
 * @param[in] b The 2D coordinate to subtract.
 * @return The result of subtracting b from a.
 */
static inline Coord2D_t SubCoord2D(const Coord2D_t a, const Coord2D_t b)
{
    Coord2D_t result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

/**
 * @brief Multiplies two 2D coordinates component-wise.
 *
 * @param[in] a The first 2D coordinate.
 * @param[in] b The second 2D coordinate.
 * @return The result of multiplying a by b.
 */
static inline Coord2D_t MulCoord2D(const Coord2D_t a, const Coord2D_t b)
{
    Coord2D_t result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
}

/**
 * @brief Divides one 2D coordinate by another component-wise.
 *
 * @note Ensure b.x and b.y are not zero.
 *
 * @param[in] a The 2D coordinate to divide.
 * @param[in] b The 2D coordinate to divide by.
 * @return The result of dividing a by b.
 */
static inline Coord2D_t DivCoord2D(const Coord2D_t a, const Coord2D_t b)
{
    Coord2D_t result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    return result;
}

/**
 * @brief Scales a 2D coordinate by a given factor.
 *
 * @param[in] a The 2D coordinate to scale.
 * @param[in] scale The factor by which to scale.
 * @return The scaled coordinate.
 */
static inline Coord2D_t ScaleCoord2D(const Coord2D_t a, const double scale)
{
    Coord2D_t result;
    result.x = a.x * scale;
    result.y = a.y * scale;
    return result;
}
