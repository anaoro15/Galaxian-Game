// File: Collisions between aliens and the lasers

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
#include "Alien.h"
#include "Player.h"
#include "Laser.h"
#include "Collision.h"


void RedAlien_collision(Player & player, std::vector<RedAlien> & alien,
                     Surface & surface, bool & immune)
{

    Sound explode("sounds/explosion.wav");
    for (int i = 0; i < 10; ++i)
    {
        if (alien[i].getDive() && alien[i].Alive())
        {
            double corner1x = player.x() + player.w();
            double corner1y = player.y() + player.h();
            
            double corner2x = alien[i].x() + alien[i].w();
            double corner2y = alien[i].y() + alien[i].h();
            
            int center_x = player.x() + (player.w() / 2);
            int center_y = player.y() + (player.h() / 2);
            int r = 2;
            
            if ((player.x() < alien[i].x() && alien[i].x() < corner1x) &&
                (player.y() < corner2y && corner2y < corner1y) &&player.isAlive())
            {
               
                alien[i].die();
                player.die();
                player.score() += alien[i].pointValue();
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
            if ((alien[i].x() < player.x() && player.x() < corner2x) &&
                (player.y() < alien[i].y() && alien[i].y() < corner1y) &&player.isAlive())
            {
                alien[i].die();
                player.die();
                player.score() += alien[i].pointValue();
                int r = 2;
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
        }
    }
}

void PurpleAlien_collision(Player & player, std::vector<PurpleAlien> & alien,
                     Surface & surface, bool & immune)
{

    Sound explode("sounds/explosion.wav");
    for (int i = 0; i < 10; ++i)
    {
        if (alien[i].getDive() && alien[i].Alive())
        {
            double corner1x = player.x() + player.w();
            double corner1y = player.y() + player.h();
            
            double corner2x = alien[i].x() + alien[i].w();
            double corner2y = alien[i].y() + alien[i].h();
            
            int center_x = player.x() + (player.w() / 2);
            int center_y = player.y() + (player.h() / 2);
            int r = 2;
            
            if ((player.x() < alien[i].x() && alien[i].x() < corner1x) &&
                (player.y() < corner2y && corner2y < corner1y) &&player.isAlive())
            {
               
                alien[i].die();
                player.die();
                player.score() += alien[i].pointValue();
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
            if ((alien[i].x() < player.x() && player.x() < corner2x) &&
                (player.y() < alien[i].y() && alien[i].y() < corner1y) &&player.isAlive())
            {
                alien[i].die();
                player.die();
                player.score() += alien[i].pointValue();
                int r = 2;
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
        }
    }
}
void BlueAlien_collision(Player & player, std::vector<BlueAlien> & alien,
                     Surface & surface, bool & immune)
{

    Sound explode("sounds/explosion.wav");
    for (int i = 0; i < 10; ++i)
    {
        if (alien[i].getDive() && alien[i].Alive())
        {
            double corner1x = player.x() + player.w();
            double corner1y = player.y() + player.h();
            
            double corner2x = alien[i].x() + alien[i].w();
            double corner2y = alien[i].y() + alien[i].h();
            
            int center_x = player.x() + (player.w() / 2);
            int center_y = player.y() + (player.h() / 2);
            int r = 2;
            
            if ((player.x() < alien[i].x() && alien[i].x() < corner1x) &&
                (player.y() < corner2y && corner2y < corner1y) &&player.isAlive())
            {
               
                alien[i].die();
                player.die();
                player.score() += alien[i].pointValue();
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
            if ((alien[i].x() < player.x() && player.x() < corner2x) &&
                (player.y() < alien[i].y() && alien[i].y() < corner1y) &&player.isAlive())
            {
                alien[i].die();
                player.die();
                player.score() += alien[i].pointValue();
                int r = 2;
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
        }
    }
}
