
#include "display.h"

extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;

int loadRules(char text[][200])
{
    ///This function reads the rules text file and loads them to the screen when called
    FILE * filePointer = fopen("rules.txt", "r");

    if (!filePointer)
    {
      al_show_native_message_box(display, "Error", "Error", "Failed to open/find rules.txt to read",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }


    for (int i = 0; i < 12; i++)
    {
        fgets(text[i], 100, filePointer);
        text[i][strlen(text[i])-1]= ' ';    //replace null char with a space
    }


    fclose(filePointer);
    return 0;
}


void displayHighScores(int highscores[], int &stage)
{
    ///This function prints the highscores from the highscore[] array to the screen
    makeBackgrounds(background, backgroundFile);

    for (int k = 0; k <= sizeof(highscores); ++k)
    {
        al_draw_textf (font, BLACK, 0, (k+1)*30, ALLEGRO_ALIGN_LEFT, "%d)    %d", k+1, highscores[k]);//Print each row of text from the text file
    }
    al_flip_display();

    displayBackButton(stage);
}

int loadHighScore(int highScores[])
{
    ///This function reads the highscores from the textfile (checking for updates to highscore since last played)
    FILE * filePointer = fopen("highScores.txt", "r");

    if (!filePointer)
    {
      al_show_native_message_box(display, "Error", "Error", "Failed to open/find highScores.txt to read",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }


    for (int i = 0; i < sizeof(highScores); i++)// or while file not end of file
    {
        fscanf(filePointer, "%d", &highScores[i]);
    }

       // while (filePointer!=EOF)

    fclose(filePointer);
    return 0;
}

int updateHighScores(int points, int highScores[])
{
    ///This function updates the order of the highscore (when a new one is added)
    for (int i = 0; i < sizeof(highScores); i++)
    {

        if(points > highScores[i])
        {
            printf("High score found: %d", points);

            //We need to move down the lower scores by one position, and last one will be lost/dumped
            for(int j=sizeof(highScores)-1; j>=i ; j--)
            {
                highScores[j+1]= highScores[j];
            }

            highScores[i] = points;
            break;
        }
    }

    FILE * filePointer = fopen("highScores.txt", "w");

    if (!filePointer)
    {
      al_show_native_message_box(display, "Error", "Error", "Failed to open/find file highScores.txt to write",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }

    //print score into text file for loop
    for (int i = 0; i < 5; i++)
    {
        fprintf(filePointer, "%d\n", highScores[i]);
    }

    fclose(filePointer);
    return 0;
}

