#include "../chess.h"
#include <cctype>
#include <cmath>
#include <iostream>
#include <raylib.h>

Piece getPieceAtMousePosition(int window_width, int window_height, Game *game) {
  float grid_width = (float)window_width / 8;
  float grid_height = (float)window_height / 8;

  int mouse_x = GetMouseX();
  int mouse_y = GetMouseY();

  int col = std::floor(mouse_x / grid_width);
  int row = std::floor(mouse_y / grid_height);

  for (int i = 0; i < game->getPieces().size(); i++) {
    Piece p = game->getPieces()[i];
    if (p.getPositionX() == col && p.getPositionY() == row) {
      return p;
    }
  }
  return Piece(false, -1, -1, '0', 0);
} 

void handleInteraction(int window_width, int window_height, Game *game, Piece *piece) {
  if (!IsMouseButtonDown(0) && piece != 0) {
    *piece = getPieceAtMousePosition(window_width, window_height, game);
  }

  if (IsMouseButtonUp(0) && piece != 0 && piece->getType() != '0') {
    float grid_width = (float)window_width / 8;
    float grid_height = (float)window_height / 8;

    int mouse_x = GetMouseX();
    int mouse_y = GetMouseY();

    int col = std::floor(mouse_x / grid_width);
    int row = std::floor(mouse_y / grid_height);

    int index = getPieceAtGridIndex(piece->getPositionX(), piece->getPositionY(), game);
    game->pieces.erase(game->pieces.begin()+index);
    game->pieces.push_back(Piece(isupper(piece->getType()), col, row, piece->getType(), piece->getSpritePosition()));
    piece = 0;
  }
}
