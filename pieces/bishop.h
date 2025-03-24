#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "piece.h"

using namespace std;

class Bishop : public Piece {
        bool onPath(vector<int> pos);
    public:
        Bishop(TeamColor tc, int row, int col, vector<Piece *> pieces);
        PieceType getPieceType() override;
        vector<vector<int>> getAllMoves() override;
        bool isAttackEnemyKing() override;
        vector<vector<int>> getAllCaptureMoves() override;
};

#endif
