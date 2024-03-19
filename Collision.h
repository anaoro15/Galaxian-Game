// File: Collisions.h between aliens and the lasers

#ifndef COLLISION_H
#define COLLISION_H
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


void RedAlien_collision(Player &, std::vector<RedAlien> &, Surface &, bool &);
void PurpleAlien_collision(Player &, std::vector<PurpleAlien> &, Surface &, bool &);
void BlueAlien_collision(Player &, std::vector<BlueAlien> &, Surface &, bool &);

#endif 
