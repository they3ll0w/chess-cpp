#ifndef __PIECE_H__
#define __PIECE_H__

#include <vector>

using namespace std;

enum class PieceType { Knight, Pawn, King, Bishop, Queen, Rook, NONE };
enum class TeamColor { White, Black };

class Piece{
        TeamColor team;
        int row, col;
    protected:
        vector<Piece *> pieces;

    public:
        virtual ~Piece();
        Piece(TeamColor tc, int row, int col, vector<Piece *> pieces);
        TeamColor getTeam();
        void setTeam(TeamColor color);
        vector<int> getPosition();
        void move(int nRow, int nCol);
        void setUpPieces(vector<Piece *> allPieces);
        void removePiece(Piece * pc);
        void addPiece(Piece *pc);
        vector<Piece *> getPieces();
    
        virtual PieceType getPieceType();
        virtual vector<vector<int>> getAllMoves() = 0;
        virtual vector<vector<int>> getAllCheckMoves();
        virtual vector<vector<int>> getAllCaptureMoves() = 0;
        virtual bool isAttackEnemyKing();
        virtual vector<int> enemyKingPos();
        virtual bool isChecked();
};

#endif
