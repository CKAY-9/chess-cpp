#include <iostream>
#include <raylib.h>
#include "chess.h"

int main (int argc, char *argv[]) {
  std::string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  std::cout << "Enter in a valid FEN string (default (0): rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR): ";
  std::cin >> fen_string;
  if (fen_string == "0") {
    fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  }

  const int screen_width = 600;
  const int screen_height = 600;

  InitWindow(screen_width, screen_height, "Chess in C++");
  SetTargetFPS(60);

  Game *game = new Game(fen_string);
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
