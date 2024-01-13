#ifndef _HUMAN_H__
#define _HUMAN_H__

#include <vector>
#include "player.h"

class Human: public Player {
  public:
    Human(TeamColor tc, Board *b, bool t);
    void turn() override;
    // void resign() override;
};

#endif
