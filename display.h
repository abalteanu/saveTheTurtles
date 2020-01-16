
#include <iostream>
#include <allegro5/allegro.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_font.h>                  // Font library
#include <allegro5/allegro_ttf.h>                   // For ttf (True Type Font) addon
#include <allegro5/allegro_image.h>                 // For adding images
#include <allegro5/allegro_primitives.h>            // For al_init_primitives_addon()
#include <allegro5/allegro_native_dialog.h> 		// For message box


const float FPS = 60;
const int SCREEN_W = 640;       // screen width
const int SCREEN_H = 880;       // screen height
const char title[30] = "Save the Turtles";
const char backgroundFile[30] = "gameBack.png";
const char menuBackgroundFile[40] = "menuBackground.png";

#define SKYBLUE        al_map_rgb(135, 206, 235)
#define STEELBLUE    al_map_rgb(70, 130, 180)
#define RED         al_map_rgb(255, 0, 0)
#define FOREGROUND al_map_rgb(0x3C, 0x64, 0x78)
#define PINK        al_map_rgb(255, 0, 255)
#define BLACK       al_map_rgb(0, 0, 0)
#define BACKGROUND_FILE "gameBack.png"

//defining structures

struct Character
{
    ALLEGRO_BITMAP *bitmap;
    int moveD = 0;  // units that it moves
    int moveU = 0;
    int bbRight, bbLeft, bbTop, bbBottom; // boundary box
    int x, y;
    const char *filename;
    ALLEGRO_BITMAP *frame [3];
};

struct Image
{
    ALLEGRO_BITMAP *bitmap;                 // picture
    int x, y;                               // position on screen
    float bbRight, bbLeft, bbTop, bbBottom; // boundary box
    int zoomX, zoomY;
    float time;                             // resting time
    int direction = 0;
    int speed = 1;
    bool print = 1;                         // if print is 0, the reloadScreen function draws over the image
};

struct Button
{
    ALLEGRO_BITMAP * bitmap;
    int x,y;
    float bbRight, bbLeft, bbTop, bbBottom; // boundary box
    const char *text;
    bool click;
};


/// Prototyping
//display.cpp
void initializeAllegro();
void createDisplay (const char title[]);
int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font);
int makeBackgrounds(ALLEGRO_BITMAP *&background, const char fileName[]);
void allegroShutDown(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_BITMAP *background);

//ImageFunctions.cpp
int loadSprite(Image &myImg, const char *filename);
void setPosition(Image &myImg, int xPos, int yPos, int zoomX, int zoomY);
void printSprite(Image &myImg, const char *filename, int xPos, int yPos, int zoomX, int zoomY);
int loadCharacter(Character &myHook, const char *filename, int xPos, int yPos);
void setCharacterPosition(Character &myHook, int xPos, int yPos);
void reloadScreen(Character person, Image cup1[], Image &boat, int score, ALLEGRO_BITMAP * background, Image cup2[], double time);
void moveGarbage(ALLEGRO_EVENT event, Image &garbage);
void calcBoundsCharacter(Character &myHook);
void calcBounds(Image &myImg);
void moveToTrash(Image &myImg);
bool isCollision(Character &a, Image &b);

//gameplay.cpp
void playGame(int &points, int &stage);
void moveCharacter(ALLEGRO_EVENT event, Character &hook);
void moveCharacter(ALLEGRO_EVENT event, Character &hook, int &mode);
void printTime(double time);
void checkTime(ALLEGRO_EVENT event, double time, int &stage);
void gameOver();

//menuFunctions.cpp
void mainMenu(int &points, int &stage);
void displayRules(int &points, int &stage);

//buttonFunctions.cpp
void calcBoundsButton(Button &myImg);
int makeButton(Button &myButton, const char *filename, int xPos, int yPos, const char *text);
bool pressButton(const Button &a, int mouseX, int mouseY);
void displayBackButton(int &stage);

//textFileFunctions.cpp
int loadRules(char text[][200]);
void displayHighScores(int highScores[], int &stage);
int loadHighScore(int highScores[]);
int updateHighScores(int points, int highScores[]);




