#include "rook.h"

Rook::Rook(TeamColor tc, int row, int col, vector<Piece *> pieces) : Piece(tc, row, col, pieces) {}

PieceType Rook::getPieceType(){
    return PieceType::Rook;
}

vector<vector<int>> Rook::getAllMoves(){

    vector<int> curPos = getPosition();
    vector<vector<int>> allMoves;
    int limitRowLeft = 0;
    int limitRowRight = 7;
    int limitColDown = 0;
    int limitColUp = 7;

    for(auto piece: pieces) {

        int pieceRow = piece->getPosition()[0];
        int pieceCol = piece->getPosition()[1];

        if(pieceRow == curPos[0]){
            if(pieceCol > curPos[1]){
                if(piece->getTeam() == getTeam()) {
                    limitRowRight = min(limitRowRight, pieceCol - 1);
                } else {
                    limitRowRight = min(limitRowRight, pieceCol);
                }
            } else {
                if(piece->getTeam() == getTeam()){
                    limitRowLeft = max(limitRowLeft, pieceCol + 1);
                } else {
                    limitRowLeft = max(limitRowLeft, pieceCol);
                }
            }
        }

        if(pieceCol == curPos[1]) {
            if(pieceRow > curPos[0]){
                if(piece->getTeam() == getTeam()) {
                    limitColUp = min(limitColUp, pieceRow - 1);
                } else {
                    limitColUp = min(limitColUp, pieceRow);
                }
            } else {
                if(piece->getTeam() == getTeam()) {
                    limitColDown = max(limitColDown, pieceRow + 1);
                } else {
                    limitColDown = max(limitColDown, pieceRow);
                }
            }
        }

    }

    for(int i = limitColDown; i <= limitColUp; ++i) {
        if(i != curPos[0]) {
            allMoves.push_back(vector<int>{i, curPos[1]});
        }
    }

    for(int j = limitRowLeft; j <= limitRowRight; ++j) {
        if(j != curPos[1]){
            allMoves.push_back(vector<int>{curPos[0], j});
        }
        
    }

    return allMoves;
}

bool Rook::isAttackEnemyKing(){

    vector<int> kingPos = enemyKingPos();
    vector<vector<int>> allMoves = getAllMoves();

    for(auto move : allMoves) {
        if(move == kingPos) {
            return true;
        }
    }

    return false;
    
}

vector<vector<int>> Rook::getAllCaptureMoves(){

    vector<int> curPos = getPosition();
    vector<vector<int>> captureMoves;
    vector<vector<int>> allMoves = getAllMoves();

    for(auto piece: pieces) {
        if(piece->getTeam() != getTeam()) {
            vector<int> piecePos = piece->getPosition();
            for(auto move: allMoves) {
                if(piecePos == move) {
                    captureMoves.push_back(piecePos);
                }
            }
        }
    }

    return captureMoves;

}

bool Rook::getNoMove(){
    return noMove;
}

void Rook::setNoMoveFalse(){
    noMove = false;
}
