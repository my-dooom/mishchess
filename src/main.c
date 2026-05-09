
#include "board.h"
#include "logger.h"
#include "raylib.h"
#include "render.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

void convert_mouse_position_to_board_coordinates(Vector2 mouse_position,
                                                 float tile_size, int *row,
                                                 int *col) {
    if (mouse_position.x < 0 || mouse_position.y < 0) {
        *row = -1;
        *col = -1;
        return;
    }
    if (mouse_position.x > tile_size * 8 || mouse_position.y > tile_size * 8) {
        *row = -1;
        *col = -1;
        return;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        *col = (int)(mouse_position.x / tile_size);
        *row = 7 - (int)(mouse_position.y / tile_size);
        const char *col_names[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
        TraceLog(LOG_INFO, "Clicked on board coordinates: %s%d", col_names[*col], *row + 1);
    }
}
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    //

    const int tile_size = 16;
    const float scale = 3.5f;
    const int margins = 150;
    const int screenWidth = 1500; // hardcoded for now, should be calculated
                                  // based on tile size and scale
    const int screenHeight = tile_size * 8 * scale + margins;
    Vector2 mouse_position = {0, 0};
    SetTraceLogCallback(LogColored);

    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");

    //--------------------------------------------------------------------------------------
    // IcNIT RENDERING
    //--------------------------------------------------------------------------------------

    Texture tex_pattern;
    tile tiles[2];
    initialize_render("assets/atlas.png", &tex_pattern, tiles);

    initialize_board();

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        mouse_position = GetMousePosition();
        int clicked_row, clicked_col;
        convert_mouse_position_to_board_coordinates(
            mouse_position, tile_size * scale, &clicked_row, &clicked_col);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_chessboard(tiles, &tex_pattern, scale);
        draw_board_labels(tile_size, scale);
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
