#include "level2.h"
#include <cstdlib>
#include <ctime>

Level2::Level2(TeamColor tc, Board *b, bool t): Player(tc, b, t) {}

void Level2::turn() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (t && team == TeamColor::White) {

        vector<Piece *> pieces = b->getAllWhitePieces();

        // check if the king is in check
        vector<Piece *> allKingPieces = b->getAllKingPieces();
        Piece *thisKing = (allKingPieces[0]->getTeam() == team) ? allKingPieces[0] : allKingPieces[1];
        if (thisKing->isChecked()) {
            for ( auto &p : pieces ) {
                vector<vector<int>> allMoves = p->getAllMoves();
                for ( auto &move : allMoves ) {
                    if (b->moveForComputer(p->getPosition(), move)) return;
                }
            }
        }

        int nPiece = pieces.size();

        for(int i = 0; i < nPiece; ++i) {
            if(pieces[i]->getAllCheckMoves().size() > 0) {
                b->moveForComputer(pieces[i]->getPosition(), pieces[i]->getAllCheckMoves()[rand() % pieces[i]->getAllCheckMoves().size()]);
                return;
            }
        }

        for(int i = 0; i < nPiece; ++i) {
            if(pieces[i]->getAllCaptureMoves().size() > 0) {
                b->moveForComputer(pieces[i]->getPosition(), pieces[i]->getAllCaptureMoves()[rand() % pieces[i]->getAllCaptureMoves().size()]);
                return;
            }
        }

        // make a random move
        Piece *thisPiece;
        vector<Piece *> notCheckedPieces = pieces;
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
                    if (b->move(thisPiece->getPosition(), theMove)) {
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

    else {
        vector<Piece *> pieces = b->getAllBlackPieces();

        // check if the king is in check
        vector<Piece *> allKingPieces = b->getAllKingPieces();
        Piece *thisKing = (allKingPieces[0]->getTeam() == team) ? allKingPieces[0] : allKingPieces[1];
        if (thisKing->isChecked()) {
            for ( auto &p : pieces ) {
                vector<vector<int>> allMoves = p->getAllMoves();
                for ( auto &move : allMoves ) {
                    if (b->moveForComputer(p->getPosition(), move)) return;
                }
            }
        }

        int nPiece = pieces.size();

        for(int i = 0; i < nPiece; ++i) {
            if(pieces[i]->getAllCheckMoves().size() > 0) {
                b->moveForComputer(pieces[i]->getPosition(), pieces[i]->getAllCheckMoves()[rand() % pieces[i]->getAllCheckMoves().size()]);
                return;
            }
        }

        for(int i = 0; i < nPiece; ++i) {
            if(pieces[i]->getAllCaptureMoves().size() > 0) {
                b->moveForComputer(pieces[i]->getPosition(), pieces[i]->getAllCaptureMoves()[rand() % pieces[i]->getAllCaptureMoves().size()]);
                return;
            }
        }

        // make a random move
        Piece *thisPiece;
        vector<Piece *> notCheckedPieces = pieces;
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
