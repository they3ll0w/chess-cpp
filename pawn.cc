#include "pawn.h"

Pawn::Pawn(TeamColor tc, int row, int col, vector<Piece *> pieces) : Piece(tc, row, col, pieces) {}

PieceType Pawn::getPieceType(){
    return PieceType::Pawn;
}

vector<vector<int>> Pawn::getAllMoves(){

    vector<int> curPos = getPosition();
    vector<vector<int>> allMoves;

    if (getTeam() == TeamColor::White) {
        if (curPos[0]+1 <= 7) {
            allMoves.push_back(vector<int>{curPos[0] + 1, curPos[1]});
        }
        if(doubleMove) {
            if (curPos[0]+2 <= 7) {
                allMoves.push_back(vector<int>{curPos[0] + 2, curPos[1]});
            }
        }

        for(auto piece: pieces) {

            vector<int> piecePos = piece->getPosition();

            if(piecePos[1] == curPos[1]) {
                if(piecePos[0] == curPos[0] + 1) {
                    allMoves.erase(allMoves.begin());
                    if(doubleMove) {
                        for(auto it = allMoves.begin(); it < allMoves.end(); ++it) {
                            if(*it == vector<int>{curPos[0] + 2, curPos[1]}){
                                allMoves.erase(it);
                            }
                        }
                    }
                }
                if(doubleMove && piecePos[0] == curPos[0] + 2) {
                    for(auto it = allMoves.begin(); it < allMoves.end(); ++it) {
                        if(*it == piecePos){
                            allMoves.erase(it);
                        }
                    }
                }
            }

            if((piecePos == vector<int>{curPos[0] + 1, curPos[1] - 1} || piecePos == vector<int>{curPos[0] + 1, curPos[1] + 1}) 
                && piece->getTeam() != getTeam())
            {
                allMoves.push_back(piecePos);
            }
        }
    }

    else {  // teamcolor == black
        if (curPos[0]-1 >= 0) {
            allMoves.push_back(vector<int>{curPos[0] - 1, curPos[1]});
        }
        if(doubleMove) {
            if (curPos[0]-2 >= 0) {
                allMoves.push_back(vector<int>{curPos[0] - 2, curPos[1]});
            }
        }

        for(auto piece: pieces) {

            vector<int> piecePos = piece->getPosition();

            if(piecePos[1] == curPos[1]) {
                if(piecePos[0] == curPos[0] - 1) {
                    allMoves.erase(allMoves.begin());
                    if(doubleMove) {
                        for(auto it = allMoves.begin(); it < allMoves.end(); ++it) {
                            if(*it == vector<int>{curPos[0] - 2, curPos[1]}){
                                allMoves.erase(it);
                            }
                        }
                    }
                }
                if(doubleMove && piecePos[0] == curPos[0] - 2) {
                    for(auto it = allMoves.begin(); it < allMoves.end(); ++it) {
                        if(*it == piecePos){
                            allMoves.erase(it);
                        }
                    }
                }
            }

            if((piecePos == vector<int>{curPos[0] - 1, curPos[1] - 1} || piecePos == vector<int>{curPos[0] - 1, curPos[1] + 1}) 
                && piece->getTeam() != getTeam())
            {
                allMoves.push_back(piecePos);
            }
        }
    }
    
    return allMoves;
}

bool Pawn::isAttackEnemyKing(){

    vector<int> curPos = getPosition();
    vector<int> kingPos = enemyKingPos();

    if(getTeam() == TeamColor::White) {
        if(kingPos == vector<int>{curPos[0] + 1, curPos[1] - 1} || kingPos == vector<int>{curPos[0] + 1, curPos[1] + 1}) {
            return true;
        }
    } else {
        if(kingPos == vector<int>{curPos[0] - 1, curPos[1] - 1} || kingPos == vector<int>{curPos[0] - 1, curPos[1] + 1}) {
            return true;
        }
    }

    return false;
}

void Pawn::setDoubleMoveFalse(){
    doubleMove = false;
}

void Pawn::setEnPassant(bool b){
    canBeEnPassant = b;
}

vector<vector<int>> Pawn::getAllCheckMoves(){

    vector<int> curPos = getPosition();
    vector<int> kingPos = enemyKingPos();
    vector<vector<int>> checkMoves;

    for(auto moves: getAllMoves()){
        move(moves[0], moves[1]);
        if(isAttackEnemyKing()){
            checkMoves.push_back(moves);
        }
    }

    move(curPos[0], curPos[1]);
    
    return checkMoves;
}

vector<vector<int>> Pawn::getAllCaptureMoves(){

    vector<int> curPos = getPosition();
    vector<vector<int>> captureMoves;
    
    for(auto piece: pieces) {

        if(piece->getTeam() != getTeam()){

            vector<int> piecePos = piece->getPosition();

            if(getTeam() == TeamColor::White){
                if(piecePos == vector<int>{curPos[0] + 1, curPos[1] - 1} || piecePos == vector<int>{curPos[0] + 1, curPos[1] + 1}) {
                    captureMoves.push_back(piecePos);
                }     
            } else {
                if(piecePos == vector<int>{curPos[0] - 1, curPos[1] - 1} || piecePos == vector<int>{curPos[0] - 1, curPos[1] + 1}) {
                    captureMoves.push_back(piecePos);
                }
            }

        }

    }
    
    return captureMoves;

}

bool Pawn::getEnPassant(){
    return canBeEnPassant;
}
