#include "cell.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"

Cell::Cell(int row, int col): row{row}, col{col} {}

Cell::~Cell(){
    if (p) delete p;
}

GridColor Cell::getGridColor(){
    return tc;
}

void Cell::setGridColor(GridColor color){
    tc = color;
}

void Cell::setPiece(Piece *piece) {
    if (p)  delete p; // prevent memory leak
    Piece *deletedP = p;
    p = piece;
    p->removePiece(deletedP);
    if (p) {
        for(auto &thisPiece: p->getPieces()){
            thisPiece->addPiece(p);
        }
    }
    notifyObservers();
}

void Cell::detachPiece() {

    for(auto &piece: p->getPieces()){
        piece->removePiece(p);
    }

    p = nullptr;
    notifyObservers();
}
int Cell::getRow(){
    return row;
}

int Cell::getCol(){
    return col;
}

Piece *Cell::getPiece(){
    return p;
}

PieceType Cell::getPieceType(){
    if (!p) return PieceType::NONE;
    return p->getPieceType();
}

void Cell::attach(Observer *o) {
    observers.emplace_back(o);
}

void Cell::notifyObservers() {
    for ( auto &n : observers ) {
        n->notify(*this);
    }
}

// determine if the player can promote a pawn in board.cc (player.cc)
void Cell::promote(PieceType pt) {
    Piece *piece = p;
    if (row != 0 && row != 7) {
        return;
    }
    if(pt == PieceType::Queen) {
        Queen *queen = new Queen(p->getTeam(), p->getPosition()[0], p->getPosition()[1], p->getPieces());
        Piece *teeeemp = getPiece();
        detachPiece();
        setPiece(queen);
    }
    else if (pt == PieceType::Knight) {
        Knight *knight = new Knight(p->getTeam(), p->getPosition()[0], p->getPosition()[1], p->getPieces());
        Piece *teeeemp = getPiece();
        detachPiece();

        setPiece(knight);
    }
    else if (pt == PieceType::Rook) {
        Rook *rook = new Rook(p->getTeam(), p->getPosition()[0], p->getPosition()[1], p->getPieces());
        Piece *teeeemp = getPiece();
        detachPiece();
        setPiece(rook);
    }
    else if (pt == PieceType::Bishop) {
        Bishop *bishop = new Bishop(p->getTeam(), p->getPosition()[0], p->getPosition()[1], p->getPieces());
        Piece *teeeemp = getPiece();
        detachPiece();
        setPiece(bishop);
    }
}
