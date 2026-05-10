#include "render.h"
#include "game.h"
#include "raylib.h"

Rectangle piece_rects[2][7] = {
    // White pieces
    [White] =
        {
            [EMPTY] = {64, 192, 16, 16},
            [PAWN] = {96, 224, 16, 16},
            [KNIGHT] = {80, 224, 16, 16},
            [BISHOP] = {64, 224, 16, 16},
            [ROOK] = {48, 224, 16, 16},
            [QUEEN] = {32, 224, 16, 16},
            [KING] = {16, 224, 16, 16},
        },
    // Black pieces
    [Black] =
        {
            [EMPTY] = {64, 192, 16, 16},
            [PAWN] = {96, 208, 16, 16},
            [KNIGHT] = {80, 208, 16, 16},
            [BISHOP] = {64, 208, 16, 16},
            [ROOK] = {48, 208, 16, 16},
            [QUEEN] = {32, 208, 16, 16},
            [KING] = {16, 208, 16, 16},
        },

};

Rectangle selected_tile_rect = {48, 192, 16, 16};

void draw_selection_highlight(float scale, board_pos *selection) {
    if (selection->row == -1 || selection->col == -1)
        return; // No selection

    float ts = 16.0f * scale;
    Rectangle dest = {selection->col * ts, selection->row * ts, ts, ts};
    DrawRectangleLinesEx(dest, 2.0f, YELLOW);
}

void draw_pieces(Texture *tex_pattern, float scale) {
    float ts = 16.0f * scale;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            piece p = board[row][col];
            if (p.type == EMPTY)
                continue;

            Rectangle src = piece_rects[p.color][p.type];
            Rectangle dest = {col * ts, row * ts, ts, ts};
            DrawTexturePro(*tex_pattern, src, dest, (Vector2){0, 0}, 0.0f,
                           WHITE);
        }
    }
}

void draw_possible_moves(possible_moves *moves, float scale) {
    float ts = 16.0f * scale;
    for (size_t i = 0; i < moves->count; i++) {
        Vector2 pos = moves->pos[i];
        Rectangle dest = {pos.x * ts, pos.y * ts, ts, ts};
        Vector2 center = {(float)dest.x + dest.width / 2,
                          (float)dest.y + dest.height / 2};
        DrawCircleV(center, ts * 0.15f, Fade(GREEN, 0.5f));
    }
}

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
        int x =
            (int)(c * ts + ts / 2) - MeasureText(col_names[c], font_size) / 2;
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
