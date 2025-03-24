#ifndef __KING_H__
#define __KING_H__

#include "piece.h"
#include <algorithm>

using namespace std;

class King : public Piece {
        //removeCommonElements removes the common elements between ourMoves and otherMoves from ourMoves
        vector<vector<int>> removeCommonElements(vector<vector<int>> & ourMoves, vector<vector<int>> otherMoves);
        bool noMove = true;
    public:
        King(TeamColor tc, int row, int col, vector<Piece *> pieces);
        PieceType getPieceType() override;
        bool getNoMove();
        vector<vector<int>> getAllMoves() override;
        bool isAttackEnemyKing() override;
        bool isChecked();
        vector<vector<int>> getAllCheckMoves() override;
        vector<vector<int>> getAllCaptureMoves() override;
        void setNoMoveFalse();
};

#endif
