#include "graphicsDisplay.h"
#include "cell.h"

char getPieceChar2(Cell &c) {
    PieceType pt = c.getPieceType();
    if (pt == PieceType::NONE){
        if ((c.getCol() + c.getRow()) % 2 == 0)
            return '_';
        else return ' ';
    }
    else if (pt == PieceType::Knight) {
        Piece *p = c.getPiece();
        TeamColor tc = p->getTeam();
        if (tc == TeamColor::White) return 'N';
        else return 'n';
    }
    else if (pt == PieceType::Pawn) {
        Piece *p = c.getPiece();
        TeamColor tc = p->getTeam();
        if (tc == TeamColor::White) return 'P';
        else return 'p';
    }
    else if (pt == PieceType::King) {
        Piece *p = c.getPiece();
        TeamColor tc = p->getTeam();
        if (tc == TeamColor::White) return 'K';
        else return 'k';
    }
    else if (pt == PieceType::Bishop) {
        Piece *p = c.getPiece();
        TeamColor tc = p->getTeam();
        if (tc == TeamColor::White) return 'B';
        else return 'b';
    }
    else if (pt == PieceType::Rook) {
        Piece *p = c.getPiece();
        TeamColor tc = p->getTeam();
        if (tc == TeamColor::White) return 'R';
        else return 'r';
    }
    else if (pt == PieceType::Queen) {
        Piece *p = c.getPiece();
        TeamColor tc = p->getTeam();
        if (tc == TeamColor::White) return 'Q';
        else return 'q';
    } 
    else return 0;
    
}

GraphicsDisplay::GraphicsDisplay(int windowSize = 500):
    w{Xwindow(windowSize, windowSize)},
    windowSize{windowSize},
    sizePerBlock{(gridNum == 0)? 0 : (windowSize-100)/(gridNum+1)} {
    // initialize the grid
    for (int i = 0; i < gridNum; ++i) {
        w.drawString(50, 75+i*sizePerBlock, std::string(1, '8'-i));
        for (int j = 0; j < gridNum; ++j) {
            int xaxis = 50 + (j+1)*sizePerBlock;
            int yaxis = 50 + i*sizePerBlock;
            if ((i+j) % 2 == 0) {
                w.fillRectangle(xaxis, yaxis, sizePerBlock, sizePerBlock, Xwindow::White);
            }
            else {
                w.fillRectangle(xaxis, yaxis, sizePerBlock, sizePerBlock, Xwindow::Black);
            }
        }
    }
    for (char c = 'a'; c <= 'h'; ++c) {
        int xaxis = 75 + (c-'a'+1)*sizePerBlock;
        int yaxis = 100 + gridNum*sizePerBlock;
        w.drawString(xaxis, yaxis, std::string(1, c));
    }
}

void GraphicsDisplay::notify(Cell &c) {
    int xaxis = 50 + (c.getCol()+1) * sizePerBlock;
    int yaxis = 50 + (7 - c.getRow()) * sizePerBlock;
    char ch = getPieceChar2(c);
    if (ch == '_') { // black grid without a piece
        w.fillRectangle(xaxis, yaxis, sizePerBlock, sizePerBlock, Xwindow::Black);
    }
    else {
        w.fillRectangle(xaxis, yaxis, sizePerBlock, sizePerBlock, Xwindow::White);
        w.drawString(xaxis + sizePerBlock/2, yaxis + sizePerBlock/2, std::string(1,ch));
    }
}
