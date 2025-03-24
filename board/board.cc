#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"

using namespace std;

Board::Board(int graphicsWinowSize): 
    gd(graphicsWinowSize),
    turn{TeamColor::White} {}

Board::~Board() {
    theBoard.clear();
}

// calls this at the start of the program, and after each game ends
void Board::init() {
    // clearing the current board
    theBoard.clear();

    turn = TeamColor::White;
    // initing cells
    for (int i = 0; i < 8; i++) { // each row
        vector<Cell> temp;
        for (int j = 0; j < 8; j++) { // each col
            Cell cell(i,j); // temp obj of this cell
            if ((i + j) % 2 == 0) {
                cell.setGridColor(GridColor::WHITE);
            } else {
                cell.setGridColor(GridColor::BLACK);
            }
            // add observer to this cell
            cell.attach(&td);
            cell.attach(&gd);

            temp.push_back(cell);
        }
        theBoard.push_back(temp);
    }
    // notify all observers
    for ( auto &row : theBoard ) {
        for ( auto &cell : row ) {
            cell.notifyObservers();
        }
    }
}

void Board::initDefault() {
    vector<Piece *> pieces;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Cell cell(i, j);

            if (i == 1 || i == 6) {
                Pawn *pawn = new Pawn(TeamColor::White, i, j, vector<Piece *>());
                pawn->setTeam((i%2) ? TeamColor::White : TeamColor::Black);
                theBoard[i][j].setPiece(pawn);
                pieces.push_back(pawn);
            }

            if (i == 0 || i == 7) {
                if (j == 0 || j == 7) {
                    Rook *rook = new Rook(TeamColor::White, i, j, vector<Piece *>());
                    rook->setTeam((!(i == 0)) ? TeamColor::Black : TeamColor::White);
                    theBoard[i][j].setPiece(rook);
                    pieces.push_back(rook);
                }
                if (j == 1 || j == 6){
                     Knight *knight  = new Knight(TeamColor::White, i, j, vector<Piece *>());
                     knight->setTeam((!(i == 0)) ? TeamColor::Black : TeamColor::White);
                     theBoard[i][j].setPiece(knight);
                     pieces.push_back(knight);
                 }
                 if (j == 2 || j == 5){
                     Bishop *bishop = new Bishop(TeamColor::White, i, j, vector<Piece *>());
                     bishop->setTeam((!(i == 0)) ? TeamColor::Black : TeamColor::White);
                     theBoard[i][j].setPiece(bishop);
                     pieces.push_back(bishop);
                 }
                if (j == 3) {
                     Queen *queen = new Queen(TeamColor::White, i, j, vector<Piece *>());
                     queen->setTeam((!(i == 0)) ? TeamColor::Black : TeamColor::White);
                     theBoard[i][j].setPiece(queen);
                    pieces.push_back(queen);
                 }
                if (j == 4) {
                    King *king = new King(TeamColor::White, i, j, vector<Piece *>());
                    king->setTeam((!(i == 0)) ? TeamColor::Black : TeamColor::White);
                    theBoard[i][j].setPiece(king);
                    pieces.push_back(king);
                }
            }
        }
    }

    for ( auto &n : pieces ) {
        n->setUpPieces(pieces);
        n->removePiece(n);
    }

}

void Board::setPiece(int row, int col, Piece *p) {
    theBoard[row][col].setPiece(p);
}

void Board::detachPiece(int row, int col) {
    theBoard[row][col].detachPiece();
}

void Board::deletePiece(int row, int col) {
    Piece *tempPiece = theBoard[row][col].getPiece();
    theBoard[row][col].detachPiece();
}

Piece *Board::getPiece(int row, int col) {
    return theBoard[row][col].getPiece();
}

