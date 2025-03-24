#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

using namespace std;

class Knight : public Piece {
    public:
        Knight(TeamColor tc, int row, int col, vector<Piece *> pieces);
        PieceType getPieceType() override;
        vector<vector<int>> getAllMoves() override;
        bool isAttackEnemyKing() override;
        vector<vector<int>> getAllCaptureMoves() override;
};

#endif
