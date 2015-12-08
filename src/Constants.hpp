#ifndef Constants_hpp
#define Constants_hpp

class Constants {
public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
    static const char * APP_NAME;

    static int CAMERA_MOVE_AMOUNT;
    
    static int PLAYER_HEIGHT;
    static int PLAYER_BOTTOM;
    static int SCREEN_TOP;
    static int SCREEN_BOTTOM;
    static int EYE_WIDTH;
    static int PLAYER_BACK;
    static int BOX_SPACE;
    static int SHADE_WIDTH;
    static int TIRE_RADIUS;
    static int PLAYER_SIZE;
    
    static int FLAG_BASE_HEIGHT;
    static int FLAG_POLE_WIDTH;
    static int FLAG_POLE_LEFT;
    static int FLAG_POLE_RIGHT;

    static unsigned int MONITOR_COLOR;
    static unsigned int MONITOR_SHADING_COLOR;
    static unsigned int SCREEN_COLOR;
    static unsigned int TIRE_COLOR;
    static unsigned int SCREEN_FACE_COLOR;
    static unsigned int WALL_COLOR;
    static unsigned int MOVABLE_COLOR;
    static unsigned int WIN_COND_COLOR;
    static unsigned int WIN_COND_POLE_COLOR;

    static int LEVEL_SIZE;
};

#endif