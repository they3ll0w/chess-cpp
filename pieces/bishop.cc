#include "bishop.h"
#include <stdlib.h>

Bishop::Bishop(TeamColor tc, int row, int col, vector<Piece *> pieces) : Piece(tc, row, col, pieces) {}

bool Bishop::onPath(vector<int> pos){

    vector<int> curPos = getPosition();

    int rowDiff = abs(curPos[0] - pos[0]);
    int colDiff = abs(curPos[1] - pos[1]);

    return rowDiff == colDiff;
}

PieceType Bishop::getPieceType(){
    return PieceType::Bishop;
}

vector<vector<int>> Bishop::getAllMoves(){

    vector<int> curPos = getPosition();
    vector<vector<int>> allMoves;
    int limitUpLeft = 0;
    int limitUpRight = 7;
    int limitLowLeft = 0;
    int limitLowRight = 7;

    for(auto piece: pieces) {

        vector<int> piecePos = piece->getPosition();
        int pieceRow = piecePos[0];
        int pieceCol = piecePos[1];

        if(onPath(piecePos)){
            if(curPos[1] > pieceCol){
                //left
                if(curPos[0] > pieceRow){
                    //low
                    if(piece->getTeam() != getTeam()){
                        limitLowLeft = max(pieceCol, limitLowLeft);
                    } else {
                        limitLowLeft = max(pieceCol + 1, limitLowLeft);
                    }
                } else {
                    //high
                     if(piece->getTeam() != getTeam()){
                        limitUpLeft = max(pieceCol, limitUpLeft);
                    } else {
                        limitUpLeft = max(pieceCol + 1, limitUpLeft);
                    }
                }
            } else {
                //right
                if(curPos[0] > pieceRow){
                    //low
                    if(piece->getTeam() != getTeam()){
                        limitLowRight = min(pieceCol, limitLowRight);
                    } else {
                        limitLowRight = min(pieceCol - 1, limitLowRight);
                    }
                } else {
                    //high
                     if(piece->getTeam() != getTeam()){
                        limitUpRight = min(pieceCol, limitUpRight);
                    } else {
                        limitUpRight = min(pieceCol - 1, limitUpRight);
                    }
                }
            }
        }
    }

    for(int i = limitUpLeft; i < curPos[1]; ++i) {
        int rowVal = curPos[0] + curPos[1] - i;
        if(rowVal < 8 && rowVal >= 0) {
            allMoves.push_back(vector<int>{rowVal, i});
        }
    }

    for(int i = limitUpRight; i > curPos[1]; --i) {
        int rowVal = curPos[0] + abs(curPos[1] - i);
        if(rowVal < 8 && rowVal >= 0) {
            allMoves.push_back(vector<int>{rowVal, i});
        }
    }

    for(int i = limitLowLeft; i < curPos[1]; ++i) {
        int rowVal = curPos[0] - abs(curPos[1] - i);
        if(rowVal < 8 && rowVal >= 0) {
            allMoves.push_back(vector<int>{rowVal, i});
        }
    }

    for(int i = limitLowRight; i > curPos[1]; --i) {
        int rowVal = curPos[0] - abs(curPos[1] - i);
        if(rowVal < 8 && rowVal >= 0) {
            allMoves.push_back(vector<int>{rowVal, i});
        }
    }

    return allMoves;
}

bool Bishop::isAttackEnemyKing(){

    vector<int> kingPos = enemyKingPos();
    vector<vector<int>> allMoves = getAllMoves();

    for(auto move : allMoves) {
        if(move == kingPos) {
            return true;
        }
    }

    return false;
    
}

vector<vector<int>> Bishop::getAllCaptureMoves() {

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
