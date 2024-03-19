// FILE: Alien.cpp

#include <ctime>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Alien.h"
#include "Player.h"

//#############################################################################
//       
//                             Alien images 
// 
//#############################################################################

Image RedAlien::red_alien_("images/galaxian/GalaxianRedAlien.gif");
Image BlueAlien::blu_alien_("images/galaxian/GalaxianAquaAlien.gif");
Image PurpleAlien::pur_alien_("images/galaxian/GalaxianPurpleAlien.gif");
int Alien::numAlive = 0;

//#############################################################################
//       
//   controls the movement of the aliens depending on the bounds of the game
// 
//#############################################################################

void Alien::move()
{
    if (isAlive)
    {
        rect_.x += speed_;
        start_x += speed_;
        if (dive)
        {
            rect_.y += 2.5;
            if (rect_.y == start_y)
            {
                dive = 0;
            }
        }
    }
    if (rect_.x + rect_.w > W)
    {
        speedUpdate();
    }
    if (rect_.x <= 0)
    {
        rect_.x = 1;
        speedUpdate();
    }

    if (rect_.y > H)
    {
        rect_.y = 0;
    }
}

//#############################################################################
//       
//        detects the collision between aliens and the lasers 
// 
//#############################################################################

void Alien::DetectCollision(Laser & laser, int & score)
{
    double corner1x = rect_.x + rect_.w;
    double corner1y = rect_.y + rect_.h;

    double corner2x = laser.x() + laser.w();
    double corner2y = laser.y() + laser.h();

    int center_x = rect_.x + (rect_.w / 2);
    int center_y = rect_.y + (rect_.h / 2);
    int r = 2;

    // handling the sace when laser is inside the alien rectangle
    if ((rect_.x < laser.x() && laser.x() < corner1x) && (rect_.y < corner2y && corner2y < corner1y) && isAlive)
    {
        isAlive = 0;
        laser.isAlive() = 0;
        dive = 0;
        die();
        score += pointValue_;
        laser.playSound();
        for (int i = 0; i < 75; ++i)
        {
            surface_.put_circle(center_x, center_y, r, 254, 4, 4);
            surface_.put_circle(center_x, center_y, r / 2, 232, 215, 8);
            if (i % 2 == 0)
                ++r;
        }
        return;
    }

    // handling the case when laser is touching the sides of the alien rectangle
    if ((laser.x() < rect_.x && rect_.x < corner2x) && (rect_.y < laser.y() && laser.y() < corner1y) && isAlive)
    {
        isAlive = 0;
        laser.isAlive() = 0;
        dive = 0;
        die();
        score += pointValue_;
        
        int r = 2;
        laser.playSound();
        for (int i = 0; i < 75; ++i)
        {
            surface_.put_circle(center_x, center_y, r, 254, 4, 4);
            surface_.put_circle(center_x, center_y, r / 2, 232, 215, 8);
            if (i % 2 == 0)
                ++r;
        }
        return;
    }
}

//#############################################################################
//       
//          shoots the available lasers in the attack mode 
// 
//#############################################################################

void Alien::attack(std::vector<Laser> &lasers)
{
    if (isAlive && !dive)
    {
        Sound pew("sounds/laser.wav");
        start_y = rect_.y;
        dive = 1;
        int available = -1;
        for (int i = 0; i < 5; ++i)
        {
            if (!lasers[i].isAlive())
            {
                available = i;
                break;
            }
        }
        if (available >= 0)
        {
            lasers[available].fire(rect_.x + (rect_.w / 2), rect_.y + 10);
            pew.play();
        }
    }
}

//#############################################################################
//       
//             resets the alien properties after the level is up
// 
//#############################################################################

void Alien::reset(int n)
{
    if (n == 0)
        rect_.x = 0;
    else
        rect_.x = (2 + (rect_.w * n));
    rect_.y = start_y;
    ++numAlive;
    isAlive = 1;
}

//#############################################################################
//       
//                      puts the images of the aliens
// 
//#############################################################################

void RedAlien::Draw()
{
    if (isAlive)
    {
        surface_.put_image(red_alien_, rect_);
    }
}

// Blue Alien
void BlueAlien::Draw()
{
    if (isAlive)
    {
        surface_.put_image(blu_alien_, rect_);
    }
}

// Purple Alien
void PurpleAlien::Draw()
{
    if (isAlive)
    {
        surface_.put_image(pur_alien_, rect_);
    }
}


