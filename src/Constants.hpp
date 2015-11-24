#ifndef Constants_hpp
#define Constants_hpp

#include <math.h>
#include <SDL.h>

class Constants {
public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
    static const char * APP_NAME;

    static int PLAYER_SIZE;
    static int CAMERA_MOVE_AMOUNT;

    static unsigned int PLAYER_COLOR;
    static unsigned int WALL_COLOR;
    static unsigned int MOVABLE_COLOR;
    static unsigned int WIN_COND_COLOR;
    
    static int LEVEL_SIZE;
};

#endif