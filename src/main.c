
#include "board.h"
#include "game.h"
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
        *row = (int)(mouse_position.y / tile_size);
        const char *col_names[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
        TraceLog(LOG_INFO, "Clicked on board coordinates: %s%d",
                 col_names[*col], *row + 1);
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
    board_pos selected = {-1, -1};
    board_pos destination = {-1, -1};
    int clicked_row = -1, clicked_col = -1;

    SetTraceLogCallback(LogColored);

    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");

    //--------------------------------------------------------------------------------------
    // IcNIT RENDERING
    //--------------------------------------------------------------------------------------

    Texture tex_pattern;
    tile tiles[2];
    initialize_render("assets/atlas.png", &tex_pattern, tiles);

    initialize_board(board);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        mouse_position = GetMousePosition();
        clicked_row = -1;
        clicked_col = -1;
        convert_mouse_position_to_board_coordinates(
            mouse_position, tile_size * scale, &clicked_row, &clicked_col);
        if (clicked_row >= 0 && clicked_col >= 0) {
            if (clicked_row == selected.row && clicked_col == selected.col) {
                // clicked same tile: deselect
                selected.row = -1;
                selected.col = -1;
            } else if (selected.row >= 0 &&
                       board[selected.row][selected.col].type != EMPTY) {
                // piece selected, second click: attempt move
                destination.row = clicked_row;
                destination.col = clicked_col;
                TraceLog(LOG_INFO, "Moving piece to: %d, %d", destination.row,
                         destination.col);
                move_piece(board, selected, destination);
                selected.row = -1;
                selected.col = -1;
                destination.row = -1;
                destination.col = -1;
            } else {
                // no piece selected yet: select
                selected.row = clicked_row;
                selected.col = clicked_col;
                if (board[selected.row][selected.col].type != EMPTY) {
                    TraceLog(LOG_INFO, "Selected piece: %d of color %d",
                             board[selected.row][selected.col].type,
                             board[selected.row][selected.col].color);
                }
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_chessboard(tiles, &tex_pattern, scale);
        draw_pieces(&tex_pattern, scale);
        draw_board_labels(tile_size, scale);
        draw_selection_highlight(scale, &selected);
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
