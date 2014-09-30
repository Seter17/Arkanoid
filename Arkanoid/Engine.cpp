#include "Engine.h"
#include "Main.h"
#include "Constraints.h"
#include "WhiteBrick.h"
#include "GreenBrick.h"
#include "BlueBrick.h"
#include "RedBrick.h"
#include "BallBonusBrick.h"
#include "PaddleBonusBrick.h"


void Engine::BuildBricks(){
    for (int i = 0; i < rows*columns; i++)
    {
        float brickX1, brickX2, brickY1, brickY2;
        brickX1 = -fieldWidth/2 + this->bricksMarginX + (this->bricksMarginX * (i % columns));
        brickX2 = brickX1 + brickWidth;
        brickY1 = bricksMarginY + (this->bricksPadding * (i / columns));
        brickY2 = brickY1 + brickHeight;

        int bonusProbability = rand()%100;

        if(bonusProbability == 1){
            bricks[i] = new BallBonusBrick(brickX1,brickY1, brickX2, brickY2);
            continue;
        }
        if(bonusProbability == 2){
            bricks[i] = new PaddleBonusBrick(brickX1,brickY1, brickX2, brickY2);
            continue;
        }
        

        switch (rand()%4){
        case 0:
             bricks[i] = new WhiteBrick(brickX1,brickY1, brickX2, brickY2);
            break;
        case 1:
             bricks[i] = new GreenBrick(brickX1,brickY1, brickX2, brickY2);
            break;
        case 2:
             bricks[i] = new BlueBrick(brickX1,brickY1, brickX2, brickY2);
            break;
        case 3:
             bricks[i] = new RedBrick(brickX1,brickY1, brickX2, brickY2);
            break;
        }

        //bricks[i]->Destroy();

    }
}

void Engine::SetupPositions(){

    this->score = 0;

    this->BuildBricks();
        
    paddle  = new Paddle(0,-50.0f);
    ball    = new Ball(rand()%180 - 100, 0.0f, -(rand()%80 + 50), ballSpeed);
}

void Engine::SetupConstraints(){

    this->paddleSpeed   = PaddleSpeed;
    this->ballSpeed     = BallSpeed;

    this->paddleWidth   = PaddleWidth;
    this->paddleHeight  = PaddleHeight;

    this->brickHeight   = BrickHeight;
    this->brickWidth    = BrickWidth;

    this->bricksMarginX = BricksMarginX;
    this->bricksMarginY = BricksMarginY;
    this->bricksPadding = BricksPadding;

    this->ballSpeedDelta = BallSpeedDelta;
    this->paddleWidthDelta = PaddleWidthDelta;

    this->cost = Cost;
}

bool Engine::Init(float w, float h){

    srand( (unsigned)time( NULL ) );

    this->GameOver = false;
    this->isActive = true;

    this->rebuild = false;

    this->oldTimeSinceStart = 0;
    this->fieldWidth   = w;
    this->fieldHight   = h;

    this->SetupConstraints();
   
    this->SetupPositions();

    return true;
}

///////GAME PHASES/////////////

void Engine::EndGame(){
    this->GameOver = true;
    PlaySound(TEXT("loose.wav"), NULL, SND_ASYNC|SND_FILENAME);
}

void Engine::RestartGame(){

    this->SetupConstraints();

    this->SetupPositions();

    this->GameOver = false;
    this->isActive = true;
}

void Engine::CountinueGame(){
    this->isActive = true;
}

void Engine::PauseGame(){
    this->isActive = false;
}

//////GAME CONTROL////////////

void Engine::MoveBall(int deltaTime){
    ball->Move(deltaTime);
}

void Engine::MoveRight(){
    if(paddle->X() + paddleWidth/2 + paddleSpeed < fieldWidth/2)
        paddle->SetPosition(paddle->X() + paddleSpeed,paddle ->Y());
    else
        paddle->SetPosition(paddle->X() + (fieldWidth/2 - paddle->X() - paddleWidth/2) ,paddle ->Y());
}

void Engine::MoveLeft(){
    if(paddle->X() - paddleWidth/2 - paddleSpeed > -fieldWidth/2)
        paddle->SetPosition(paddle->X() - paddleSpeed,paddle ->Y());
    else
        paddle->SetPosition(paddle->X() - (fieldWidth/2 + paddle->X() - paddleWidth/2),paddle ->Y());
}

//////GAME LOGIC////////////

