#pragma once

#include <string>
#include "Main.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Constraints.h"

class Engine{
private:
    bool    rebuild, isActive, GameOver;

    float   oldTimeSinceStart;
    float   paddleSpeed;
    float   paddleWidth;
    float   paddleHeight;

    float   ballSpeed;

    float   brickWidth;
    float   brickHeight;

    float   bricksMarginX;
    float   bricksMarginY;
    float   bricksPadding;

    float   fieldWidth;
    float   fieldHight;

    int     score;
    int     cost;

    float     paddleWidthDelta;
    float     ballSpeedDelta;

    Brick*  bricks[rows*columns];

    Ball*   ball;
    Paddle* paddle;
    
    void    ProceedLogic();

    void    SetupConstraints();
    void    SetupPositions();

    void    BuildBricks();
    void    DecreasePaddle();
    void    IncreaseBallSpeed();
    void    NextLevel();

    void    EndGame();

    void    DrawBricks();
    void    DrawPaddle();
    void    DrawBall();

public:
    Engine(){};

    bool Init(float w, float h);

    void DrawScene();
    void RenderText(float x, float y, void *font, std::string string, COLORREF const& rgb);

    void MoveBall(int deltaTime);
    void MoveRight();
    void MoveLeft();

    bool IsPaused() {return !isActive;};
    bool IsEnded()  {return GameOver;};

    void PauseGame();

    void CountinueGame();
    void RestartGame();

    void IncreasePaddle();
    void DecreaseBallSpeed();
    void IncreaseDifficulty();
};