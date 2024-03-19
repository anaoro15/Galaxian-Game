// FILE: Stars.cpp

#include <iostream>
#include "Stars.h"
#include "Surface.h"

void Galaxy::draw()
{
    for (int i = 0; i < 75; ++i)
    {
        if (stars[i].y() >= H - 51)
        {
            stars[i].y(0);
            stars[i].x(rand() % W);
        }
        stars[i].move();
        surface_.put_rect(stars[i].x(), stars[i].y(), stars[i].w(), stars[i].h(),
                          stars[i].r(), stars[i].g(), stars[i].b());
    }
}

void Galaxy::build()
{
    for (int i = 0; i < 75; ++i)
    {
        Stars star;
        
        star.x(rand() % W);
        star.y(rand() % (H - 51));

        star.type(rand() % 3 + 1);

        switch(star.type())
        {
            case 1:
                star.w(3);
                star.h(3);
                star.speed(2.0);
                star.r(51);
                star.g(255);
                star.b(255);
                break;
            case 2:
                star.w(2);
                star.h(2);
                star.speed(1.23);
                star.r(255);
                star.g(204);
                star.b(255);
                break;
            case 3:
                star.w(2);
                star.h(3);
                star.speed(1.75);
                star.r(255);
                star.g(255);
                star.b(153);
                break;
        }
        stars.push_back(star);
    }
    stars.shrink_to_fit();
}

void Stars::move()
{
    y_ += speed_;
}
