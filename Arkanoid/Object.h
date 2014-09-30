#pragma once

class Object{
protected:
    float x,y;

public:
    virtual void SetPosition(float x, float y) { this-> x = x; this->y =y;};

    Object(float x, float y)    { SetPosition(x,y);};
    Object()                    { SetPosition(0,0);};

    virtual ~Object(){};

    virtual float X() const {return x;};
    virtual float Y() const {return y;};
};