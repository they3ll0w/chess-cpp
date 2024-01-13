#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "board.h"
#include "player.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"
#include "human.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

using namespace std;

const int WINDOW_SIZE = 500;


Piece *getNewPiece(char piece) {
    Piece *p = nullptr;
    vector<Piece *> emptyPieceVector;
    if (piece == 'K') {
        p = new King(TeamColor::White, 0, 0, emptyPieceVector);
    } else if (piece == 'k') {
        p = new King(TeamColor::Black, 0, 0, emptyPieceVector);
    } else if (piece == 'Q') {
        p = new Queen(TeamColor::White, 0, 0, emptyPieceVector);
    } else if (piece == 'q') {
        p = new Queen(TeamColor::Black, 0, 0, emptyPieceVector);
    } else if (piece == 'B') {
        p = new Bishop(TeamColor::White, 0, 0, emptyPieceVector);
    } else if (piece == 'b') {
        p = new Bishop(TeamColor::Black, 0, 0, emptyPieceVector);
    } else if (piece == 'R') {
        p = new Rook(TeamColor::White, 0, 0, emptyPieceVector);
    } else if (piece == 'r') {
        p = new Rook(TeamColor::Black, 0, 0, emptyPieceVector);
    } else if (piece == 'N') {
        p = new Knight(TeamColor::White, 0, 0, emptyPieceVector);
    } else if (piece == 'n') {
        p = new Knight(TeamColor::Black, 0, 0, emptyPieceVector);
    } else if (piece == 'P') {
        p = new Pawn(TeamColor::White, 0, 0, emptyPieceVector);
    } else if (piece == 'p') {
        p = new Pawn(TeamColor::Black, 0, 0, emptyPieceVector);
    }
    return p;
}

