// FILE: Laser.h

#ifndef LASER_H
#define LASER_H

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

//#############################################################################
//       
//                               Laser class
// 
//#############################################################################

class Laser
{
public:
    // constructor takes in color r,g,b, and type is set to 1
    Laser(Surface & surface, int r, int g, int b, bool t = 1)
    :surface_(surface), r_(r), g_(g), b_(b), type(t)
    {
        // the width and height of the laser is set
        rect_.w = 3;
        rect_.h = 10;
    }
    // returns the x coordinate of the laser rect
    int x()const
    {
        return rect_.x;
    }
    // returns the y coordinate of the laser rect
    int y()const
    {
        return rect_.y;
    }
    // returns the width of the laser rect
    int w()const
    {
        return rect_.w;
    }
    // returns the height of the laser rect
    int h()const
    {
        return rect_.h;
    }
    // returns true if the laser is available
    bool isAlive() const
    {
        return isLive;
    }
    // used to adjust laser availability
    bool & isAlive()
    {
        return isLive;
    }
    // plays the sound when laser fired
    void playSound()
    {
        explosion.play();
    }
    // these methods are implemented in the Laser.cpp file
    void fire(int, int);
    void stopFire();
    void move();
    void draw();

private:
    Rect rect_;
    bool isLive = 0;
    double speed_ = 6.75;
    int r_,g_,b_;
    Surface surface_;
    bool type;
    static Sound explosion;
    friend class Player;
};
#endif
