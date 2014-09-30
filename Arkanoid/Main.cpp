#include "Engine.h"
#include "Main.h"

float screenWidth     = 800;
float screenHeight    = 600;

float fieldWidth        = 400.0f;
float activeFieldWidth  = 220.0f;
float fieldHeight       = 300.0f;
float activeFieldHeight = 130.0f;

Engine* ArkanoidEngine = new Engine();

void Timer(int value) // Timer function
{
    if(!ArkanoidEngine->IsPaused() &&!ArkanoidEngine->IsEnded())
        ArkanoidEngine->IncreaseDifficulty();
    glutTimerFunc(TimeToIncerasingDifficulty, Timer, 0); // Setup next timer
}

void KeyPressFunc(unsigned char key, int x, int y)
{
    if(!ArkanoidEngine->IsPaused() && !ArkanoidEngine->IsEnded())
    {
        switch(key){
        case 'A':
        case 'a':
            ArkanoidEngine->MoveLeft();
            break;
        case 'D':
        case 'd':
            ArkanoidEngine->MoveRight();
            break;
        case 'P':
        case 'p':
            ArkanoidEngine->PauseGame();
            break;
        case 'R':
        case 'r':
            ArkanoidEngine->RestartGame();
            break;
        case 'W':
        case 'w':
            ArkanoidEngine->IncreasePaddle();
            break;
        case 'S':
        case 's':
            ArkanoidEngine->DecreaseBallSpeed();
            break;
        }
        return;
    }

    if(ArkanoidEngine->IsEnded())
    {
        switch(key){
        case 'R':
        case 'r':
            ArkanoidEngine->RestartGame();
            break;
        }
        return;
    }

    if(ArkanoidEngine->IsPaused())
    {
        switch(key){
        case 'P':
        case 'p':
            ArkanoidEngine->CountinueGame();
            break;
        case 'R':
        case 'r':
            ArkanoidEngine->RestartGame();
            break;
        case 'W':
        case 'w':
            ArkanoidEngine->IncreasePaddle();
            break;
        case 'S':
        case 's':
            ArkanoidEngine->DecreaseBallSpeed();
            break;
        }
        return;
    }

	// Refresh the Window
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    screenWidth     = w;
    screenHeight    = h;

	glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    glOrtho(-fieldWidth/2, fieldWidth/2, -fieldHeight/2, fieldHeight/2, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    ArkanoidEngine->DrawScene();

	// Flush drawing commands
	glutSwapBuffers();
    glutPostRedisplay();
}

bool Setup(){
    //PlaySound(TEXT("sound.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    return ArkanoidEngine->Init(activeFieldWidth,activeFieldHeight);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Arcanoid");
	
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(KeyPressFunc);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(TimeToIncerasingDifficulty, Timer, 0); // Setup next timer
    if(!Setup()){
        std::cout<<"Arkanoid initialization error!\n";
        std::cin.get();
        return 0;
    }

    glutMainLoop();
    
    return 0;
}
