#ifndef __CELL_H__
#define __CELL_H__

#include <vector>
#include "observer.h"
#include "piece.h"

using namespace std;

enum class GridColor { WHITE, BLACK };

class Cell {
    Piece *p = nullptr;
    int row;
    int col;
    GridColor tc;
    vector<Observer *> observers;

  public:
    Cell(int row, int col);
    ~Cell();
    GridColor getGridColor();
    void setGridColor(GridColor color);
    void setPiece(Piece *p);
    void detachPiece();
    int getRow();
    int getCol();
    Piece *getPiece();
    PieceType getPieceType();
    void attach(Observer *o);
    void promote(PieceType pt);
    void notifyObservers();
};

#endif
