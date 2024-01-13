#ifndef _PLAYER_H__
#define _PLAYER_H__

#include <vector>
#include "board.h"

class Player {
  protected:
    TeamColor team;
    Board *b;
    bool t;
  public:
    Player(TeamColor tc, Board *b, bool t);
    virtual ~Player();
    virtual void turn() = 0;
    // virtual void resign() = 0;
    bool getTurn();
    TeamColor getTeam();
    void setTeam(TeamColor tc);
    void setTurn(bool t);
};

#endif
