#include "game.h"

int move_piece(piece board[8][8], board_pos src, board_pos dest) {

    switch (board[src.row][src.col].type) {
    case PAWN:
        board[dest.row][dest.col] = board[src.row][src.col];
        board[src.row][src.col].type = EMPTY;
        break;
    default:
        break;
    }
    return 1;
}
