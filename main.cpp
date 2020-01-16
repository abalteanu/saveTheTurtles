/// This program will be the base game for the SAVE THE TURTLES summative game  ///
/// Ana Balteanu

#include "display.h"    // Include the header file.


ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_FONT *font = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_BITMAP *background = nullptr;
ALLEGRO_BITMAP* menuBackground = nullptr;

// NOTE: argc, argv parameters are required.
int main(int argc, char *argv[])
{
    /**     Setup      **/

    //initializing allegro
    initializeAllegro();

    // create a display
    createDisplay(title);

    //checking initialization allegro
	checkSetup(display, font);

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    /**     Game        **/

    int stage = 0;
    int points = 0;
    int exitGame = 0;

    int highScores[5]= {0,0,0,0,0};
    loadHighScore(highScores);

    while (!exitGame)
    {
        switch (stage)
        {
        case 0:
            // main menu and path choice
            mainMenu(points, stage);
            break;

        case 1:
            //game case
            printf("case 1 begin\n");
            points = 0;
            playGame(points, stage);
            //AFter game is over, user closed or timer done, update High Scores:
            updateHighScores(points, highScores);
            break;
        case 2:
            displayHighScores(highScores, stage);
            break;
        case 3:
            displayRules(points, stage);
            break;
        default:
            allegroShutDown(display, event_queue, background);
            exitGame = true;    //exists game loop
            break;
        }// switch bracket
    }


	/**     Ending Program      **/



    // Exit with no errors
	return 0;

}
