#pragma once
#include "Object.h"


class Brick{

private:
    float x1,x2,y1,y2;
    bool destroyed;
protected:
    float rgb[3];
public:
   
    Brick(float x1, float y1, float x2, float y2)   
    {   
        this->destroyed = false;   
        this->x1 = x1;
        this->x2 = x2;
        this->y1 = y1;
        this->y2 = y2;
    };

    virtual ~Brick(){};

    float virtual GetReward() = 0;

    void virtual  ActivateBonus(float* paddleWidth, float* ballSpeed) = 0;

    bool IsDestroyed();
    void Destroy();
    bool IsInside(float x, float y);

    float R();
    float G();
    float B();
};