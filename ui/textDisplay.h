#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <iostream>
#include <vector>
#include "observer.h"

class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
    const int gridSize = 8;
  public:
    TextDisplay();
    void notify(Cell &c) override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
