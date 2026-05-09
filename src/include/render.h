#include "raylib.h"

typedef struct {
    Rectangle rec_pos_from_texture;
} tile;

void initialize_render(const char *texture_path, Texture *tex_pattern,
                       tile *tiles);
void draw_chessboard(tile *tiles, Texture *tex_pattern, float scale);
void draw_board_labels(float tile_size, float scale);

#define SIZEOF(A) sizeof(A) / sizeof(A[0])
