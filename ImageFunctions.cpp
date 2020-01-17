#include "display.h"

extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;

int loadSprite(Image &myImg, const char *filename)
{
    ///This function loads the image file to struct location and makes sure it works
    myImg.bitmap = al_load_bitmap(filename);
    if (myImg.bitmap == nullptr)
    {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        allegroShutDown(display, event_queue, background);
        return -1;
    }
    return 0;
}

void setPosition(Image &myImg, int xPos, int yPos, int zoomX, int zoomY)
{
    ///This function sets the position of the image on the screen
    myImg.x = xPos;
    myImg.y = yPos;
    myImg.zoomX = zoomX;
    myImg.zoomY = zoomY;
}

void printSprite(Image &myImg, const char *filename, int xPos, int yPos, int zoomX, int zoomY)
{
    ///This function just draws the image to the screen (so that this does not have to be done in main) and flips the display
    loadSprite(myImg, filename);
    setPosition(myImg, xPos, yPos, zoomX, zoomY);
    //al_draw_bitmap(myImg.bitmap, xPos, yPos, 0);

    al_draw_scaled_bitmap(myImg.bitmap,
                          0, 0,
                          al_get_bitmap_width(myImg.bitmap), al_get_bitmap_height(myImg.bitmap),
                          xPos, yPos,
                          zoomX, zoomY,
                          0);


    al_flip_display();
}

int loadCharacter(Character &myHook, const char *filename, int xPos, int yPos)
{
    ///This function is similar to load sprite, but it also sets position and is specific to the moving character (the struct is different)
    myHook.bitmap = al_load_bitmap(filename);
    if (myHook.bitmap == nullptr)
    {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        allegroShutDown(display, event_queue, background);
        return -1;
    }

    //setting position
    setCharacterPosition(myHook, xPos, yPos);
    return 0;
}

void setCharacterPosition(Character &myHook, int xPos, int yPos)
{
    ///This function sets the position of the image on the screen (for character struct only)
    myHook.x = xPos;
    myHook.y = yPos;
}

void reloadScreen(Character person, Image cup1[], Image &boat, int score, ALLEGRO_BITMAP * background, Image cup2[], double time)
{
    ///This function reloads existing images and updates screen
    int w = SCREEN_W;
    int h = SCREEN_H;

    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, w, h, 0);
    al_draw_textf(font, STEELBLUE, 0, 0, ALLEGRO_ALIGN_LEFT, "Press down arrowkey to begin fishing!");   //drawing score
    al_draw_textf(font, STEELBLUE, 0, 30, ALLEGRO_ALIGN_LEFT, "Score: %d", score);   //drawing score
    al_draw_bitmap(person.bitmap, person.x, person.y, 0); //Draw hook

    //reprinting cup1
    for (int i=0; i<5; i++)//draws array of cups
    {
        if (cup1[i].print == 1)
        {
            al_draw_bitmap(cup1[i].bitmap, cup1[i].x, cup1[i].y, 0); //Draw cup
            calcBounds(cup1[i]);    //recalculates bounding box
        }
    }

    //reprinting cup2
    for (int i=0; i<5; i++)//draws array of cups
    {
        if (cup2[i].print == 1)
        {
            al_draw_bitmap(cup1[i].bitmap, cup2[i].x, cup2[i].y, 0); //Draw cup
            calcBounds(cup2[i]);    //recalculates bounding box
        }
    }

    if (boat.print == 1)    //Draw boat
    {
        al_draw_bitmap(boat.bitmap, boat.x, boat.y, 0);
    }
    printTime(time);

    al_flip_display();
}

void moveGarbage(ALLEGRO_EVENT event, Image &garbage)
{
    ///This function moves the garbage sprite array
    int screenW = SCREEN_W;
    int imageW = al_get_bitmap_width(garbage.bitmap);

    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        if (garbage.x < 0)  //changes direction of movement depending on which side of the screen the cups are
            garbage.direction = 0;

        if (garbage.x > screenW - imageW)
            garbage.direction = 1;

        switch(garbage.direction)   //applies movement
        {
        case 0:
            garbage.x+= garbage.speed;
            break;
        case 1:
            garbage.x-= garbage.speed;
            break;
        }
    }
}

void calcBoundsCharacter(Character &myHook)
{
    ///This function calculates the bounds for the character image
    myHook.bbLeft = myHook.x;
	myHook.bbTop = myHook.y;
	myHook.bbRight = myHook.bbLeft + al_get_bitmap_width(myHook.bitmap);
	myHook.bbBottom = myHook.bbTop + al_get_bitmap_height(myHook.bitmap);

}
void calcBounds(Image &myImg)
{
    ///This function calculates the bounds for an image
    myImg.bbLeft = myImg.x;
	myImg.bbTop = myImg.y;
	myImg.bbRight = myImg.bbLeft + al_get_bitmap_width(myImg.bitmap);
	myImg.bbBottom = myImg.bbTop + al_get_bitmap_height(myImg.bitmap);
}

void moveToTrash(Image &myImg)
{
    ///This function does the animation for pulling the cup upwards with the hook
    int ImgW = al_get_bitmap_width(myImg.bitmap);
    int screenW = SCREEN_W;
    myImg.y = 0;
    myImg.x = screenW - ImgW;
}

bool isCollision(Character &a, Image &b) {
    ///This function checks if the bounding box of two images have collided (collision detection)
    if (a.bbBottom < b.bbTop)
    {
        return false;
    }
    else if (a.bbTop > b.bbBottom)
    {
        return false;
    }
    else if (a.bbRight < b.bbLeft)
    {
        return false;
    }
    else if (a.bbLeft > b.bbRight)
    {
        return false;
    }
    return true;
}
