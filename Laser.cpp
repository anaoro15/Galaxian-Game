// FILE: Laser.cpp

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

// explosion sound
Sound Laser::explosion("sounds/explosion.wav");

//#############################################################################
//       
//                   function that fires the lasers
// 
//#############################################################################

void Laser::fire(int x, int y)
{
        isLive = 1;
        rect_.x = x;
        rect_.y = y;
    
}

//#############################################################################
//       
//                    moves the laser to top of the screen
// 
//#############################################################################

void Laser::move()
{
    if (type)
        rect_.y -= speed_;
    else
        rect_.y += speed_;
}

//#############################################################################
//       
//                     draws the laser on the screen
// 
//#############################################################################

void Laser::draw()
{
    if (isLive)
        surface_.put_rect(rect_.x, rect_.y, rect_.w, rect_.h, r_, g_, b_);
}

void Laser::stopFire()
{
    isLive = 0;
}
