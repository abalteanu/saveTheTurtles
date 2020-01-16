#include "display.h"

extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;


void playGame(int &points, int &stage)
{
    //game
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
        loadCharacter(hook, "hook.png", 270, 170);
        al_draw_bitmap(hook.bitmap, hook.x, hook.y, 0); //Draw hook
        al_flip_display();

        ///gameplay loop
        bool exitgame = false;
        al_start_timer(timer);

        //for game timer
        double startTime = al_get_time();
        printf("\n START TIME %f\n",startTime); //starts counting when compiled
        double endTime = 0;
        double currentTime;

        while (stage == 1)
        { // Keep going until we hit Close DISPLAY (X button).

            ALLEGRO_EVENT ev;

            al_wait_for_event(event_queue, &ev);    //waiting for event in the queue


            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                stage = 0;
            }
            else //ev.type == ALLEGRO_EVENT_TIMER)
            {
                endTime = al_get_time();    //detecting time at time of play
                //printf("\n%f\n",endTime);

                currentTime = endTime - startTime;
                checkTime(ev, currentTime, stage);  //prints time to screen and ends game if over 60 seconds

                if (stage == 0)
                    break;

                //printTime(ev, currentTime, stage);

                for (int i=0; i<5; i++)
                {
                    moveGarbage(ev, cup1[i]);
                    moveGarbage(ev, cup2[i]);
                }

                moveCharacter(ev, hook);


                for (int j=0; j<5; j++){
                    //reloadImages(hook, cup1, boat, points);
                    if (cup1[j].print == 1)     //if the cup is being printed (is not in garbage
                    {
                        if (isCollision(hook, cup1[j]) == true)
                        {
                            //make a reel hook in funciotn reelHook
                            points+=30;
                            for(int i=hook.y; i>50; i--)
                            {
                                //reels the garbage and cup upwards
                                hook.y-=1;
                                cup1[j].y-=1;
                                al_rest(0.001);     //so user can see the hook being reeled up
                                reloadImages(hook, cup1, boat, points, background, cup2);

                            }
                            moveToTrash(cup1[j]);   //moves the garbage collected to inventory once it is collected
                            cup1[j].print = 0;      //stop printing the cup
                        }
                    }

                    //processing images of cup2
                    if (cup2[j].print == 1)     //if the cup is being printed (is not in garbage
                    {
                        if (isCollision(hook, cup2[j]) == true)
                        {
                            //make a reel hook in funciotn reelHook
                            points+=10;
                            for(int i=hook.y; i>50; i--)
                            {
                                //reels the garbage and cup upwards
                                hook.y-=1;
                                cup2[j].y-=1;
                                al_rest(0.001);     //so user can see the hook being reeled up
                                reloadImages(hook, cup1, boat, points, background, cup2);
                            }
                            moveToTrash(cup2[j]);   //moves the garbage collected to inventory once it is collected
                            cup2[j].print = 0;      //stop printing the cup
                        }
                    }
                    //reloadImages(hook, cup1, boat, points);
                }

            }


            //redraw all the images
            reloadImages(hook, cup1, boat, points, background, cup2);
        }


}



void moveCharacter(ALLEGRO_EVENT event, Character &hook)
{
    calcBoundsCharacter(hook);

    if (event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            hook.moveD = 3;
        }
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
            //if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            //{
                    hook.moveD = -4;
            //}
    }
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        // applying movement to hook
        if (hook.y >= 100)
        {
            hook.y += hook.moveD;
        }

        else if (hook.y <= 100)
        {
            //this fixes my out of bounds problem... but how do i make it look smoother
            hook.y = 101;
        }

        //printf("%d\n",hook.moveD);
    }
}

void printTime(ALLEGRO_EVENT event, double time)
{
    //if (event.type == ALLEGRO_EVENT_TIMER)

        al_draw_textf(font, STEELBLUE, 0, 30, ALLEGRO_ALIGN_LEFT, "%0.2f", time);
        al_flip_display();

}

void checkTime(ALLEGRO_EVENT event, double time, int &stage)
{
        printTime(event, time);

        if (time > 10) //breaks out of loop when 10s has been reached
        {
            gameOver();
            displayBackButton(stage);
            stage = 0;
            //break;
        }

}

void gameOver()
{
    struct Image imgOver;
    printSprite(imgOver, "gameOver.png", 200, 500, 200, 200);
}



