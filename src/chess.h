#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <vector>
#include <raylib.h>

class Piece {
  private:
    bool white;
    int position[2];
    char piece_type;
    int sprite_position;
  public:
    Piece(bool white, int x, int y, char piece, int sprite_position);
    bool isWhite();
    int getPositionX();
    int getPositionY();
    char getType();
    int getSpritePosition(); 
};

class Game {
  public:
    std::vector<Piece> pieces;
    Texture2D piece_sprites[12] = {};
    Game(std::string fen_string);
    std::vector<Piece> getPieces();
    void read_fen_string(std::string fen_string);
    void load_piece_sprites(); 
};

void drawChessBoard(int window_width, int window_height);
void drawPieces(int window_width, int window_height, Game *game, Piece *piece);

Piece getPieceAtGrid(int column, int row, Game *game);
int getPieceAtGridIndex(int column, int row, Game *game);
Piece getPieceAtMousePosition(int window_width, int window_height, Game *game);

void handleInteraction(int window_width, int window_height, Game *game, Piece *piece);

#endif
