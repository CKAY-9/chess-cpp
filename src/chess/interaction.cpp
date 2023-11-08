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

  for (int i = 0; i < game->pieces.size(); i++) {
    Piece p = game->pieces[i];
    if (p.getPositionX() == col && p.getPositionY() == row) {
      return p;
    }
  }
  return Piece(false, -1, -1, '0', 0);
} 

void handleInteraction(int window_width, int window_height, Game *game, Piece *piece) {
  if (IsMouseButtonReleased(0) && piece != 0 && piece->getType() != '0') {
    float grid_width = (float)window_width / 8;
    float grid_height = (float)window_height / 8;

    int mouse_x = GetMouseX();
    int mouse_y = GetMouseY();

    int col = std::floor(mouse_x / grid_width);
    int row = std::floor(mouse_y / grid_height);

    int to_move_index = getPieceAtGridIndex(piece->getPositionX(), piece->getPositionY(), game);
    int to_take_index = getPieceAtGridIndex(col, row, game);

    Piece to_move = getPieceAtGrid(piece->getPositionX(), piece->getPositionY(), game);
    // turn checking
    if (((game->current_move % 2 == 1) && to_move.isWhite()) || ((game->current_move % 2 == 0) && !to_move.isWhite())) {
      *piece = Piece(false, -1, -1, '0', 0);
      return;
    }
    Piece to_take = getPieceAtGrid(col, row, game);

    // check if pieces are on same team
    if ((to_move.getType() != '0' && to_take.getType() != '0') && to_take.isWhite() == to_move.isWhite()) {
      *piece = Piece(false, -1, -1, '0', 0);
      return;
    }

    if (!can_piece_move_to_position(col, row, game, &to_move, &to_take)) {
      *piece = Piece(false, -1, -1, '0', 0);
      return;
    }

    // replace piece at position
    game->pieces.push_back(Piece(isupper(piece->getType()), col, row, piece->getType(), piece->getSpritePosition()));
    // move and delete pieces
    if (to_take_index != -1) {
      game->pieces.erase(game->pieces.begin()+to_take_index);
      PlaySound(game->sounds[0]);
    } else {
      PlaySound(game->sounds[1]);
    }
    if (to_move_index != -1) {
      game->pieces.erase(game->pieces.begin()+to_move_index);
    }
    *piece = Piece(false, -1, -1, '0', 0);
    game->current_move += 1;
  }

  if (IsMouseButtonDown(0) && piece->getType() == '0') {
    *piece = getPieceAtMousePosition(window_width, window_height, game);
  }
}
