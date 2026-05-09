#include "render.h"
#include "raylib.h"

void initialize_render(const char *texture_path, Texture *tex_pattern,
                       tile *tiles) {
    /// Initializes the rendering system, including loading textures and setting
    /// up any necessary OpenGL state.
    // NOTE: Textures must be loaded after Window initialization (OpenGL context
    // is required)
    *tex_pattern = LoadTexture(texture_path);
    SetTextureFilter(*tex_pattern, TEXTURE_FILTER_POINT);
    tiles[0].rec_pos_from_texture = (Rectangle){32, 8, 16, 16};
    tiles[1].rec_pos_from_texture = (Rectangle){48, 8, 16, 16};
}

void draw_board_labels(float tile_size, float scale) {
    const char *col_names[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    float ts = tile_size * scale;
    int font_size = (int)(ts * 0.35f);
    for (int c = 0; c < 8; c++) {
        int x = (int)(c * ts + ts / 2) - MeasureText(col_names[c], font_size) / 2;
        DrawText(col_names[c], x, (int)(8 * ts) + 4, font_size, BLACK);
    }
    for (int r = 0; r < 8; r++) {
        int rank = 8 - r;
        const char *label = TextFormat("%d", rank);
        int y = (int)(r * ts + ts / 2) - font_size / 2;
        DrawText(label, (int)(8 * ts) + 4, y, font_size, BLACK);
    }
}

void draw_chessboard(tile *tiles, Texture *tex_pattern, float scale) {
    float tile_size = 16.0f * scale;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int tile_index = (col + row) % 2; // 0 = White, 1 = Black
            Rectangle dest = {col * tile_size, row * tile_size, tile_size,
                              tile_size};
            DrawTexturePro(*tex_pattern, tiles[tile_index].rec_pos_from_texture,
                           dest, (Vector2){0, 0}, 0.0f, WHITE);
        }
    }
}