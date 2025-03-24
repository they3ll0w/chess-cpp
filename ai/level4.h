#ifndef _LEVEL4_H__
#define _LEVEL4_H__

#include <map>
#include "player.h"

// Level 4 is to implement priority among capture moves
// the map maps a PieceType to a int, indicating the priority of capture
// for each PieceType. Higher priority number means computer take priority
// capturing this type of piece.
const map<PieceType, int> priorityMap = {
  make_pair(PieceType::King, 6),
  make_pair(PieceType::Queen, 5),
  make_pair(PieceType::Rook, 4),
  make_pair(PieceType::Bishop, 3),
  make_pair(PieceType::Knight, 2),
  make_pair(PieceType::Pawn, 1)
};

class Level4: public Player {
  public:
    Level4(TeamColor tc, Board *b, bool t);
    void turn() override;
};

#endif
