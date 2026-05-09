#include "raylib.h"
#include "render.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");

    //--------------------------------------------------------------------------------------
    // INIT RENDERING
    //--------------------------------------------------------------------------------------

    Texture tex_pattern;
    tile tiles[2];
    initialize_render("assets/atlas.png", &tex_pattern, tiles);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    /// TODO: PLEASE REMEMBER ABOUT TILES
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_chessboard(tiles, &tex_pattern, 3.5f);
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
