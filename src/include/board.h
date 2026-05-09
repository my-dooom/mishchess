#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"

//------------------------------------------------------------------------------------
// DATA STRUCTURES
//------------------------------------------------------------------------------------
//
typedef enum {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
} piece_type;

typedef enum {
    White,
    Black,
} color;

typedef struct {
    piece_type type;
    color color;
    // Position on the board (e.g., (0,0) for a1, (7,7) for h8)
    Vector2 position;
} piece;

extern piece board[8][8];

void initialize_board();

#endif // BOARD_H
