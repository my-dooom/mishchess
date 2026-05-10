#ifndef RENDER_H
#define RENDER_H

#include "board.h"
#include "raylib.h"

#include "game.h"

typedef struct {
    Rectangle rec_pos_from_texture;
} tile;

extern Rectangle selected_tile_rect;

extern Rectangle piece_rects[2][7]; // [color][piece_type]

void draw_selection_highlight(float scale, board_pos *selection);

void draw_possible_moves(possible_moves *moves, float scale);

void draw_pieces(Texture *tex_pattern, float scale);

void initialize_render(const char *texture_path, Texture *tex_pattern,
                       tile *tiles);
void draw_chessboard(tile *tiles, Texture *tex_pattern, float scale);
void draw_board_labels(float tile_size, float scale);

#define SIZEOF(A) sizeof(A) / sizeof(A[0])

#endif // RENDER_H
