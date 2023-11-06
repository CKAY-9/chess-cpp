#include <raylib.h>
#include "chess.h"

int main (int argc, char *argv[]) {
  
  const int screen_width = 640;
  const int screen_height = 640;

  InitWindow(screen_width, screen_height, "Chess in C++");
  SetTargetFPS(60);

  Game *game = new Game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(RAYWHITE);   
      drawChessBoard(screen_width, screen_height);
      drawPieces(screen_width, screen_height, game);
    EndDrawing();
  }

  return 0;
}
