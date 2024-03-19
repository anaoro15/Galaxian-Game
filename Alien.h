// FILE: Alien.h

#ifndef ALIEN_H
#define ALIEN_H

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
#include "Player.h"
#include "Laser.h"


//#############################################################################
//       
//                             Alien class 
// 
//#############################################################################

class Alien
{
public:
    // constructor takes in the n, default value of pointValue is 25
    // (score increments by pointValue when alien is killed)
    Alien(Surface & surface, int n, int s = 25)
        :surface_(surface), pointValue_(s)
    {
        // dive is initiated to 0
        dive = 0;
        // every time a new alien is created the number is updated
        ++numAlive;
    }
    // returns the width of the alien rect
    int w() const
    {
        return rect_.w;
    }
    // returns the height of the alien rect
    int h()
    {
        return rect_.h;
    }
    // returns the x coordinate of the alien rect
    int x() const
    {
        return rect_.x;
    }
    // used to adjust the coordinate x when moing the alien
    int & x()
    {
        return rect_.x;
    }
    // returns the y coordinate of the alien rect
    int y() const
    {
        return rect_.y;
    }
    // returns the s = 25
    int pointValue()
    {
        return pointValue_;
    }
    // returns true if alien is alive
    bool & Alive()
    {
        return isAlive;
    }
    // revives the alien (used when advance level)
    void revive()
    {
        isAlive = 1;
        numAlive += 1;
    }
    // speed of the movement is updated depending on the bounds of the game
    // once x hits W it becomes negative and once it hits 0 it becomes positive
    void speedUpdate()
    {
        speed_ *= -1;
    }
    // called when alien is collided with laser
    void die()
    {
        // isAlive is set to false
        isAlive = 0;
        // number of alive aliens is updated
        numAlive -= 1;
    }
    // returns the state of alien (is diving or not)
    bool getDive()
    {
        return dive;
    }
    // return the number of alive aliens
    int numberAlive()
    {
        return numAlive;
    }

    // these methods are implemented in the Alien.cpp file
    void Draw();
    void move();
    void DetectCollision(Laser &, int &);
    void reset(int);
    void attack(std::vector<Laser> &);
    
private:
    static int numAlive;
    bool isAlive = 1;
    double speed_ = 3.1;
    int pointValue_;
    Rect rect_;
    bool dive;
    int start_y;
    int start_x;
    Surface & surface_;
    friend class RedAlien;
    friend class BlueAlien;
    friend class PurpleAlien;
};

//#############################################################################
//       
//                             RedAlien class 
// 
//#############################################################################

class RedAlien: public Alien
{
public:
    RedAlien(Surface & surface, int n)
        :Alien(surface, n, 30)
    {
        rect_ = red_alien_.getRect();
        rect_.x += rect_.w * n + 2;
        rect_.y = rect_.h + 30;
        start_y = rect_.y;
    }
    
    void Draw();
        
private:
    static Image red_alien_;
};

//#############################################################################
//       
//                             BlueAlien class 
// 
//#############################################################################

class BlueAlien: public Alien
{
public:
    BlueAlien(Surface & surface, int n)
        :Alien(surface, n, 10)
    {
        rect_ = blu_alien_.getRect();
        rect_.x = rect_.w * n + 2;
        rect_.y = (rect_.h * 3) + 30;
        start_y = rect_.y;
    }
    
    void Draw();
    
    
private:
    static Image blu_alien_;
};

//#############################################################################
//       
//                             PurpleAlien class 
// 
//#############################################################################

class PurpleAlien: public Alien
{
public:
    PurpleAlien(Surface & surface, int n)
        :Alien(surface, n, 20)
    {
        rect_ = pur_alien_.getRect();
        rect_.x = rect_.w * n + 2;
        rect_.y = (rect_.h * 2) + 30;
        start_y = rect_.y;
    }
    
    void Draw();
    
    
private:
    static Image pur_alien_;
};

#endif
