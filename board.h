#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <iostream>
#include <algorithm>
#include "cell.h"
#include "textDisplay.h"
#include "graphicsDisplay.h"

using namespace std;

class Board {
  vector<vector<Cell>> theBoard;  
  TextDisplay td;
  GraphicsDisplay gd;
  TeamColor turn;
public:
    Board(int graphicsWindowSize);
    ~Board();
    void init();
    void initDefault();
    bool move(vector<int>, vector<int>);
    bool moveForComputer(vector<int> start, vector<int> end);
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    void toggleTurn();
    TeamColor getCheckedPlayer();
    friend ostream &operator<<(ostream &out, const Board &b);
    void resign();
    void setPiece(int row, int col, Piece *p);
    void detachPiece(int row, int col);
    void deletePiece(int row, int col);
    Piece *getPiece(int row, int col);
    vector<Piece *> getAllWhitePieces();
    vector<Piece *> getAllBlackPieces();
    vector<Piece *> getAllKingPieces();
    vector<Piece *> getAllPieces();
    bool promote(int row, int col , char type);
};

#endif



