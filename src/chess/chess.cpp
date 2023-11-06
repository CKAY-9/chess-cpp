#include "../chess.h"
#include <cmath>
#include <iostream>
#include <raylib.h>
#include <cctype>

void Game::read_fen_string(std::string fen_string) {
  int position = 0;
  for (int i = 0; i < fen_string.length(); i++) {
    char c = fen_string[i];
    if (isdigit(c)) {
      int columns_to_skip = c - '0';
      position += columns_to_skip;
      continue;
    }

    switch (c) {
      case '/':
        continue;
      case 'p':
        this->pieces.push_back(Piece(false, position, 'p'));
        break;
      case 'P':
        this->pieces.push_back(Piece(true, position, 'P'));
        break;
      case 'b':
        this->pieces.push_back(Piece(false, position, 'b'));
        break;
      case 'B':
        this->pieces.push_back(Piece(true, position, 'B'));
        break;
      case 'n':
        this->pieces.push_back(Piece(false, position, 'n'));
        break;
      case 'N':
        this->pieces.push_back(Piece(true, position, 'N'));
        break;
      case 'r':
        this->pieces.push_back(Piece(false, position, 'r'));
        break;
      case 'R':
        this->pieces.push_back(Piece(true, position, 'R'));
        break;
      case 'k':
        this->pieces.push_back(Piece(false, position, 'k'));
        break;
      case 'K':
        this->pieces.push_back(Piece(true, position, 'K'));
        break;
      case 'q':
        this->pieces.push_back(Piece(false, position, 'q'));
        break;
      case 'Q':
        this->pieces.push_back(Piece(true, position, 'Q'));
        break;
    }

    position += 1;
  } 
}

Game::Game(std::string fen_string) {
  std::cout << "Starting chess game with FEN: " << fen_string << std::endl;
  this->read_fen_string(fen_string);
}

std::vector<Piece> Game::getPieces() {
  return this->pieces;
}

void drawChessBoard(int window_width, int window_height) {
  float grid_width = (float)window_width / 8;
  float grid_height = (float)window_height / 8;
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      Color color = MAROON;
      if (x % 2 == 0) {
        color = WHITE;
      }
      DrawRectangle(x * grid_width - (grid_width * (y % 2 == 1)), y * grid_height, grid_width, grid_height, color);
    }
  }
}

void drawPieces(int window_width, int window_height, Game *game) {
  float grid_width = (float)window_width / 8;
  float grid_height = (float)window_height / 8;

  int row = 0;
  int column = 0;
  for (int i = 0; i < game->getPieces().size(); i++) {
    Piece p = game->getPieces()[i];
    std::string piece = "";
    piece.push_back(p.getType());

    DrawText(piece.c_str(), row * grid_width + (grid_width / 2 - 10), column * grid_height + (grid_height / 2 - 10), 20, BLACK);

    row++;
    column = std::floor(p.getPosition() / 8);

    if (row % 8 == 0) {
      row = 0;
    }
  }
}