int main(int argc, char *argv[]) {
    Player *whitePlayer = nullptr;
    Player *blackPlayer = nullptr;
    Board b(WINDOW_SIZE);


    // settings of this game
    bool DEFAULTBOARD = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-defaultBoard") == 0) {
            cout << "the game would have a default board" << endl;
            DEFAULTBOARD = true;
        }
    }

    b.init();
    if (DEFAULTBOARD) {
        b.initDefault();
    }
    
    // the number stored in this score vector is 2 times the actual score of a player
    vector<unsigned int> score;
    score.resize(2, 0);
    string cmd, line;
    TeamColor curTurn = TeamColor::White;
    bool isSetup = false;

    // read command recursively
    // a line is a command

    while (getline(cin, line)) {
        istringstream iss{line};
        iss >> cmd;
        if (cmd == "setup") {   // enter setup mode
            vector<Piece *> allPieces = b.getAllPieces();
            while (getline(cin, line)) {
                istringstream iss{line};
                iss >> cmd;
                if (cmd == "+") { // add a piece to the board
                    char piece;
                    string place;
                    if (!(iss >> piece >> place) || place.size() != 2 ||
                        place[0] < 'a' || place[0] > 'h' ||
                        place[1] < '1' || place[1] > '8' ) {
                        cerr << "invalid command" << endl;
                        continue;
                    }
                    if (piece == 'p') {
                        if (place[1]-'1' == 0) {
                            cerr << "a black pawn can not be at the bottom row" << endl;
                            continue;
                        }
                    } else if (piece == 'P') {
                        if (place[1]-'1' == 7) {
                            cerr << "a white pawn can not be at the top row" << endl;
                            continue;
                        }
                    }
                    Piece *newp = getNewPiece(piece);
                    if (!newp) {
                        cerr << "invalid command" << endl;
                        continue;
                    }
                    int row = place[1]-'1';
                    int col = place[0]-'a';
                    newp->move(row, col);
                    allPieces.push_back(newp);
                    if (b.getPiece(row, col)) {
                        // delete the piece in the allPieces vector
                        Piece *p = b.getPiece(row, col);
                        for (auto it = allPieces.begin(); it != allPieces.end(); ++it) {
                            if (*it == p) {
                                allPieces.erase(it);
                                break;
                            }
                        }
                    }
                    b.setPiece(row, col, newp);
                    std::cout << b;
                } else if (cmd == "-") {
                    string place;
                    if (!(iss >> place) || place.size() != 2 ||
                        place[0] < 'a' || place[0] > 'h' ||
                        place[1] < '1' || place[1] > '8' ) {
                        cerr << "invalid command" << endl;
                        continue;
                    }
                    
                    // check if there is a piece there
                    if (!b.getPiece(place[1]-'1', place[0]-'a')) continue;

                    // delete the piece in the allPieces vector
                    Piece *p = b.getPiece(place[1]-'1', place[0]-'a');
                    for (auto it = allPieces.begin(); it != allPieces.end(); ++it) {
                        if (*it == p) {
                            allPieces.erase(it);
                            break;
                        }
                    }
                    //auto it = find(allPieces.begin(), allPieces.end(), p);
                    //if (it != allPieces.end()) allPieces.erase(it);
                    // delete the piece in the board
                    Piece *teeeemp = b.getPiece(place[1]-'1', place[0]-'a');
                    b.detachPiece(place[1]-'1', place[0]-'a');
                    delete teeeemp;
                    std::cout << b;
                } else if (cmd == "=") {
                    string color;
                    if (!(iss >> color)) {
                        cerr << "invalid command" << endl;
                        continue;
                    }
                    if (color == "white") {
                        /*if (whitePlayer && !whitePlayer->getTurn()) {
                            if (whitePlayer) whitePlayer->setTurn(true);
                            if (blackPlayer) blackPlayer->setTurn(false);
                            curTurn = TeamColor::White;
                            b.toggleTurn();
                        }*/
                        std::cout << "white player plays next" << endl;
                    }
                    else if (color == "black") {
                        //if (blackPlayer && !blackPlayer->getTurn()) {
                           // if (blackPlayer) blackPlayer->setTurn(true);
                            //if (whitePlayer) whitePlayer->setTurn(false);
                            curTurn = TeamColor::Black;
                            b.toggleTurn();
                        //}
                        std::cout << "black player plays next" << endl;
                    }
                    else cerr << "bad color given" << endl;
                } else if (cmd == "done") {
                    // check if both team have exactly 1 king
                    vector<Piece *> allKingPieces = b.getAllKingPieces();
                    if (allKingPieces.size() != 2 || allKingPieces[0]->getTeam() == allKingPieces[1]->getTeam()) {
                        cerr << "not both player have exactly one king, cannot exit setup mode" << endl;
                        continue;
                    }

                    // store all the pointers of pieces into all pieces
                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            Piece *p = b.getPiece(i,j);
                            if (p) {
                                // create a temporary vector so that p doesnt exist in this vector
                                vector<Piece *> tempAllPieces = allPieces;
                                auto it = find(tempAllPieces.begin(), tempAllPieces.end(), p);
                                if (it != tempAllPieces.end()) {
                                    tempAllPieces.erase(it);
                                }
                                p->setUpPieces(tempAllPieces);
                            }
                        }
                    }

                    // check if either king is being checked
                    if (allKingPieces[0]->isChecked() || allKingPieces[1]->isChecked()) {
                        cerr << "at least one king ie checked, cannot exit setup mode" << endl;
                        continue;
                    }

                    //check if two kings are "checking"
                    if ((abs(allKingPieces[0]->getPosition()[0] - allKingPieces[1]->getPosition()[0]) <= 1) && 
                        (abs(allKingPieces[0]->getPosition()[1] - allKingPieces[1]->getPosition()[1]) <= 1)) {
                        cerr << "the two kings are checking each other?!! cannot exit setup mode" << endl;
                        continue;
                    }
                    // finishing setup mode
                    std::cout << "exiting setup mode" << endl;
                    isSetup = true;
                    break;
                }
                else cerr << "bad command in setup mode" << endl;
            }
        }
        
        else if (cmd == "game") {
            if (!isSetup) {
                b.initDefault();
            }

            // check if the game can start
            // check if both team have exactly 1 king
            vector<Piece *> allKingPieces = b.getAllKingPieces();
            if (allKingPieces.size() != 2 || allKingPieces[0]->getTeam() == allKingPieces[1]->getTeam()) {
                cerr << "not both player have exactly one king, cannot enter game" << endl;
                continue;
            }
            // check if either king is being checked
            if (allKingPieces[0]->isChecked() || allKingPieces[1]->isChecked()) {
                cerr << "at least one king ie checked, cannot enter game" << endl;
                continue;
            }

            string player1, player2;
            if (!(iss >> player1 >> player2)) {
                cerr << "bad command" << endl;
                continue;
            }

            // initialize player1
            if (whitePlayer) {
                delete whitePlayer;
                whitePlayer = nullptr;
            }
            if (player1 == "human") whitePlayer = new Human(TeamColor::White, &b, true);
            else if (player1 == "computer[1]") whitePlayer = new Level1(TeamColor::White, &b, true);
            else if (player1 == "computer[2]") whitePlayer = new Level2(TeamColor::White, &b, true);
            else if (player1 == "computer[3]") whitePlayer = new Level3(TeamColor::White, &b, true);
            else if (player1 == "computer[4]") whitePlayer = new Level4(TeamColor::White, &b, true);
            else {
                cerr << "bad player1 name" << endl;
                continue;
            }

            if (blackPlayer) {
                delete blackPlayer;
                blackPlayer = nullptr;
            }
            // initialize player2
            if (player2 == "human") blackPlayer = new Human(TeamColor::Black, &b, false);
            else if (player2 == "computer[1]") blackPlayer = new Level1(TeamColor::Black, &b, false);
            else if (player2 == "computer[2]") blackPlayer = new Level2(TeamColor::Black, &b, false);
            else if (player2 == "computer[3]") blackPlayer = new Level3(TeamColor::Black, &b, false);
            else if (player2 == "computer[4]") blackPlayer = new Level4(TeamColor::Black, &b, false);
            else {
                cerr << "bad player2 name" << endl;
                delete whitePlayer;
                whitePlayer = nullptr;
                continue;
            }

            // store if player1/player2 are human/computer
            bool player1IsHuman = (player1 == "human") ? true : false;
            bool player2IsHuman = (player2 == "human") ? true : false;

            if (curTurn == TeamColor::White) {
                whitePlayer->setTurn(true);
                blackPlayer->setTurn(false);
            }
            else {
                whitePlayer->setTurn(false);
                blackPlayer->setTurn(true);
            }
            //b.setTurn(curTurn);
            std::cout << "the game started!" << endl;
            std::cout << b;
            std::cout << ((curTurn == TeamColor::White) ? "White" : "Black")
                 << "'s turn to go next" << endl;
            
            // check if the game is stalemate
            if (b.isStalemate()) {
                // add half a point to both player
                score[0] += 1;
                score[1] += 1;
                // reinitialize the board
                delete whitePlayer;
                delete blackPlayer;
                whitePlayer = nullptr;
                blackPlayer = nullptr;
                b.init();
                if (DEFAULTBOARD) b.initDefault();
                isSetup = false;
                curTurn = TeamColor::White;
                continue;
            }
            // the game loop 
            while (getline(cin, line)) {

                istringstream iss{line};
                if (!(iss >> cmd)) {
                    cerr << "bad command" << endl;
                    continue;
                }

                if (cmd == "move") {
                    // get if the current player is human or computer
                    bool thisPlayerIsHuman = (curTurn == TeamColor::White) ? player1IsHuman : player2IsHuman;
                    if (thisPlayerIsHuman) {
                        string startPos, endPos;
                        iss >> startPos >> endPos;
                        vector<int> pos1 = {startPos[1]-'1', startPos[0]-'a'};
                        vector<int> pos2 = {endPos[1]-'1', endPos[0]-'a'};
                        
                        if (b.move(pos1, pos2)) {
                            // check if this move contains a promotion here
                            Piece *p = b.getPiece(pos2[0], pos2[1]);
                            if (p->getPieceType() == PieceType::Pawn && 
                            ((p->getTeam() == TeamColor::White && p->getPosition()[0] == 7) ||
                             (p->getTeam() == TeamColor::Black && p->getPosition()[0] == 0))) {
                                char promoteTo = 0;
                                iss >> promoteTo; // error checking to be added
                                if (!b.promote(pos2[0], pos2[1], promoteTo)) {
                                    cerr << "promotion failed" << endl;
                                }
                            }

                            b.toggleTurn();
                            if (curTurn == TeamColor::White) {
                                curTurn = TeamColor::Black;
                                whitePlayer->setTurn(false);
                                blackPlayer->setTurn(true);
                            } else {
                                curTurn = TeamColor::White;
                                whitePlayer->setTurn(true);
                                blackPlayer->setTurn(false);
                            }
                            std::cout << b;
                        }
                    }
                    else {  // computer player
                        if (curTurn == TeamColor::White) {
                            whitePlayer->turn();
                            b.toggleTurn();
                            curTurn = TeamColor::Black;
                            whitePlayer->setTurn(false);
                            blackPlayer->setTurn(true);
                        } else {
                            blackPlayer->turn();
                            b.toggleTurn();
                            curTurn = TeamColor::White;
                            whitePlayer->setTurn(true);
                            blackPlayer->setTurn(false);
                        }
                        std::cout << b;
                    }
                } else if (cmd == "resign") {
                    b.resign();
                    if (curTurn == TeamColor::White) score[1] += 2;
                    else score[0] += 2;
                    // reinitialize the board
                    delete whitePlayer;
                    delete blackPlayer;
                    whitePlayer = nullptr;
                    blackPlayer = nullptr;
                    b.init();
                    if (DEFAULTBOARD) b.initDefault();
                    isSetup = false;
                    curTurn = TeamColor::White;
                    break;
                } else {
                    cerr << "bad command" << endl;
                    continue;
                }
                // check if one of the king is captured
                vector<Piece *> allKingPieces = b.getAllKingPieces();
                if (allKingPieces.size() != 2) {
                    if (allKingPieces.size() == 1) {
                        TeamColor winner = allKingPieces[0]->getTeam();
                        if (winner == TeamColor::White) {
                            cout << "king capture! white player wins!" << endl;
                            score[0] += 2;
                        } else {
                            cout << "king capture! black player wins!" << endl;
                            score[1] += 2;
                        }
                        // reinitialize the board
                        delete whitePlayer;
                        delete blackPlayer;
                        whitePlayer = nullptr;
                        blackPlayer = nullptr;
                        b.init();
                        if (DEFAULTBOARD) b.initDefault();
                        isSetup = false;
                        curTurn = TeamColor::White;
                        break;
                    }
                    else { // this should be impossible if all implementation is correct
                        cerr << "some error occured! quitting this game" << endl;
                        break;
                    }
                }
                // check if the game have won
                if (b.isStalemate()) {
                    // add half a point to both player
                    score[0] += 1;
                    score[1] += 1;
                    // reinitialize the board
                    delete whitePlayer;
                    delete blackPlayer;
                    whitePlayer = nullptr;
                    blackPlayer = nullptr;
                    b.init();
                    if (DEFAULTBOARD) b.initDefault();
                    isSetup = false;
                    curTurn = TeamColor::White;
                    break;
                }
                if (b.isCheck()) {
                    if (b.isCheckmate()) {
                        // add a point to the winner                 
                        (curTurn == TeamColor::Black) ? score[0]+=2 : score[1]+=2;
                        // reinitialize the board
                        delete whitePlayer;
                        delete blackPlayer;
                        whitePlayer = nullptr;
                        blackPlayer = nullptr;
                        b.init();
                        if (DEFAULTBOARD) b.initDefault();
                        isSetup = false;
                        curTurn = TeamColor::White;
                        break;
                    }
                    TeamColor checked = b.getCheckedPlayer();
                    (checked == TeamColor::White) ? std::cout << "White" : std::cout << "Black";
                    std::cout << " is in check." << endl;
                }
                std::cout << ((curTurn == TeamColor::White) ? "White" : "Black")
                     << "'s turn to go next" << endl;
            }

        }  else {
            cerr << "bad command" << endl;
        }
    }

    // print the scoring of white/black player
    std::cout << "Final Score:" << endl
         << "White: " << score[0]/2 << '.' << ((score[0]%2)? 5: 0) << endl
         << "Black: " << score[1]/2 << '.' << ((score[1]%2)? 5: 0) << endl;
    
    if (whitePlayer) delete whitePlayer;
    if (blackPlayer) delete blackPlayer;
}
