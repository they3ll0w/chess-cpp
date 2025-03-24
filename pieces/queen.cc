#include "queen.h"
#include <stdlib.h>

Queen::Queen(TeamColor tc, int row, int col, vector<Piece *> pieces) : Piece(tc, row, col, pieces) {}

bool Queen::onPath(vector<int> pos){
    vector<int> curPos = getPosition();

    int rowDiff = abs(curPos[0] - pos[0]);
    int colDiff = abs(curPos[1] - pos[1]);

    return rowDiff == colDiff;
}

PieceType Queen::getPieceType(){
    return PieceType::Queen;
}

vector<vector<int>> Queen::getAllMoves(){

    vector<int> curPos = getPosition();
    vector<vector<int>> allMoves;

//create the limits

    //Straight lines
    int limitRowLeft = 0;
    int limitRowRight = 7;
    int limitColDown = 0;
    int limitColUp = 7;
    //Diagonals
    int limitUpLeft = 0;
    int limitUpRight = 7;
    int limitLowLeft = 0;
    int limitLowRight = 7;


    for(auto piece: pieces) {

        vector<int> piecePos = piece->getPosition();
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

    //Setup the allMoves vector

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

    for(int i = limitUpLeft; i < curPos[1]; ++i) {
        int rowVal = curPos[0] + abs(curPos[1] - i);
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

bool Queen::isAttackEnemyKing(){
    vector<int> kingPos = enemyKingPos();
    vector<vector<int>> allMoves = getAllMoves();

    for(auto move : allMoves) {
        if(move == kingPos) {
            return true;
        }
    }

    return false;

}

vector<vector<int>> Queen::getAllCaptureMoves() {
    
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
