#include "knight.h"

Knight::Knight(TeamColor tc, int row, int col, vector<Piece *> pieces) : Piece(tc, row, col, pieces) {}

PieceType Knight::getPieceType(){
    return PieceType::Knight;
}

vector<vector<int>> Knight::getAllMoves(){

    vector<int> curPos = getPosition();
    int curRow = curPos[0];
    int curCol = curPos[1];
    vector<vector<int>> allMoves;

    if(curRow + 2 < 8) {
        if(curCol - 1 >= 0) {
            allMoves.push_back(vector<int>{curRow + 2, curCol - 1});
        }
        if(curCol + 1 < 8) {
            allMoves.push_back(vector<int>{curRow + 2, curCol + 1});
        }
    }
    if(curRow + 1 < 8) {
        if(curCol - 2 >= 0) {
            allMoves.push_back(vector<int>{curRow + 1, curCol - 2});
        }
        if(curCol + 2 < 8) {
            allMoves.push_back(vector<int>{curRow + 1, curCol + 2});
        }
    }
    if(curRow - 1 >= 0) {
        if(curCol - 2 >= 0) {
            allMoves.push_back(vector<int>{curRow - 1, curCol - 2});
        }
        if(curCol + 2 < 8) {
            allMoves.push_back(vector<int>{curRow - 1, curCol + 2});
        }
    }
    if(curRow - 2 >= 0) {
        if(curCol - 1 >= 0) {
            allMoves.push_back(vector<int>{curRow - 2, curCol - 1});
        }
        if(curCol + 1 < 8) {
            allMoves.push_back(vector<int>{curRow - 2, curCol + 1});
        }
    }

    for(auto piece: pieces) {
        if(piece->getTeam() == getTeam()) {
            vector<int> piecePos = piece->getPosition();
            for(auto it = allMoves.begin(); it < allMoves.end(); ++it) {
                if(piecePos == *it){
                    allMoves.erase(it);
                }
            }
        }
    }
    
    return allMoves;
}

bool Knight::isAttackEnemyKing(){
    
    vector<int> kingPos = enemyKingPos();
    vector<vector<int>> allMoves = getAllMoves();

    for(auto move : allMoves) {
        if(move == kingPos) {
            return true;
        }
    }

    return false;
}

vector<vector<int>> Knight::getAllCaptureMoves(){

    vector<int> curPos = getPosition();
    int curRow = curPos[0];
    int curCol = curPos[1];
    vector<vector<int>> captureMoves;

    for(auto piece: pieces) {

        vector<int> piecePos = piece->getPosition();
        int pieceRow = piecePos[0];
        int pieceCol = piecePos[1];

        if(piece->getTeam() != getTeam()) {
            if((pieceRow == curRow + 2 && pieceCol == curCol - 1) ||
               (pieceRow == curRow + 2 && pieceCol == curCol + 1) ||
               (pieceRow == curRow + 1 && pieceCol == curCol - 2) ||
               (pieceRow == curRow + 1 && pieceCol == curCol + 2) ||
               (pieceRow == curRow - 1 && pieceCol == curCol - 2) ||
               (pieceRow == curRow - 1 && pieceCol == curCol + 2) ||
               (pieceRow == curRow - 2 && pieceCol == curCol - 1) ||
               (pieceRow == curRow - 2 && pieceCol == curCol - 1)) {
                captureMoves.push_back(piecePos);
            } 
        }
    }

    return captureMoves;
}