bool Board::move(vector<int> start, vector<int> end) {

    Piece *p = theBoard[start[0]][start[1]].getPiece();

    if (p == nullptr) {
        cerr << "square has no piece" << endl;
        return false;
    }

    if (p->getTeam() != turn) {
        cerr << "you are trying to move your opponent's piece" << endl;
        return false;
    }

    if(isCheck()){
        p->move(end[0],end[1]);
        vector<Piece *> allPieces = p->getPieces();
        allPieces.push_back(p);
        for(auto piece: allPieces){    
            if(piece->getTeam() == p->getTeam() && piece->isChecked()){
                cerr << "King is being checked. Protect your king." << endl;
                p->move(start[0], start[1]);
                return false;
            }
        }
        p->move(start[0], start[1]);
    }

    //check if castling is valid
    if(p->getPieceType() == PieceType::King && start[0] == end[0] && abs(start[1] - end[1]) == 2){

        vector<int> kingPos = p->getPosition();

        if(static_cast<King *>(p)->getNoMove() && end[1] > start[1]){

            Piece * rookRight = getPiece(kingPos[0], 7);

            if(!rookRight || rookRight->getPieceType() != PieceType::Rook){
                cerr << "invalid castling: No rook at corner" << endl;
                return false;
            }

            if(!static_cast<Rook *>(rookRight)->getNoMove()){
                cerr << "invalid castling: Rook already moved" << endl;
                return false;
            }

            for(int i = 5; i <= 6; ++i){
                Piece * checkEmpty = getPiece(kingPos[0], i);
                if(checkEmpty){
                    cerr << "invalid castling: Piece in the way" << endl;
                    p->move(kingPos[0], kingPos[1]);
                    return false;
                }
                p->move(kingPos[0], i);
                if(p->isChecked()){
                    cerr << "invalid castling: King would be checked" << endl;
                    p->move(kingPos[0], kingPos[1]);
                    return false;               
                }
            }

            theBoard[start[0]][start[1]].detachPiece();
            p->move(end[0], end[1]);
            theBoard[end[0]][end[1]].setPiece(p);

            theBoard[start[0]][7].detachPiece();
            rookRight->move(end[0], 5);
            theBoard[end[0]][5].setPiece(rookRight);

            static_cast<King *>(p)->setNoMoveFalse();
            static_cast<Rook *>(rookRight)->setNoMoveFalse();

            return true;

        } else if (static_cast<King *>(p)->getNoMove() && end[1] < start[1]) {
            Piece * rookLeft = getPiece(kingPos[0], 0);

            if(!rookLeft || rookLeft->getPieceType() != PieceType::Rook){
                cerr << "invalid castling: No rook at corner" << endl;
                return false;
            }

            if(!static_cast<Rook *>(rookLeft)->getNoMove()){
                cerr << "invalid castling: Rook already moved" << endl;
                return false;
            }

            for(int i = 1; i <= 3; ++i){
                Piece * checkEmpty = getPiece(kingPos[0], i);
                if(checkEmpty){
                    cerr << "invalid castling: Piece in the way" << endl;
                    p->move(kingPos[0], kingPos[1]);
                    return false;
                }
                p->move(kingPos[0], i);
                if(p->isChecked()){
                    cerr << "invalid castling: King would be checked" << endl;
                    p->move(kingPos[0], kingPos[1]);
                    return false;               
                }
            }

            theBoard[start[0]][start[1]].detachPiece();
            p->move(end[0], end[1]);
            theBoard[end[0]][end[1]].setPiece(p);

            theBoard[start[0]][0].detachPiece();
            rookLeft->move(end[0], 3);
            theBoard[end[0]][3].setPiece(rookLeft);

            static_cast<King *>(p)->setNoMoveFalse();
            static_cast<Rook *>(rookLeft)->setNoMoveFalse();

            return true;

        } else {
            cerr << "invalid castling" << endl;
            return false;
        }
    }

    //check if enpassant is valid
    if(p->getPieceType() == PieceType::Pawn && ((p->getTeam() == TeamColor::White && start[0] == 4 && end[0] == 5) || (p->getTeam() == TeamColor::Black && start[0] == 3 && end[0] == 2))) {
        if(end[1] == start[1] - 1 || end[1] == start[1] + 1){

            Piece * leftPawn = getPiece(start[0], end[1]);

            if(leftPawn && leftPawn->getTeam() != p->getTeam() && leftPawn->getPieceType() == PieceType::Pawn){

                if(static_cast<Pawn *>(leftPawn)->getEnPassant()) {

                    theBoard[start[0]][start[1]].detachPiece();

                    if(theBoard[end[0]][end[1]].getPieceType() != PieceType::NONE) {
                        Piece *teeeemp = theBoard[end[0]][end[1]].getPiece();
                        theBoard[end[0]][end[1]].detachPiece();
                    }

                    p->move(end[0], end[1]);
                    theBoard[end[0]][end[1]].setPiece(p);

                    Piece *teeeemp = theBoard[end[0]][end[1]].getPiece();
                    theBoard[start[0]][end[1]].detachPiece();
                    delete teeeemp;

                    return true;

                }
            }
        }
    }

    bool validMove = false;
    vector<vector<int>> allMoves = p->getAllMoves();
    for ( auto &n : allMoves ) {
        if (n == end) {
            validMove = true;
            break;
        }
    }
    if (!validMove) {
        cerr << "invalid move!" << endl;
        return false;
    }

    p->move(end[0],end[1]);
    for(auto piece: p->getPieces()){    
        if(piece->getTeam() != p->getTeam() && piece->getPosition() != end && piece->isAttackEnemyKing()){
            p->move(start[0], start[1]);
            cerr << "King will be attacked." << endl;
            return false;
        }
    }
    p->move(start[0], start[1]);
    
    if(p->getPieceType() == PieceType::Pawn){
        if(static_cast<Pawn *>(p)->getEnPassant()){
            static_cast<Pawn *>(p)->setEnPassant(false);
        }
    }

    if(p->getPieceType() == PieceType::Pawn && abs(start[0] - end[0]) == 2) {
        static_cast<Pawn *>(p)->setDoubleMoveFalse();
        static_cast<Pawn *>(p)->setEnPassant(true);
    }

    if(p->getPieceType() == PieceType::King){
        static_cast<King *>(p)->setNoMoveFalse();
    }

    if(p->getPieceType() == PieceType::Rook){
        static_cast<Rook *>(p)->setNoMoveFalse();
    }

    if(theBoard[end[0]][end[1]].getPieceType() != PieceType::NONE) {
        Piece *teeeemp = theBoard[end[0]][end[1]].getPiece();
        theBoard[end[0]][end[1]].detachPiece();
        delete teeeemp;
    }
    theBoard[start[0]][start[1]].detachPiece();

    p->move(end[0], end[1]);
    theBoard[end[0]][end[1]].setPiece(p);
    return true;
}

