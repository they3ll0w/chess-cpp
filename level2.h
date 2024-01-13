#ifndef _LEVEL2_H__
#define _LEVEL2_H__

#include <vector>
#include "player.h"

class Level2: public Player {
  public:
    Level2(TeamColor tc, Board *b, bool t);
    void turn() override;
};

#endif
