#include "Brick.h"

class WhiteBrick:public Brick{

public:

    WhiteBrick(float x1, float y1, float x2, float y2):Brick(x1,y1,x2,y2)
    {
        rgb[0]= 0.752941f;
        rgb[1]= 0.752941f;
        rgb[2]= 0.752941f;
    };

    float WhiteBrick::GetReward(){
        return 10;
    };

    void ActivateBonus(float* paddleWidth, float* ballSpeed){};
};

