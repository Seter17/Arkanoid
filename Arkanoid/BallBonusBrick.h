#include "Brick.h"

class BallBonusBrick:public Brick{

public:

    BallBonusBrick(float x1, float y1, float x2, float y2):Brick(x1,y1,x2,y2)
    {
        rgb[0]= 1.5f;
        rgb[1]= 0.5f;
        rgb[2]= 0.0f;
    };

    float BallBonusBrick::GetReward(){
        return 0;
    };

    void ActivateBonus(float* paddleWidth, float* ballSpeed){
        if(*ballSpeed - 0.4f > 0)
            *ballSpeed -= 0.4f;
    };
};
