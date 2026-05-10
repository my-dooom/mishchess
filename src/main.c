
#include "board.h"
#include "game.h"
#include "logger.h"
#include "raylib.h"
#include "render.h"

#define null_pos (board_pos){-1, -1}
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
    int clicked_row = -1, clicked_col = -1;
    possible_moves moves = {0};

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
            if (selected.row >= 0 &&
                board[selected.row][selected.col].type != EMPTY) {
                if (clicked_row == selected.row &&
                    clicked_col == selected.col) {
                    // deselect
                    selected = null_pos;
                    moves.count = 0;
                } else {
                    // attempt move: check if destination is in possible moves
                    for (size_t i = 0; i < moves.count; i++) {
                        if ((int)moves.pos[i].y == clicked_row &&
                            (int)moves.pos[i].x == clicked_col) {
                            move_piece(board, selected,
                                       (board_pos){clicked_row, clicked_col});
                            TraceLog(LOG_INFO, "Moved piece to: %d, %d",
                                     clicked_row, clicked_col);
                            break;
                        }
                    }
                    selected = null_pos;
                    moves.count = 0;
                }
            } else {
                // select piece and compute its moves
                selected = (board_pos){clicked_row, clicked_col};
                moves.count = 0;
                check_possible_moves(board, selected, &moves);
                TraceLog(LOG_INFO, "Selected piece: %d of color %d",
                         board[selected.row][selected.col].type,
                         board[selected.row][selected.col].color);
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_chessboard(tiles, &tex_pattern, scale);
        draw_pieces(&tex_pattern, scale);
        draw_board_labels(tile_size, scale);
        draw_selection_highlight(scale, &selected);
        draw_possible_moves(&moves, scale);
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
