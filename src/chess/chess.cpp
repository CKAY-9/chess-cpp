#include "../chess.h"
#include <cmath>
#include <iostream>
#include <raylib.h>
#include <cctype>

void Game::read_fen_string(std::string fen_string) {
  int row = 0;
  int column = 0;
  for (int i = 0; i < fen_string.length(); i++) {
    char c = fen_string[i];
    if (isdigit(c)) {
      int rows_to_skip = c - '0';
      column += rows_to_skip;
      continue;
    }

    std::cout << column << ", " << row << " | ";

    int sprite_index = 0;
    switch (c) {
      case 'p':
        sprite_index = 2;
        break;
      case 'P':
        sprite_index = 3;
        break;
      case 'b':
        sprite_index = 0;
        break;
      case 'B':
        sprite_index = 1;
        break;
      case 'k':
        sprite_index = 4;
        break;
      case 'K':
        sprite_index = 5;
        break;
      case 'n':
        sprite_index = 6;
        break;
      case 'N':
        sprite_index = 7;
        break;
      case 'q':
        sprite_index = 10;
        break;
      case 'Q':
        sprite_index = 11;
        break;
      case 'r':
        sprite_index = 8;
        break;
      case 'R':
        sprite_index = 9;
        break;
    }

    this->pieces.push_back(Piece(isupper(c), column, row, c, sprite_index));

    column++;
    if (column > 8) {
      row++;
      column = 0;
    }
  } 
}

void Game::load_piece_sprites() {
  this->piece_sprites[0] = LoadTexture("assets/bb.png");
  this->piece_sprites[1] = LoadTexture("assets/wb.png");
  this->piece_sprites[2] = LoadTexture("assets/bp.png");
  this->piece_sprites[3] = LoadTexture("assets/wp.png");
  this->piece_sprites[4] = LoadTexture("assets/bk.png");
  this->piece_sprites[5] = LoadTexture("assets/wk.png");
  this->piece_sprites[6] = LoadTexture("assets/bn.png");
  this->piece_sprites[7] = LoadTexture("assets/wn.png");
  this->piece_sprites[8] = LoadTexture("assets/br.png");
  this->piece_sprites[9] = LoadTexture("assets/wr.png");
  this->piece_sprites[10] = LoadTexture("assets/bq.png");
  this->piece_sprites[11] = LoadTexture("assets/wq.png");
}

Game::Game(std::string fen_string) {
  std::cout << "Starting chess game with FEN: " << fen_string << std::endl;
  this->read_fen_string(fen_string);
  this->load_piece_sprites();
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

void drawPieces(int window_width, int window_height, Game *game, Piece *piece) {
  float grid_width = (float)window_width / 8;
  float grid_height = (float)window_height / 8;

  if (piece != 0 && piece->getType() != '0' && IsMouseButtonDown(0)) {
    DrawTexture(game->piece_sprites[piece->getSpritePosition()], GetMouseX() - 30, GetMouseY() - 30, WHITE);
  }

  for (int i = 0; i < game->getPieces().size(); i++) {
    Piece p = game->getPieces()[i];

    if (piece != 0 
      && piece->getType() == p.getType() 
      && piece->getPositionY() == p.getPositionY()
      && piece->getPositionX() == p.getPositionX()
      && IsMouseButtonDown(0)) {
      continue;
    }
    DrawTexture(game->piece_sprites[p.getSpritePosition()], grid_width * p.getPositionX(), grid_height * p.getPositionY(), WHITE);
  }
}
