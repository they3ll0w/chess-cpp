#include "piece.h"

Piece::~Piece() {}

Piece::Piece(TeamColor tc, int row, int col, vector<Piece *> pieces) :
    team{tc}, row{row}, col{col}, pieces{pieces} {}

TeamColor Piece::getTeam() {
    return team;
}

void Piece::setTeam(TeamColor color) {
    team = color;
}

vector<int> Piece::getPosition() {
    return vector<int>{row, col};
}

void Piece::move(int nRow, int nCol){
    row = nRow;
    col = nCol;
}

void Piece::setUpPieces(vector<Piece *> allPieces){
    pieces = allPieces;
}

void Piece::removePiece(Piece * pc){

    for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        if (*it == pc) {
            pieces.erase(it);
            break;
        }
    }
}

void Piece::addPiece(Piece * pc) {
    pieces.push_back(pc);
}

vector<Piece *> Piece::getPieces(){
    return pieces;
}

PieceType Piece::getPieceType(){
    return PieceType::NONE;
}

vector<vector<int>> Piece::getAllCheckMoves(){

    vector<int> curPos = getPosition();
    vector<vector<int>> allMoves = getAllMoves();
    vector<vector<int>> checkMoves;

    for(auto moves: allMoves) {
        move(moves[0], moves[1]);
        if(isAttackEnemyKing()) {
            checkMoves.push_back(moves);
        }
    }

    move(curPos[0], curPos[1]);
    return checkMoves;
}

bool Piece::isChecked(){
    return false;
}

bool Piece::isAttackEnemyKing(){

    vector<int> positionEnemyKing;
    vector<vector<int>> allMoves = getAllMoves();

    for(auto piece: pieces){
        if(piece->getTeam() != getTeam() && piece->getPieceType() == PieceType::King) {
            positionEnemyKing = piece->getPosition();
            break;
        }
    }

    for(auto position: allMoves) {
        if(position == positionEnemyKing) {
            return true;
        }
    }

    return false;
}

vector<int> Piece::enemyKingPos(){
    for(auto piece: pieces) {
        if(piece->getPieceType() == PieceType::King && piece->getTeam() != getTeam()){
            return piece->getPosition();
        }
    }
    return vector<int>{0,0};
}
