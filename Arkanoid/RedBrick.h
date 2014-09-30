#include "Brick.h"

class RedBrick:public Brick{

public:

    RedBrick(float x1, float y1, float x2, float y2):Brick(x1,y1,x2,y2)
    {
        rgb[0]= 0.5f;
        rgb[1]= 0.0f;
        rgb[2]= 0.0f;
    };

    float RedBrick::GetReward(){
        return 30;
    };

    void ActivateBonus(float* paddleWidth, float* ballSpeed){};
};

