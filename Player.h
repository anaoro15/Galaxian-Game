// FILE: Player.h

#ifndef PLAYER_H
#define PLAYER_H

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
#include "Laser.h"

//#############################################################################
//       
//                             Player class 
// 
//#############################################################################

class Player
{
public:
    // lives initialized with 3 
    Player(Surface & surface, int l = 3)
        :surface_(surface), lives_(l)
    {
        // calculates the position of the spaceshift
        rect_ = you_.getRect();
        rect_.y = surface.h() - 75;
        rect_.x = (surface.w()) / 2 - rect_.w;
    }
    // returns the x coordinate of the spaceshift
    int x()
    {   
        return rect_.x;  
    }
    // returns the y coordinate of the spaceshift
    int y()
    {
        return rect_.y;
    }
    // returns the width of the spaceshift
    int w()
    {
        return rect_.w;
    }
    // returns the height of the spaceshift
    int h()
    {
        return rect_.h;
    }
    // returns the score
    int score() const
    {
        return score_;
    }
    // reference score (used to adjust the score)
    int & score()
    {
        return score_;
    }
    // returns the current number of lives
    int lives() const
    {
        return lives_;
    }
    // returns true if player is alive
    bool isAlive() const
    {
        return alive;
    }
    // used to adjust if the player is alive or not
    bool & isAlive()
    {
        return alive;
    }
    // decrements the lives and plays the sound 
    void die()
    {
        --lives_;
        explode_.play();
    }
    // used to revive the player, positions the player back to old spot
    void revive()
    {
        alive = 1;
        rect_.x = (surface_.w()) / 2 - rect_.w;
    }
    // these methods are implemented in the Player.cpp file
    void Draw();
    void move();
    void DetectCollision(Laser & laser);
       
private:
    // rect of the spaceshift
    Rect rect_;
    Surface surface_;
    // speed of the spaceshift
    double speed_ = 3.0;
    // alive set to true
    bool alive = 1;   
    int lives_;
    // score initialized to 0
    int score_ = 0;
    static Image you_;
    static Sound explode_;
};
#endif
