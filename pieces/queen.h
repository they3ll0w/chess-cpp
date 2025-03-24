#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

using namespace std;

class Queen : public Piece {
        //onPath returns true if pos is in the diagonals of the piece
        bool onPath(vector<int> pos);
    public:
        Queen(TeamColor tc, int row, int col, vector<Piece *> pieces);
        PieceType getPieceType() override;
        vector<vector<int>> getAllMoves() override;
        bool isAttackEnemyKing() override;
        vector<vector<int>> getAllCaptureMoves() override;
};

#endif
