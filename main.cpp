/****************************************************************************
 Yihsiang Liow
 Copyright
 ****************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Stars.h"
#include "Alien.h"
#include "Player.h"
#include "Laser.h"
#include "Collision.h"
#include "Play.h"

//##############################################################
//
//                   welcome screen menu
//
//##############################################################

int welcome(Surface & surface, Event & event)
{
    Galaxy galaxy(surface);
    galaxy.build();

    Font font("fonts/FreeMonoBoldOblique.ttf", 55);
    Font font_options1("fonts/FreeMonoBoldOblique.ttf", 31);
    Font font_options2("fonts/FreeMonoBoldOblique.ttf", 20);
    Font font_options3("fonts/FreeMonoBoldOblique.ttf", 26);
    Font score("fonts/FreeMonoOblique.ttf", 20);
    Image Title(font.render("GALAXIAN", RED));
    Rect title_rect = Title.getRect();
    title_rect.x = 185;
    title_rect.h = H / 3;

    Image play_(font_options1.render("Press <SPACE> to Play", YELLOW));
    Image close_(font_options2.render("Press <TAB> to Quit", BLUE));
    
    Rect rect_play = play_.getRect();
    rect_play.x = (title_rect.x + title_rect.w / 2 - rect_play.w / 2);
    rect_play.y = title_rect.y + 200;
    Rect rect_close = close_.getRect();
    rect_close.x = (title_rect.x + title_rect.w / 2 - rect_close.w / 2);
    rect_close.y = title_rect.y + 250;

  
    Music music("sounds/GameLoop.ogg");
    music.play();
        
       
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;

        KeyPressed key = get_keypressed();
        if (key[SPACE])
        {
            return 1;
        }
        if (key[UPARROW])
        {
            return 2;
        }
        if (key[TAB])
        {
            return 3;
        }
        surface.lock();
        surface.fill(BLACK);
        surface.put_image(Title, title_rect);
        
        galaxy.draw();
        surface.put_image(play_, rect_play);
        surface.put_image(close_, rect_close);
        surface.unlock();
        surface.flip();
        delay(20);
    }
    return 3;
}

//##############################################################
//
//                            main 
//
//##############################################################

int main(int argc, char* argv[])
{
    srand((unsigned int) time(NULL));

    Surface surface(W, H);
    Event event;
   
    while (1)
    {
        if (event.poll() && event.type() == QUIT)
            break;
        int option = welcome(surface, event);
        switch (option)
        {
            case 0:
                option = welcome(surface, event);
                break;
                
            case 1:
                play(surface, event);
                break;
           
            case 3:
                break;
        }
        if (option == 3)  
        {
            break;
        }
    }
    
    return 0;
}

    
