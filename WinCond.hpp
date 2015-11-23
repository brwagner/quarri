#ifndef WinCond_hpp
#define WinCond_hpp

#include "Block.hpp"

class WinCond : public Block {
public:
    WinCond(std::pair<double, double> pos);
    virtual void update();
};

#endif