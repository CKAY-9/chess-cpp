#include "../chess.h"
#include <cctype>
#include <cstdlib>
#include <iostream>

Piece::Piece(bool white, int x, int y, char piece, int sprite_position) {
  this->white = white;
  this->position[0] = x;
  this->position[1] = y;
  this->sprite_position = sprite_position;
  this->piece_type = piece;
}

bool Piece::isWhite() {
  return this->white;
}

int Piece::getPositionX() {
  return this->position[0];
}

int Piece::getPositionY() {
  return this->position[1];
}

char Piece::getType() {
  return this->piece_type;
}

int Piece::getSpritePosition() {
  return this->sprite_position;
}

bool can_piece_move_to_position(int new_column, int new_row, Game *game, Piece *piece, Piece *target_piece) {
  int move_x = abs(new_column - piece->getPositionX());
  if (piece->getPositionX() > new_column) {
    move_x = abs(piece->getPositionX() - new_column);
  }
  bool err_slope = move_x == 0;
  int move_y = abs(new_row - piece->getPositionY());
  if (piece->getPositionY() > new_row) {
    move_y = abs(piece->getPositionY() - new_row);
  }
  float move_slope = 0;
  if (!err_slope) {
    move_slope = (float)move_y / (float)move_x; 
  }
  

  // pawn movement
  bool white_check = piece->isWhite() && (piece->getPositionY() == 6);
  bool black_check = !piece->isWhite() && (piece->getPositionY() == 1);

  switch (tolower(piece->getType())) {
    case 'p':
      if (move_y == 2 && move_x == 0 && (white_check || black_check)) {
        return true;
      }

      if (move_y > 1) {
        return false;
      }
      if (move_slope != 0 && target_piece->getType() == '0') {
        return false;
      }
      if (move_slope != 1 && target_piece->getType() != '0') {
        return false;
      }
      if (move_x > 0 && target_piece->getType() == '0') {
        return false;
      }
      break;
    case 'r':
      if (move_slope != 0) {
        return false;
      }
      if (move_x >= 1 && move_y >= 1) {
        return false;
      }
      break;
    case 'n':
      if (move_slope != 2 && move_slope != 0.5) {
        return false; 
      }
      if ((move_x + move_y) > 3) {
        return false;
      }
      break;
    case 'k':
      if (move_x >= 1 && move_y >= 1 && move_slope != 1) {
        return false;
      }
      if (move_y == 0 && move_x > 1) {
        return false;
      }
      if (move_x == 0 && move_y > 1) {
        return false;
      }
      break;
    case 'b':
      if (move_slope != 1) {
        return false;
      }
      break;
    case 'q':
      if (move_slope != 1 && move_slope != 0) {
        return false; 
      }
  }

  return true;
}

Piece getPieceAtGrid(int column, int row, Game *game) {
  for (int i = 0; i < game->pieces.size(); i++) {
    Piece p = game->pieces[i];
    if (p.getPositionX() == column && p.getPositionY() == row) {
      return p;
    }
  }
  return Piece(false, -1, -1, '0', 0);
}

int getPieceAtGridIndex(int column, int row, Game *game) {
  for (int i = 0; i < game->pieces.size(); i++) {
    Piece p = game->pieces[i];
    if (p.getPositionX() == column && p.getPositionY() == row) {
      return i;
    }
  }
  return -1;
}
