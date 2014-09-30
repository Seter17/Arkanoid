#pragma once
#include "Object.h"

class Paddle : public Object{

public:
   
    Paddle(float x, float y):Object(x,y){};
    Paddle():Object(){};

};