bool Board::moveForComputer(vector<int> start, vector<int> end) {

    Piece *p = theBoard[start[0]][start[1]].getPiece();

    if (p == nullptr) {
        cerr << "square has no piece" << endl;
        return false;
    }

    if (p->getTeam() != turn) {
        cerr << "you are trying to move your opponent's piece" << endl;
        return false;
    }

    if(isCheck()){
        p->move(end[0],end[1]);
        vector<Piece *> allPieces = p->getPieces();
        allPieces.push_back(p);
        for(auto piece: allPieces){    
            if(piece->getTeam() == p->getTeam() && piece->isChecked()){
                p->move(start[0], start[1]);
                return false;
            }
        }
        p->move(start[0], start[1]);
    }


    p->move(end[0],end[1]);
    for(auto piece: p->getPieces()){    
        if(piece->getTeam() != p->getTeam() && piece->getPosition() != end && piece->isAttackEnemyKing()){
            p->move(start[0], start[1]);
            return false;
        }
    }
    p->move(start[0], start[1]);
    
    if(p->getPieceType() == PieceType::Pawn){
        if(static_cast<Pawn *>(p)->getEnPassant()){
            static_cast<Pawn *>(p)->setEnPassant(false);
        }
    }

    if(p->getPieceType() == PieceType::Pawn) {
        if(abs(start[0] - end[0]) == 2){
            static_cast<Pawn *>(p)->setEnPassant(true);
        }
        static_cast<Pawn *>(p)->setDoubleMoveFalse();
    }
    
    
    if(theBoard[end[0]][end[1]].getPieceType() != PieceType::NONE) {
        Piece *teeeemp = theBoard[end[0]][end[1]].getPiece();
        theBoard[end[0]][end[1]].detachPiece();
        delete teeeemp;
    }

    theBoard[start[0]][start[1]].detachPiece();
    p->move(end[0], end[1]);
    theBoard[end[0]][end[1]].setPiece(p);

    return true;
}

