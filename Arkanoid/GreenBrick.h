#include "Brick.h"

class GreenBrick: public Brick {

public:

    GreenBrick(float x1, float y1, float x2, float y2):Brick(x1,y1,x2,y2)
    {
        rgb[0]= 0.0f;
        rgb[1]= 0.5f;
        rgb[2]= 0.0f;
    };

    float GreenBrick::GetReward(){
        return 20;
    };

    void ActivateBonus(float* paddleWidth, float* ballSpeed){};
};

