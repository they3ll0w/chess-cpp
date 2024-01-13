#include <cstdlib>
#include <ctime>
#include "level1.h"


Level1::Level1(TeamColor tc, Board *b, bool t): Player(tc, b, t) {}

void Level1::turn() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));


    if (t && team == TeamColor::White) {

        vector<Piece *> allWhitePieces = b->getAllWhitePieces();

        // check if the king is in check
        vector<Piece *> allKingPieces = b->getAllKingPieces();
        Piece *thisKing = (allKingPieces[0]->getTeam() == team) ? allKingPieces[0] : allKingPieces[1];
        if (thisKing->isChecked()) {
            for ( auto &p : allWhitePieces ) {
                vector<vector<int>> allMoves = p->getAllMoves();
                for ( auto &move : allMoves ) {
                    if (b->moveForComputer(p->getPosition(), move)) return;
                }
            }
        }

        // make a random move
        Piece *thisPiece;
        vector<Piece *> notCheckedPieces = allWhitePieces;
        int nPieces = notCheckedPieces.size();
        while (true) {
            int pieceIndex = rand() % nPieces; // nPieces should never be 0 
            if (!(notCheckedPieces[pieceIndex]->getAllMoves().empty())) {
                thisPiece = notCheckedPieces[pieceIndex];
                vector<vector<int>> allMoves = thisPiece->getAllMoves();
                int nMoves = allMoves.size();
                while (true) {
                    int randMove = rand() % nMoves;
                    vector<int> theMove = thisPiece->getAllMoves()[randMove];
                    if (b->moveForComputer(thisPiece->getPosition(), theMove)) {
                        return;
                    }
                    allMoves.erase(allMoves.begin() + randMove);
                    nMoves = allMoves.size();
                }
            }
            notCheckedPieces.erase(notCheckedPieces.begin() + pieceIndex);
            nPieces = notCheckedPieces.size();
        }
    }

    else if (t && team == TeamColor::Black) {

        vector<Piece *> allBlackPieces = b->getAllBlackPieces();

        // check if the king is in check
        vector<Piece *> allKingPieces = b->getAllKingPieces();
        Piece *thisKing = (allKingPieces[0]->getTeam() == team) ? allKingPieces[0] : allKingPieces[1];
        if (thisKing->isChecked()) {
            for ( auto &p : allBlackPieces ) {
                vector<vector<int>> allMoves = p->getAllMoves();
                for ( auto &move : allMoves ) {
                    if (b->moveForComputer(p->getPosition(), move)) return;
                }
            }
        }

        // make a random move
        Piece *thisPiece;
        vector<Piece *> notCheckedPieces = allBlackPieces;
        int nPieces = notCheckedPieces.size();
        while (true) {
            int pieceIndex = rand() % nPieces; // nPieces should never be 0 
            if (!(notCheckedPieces[pieceIndex]->getAllMoves().empty())) {
                thisPiece = notCheckedPieces[pieceIndex];
                vector<vector<int>> allMoves = thisPiece->getAllMoves();
                int nMoves = allMoves.size();
                while (true) {
                    int randMove = rand() % nMoves;
                    vector<int> theMove = thisPiece->getAllMoves()[randMove];
                    if (b->moveForComputer(thisPiece->getPosition(), theMove)) {
                        return;
                    }
                    allMoves.erase(allMoves.begin() + randMove);
                    nMoves = allMoves.size();
                }
            }
            notCheckedPieces.erase(notCheckedPieces.begin() + pieceIndex);
            nPieces = notCheckedPieces.size();
        }
    } 
}
