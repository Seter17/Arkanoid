#include "Brick.h"

class PaddleBonusBrick:public Brick{

public:

    PaddleBonusBrick(float x1, float y1, float x2, float y2):Brick(x1,y1,x2,y2)
    {
        rgb[0]= 1.0f;
        rgb[1]= 1.0f;
        rgb[2]= 0.0f;
    };

    float PaddleBonusBrick::GetReward(){
        return 0;
    };

    void ActivateBonus(float* paddleWidth, float* ballSpeed){
        *paddleWidth += 40.0f;
    };
};
