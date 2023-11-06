#include "../chess.h"

Piece::Piece(bool white, int position, char piece) {
  this->white = white;
  this->position = position;
  this->piece_type = piece;
}

bool Piece::isWhite() {
  return this->white;
}

int Piece::getPosition() {
  return this->position;
}

char Piece::getType() {
  return this->piece_type;
}
