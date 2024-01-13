#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

using namespace std;

class Pawn : public Piece {
    bool doubleMove = true;
    bool canBeEnPassant = false;
    public:
        Pawn(TeamColor tc, int row, int col, vector<Piece *> pieces);
        PieceType getPieceType() override;
        vector<vector<int>> getAllMoves() override;
        vector<vector<int>> getAllCheckMoves() override;
        vector<vector<int>> getAllCaptureMoves() override;
        bool isAttackEnemyKing() override;
        void setDoubleMoveFalse();
        void setEnPassant(bool b);
        bool getEnPassant();
};

#endif
