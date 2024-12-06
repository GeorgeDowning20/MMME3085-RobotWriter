#pragma once

typedef struct Coord2D_s {
    double x;
    double y;
} Coord2D_t;


static inline Coord2D_t AddCoord2D(const Coord2D_t a,const Coord2D_t b)
{
    Coord2D_t result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}
