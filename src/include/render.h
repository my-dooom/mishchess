#include "raylib.h"
typedef enum {
    White,
    Black,
} tile_color;

typedef struct {
    tile_color color;
    Rectangle rec_pos_from_texture;
} tile;

void initialize_render(const char *texture_path, Texture *tex_pattern,
                       tile *tiles);
void draw_chessboard(tile *tiles, Texture *tex_pattern, float scale);

#define SIZEOF(A) sizeof(A) / sizeof(A[0])
