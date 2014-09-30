#pragma once
#include "Object.h"


class Ball : public Object{
private:
    float direction;
    float speed;
public:
   
    Ball(float x, float y, float direction, float speed):Object(x,y)
    { 
        this->direction = direction; 
        this->speed = speed; 
    };
    Ball():Object(){direction = -135.0f; speed = 0.3f;};

    void    SetDirection(float direction);
    float   GetDirection();
    void    SetSpeed(float speed);
    void    Move(int deltaTime);
};