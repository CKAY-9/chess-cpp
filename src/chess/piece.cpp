#include "../chess.h"

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

Piece getPieceAtGrid(int column, int row, Game *game) {
  for (int i = 0; i < game->getPieces().size(); i++) {
    Piece p = game->getPieces()[i];
    if (p.getPositionX() == column && p.getPositionY() == row) {
      return p;
    }
  }
  return Piece(false, -1, -1, '0', 0);
}

int getPieceAtGridIndex(int column, int row, Game *game) {
  for (int i = 0; i < game->getPieces().size(); i++) {
    Piece p = game->getPieces()[i];
    if (p.getPositionX() == column && p.getPositionY() == row) {
      return i;
    }
  }
  return -1;
}
