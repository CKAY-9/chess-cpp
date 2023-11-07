#include <iostream>
#include <raylib.h>
#include "chess.h"

int main (int argc, char *argv[]) {
  
  const int screen_width = 600;
  const int screen_height = 600;

  InitWindow(screen_width, screen_height, "Chess in C++");
  SetTargetFPS(60);

  Game *game = new Game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
  Piece* piece = new Piece(false, -1, -1, '0', 0);

  while (!WindowShouldClose()) {
    BeginDrawing();

      handleInteraction(screen_width, screen_height, game, piece);
      
      ClearBackground(RAYWHITE);   

      drawChessBoard(screen_width, screen_height);
      drawPieces(screen_width, screen_height, game, piece);

    EndDrawing();
  }

  return 0;
}
