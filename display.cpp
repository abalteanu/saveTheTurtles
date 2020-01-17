#include "display.h"

extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;


void initializeAllegro()
{
    ///This function initializes allegro and other addons
    // Initialize Allegro
	al_init();


	al_init_font_addon();   //initialize font addon
    al_init_ttf_addon();    //initialize True Type Font addon

}

void createDisplay(const char title [])
{
    ///This function creates the display and names the window
    display = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_title(display, title);
    font = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 24, 0);
}

int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font)
{
    ///This function checks all initializations (display, keyboard, etc.) and creates a timer and an event queue
    //checking initialization of allegro
    if(!al_init())
    {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }

    //check display
	if (!display)
    {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

   	// Initialize keyboard routines
	if (!al_install_keyboard())
    {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

   	// Initialize mouse
   	if (!al_install_mouse())
    {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the mouse!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

	// Adding image processor
 	if (!al_init_image_addon())
    {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	// Setting up timer
	timer = al_create_timer(1.0 / FPS);

   	if (!timer)
    {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }


    if (!font)
    {
        al_show_native_message_box(display, "Error", "Error", "Could not load font 1.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Initialize primative add on
 	if (!al_init_primitives_addon())
    {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	// set up event queue
	event_queue = al_create_event_queue();

	if (!event_queue)
    {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}


	return 0; //WILL THIS RETURN 0 EVEN IF THE ERROR IS REAL??

}

int makeBackgrounds(ALLEGRO_BITMAP *&background, const char fileName[])
{
    ///This function makes the desired background
    int w = SCREEN_W;
    int h = SCREEN_H;

    background = al_load_bitmap(fileName);
    //al_draw_bitmap(background,0 , 0, 0);
    al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, w, h, 0);

    if(!background)
    {
        fprintf(stderr, "failed to load background bitmap!\n");
        return -1;  //breaks out of function if error occurs, returns -1 instead of 0
    }

    al_flip_display();

    return 0;
}

void allegroShutDown(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_BITMAP *background)
{
    ///This function shuts down allegro
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    //al_uninstall_audio();
    //al_shutdown_ttf_addon();
    al_shutdown_image_addon();
    al_uninstall_mouse();
    al_shutdown_font_addon();
    al_destroy_timer(timer);
    al_uninstall_keyboard();
    al_shutdown_primitives_addon();
    al_destroy_bitmap(background);
    al_destroy_bitmap(menuBackground);
    al_uninstall_system();
}
