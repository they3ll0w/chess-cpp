#include "textDisplay.h"
#include "cell.h"

char getPieceChar(Cell &c) {
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

TextDisplay::TextDisplay() {
    theDisplay.resize(gridSize, std::vector<char>(gridSize, ' '));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 0)
                theDisplay[i][j] = '_';
        }
    }
}

void TextDisplay::notify(Cell &c) {
    int row = c.getRow();
    int col = c.getCol();
    theDisplay[row][col] = getPieceChar(c);
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int r = 7; r >= 0; --r) {
        out << r + 1 << ' ';
        for (int c = 0; c <= 7; ++c) {
            out << td.theDisplay[r][c];
        }
        out << std::endl;
    }
    out << std::endl;
    out << "  abcdefgh" << std::endl;
    return out;
}
