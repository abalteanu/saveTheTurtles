const int SCREEN_W = 640;       // screen width
const int SCREEN_H = 480;       // screen height

const int COL_1 = 5;    //tabs for chart layout
const int COL_2 = 180;
const int COL_3 = 400;

//#define BACKGROUND al_map_rgb(0x09, 0x31, 0x45)
#define BACKGROUND  al_map_rgb(135, 206, 235)
#define SKYBLUE        al_map_rgb(135, 206, 235)
#define STEELBLUE    al_map_rgb(70, 130, 180)

//defining structures
struct Image {
    ALLEGRO_BITMAP *bitmap;               // picture
    int x, y;                             // position on screen
    int bbRight, bbLeft, bbTop, bbBottom; // boundary box
};
