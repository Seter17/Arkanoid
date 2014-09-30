#include "Brick.h"

class BlueBrick:public Brick{

public:

    BlueBrick(float x1, float y1, float x2, float y2):Brick(x1,y1,x2,y2)
    {
        rgb[0]= 0.0f;
        rgb[1]= 0.0f;
        rgb[2]= 0.5f;
    };

    float BlueBrick::GetReward(){
        return 40;
    };

    void ActivateBonus(float* paddleWidth, float* ballSpeed){};
};

