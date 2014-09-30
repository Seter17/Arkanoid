#include "Brick.h"

bool Brick::IsDestroyed()   {return this -> destroyed;}

void Brick::Destroy()       {this -> destroyed = true;}

bool Brick::IsInside(float x, float y)  
                            { return x > this->x1 && x < this->x2 && 
                                y > this->y1 && y < this->y2;}

float Brick::R()            { return rgb[0];}
float Brick::G()            { return rgb[1];}
float Brick::B()            { return rgb[2];}