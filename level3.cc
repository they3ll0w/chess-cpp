#include "level2.h"
#include "level3.h"
#include <cstdlib>
#include <algorithm>

Level3::Level3(TeamColor tc, Board *b, bool t): Player(tc, b, t) {}

void Level3::turn() {
    vector<Piece *> whitePieces = b->getAllWhitePieces();
    vector<Piece *> blackPieces = b->getAllBlackPieces();

    

    if (t && team == TeamColor::White) {

        // check if the king is in check
        vector<Piece *> allKingPieces = b->getAllKingPieces();
        Piece *thisKing = (allKingPieces[0]->getTeam() == team) ? allKingPieces[0] : allKingPieces[1];
        if (thisKing->isChecked()) {
            for ( auto &p : whitePieces ) {
                vector<vector<int>> allMoves = p->getAllMoves();
                for ( auto &move : allMoves ) {
                    if (b->moveForComputer(p->getPosition(), move)) return;
                }
            }
        }

        for(auto whitePiece: whitePieces) {
            if(whitePiece->getAllCaptureMoves().size() > 0) {
                b->move(whitePiece->getPosition(), whitePiece->getAllCaptureMoves()[0]);
                return;
            }
        }
        for(auto whitePiece: whitePieces) {
            vector<vector<int>> whiteCheckMoves = whitePiece->getAllCheckMoves();
            for(auto checkMove: whiteCheckMoves) {
                for (auto blackPiece: blackPieces) {
                    auto it = find(blackPiece->getAllMoves().begin(), blackPiece->getAllMoves().end(), checkMove);
                    if (it != blackPiece->getAllMoves().end()) {
                        continue;
                    } else {
                        b->move(whitePiece->getPosition(), checkMove);
                        return;
                    }
                }       
            }
        }

        for(auto whitePiece: whitePieces) {
            vector<vector<int>> whiteMoves = whitePiece->getAllMoves();
            for(auto move: whiteMoves) {
                for (auto blackPiece: blackPieces) {
                    auto it = find(blackPiece->getAllMoves().begin(), blackPiece->getAllMoves().end(), move);
                    if (it != blackPiece->getAllMoves().end()) {
                        continue;
                    } else {
                        b->move(whitePiece->getPosition(), move);
                        return;
                    }
                }       
            }
        }

        // make a random move
        Piece *thisPiece;
        vector<Piece *> notCheckedPieces = whitePieces;
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

    else {
        
        // check if the king is in check
        vector<Piece *> allKingPieces = b->getAllKingPieces();
        Piece *thisKing = (allKingPieces[0]->getTeam() == team) ? allKingPieces[0] : allKingPieces[1];
        if (thisKing->isChecked()) {
            for ( auto &p : blackPieces ) {
                vector<vector<int>> allMoves = p->getAllMoves();
                for ( auto &move : allMoves ) {
                    if (b->moveForComputer(p->getPosition(), move)) return;
                }
            }
        }

        for(auto blackPiece: blackPieces) {
            if(blackPiece->getAllCaptureMoves().size() > 0) {
                b->move(blackPiece->getPosition(), blackPiece->getAllCaptureMoves()[0]);
                return;
            }
        }
        for(auto blackPiece: blackPieces) {
            vector<vector<int>> blackCheckMoves = blackPiece->getAllCheckMoves();
            for(auto checkMove: blackCheckMoves) {
                for (auto whitePiece: whitePieces) {
                    auto it = find(whitePiece->getAllMoves().begin(), whitePiece->getAllMoves().end(), checkMove);
                    if (it != whitePiece->getAllMoves().end()) {
                        continue;
                    } else {
                        b->move(blackPiece->getPosition(), checkMove);
                        return;
                    }
                }       
            }
        }

        for(auto blackPiece: blackPieces) {
            vector<vector<int>>blackMoves = blackPiece->getAllMoves();
            for(auto move: blackMoves) {
                for (auto whitePiece: whitePieces) {
                    auto it = find(whitePiece->getAllMoves().begin(), whitePiece->getAllMoves().end(), move);
                    if (it != whitePiece->getAllMoves().end()) {
                        continue;
                    } else {
                        b->move(blackPiece->getPosition(), move);
                        return;
                    }
                }       
            }
        }

        // make a random move
        Piece *thisPiece;
        vector<Piece *> notCheckedPieces = blackPieces;
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
