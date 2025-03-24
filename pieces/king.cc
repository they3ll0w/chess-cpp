#include "king.h"
#include "rook.h"

King::King(TeamColor tc, int row, int col, vector<Piece *> pieces) : Piece(tc, row, col, pieces) {}

vector<vector<int>> King::removeCommonElements(vector<vector<int>>& ourMoves, vector<vector<int>> otherMoves) {

    // Use iterators for safe removal
    for(auto it = ourMoves.begin(); it != ourMoves.end();) {
        auto move = *it;

        auto findIt = find(otherMoves.begin(), otherMoves.end(), move);

        if (findIt != otherMoves.end()) {
            it = ourMoves.erase(it);
        } else {
            ++it;
        }
    }

    return ourMoves;
}

PieceType King::getPieceType() {
    return PieceType::King;
}

vector<vector<int>> King::getAllMoves(){

    vector<vector<int>> allMoves;
    vector<int> curPosition = getPosition();
    //All the moves the king can make
    if(curPosition[0] != 0 && curPosition[1] != 0){
        allMoves.push_back(vector<int>{curPosition[0] - 1, curPosition[1] - 1});
    }
    if(curPosition[0] != 0){
        allMoves.push_back(vector<int>{curPosition[0] - 1, curPosition[1]});
    }
    if(curPosition[0] != 0 && curPosition[1] != 7){
        allMoves.push_back(vector<int>{curPosition[0] - 1, curPosition[1] + 1});
    }
    if(curPosition[1] != 0){
        allMoves.push_back(vector<int>{curPosition[0], curPosition[1] - 1});
    }
    if(curPosition[1] != 7){
        allMoves.push_back(vector<int>{curPosition[0], curPosition[1] + 1});
    }
    if(curPosition[0] != 7 && curPosition[1] != 0){
        allMoves.push_back(vector<int>{curPosition[0] + 1, curPosition[1] - 1});
    }
    if(curPosition[0] != 7){
        allMoves.push_back(vector<int>{curPosition[0] + 1, curPosition[1]});
    }
    if(curPosition[0] != 7 && curPosition[1] != 7){
        allMoves.push_back(vector<int>{curPosition[0] + 1, curPosition[1] + 1});
    }

    for(auto piece : pieces) {

        vector<int> piecePos = piece->getPosition();

        if(piece->getTeam() != getTeam() && piece->getPieceType() != PieceType::King){

            vector<vector<int>> removeMoves;

            if (piece->getPieceType() == PieceType::Pawn) {
                vector<int> pawnPos = piece->getPosition();
                int r = pawnPos[0];
                int c = pawnPos[1];
                if (piece->getTeam() == TeamColor::White) {
                    if (r+1<=7 && c-1>=0) removeMoves.push_back({r+1, c-1});
                    if (r+1<=7 && c+1<=7) removeMoves.push_back({r+1, c+1});
                } else {
                    if (r-1>=0 && c+1<=7) removeMoves.push_back({r-1, c+1});
                    if (r-1>=0 && c-1>=0) removeMoves.push_back({r-1, c-1});
                }
            }
            else removeMoves = piece->getAllMoves();

            allMoves = removeCommonElements(allMoves, removeMoves);

            for(auto it = allMoves.begin(); it != allMoves.end(); ++it) {
                if(piecePos == *it) {
                    move(piecePos[0], piecePos[1]);
                    if(isChecked()){
                        allMoves.erase(it);
                    }
                    move(curPosition[0], curPosition[1]);
                }
            }

        }
        // we can not call king::getAllMoves in king::getAllMoves
        else if (piece->getTeam() != getTeam() && piece->getPieceType() == PieceType::King) {
            vector<int> otherKingPos = piece->getPosition();
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if ((i != 0) || (j != 0)) {
                        vector<int> thisKingMove = {otherKingPos[0]+i, otherKingPos[1]+j};
                        auto it = find(allMoves.begin(), allMoves.end(), thisKingMove);
                        if (it != allMoves.end()) {
                            allMoves.erase(it);
                        }
                    }
                }
            }
        }

        else {

            for (auto it = allMoves.begin(); it != allMoves.end(); ++it) {
                if (*it == piecePos) {
                    allMoves.erase(it);
                    break;
                }
            }

        }
    
    }

    return allMoves;
}

bool King::isAttackEnemyKing() {
    return false;
}

bool King::isChecked() {
    
    for(auto piece: pieces) {
        if(piece->getTeam() != getTeam()) {
            if(piece->isAttackEnemyKing()){
                return true;
            }
        }
    }

    return false;
}

vector<vector<int>> King::getAllCheckMoves() {
    return vector<vector<int>>();
}

vector<vector<int>> King::getAllCaptureMoves(){

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

bool King::getNoMove(){
    return noMove;
}

void King::setNoMoveFalse(){
    noMove = false;
}
