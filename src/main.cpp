#include "utils/OpenGLInclude.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>

#include "devices/Keyboard.h"
#include "devices/Mouse.h"
#include "scene/Camera.h"
#include "scene/Scene.h"
#include "utils/GlutUtils.h"
#include "utils/ImageUtils.h"
#include "utils/Logger.h"
#include "utils/Timer.h"
#include "utils/Config.h"

using namespace std;

Scene* scene;
Camera* camera;
Keyboard* keyboard;
Mouse* mouse;

bool blockMouseMove = false;

const int WINDOW_INIT_POS_X = 100;
const int WINDOW_INIT_POS_Y = 100;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const string WINDOW_TITLE = "Symulacja wulkanu";

void initOpenGlEnvironment(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(WINDOW_INIT_POS_X, WINDOW_INIT_POS_Y);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(WINDOW_TITLE.c_str());

    glewInit();
    scene->initFBO(); // musi być po glewInit(), więc nie mogło być w konstruktorze Scene()

    glClearColor(Config::getInstance()->colorSky[0], Config::getInstance()->colorSky[1], Config::getInstance()->colorSky[2], 1.0);

    glutIgnoreKeyRepeat(1);
}

string configFileName;

void printWithTimestamp(string s) {
    time_t t = time(0);
    struct tm * now = localtime(&t);
    cout << "["
         << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << ' '
         <<  now->tm_hour << ':'
         <<  now->tm_min << ':'
         <<  now->tm_sec << "] "
         << s << endl;
}

void exitProgram() {
    // Łączymy powstałe klatki w plik video.
    if(Config::getInstance()->dumpFrames) {
        string imagesToVideoCmd = "ffmpeg.exe -y -loglevel panic -i frames\\test_%d.tga -c:v ffv1 -qscale:v 0 .\\" + configFileName + ".avi";
        system(imagesToVideoCmd.c_str());
    }

    printWithTimestamp("  Koniec przetwarzania " + configFileName);

    exit(0);
}

void display() {
    Timer::getInstance().incrementFrame();
    int currentFrame = Timer::getInstance().getCurrentFrame();
    if(currentFrame > Config::getInstance()->maxFrames) {
        exitProgram();
    }

    if(currentFrame % Config::getInstance()->framesToSkipRender != 0) {
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera->update(keyboard, mouse);

    scene->draw();
    Logger::getInstance().printOnScreen();

    if (Config::getInstance()->dumpFrames) {
        char frameString[20];
        string fileName = string("test_") + itoa(currentFrame / Config::getInstance()->framesToSkipRender, frameString, 10) + ".tga";
        dumpScreenToImage(fileName);
    }

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (height == 0) {
        height = 1;
    }
    GLfloat screenRatio = 1.0 * width / height;

    glViewport(0, 0, width, height);
    gluPerspective(camera->viewAngle, screenRatio, camera->viewMinDistance, camera->viewMaxDistance);

    glMatrixMode(GL_MODELVIEW);
}

void onKeyDown(unsigned char asciiKey, int mouseX, int mouseY) {
    keyboard->asciiKeyDown(asciiKey);
    if (keyboard->isAsciiKeyPressed(27)) { // ESC
        exitProgram();
    }

    if (keyboard->isAsciiKeyPressed('\t')) {
        camera->toggleFpsMode();
    }
    if (keyboard->isAsciiKeyPressed('r')) {
        scene->setStartingConditions();
    }
    if (keyboard->isAsciiKeyPressed('q')) {
        scene->tooglePlayback();
    }

}

void onKeyUp(unsigned char asciiKey, int mouseX, int mouseY) {
    keyboard->asciiKeyUp(asciiKey);
}

void onIdle() {
    scene->proceed();
    glutPostRedisplay();
}

void onMouseClick(int button, int state, int mouseX, int mouseY) {
    mouse->toggleButton(button, state);
}

void onMouseMove(int mouseX, int mouseY) {
    if (blockMouseMove || !camera->isFpsModeOn()) {
        blockMouseMove = false;
        //zabezpieczenie przed rekurencyjnym wykonaniem w glutWarpPointer poniżej
        return;
    }

    camera->rotate(mouseX, mouseY);

    glutWarpPointer(getWindowMiddleX(), getWindowMiddleY());
    blockMouseMove = true;
}

void addEventListeners() {
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMouseFunc(onMouseClick);
    glutMotionFunc(onMouseMove);
    glutPassiveMotionFunc(onMouseMove);

    glutKeyboardFunc(onKeyDown);
    glutKeyboardUpFunc(onKeyUp);

    glutIdleFunc(onIdle);
}

int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    if(argc != 2) {
        cerr << "Błędne wywołanie, spróbuj tak:" << endl;
        cerr << argv[0] << " plik_konfiguracyjny" << endl;
        exit(0);
    }

    configFileName = string(argv[1]);
    Config::init(configFileName);
    system("del frames\\*.tga");

    camera = new Camera();
    scene = new Scene(camera);
    keyboard = new Keyboard();
    mouse = new Mouse();

    printWithTimestamp("Początek przetwarzania " + configFileName);

    initOpenGlEnvironment(argc, argv);
    addEventListeners();
    glutMainLoop();

    return 0;

}

