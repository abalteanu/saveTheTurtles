#include "display.h"

extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;

void mainMenu(int &points, int &stage)
{
    ///This function loads the main menu and its buttons and paths
    makeBackgrounds(menuBackground, menuBackgroundFile);

    Image turtle;
    printSprite(turtle, "turtle.png", 450, 400, 175, 175);

    Image titleImg;
    printSprite(titleImg, "title.png", 0, 0, 320, 220);

    Button play;
    makeButton(play, "button1.png", 100, 300, "play");
    calcBoundsButton(play);

    Button highscores;
    makeButton(highscores, "button1.png", 100, 400, "highscores");
    calcBoundsButton(highscores);

    Button rules;
    makeButton(rules, "button1.png", 100, 500, "rules");
    calcBoundsButton(rules);

    Button exit;
    makeButton(exit, "button1.png", 100, 600, "exit");
    calcBoundsButton(exit);

    ///Button play points highscore rules exit

    while (stage == 0)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);    //waiting for event in the queue

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
        {
            stage = -1;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            //Determine which of the button was pressed:

            int pressedButton = -1;

            if (pressButton(play, ev.mouse.x, ev.mouse.y))
            {
                pressedButton =1;
            }
            else if (pressButton (highscores, ev.mouse.x, ev.mouse.y))
            {
                pressedButton = 2;
            }
            else if (pressButton (rules, ev.mouse.x, ev.mouse.y))
            {
                pressedButton = 3;
            }
            else if (pressButton (exit, ev.mouse.x, ev.mouse.y))
            {
                pressedButton = 0;
            }

            switch (pressedButton)
            {
            case 1:
                //play button
                stage = 1;
                break;
            case 2:
                // highscore button
                stage = 2;
                break;
            case 3:
                //rules button
                stage = 3;
                break;
            case 0:
                //exit button
                stage = -1;
                break;
            default:
                //none of the buttons
                break;
            }
        }
    }
}


void displayRules(int &points, int &stage)
{
    ///This function displays the rules from the text file when called
    makeBackgrounds(background, backgroundFile);

    Button backButton;
    makeButton(backButton, "button1.png", 500, 800, "back");
    calcBoundsButton(backButton);

    char rules[12][200];
    loadRules(rules);
    for (int k = 0; k < 12; ++k)
    {
        al_draw_textf (font, BLACK, 0, (k+1)*30, ALLEGRO_ALIGN_LEFT, rules[k]);//Print each row of text from the text file
    }
    al_flip_display();

    while (stage == 3)
    { // Keep going until we hit escape.

        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);    //waiting for event in the queue
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {   //closes the rules page
            stage = 0;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (pressButton(backButton, ev.mouse.x, ev.mouse.y))
            {   //if back button is pressed
                stage = 0;
            }
        }
    }
}

