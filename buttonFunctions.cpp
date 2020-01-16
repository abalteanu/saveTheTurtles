#include "display.h"

extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;

int makeButton(Button &myButton, const char *filename, int xPos, int yPos, const char *text)
{
    myButton.bitmap = al_load_bitmap(filename);

    if(!filename)
    {
        fprintf(stderr, "failed to load button bitmap!\n");
        return -1;  //breaks out of function if error occurs, returns -1 instead of 0
    }

    myButton.x = xPos;
    myButton.y = yPos;

    /*
    al_draw_scaled_bitmap(myButton.bitmap,
                          0, 0,
                          al_get_bitmap_width(myButton.bitmap), al_get_bitmap_height(myButton.bitmap),
                          xPos, yPos,
                          zoomX, zoomY,
                          0);
                          */

    al_draw_bitmap(myButton.bitmap, xPos, yPos, 0);
    al_draw_textf(font, STEELBLUE, xPos, yPos, ALLEGRO_ALIGN_LEFT, text);
    al_flip_display();

    myButton.text = text;

    myButton.click = false;

    return 0;
}

void calcBoundsButton(Button &myImg)
{
    myImg.bbLeft = myImg.x; printf("Button left: %f\n", myImg.bbLeft);
	myImg.bbTop = myImg.y;
	myImg.bbRight = myImg.bbLeft + al_get_bitmap_width(myImg.bitmap);
	myImg.bbBottom = myImg.bbTop + al_get_bitmap_height(myImg.bitmap);
}

bool pressButton(const Button &a, int mouseX, int mouseY)
{
    bool bPressed = false;

    printf("bbleft of play = %f\n",a.bbLeft);
    printf("bbRight of play = %f\n>>",a.bbRight);
    printf("bbTop of play = %f\n>>",a.bbTop);
    printf("bbBootom of play = %f\n",a.bbBottom);



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

    printf ("Real button pressed: %d\n:", bPressed);
    return bPressed;
}

void displayBackButton( int &stage)
{
    Button backButton;
    makeButton(backButton, "button1.png", 500, 800, "back");
    calcBoundsButton(backButton);

    while (stage != 0)
    { // Keep going until we hit escape.

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

