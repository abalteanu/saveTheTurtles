#include "display.h"

extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;


void playGame(int &points, int &stage)
{
    ///This function is the official game play function, all the steps for each part of the actual game occur here.

    makeBackgrounds(background, backgroundFile);

    Image boat;
    printSprite(boat, "boat4.png", 300, 50, 0, 0);

    Image cup1[5];
    for (int i=0; i<5; i++)
    {
        //prints an array of garbage
        printSprite(cup1[i], "mcDonalds.png", i*100, 800, 0, 0);
        calcBounds(cup1[i]);
    }

    Image cup2[5];
    for (int i=0; i<5; i++)
    {
        //prints an array of garbage
        printSprite(cup2[i], "mcDonalds.png", i*100, 500, 0, 0);
        cup2[i].speed = 2;
        calcBounds(cup2[i]);
    }

    //making hook image
    struct Character hook;
    loadCharacter(hook, "hook.png", 270, 200);
    al_draw_bitmap(hook.bitmap, hook.x, hook.y, 0); //Draw hook
    al_flip_display();


    al_start_timer(timer);  //starting timer

    //for game timer
    double startTime = al_get_time();
    double endTime = 0;
    double currentTime;

    int hookMode = 1; //1 - moving down, 0 - moving up

    ///gameplay loop
    while (stage == 1)
    {

        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);    //waiting for event in the queue

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)// Keep going until we hit Close DISPLAY (X button).
        {
            stage = 0;
        }
        else
        {
            endTime = al_get_time();    //detecting time at time of play

            currentTime = 30-(endTime - startTime);     //countdown from 30 seconds
            checkTime(ev, currentTime, stage);  //prints time to screen and ends game has reached 0 seconds

            if (stage == 0)
                break;

            for (int i=0; i<5; i++) //moving garbage arrays
            {
                moveGarbage(ev, cup1[i]);
                moveGarbage(ev, cup2[i]);
            }

            moveCharacter(ev, hook, hookMode);  //moves hook


            for (int j=0; j<5; j++)
            {
                //for cup1, processing if the cup was caught
                if (cup1[j].print == 1)     //if the cup is being printed (is not in garbage)
                {
                    if (isCollision(hook, cup1[j]) == true)//check for collision
                    {
                        //reeling in the garbaage
                        points+=30; //adding points to total
                        for(int i=hook.y; i>200; i--)
                        {
                            //reels the garbage and cup upwards
                            hook.y-=1;
                            cup1[j].y-=1;
                            al_rest(0.001);     //so user can see the hook being reeled up
                            reloadScreen(hook, cup1, boat, points, background, cup2, currentTime);

                        }
                        moveToTrash(cup1[j]);   //moves the garbage collected to inventory once it is collected
                        cup1[j].print = 0;      //stop printing the cup
                    }
                }

                //processing images of cup2
                //this is repeating code, but there are so many parameters in the reloadScreen function that making a separate function would be pointless
                if (cup2[j].print == 1)     //if the cup is being printed (is not in garbage)
                {
                    if (isCollision(hook, cup2[j]) == true)
                    {
                        //make a reel hook in funciotn reelHook
                        points+=10;     //only ten points for cups nearer to the surface
                        for(int i=hook.y; i>200; i--)
                        {
                            //reels the garbage and cup upwards
                            hook.y-=1;
                            cup2[j].y-=1;
                            al_rest(0.001);     //so user can see the hook being reeled up
                            reloadScreen(hook, cup1, boat, points, background, cup2, currentTime);
                        }
                        moveToTrash(cup2[j]);   //moves the garbage collected to inventory once it is collected
                        cup2[j].print = 0;      //stop printing the cup
                    }
                }
            }

        }
        //redraw all the images
        reloadScreen(hook, cup1, boat, points, background, cup2, currentTime);
    }


}

void moveCharacter(ALLEGRO_EVENT event, Character &hook, int &mode)
{
    ///This function moves the hook downwards
    calcBoundsCharacter(hook);

    if (event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (event.keyboard.keycode == ALLEGRO_KEY_DOWN && mode == 1)
        {
            hook.moveD = 3;
        }
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                    hook.moveD = -4;
                    mode = 0;
            }
    }
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        // applying movement to hook
        if (hook.y >= 200)
        {
            hook.y += hook.moveD;
        }
        else
        {
            hook.y = 200;
            mode = 1;
        }
    }
}

void printTime(double time)
{
    ///This function prints the time on the screen when called
    al_draw_textf(font, STEELBLUE, 0, 60, ALLEGRO_ALIGN_LEFT, "%0.2f", time);
    al_flip_display();

}

void checkTime(ALLEGRO_EVENT event, double time, int &stage)
{
    ///This function checks the time and prints the time to screen when called
    printTime(time);

    if (time < 0) //breaks out of loop when 0s has been reached
    {
        gameOver();
        displayBackButton(stage);
        stage = 0;
    }
}

void gameOver()
{
    ///This function prints game over to the screen when the timer runs out (or when called)
    struct Image imgOver;
    printSprite(imgOver, "gameOver.png", 150, 500, 300, 300);
}


