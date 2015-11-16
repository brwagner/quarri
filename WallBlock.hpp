#ifndef WallBlock_hpp
#define WallBlock_hpp

#include "ABlock.hpp"

class WallBlock : public ABlock {
public:
    virtual bool isMovable();
    virtual int getColor();
};
    
#endif