bool Board::isCheck() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard[i][j].getPieceType() == PieceType::King) {
                if (theBoard[i][j].getPiece()->isChecked())
                    return true;
            }
        }
    }
    return false;
}

TeamColor Board::getCheckedPlayer() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard[i][j].getPieceType() == PieceType::King) {
                if (theBoard[i][j].getPiece()->isChecked())
                    return theBoard[i][j].getPiece()->getTeam();
            }
        }
    }
    return TeamColor::White; // this should not happen
}

bool Board::isCheckmate() {

    vector<Piece *> pieces;

    if (turn == TeamColor::Black) {
        pieces = getAllBlackPieces();
    } else {
        pieces = getAllWhitePieces();
    }

    for (auto &piece: pieces) {
        vector<vector<int>> allMoves = piece->getAllMoves();
        for (auto &move : allMoves) {
            vector<int> temp = piece->getPosition();
            Piece *p = getPiece(move[0], move[1]); 
            if(p) p->move(temp[0], temp[1]);
            piece->move(move[0], move[1]);
            if (!isCheck()) {
                piece->move(temp[0], temp[1]);
                if(p) p->move(move[0], move[1]);
                return false;
            }
            piece->move(temp[0], temp[1]);
           
        }    
    }

    cout << "Checkmate! " 
    << ((turn == TeamColor::White) ? "Black" : "White")
    << " wins!" << endl;
    return true;
}

bool Board::isStalemate() {

    vector<Piece *> pieces;

    if (turn == TeamColor::Black) {
        pieces = getAllBlackPieces();
    } else {
        pieces = getAllWhitePieces();
    }

    for (auto &piece : pieces) {
        if (!(piece->getAllMoves().empty())) {
            return false;
        }
    }

    for (auto &piece : pieces) {
        if (piece->getPieceType() == PieceType::King) {
            if (!(piece->isChecked())){
                cout << "Stalemate!" << endl;
                return true;
            }
           
        }
    }

    return false;
}

void Board::toggleTurn() {
    turn = (turn == TeamColor::White) ? TeamColor::Black : TeamColor::White;
}

void Board::resign() {
    cout << ((turn == TeamColor::White) ? "Black" : "White")
         << " wins!" << endl;
}

vector<Piece *> Board::getAllWhitePieces() {

    vector<Piece *> allWhitePieces;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece *p = theBoard[i][j].getPiece();
            if (p && p->getTeam() == TeamColor::White){
                allWhitePieces.push_back(p);
            }
        }
    }

    return allWhitePieces;
}

vector<Piece *> Board::getAllBlackPieces() {

    vector<Piece *> allBlackPieces;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece *p = theBoard[i][j].getPiece();
            if (p && p->getTeam() == TeamColor::Black){
                allBlackPieces.push_back(p);
            }
        }
    }

    return allBlackPieces;
}

vector<Piece *> Board::getAllKingPieces() {

    vector<Piece *> kingPieces;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece *p = theBoard[i][j].getPiece();
            if (p && p->getPieceType() == PieceType::King) {
                kingPieces.push_back(p);
            }
        }
    }

    return kingPieces;
}

vector<Piece *> Board::getAllPieces() {
    vector<Piece *> allPieces;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece *p = theBoard[i][j].getPiece();
            if (p) allPieces.push_back(p);
        }
    }
    return allPieces;
}

bool Board::promote(int row, int col , char type){
    if(type == 'q' || type == 'Q') {
        theBoard[row][col].promote(PieceType::Queen);
    } else if(type == 'r' || type == 'R') {
        theBoard[row][col].promote(PieceType::Rook);
    } else if(type == 'n' || type == 'N') {
        theBoard[row][col].promote(PieceType::Knight);
    } else if(type == 'b' || type == 'B') {
        theBoard[row][col].promote(PieceType::Bishop);
    } else {
        cerr << "Need to promote to one of Q, R, N, B" << endl;
        return false;
    }
    return true;
}

ostream &operator<<(ostream &out, const Board &b) {
  out << b.td;
  return out;
}