void Engine::ProceedLogic(){
    if(GameOver || !isActive) return;

    float newDirection = (int)(ball ->GetDirection() - rand()%50)%180;

    //Paddle collisison
    if(ball->Y() > paddle->Y() && ball->Y() < (paddle->Y()+paddleHeight)
                            && ball->X() > (paddle->X() - paddleWidth/2)
                            && ball->X() < (paddle->X() + paddleWidth/2)){
        PlaySound(TEXT("paddle.wav"), NULL, SND_ASYNC|SND_FILENAME);
        
        ball->SetDirection((newDirection < -160 || newDirection >= 0)
                            ? -ball->GetDirection()
                            : -newDirection);
    }

    if (ball->X() > this->fieldWidth/2 || ball->X() < - this->fieldWidth/2)
        ball->SetDirection(180 - ball->GetDirection());

    if (ball->Y() > this->fieldHight/2)
        ball->SetDirection(-ball->GetDirection());

    if (ball->Y() < -this->fieldHight/2)
        this->EndGame();

    //Bricks collision
    for (int i = 0; i< rows*columns;i++){
        if(!bricks[i] || bricks[i]->IsDestroyed()) continue;

        if(bricks[i]->IsInside(ball->X(),ball->Y())){
            PlaySound(TEXT("brick.wav"), NULL, SND_ASYNC|SND_FILENAME);
            bricks[i]->Destroy();
            this->score += bricks[i]->GetReward();
            bricks[i]->ActivateBonus(&this->paddleWidth,&this->ballSpeed);
            ball->SetDirection(-(ball ->GetDirection()));
        }
    }

    //Check bricks
    for (int i = 0; i< rows*columns;i++){
        if(!bricks[i]) continue;
        if(bricks[i]->IsDestroyed())
            this->rebuild = true;
        else
        {
            this->rebuild = false;
            break;
        }
    }
    

    if(rebuild)
        this->NextLevel();

    ball->SetSpeed(this->ballSpeed);
    MoveBall(1);
   
}

void Engine::IncreaseBallSpeed(){
    this->ballSpeed += this->ballSpeedDelta;
}

void Engine::DecreaseBallSpeed(){
    if(this->score - this->cost >= 0){
        this->ballSpeed -= this->ballSpeedDelta;
        this->score -= this->cost;
    }
}

void Engine::DecreasePaddle(){
    if(this->paddleWidth - this->paddleWidthDelta > 0)
        this->paddleWidth -= this->paddleWidthDelta;
}

void Engine::IncreasePaddle(){
    if(this->score - this->cost >= 0){
        this->paddleWidth += this->paddleWidthDelta;
        this->score -= this->cost;
    }
}

void Engine::IncreaseDifficulty(){
    this->IncreaseBallSpeed();
    this->DecreasePaddle();
}

void Engine::NextLevel(){
    this->BuildBricks();
    this->IncreaseDifficulty();
}

////////DRAWING//////////////

void Engine::DrawBricks(){
    glLoadIdentity();
    glTranslatef(-fieldWidth/2, bricksMarginY, 1.0f);
    for (int i = 0; i < rows * columns; i++)
    {        
        glColor3f(bricks[i]->R(), bricks[i]->G(), bricks[i]->B());

        glTranslatef(this->bricksMarginX, 0.0f, 0.0f);
        if (i % columns == 0 && i > 0)
                glTranslatef(-this->bricksMarginX * columns, this->bricksPadding, 0.0f);

        if (bricks[i]->IsDestroyed()) continue;

        glBegin(GL_QUADS);
        glVertex3f(0.0f, brickHeight, 0.0f);
        glVertex3f(brickWidth, brickHeight, 0.0f);
        glVertex3f(brickWidth, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();
    }

}

void Engine::DrawPaddle(){
    glLoadIdentity();
    glTranslatef(0, paddle->Y(), 1.0f);
    glColor3f(1.0f, 0.75f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-paddleWidth/2 + paddle->X(), paddleHeight, 0.0f);
    glVertex3f(paddleWidth/2  + paddle->X(), paddleHeight, 0.0f);
    glVertex3f(paddleWidth/2  + paddle->X(), 0.0f, 0.0f);
    glVertex3f(-paddleWidth/2 + paddle->X(), 0.0f, 0.0f);
    glEnd();

}

void Engine::DrawBall(){
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f( 0.0f + ball->X(), -1.0f + ball->Y(), 1.0f);
    glVertex3f( 1.5f + ball->X(),  0.0f + ball->Y(), 1.0f);
    glVertex3f( 0.0f + ball->X(),  1.0f + ball->Y(), 1.0f);
    glVertex3f( 0.0f + ball->X(), -1.0f + ball->Y(), 1.0f);
    glVertex3f(-1.5f + ball->X(),  0.0f + ball->Y(), 1.0f);
    glVertex3f( 0.0f + ball->X(),  1.0f + ball->Y(), 1.0f);
    glEnd();
 
}

void Engine::RenderText(float x, float y, void *font, std::string string, COLORREF const& rgb){

    glColor3f(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)); 
    glRasterPos2f(x, y);

    glutBitmapString(font, (unsigned char*)(string.c_str()));
}

void Engine::DrawScene(){

    if(this->IsEnded())
        this->RenderText(-10.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Game Over", RGB(1.0f, 0.0f, 0.0f));

    if(this->IsPaused())
        this->RenderText(-10.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Paused", RGB(1.0f, 0.0f, 0.0f));

    char numstr[21];
    sprintf(numstr, "%d", this->score);
    char other_string[64] = "Score: ";
    this->RenderText(-95.0f, 55.0f, GLUT_BITMAP_TIMES_ROMAN_24, strcat(other_string,numstr), RGB(1.0f, 0.0f, 0.0f));

    this->RenderText(-95.0f, -55.0f, GLUT_BITMAP_TIMES_ROMAN_10, "A/D - move left / right\t\t\t\t\t W - to spend 300 points to increase paddle width on 40% \n R/P - restart / pause\t\t\t\t\t\t\t\t\t\t\t\t\t S - to spend 300 points to decrease ball speed on 30% ", RGB(1.0f, 0.0f, 0.0f));


    this->DrawBricks();

    this->DrawPaddle();

    this->DrawBall();
 
    ProceedLogic();
}
