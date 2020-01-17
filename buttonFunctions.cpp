#include "display.h"

extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;

int makeButton(Button &myButton, const char *filename, int xPos, int yPos, const char *text)
{
    ///This function makes a button and draws it to the screen when it is called
    myButton.bitmap = al_load_bitmap(filename);

    if(!filename)
    {
        fprintf(stderr, "failed to load button bitmap!\n");
        return -1;  //breaks out of function if error occurs, returns -1 instead of 0
    }

    myButton.x = xPos;
    myButton.y = yPos;

    al_draw_bitmap(myButton.bitmap, xPos, yPos, 0);
    al_draw_textf(font, STEELBLUE, xPos, yPos, ALLEGRO_ALIGN_LEFT, text);
    al_flip_display();

    myButton.text = text;

    myButton.click = false;

    return 0;
}

void calcBoundsButton(Button &myImg)
{
    ///This function calculates the bounds of the button
    myImg.bbLeft = myImg.x;
	myImg.bbTop = myImg.y;
	myImg.bbRight = myImg.bbLeft + al_get_bitmap_width(myImg.bitmap);
	myImg.bbBottom = myImg.bbTop + al_get_bitmap_height(myImg.bitmap);
}

bool pressButton(const Button &a, int mouseX, int mouseY)
{
    ///This function checks if the button has been pressed
    bool bPressed = false;

    if (a.bbTop < mouseY && mouseY < a.bbBottom )
    {
        if( a.bbLeft < mouseX &&  mouseX < a.bbRight )
        {
            bPressed = true;
        }
        else
        {
            bPressed = false;
        }
    }

    return bPressed;
}

void displayBackButton( int &stage)
{
    ///This button creates a back button specifically
    Button backButton;
    makeButton(backButton, "button1.png", 500, 800, "back");
    calcBoundsButton(backButton);

    while (stage != 0)
    {
            ALLEGRO_EVENT ev;

            al_wait_for_event(event_queue, &ev);    //waiting for event in the queue
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                stage = 0;
            }
            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                if (pressButton(backButton, ev.mouse.x, ev.mouse.y))
                {
                    stage = 0;
                }
            }
        }
}

