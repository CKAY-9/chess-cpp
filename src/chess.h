#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <vector>
#include <raylib.h>

class Piece {
  private:
    bool white;
    int position;
    char piece_type;
  public:
    Piece(bool white, int position, char piece);
    bool isWhite();
    int getPosition();
    char getType();
};

class Game {
  private:
    std::vector<Piece> pieces;
  public:
    Game(std::string fen_string);
    std::vector<Piece> getPieces();
    void read_fen_string(std::string fen_string);
};

void drawChessBoard(int window_width, int window_height);
void drawPieces(int window_width, int window_height, Game *game);

#endif
