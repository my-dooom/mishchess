#include "game.h"
#include "raylib.h"

void check_possible_moves(piece board[8][8], board_pos pos,
                          possible_moves *moves) {
    piece p = board[pos.row][pos.col];
    int dir = (p.color == White) ? -1 : 1;
    switch (p.type) {
    case PAWN: {
        
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
    case ROOK: {
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int d = 0; d < 4; d++) {
            int dr = dirs[d][0], dc = dirs[d][1];
            int r = pos.row + dr, c = pos.col + dc;
            while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                if (board[r][c].type == EMPTY) {
                    da_append(*moves, ((Vector2){c, r}));
                } else {
                    if (board[r][c].color != p.color)
                        da_append(*moves, ((Vector2){c, r})); // capture
                    break; // blocked either way
                }
                r += dr;
                c += dc;
            }
        }
        break;
    }
    case BISHOP: {
        int dirs[4][2] = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
        for (int d = 0; d < 4; d++) {
            int dr = dirs[d][0], dc = dirs[d][1];
            int r = pos.row + dr, c = pos.col + dc;
            while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                if (board[r][c].type == EMPTY) {
                    da_append(*moves, ((Vector2){c, r}));
                } else {
                    if (board[r][c].color != p.color)
                        da_append(*moves, ((Vector2){c, r})); // capture
                    break; // blocked either way
                }
                r += dr;
                c += dc;
            }
        }
        break;
    }

    case QUEEN: {
        int dirs[8][2] = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int d = 0; d < 8; d++) {
            int dr = dirs[d][0], dc = dirs[d][1];
            int r = pos.row + dr, c = pos.col + dc;
            while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                if (board[r][c].type == EMPTY) {
                    da_append(*moves, ((Vector2){c, r}));
                } else {
                    if (board[r][c].color != p.color)
                        da_append(*moves, ((Vector2){c, r})); // capture
                    break; // blocked either way
                }
                r += dr;
                c += dc;
            }
        }
        break;
    }
    case KING: {
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int d = 0; d < 4; d++) {
            int dr = dirs[d][0], dc = dirs[d][1];
            int r = pos.row + dr, c = pos.col + dc;
            if (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[r][c].type == EMPTY) {

                da_append(*moves, ((Vector2){c, r}));
            }
            r += dr;
            c += dc;
        }
        break;
    }
    case KNIGHT: {
        int jumps[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                           { 1, -2}, { 1, 2}, { 2, -1}, { 2, 1}};
        for (int i = 0; i < 8; i++) {
            int r = pos.row + jumps[i][0];
            int c = pos.col + jumps[i][1];
            if (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                (board[r][c].type == EMPTY || board[r][c].color != p.color)) {
                da_append(*moves, ((Vector2){c, r}));
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
