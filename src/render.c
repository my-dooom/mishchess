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
    tiles[0].color = White;
    tiles[0].rec_pos_from_texture = (Rectangle){32, 8, 16, 16};
    tiles[1].color = Black;
    tiles[1].rec_pos_from_texture = (Rectangle){48, 8, 16, 16};
}

void draw_chessboard(tile *tiles, Texture *tex_pattern, float scale) {
    float tile_size = 16.0f * scale;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int tile_index = (col + row) % 2; // 0 = White, 1 = Black
            Rectangle dest = {col * tile_size, row * tile_size, tile_size, tile_size};
            DrawTexturePro(*tex_pattern, tiles[tile_index].rec_pos_from_texture,
                           dest, (Vector2){0, 0}, 0.0f, WHITE);
        }
    }
}
