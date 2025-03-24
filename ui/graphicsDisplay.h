#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__

#include <vector>
#include "observer.h"
#include "window.h"

class GraphicsDisplay: public Observer {
    Xwindow w;
    const int windowSize;
    const int gridNum = 8;
    const int sizePerBlock;
  public:
    GraphicsDisplay(int windowSize);
    void notify(Cell &c) override;
};

#endif
