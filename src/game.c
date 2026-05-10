#include "game.h"
#include "raylib.h"

void check_possible_moves(piece board[8][8], board_pos pos,
                          possible_moves *moves) {
    piece p = board[pos.row][pos.col];
    switch (p.type) {
    case PAWN: {
        int dir = (p.color == White) ? -1 : 1;
        int next_row = pos.row + dir;
        if (next_row >= 0 && next_row < 8 &&
            board[next_row][pos.col].type == EMPTY) {
            da_append(*moves, ((Vector2){pos.col, next_row}));
            if (p.en_passant) {
                int double_row = pos.row + 2 * dir;
                if (double_row >= 0 && double_row < 8 &&
                    board[double_row][pos.col].type == EMPTY) {
                    da_append(*moves, ((Vector2){pos.col, double_row}));
                }
            }
        }
        // diagonal captures
        int capture_cols[] = {pos.col - 1, pos.col + 1};
        for (int i = 0; i < 2; i++) {
            int c = capture_cols[i];
            if (next_row >= 0 && next_row < 8 && c >= 0 && c < 8 &&
                board[next_row][c].type != EMPTY &&
                board[next_row][c].color != p.color) {
                da_append(*moves, ((Vector2){c, next_row}));
            }
        }
        break;
    }
    default:
        break;
    }
}

int move_piece(piece board[8][8], board_pos src, board_pos dest) {
    board[dest.row][dest.col] = board[src.row][src.col];
    board[dest.row][dest.col].en_passant = false;
    board[src.row][src.col].type = EMPTY;
    return 1;
}
