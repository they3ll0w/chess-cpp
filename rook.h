#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

using namespace std;

class Rook : public Piece {
        bool noMove = true;
    public:
        Rook(TeamColor tc, int row, int col, vector<Piece *> pieces);
        PieceType getPieceType() override;
        vector<vector<int>> getAllMoves() override;
        bool isAttackEnemyKing() override;
        vector<vector<int>> getAllCaptureMoves() override;
        bool getNoMove();
        void setNoMoveFalse();
};

#endif
