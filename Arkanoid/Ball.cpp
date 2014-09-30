#include "Ball.h"
#include "Main.h"

void Ball::SetDirection(float direction){
    this -> direction = direction;
}

float Ball::GetDirection() { return direction;}

void Ball::SetSpeed(float speed){
    this -> speed = speed;
}

void Ball::Move(int deltaTime){
    this->x += cos(direction * PI/180)*deltaTime*speed;
    this->y += sin(direction * PI/180)*deltaTime*speed;
}
