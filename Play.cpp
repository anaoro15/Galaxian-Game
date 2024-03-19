//File: Play.h

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
#include "Play.h"
#include "Stars.h"

void play(Surface & surface, Event & event)
{
    int endLoop = 0;
    Player player(surface);
    const int PLAYER_R = 227;
    const int PLAYER_G = 42;
    const int PLAYER_B = 5;
    Laser laser(surface, PLAYER_R, PLAYER_G, PLAYER_B);

//##############################################################
//
//   creating array of lasers for the player and for the aliens
//
//##############################################################

    std::vector<Laser>playerLaser;
    for (int i = 0; i < 100; ++i)
    {
        Laser pL(surface, PLAYER_R, PLAYER_G, PLAYER_B);
        playerLaser.push_back(pL);
    }
    const int ENEMY_R = 3;
    const int ENEMY_G = 243;
    const int ENEMY_B = 21;
    
    std::vector<Laser>enemyLasers;
    for (int i = 0; i < 1000; ++i)
    {
        Laser eL(surface, ENEMY_R, ENEMY_G, ENEMY_B, 0);
        enemyLasers.push_back(eL);
    }

//##############################################################
//
//   initializing sound and music object for the game and lasers
//
//##############################################################
    
    Sound sound("sounds/laser.wav");
    Music music("sounds/GameLoop.ogg");

    
    char str_score[20];
    char str_wave[3];
    char lives_remaining[1];
    Font font("fonts/FreeMonoBold.ttf", 15);
    Font WaveFont("fonts/FreeSansBoldOblique.ttf", 15);

//##############################################################
//
//   positioning of the score, wave and game over label
//
//##############################################################

    Image ScoreLable(font.render("SCORE: ", YELLOW));
    Rect score_lable_rect = ScoreLable.getRect();

    Image WaveLable(WaveFont.render("WAVE: ", YELLOW));
    Rect wave_lable_rect = WaveLable.getRect();

    Image GameOver(font.render("GAME OVER", RED));
    Rect gameOver_rect = GameOver.getRect();

    Image x(WaveFont.render("x", YELLOW));
    Rect x_rect = ScoreLable.getRect();
     
    wave_lable_rect.y = H - 480;
    wave_lable_rect.x = 0 + 10;

    gameOver_rect.x = (W / 2) - 75;
    gameOver_rect.y = (H / 2);
    
    score_lable_rect.x = 0 + 10;
    score_lable_rect.y = H - 30;

    bool gameOver = 0;

    Image you_Lives1("images/galaxian/GalaxianGalaxip.gif");
    Image you_Lives2("images/galaxian/GalaxianGalaxip.gif");
    Image you_Lives3("images/galaxian/GalaxianGalaxip.gif");

    Rect you_Lives_rect1 = you_Lives1.getRect();
    you_Lives_rect1.x = W - (you_Lives_rect1.w + 20);
    you_Lives_rect1.y = H - (you_Lives_rect1.h);
    Rect you_Lives_rect2 = you_Lives2.getRect();
    you_Lives_rect2.x = W - (you_Lives_rect2.w + 60);
    you_Lives_rect2.y = H - (you_Lives_rect2.h);
    Rect you_Lives_rect3 = you_Lives3.getRect();
    you_Lives_rect3.x = W - (you_Lives_rect3.w + 100);
    you_Lives_rect3.y = H - (you_Lives_rect3.h);
   
//##############################################################
//
//   creating vectors for the aliens
//
//##############################################################

    std::vector<RedAlien> rAliens;
    std::vector<BlueAlien> bAliens;
    std::vector<PurpleAlien> pAliens;
    int Level = 1;

//##############################################################
//
//   creating the background
//
//##############################################################

    Galaxy galaxy(surface);
    galaxy.build();


//##############################################################
//
//   creating the aliens (position, speed)
//
//##############################################################

    Rect Aliens;
    Aliens.x = 0;
    Aliens.y = 0;
    Aliens.h = 0;
    Aliens.w = 0;
    double aliensSpeed = 3.1;
    
//##############################################################
//
//   creating the first row of aliens
//
//##############################################################

    
    for (int i = 0; i < 10; ++i)
    {
        RedAlien r(surface,  i);
        Aliens.w += r.w() + 2;
        if(i == 0)
        {
            // setting the rect to the first alien
            Aliens.y = r.y();
            Aliens.h = 5 * r.h();
            Aliens.x = r.x();
        }
        rAliens.push_back(r);
    }
    rAliens.shrink_to_fit();

//##############################################################
//
//   creating the second row of aliens
//
//##############################################################

    for(int i = 0; i < 10; ++i)
    {
        BlueAlien b(surface, i);
        bAliens.push_back(b);
    }
    bAliens.shrink_to_fit();

//##############################################################
//
//   creating the third row of aliens
//
//##############################################################

    for(int i = 0; i < 10; ++i)
    {
        
        PurpleAlien p(surface, i);
        pAliens.push_back(p);
    }
    pAliens.shrink_to_fit();

//##############################################################
//
//   getting num of aliens, setting the timers for the game
//
//##############################################################
    
    int numberAliens = rAliens[0].numberAlive();
    bool canAttack = 0;
    bool immune = 0;
    
    int ticks = getTicks();
    int newTicks = ticks + 500;
    int endTicks = 0;
    int stopT = 0;
    int immunityTick = 0;
    int stopImmunity = 0;


//##############################################################
//
//   game loop
//
//##############################################################
   
    music.play();
    while (1)
    {
        // exit if quit is clicked
        if (event.poll() && event.type() == QUIT) break;
        //Gets the total number of Aliens
        numberAliens = rAliens[0].numberAlive();
        
        // Displaying  the Score
        sprintf(str_score, "%d", player.score());
        Image score(font.render(str_score, WHITE));
        Rect score_rect = score.getRect();
        score_rect.x = score_lable_rect.x + 80;
        score_rect.y = score_lable_rect.y;
        
        // Displays the Current Level
        sprintf(str_wave, "%d", Level);
        Image wave(WaveFont.render(str_wave, YELLOW));
        Rect wave_rect = wave_lable_rect;
        wave_rect.x = wave_lable_rect.x + 75;
        
        // Determines if an alien can attack
        if (rand() % 150 == 117 || rand() % 150 == 42 && player.isAlive() && !gameOver && !immune)
        {
            canAttack = 1;
            int row = rand() % 4;
            int col = rand() % 10;
            sound.play();

            switch (row)
            {
                case 0:
                    // if the alien is not diving already (dive = 0)
                    if(!bAliens[col].getDive())
                        // send him to attack
                        // random alien from column 0 - 10 attacks
                        bAliens[col].attack(enemyLasers); 
                    // randomization gets advanced when the level advances
                    if (Level == 2)   
                    {
                        if (col < 10) bAliens[col + 1].attack(enemyLasers);
                    }
                    if (Level > 3)
                    {
                        if (col > 0) bAliens[col - 1].attack(enemyLasers);
                    }
                    break;
                case 1:
                    if(!pAliens[col].getDive())
                        pAliens[col].attack(enemyLasers);

                    if (Level == 2)
                    {
                        if (col < 10) pAliens[col + 1].attack(enemyLasers);
                    }
                    if (Level > 3)
                    {
                        if (col > 0) pAliens[col - 1].attack(enemyLasers);
                    }
                    break;
                case 2:
                    if(!rAliens[col].getDive())
                    rAliens[col].attack(enemyLasers);

                    if (Level == 2)
                    {
                        if (col < 10) rAliens[col + 1].attack(enemyLasers);
                    }
                    if (Level > 2)
                    {
                        if (col > 0) rAliens[col - 1].attack(enemyLasers);
                    }                     
                    break;
                case 3:
                    if (!rAliens[col].getDive())
                    {
                        if (Level > 1)
                        {
                            rAliens[col].attack(enemyLasers);
                            rAliens[col - 1].attack(enemyLasers);
                            rAliens[col + 1].attack(enemyLasers);
                            pAliens[col].attack(enemyLasers);
                        }
                    }
            }
        }
        
        KeyPressed key = get_keypressed();
        
        player.move();
        for (int i = 0; i < 20; ++i)
        {
            if (playerLaser[i].y() < 0)
            {
                playerLaser[i].stopFire();
            }
        }
        
        surface.lock();
        surface.fill(BLACK);

//#######################################################################
//
// the following Logic determines if a laser can fire and moves/draws it  
//
//#######################################################################

        if (key[SPACE] && player.isAlive())
        {
            ticks = getTicks();
            if (ticks >= newTicks)
            {
                newTicks = ticks + 500;
                int available = -1;
                for (int i = 0; i < 100; ++i)
                {
                    
                    if (!playerLaser[i].isAlive())
                    {
                        available = i;
                        break;
                    }
                    
                }
                // if laser is available, shoot it 
                if (available >= 0) 
                {
                    sound.play();
                    playerLaser[available].fire(player.x() + (player.w() / 2), player.y() + 10);
                }
            }
        }
        for (int i = 0; i < 20; ++i)
        {
            if (playerLaser[i].isAlive())
            {
                playerLaser[i].move();
            
                playerLaser[i].draw();
            }
        }
        
//#############################################################################
//
//           The following logic moves the Aliens
//        and detects collisions with the bounds of the game   
//
//#############################################################################

        Aliens.x += aliensSpeed;
        if (Aliens.x + Aliens.w > W)
        {
            
            for (int i = 0; i < 10; ++i)
            {
                rAliens[i].speedUpdate();
                bAliens[i].speedUpdate();
                pAliens[i].speedUpdate();
                
            }
            aliensSpeed *= -1;
        }
        if (Aliens.x < 0)
        {
            rAliens[0].x() = 0;
            bAliens[0].x() = 0;
            pAliens[0].x() = 0;
            for (int i = 0; i < 10; ++i)
            {
                rAliens[i].speedUpdate();
                bAliens[i].speedUpdate();
                pAliens[i].speedUpdate();
                if (i != 0)
                {
                    rAliens[i].x() = 0 + rAliens[i].w() * i;
                    bAliens[i].x() = 0 + bAliens[i].w() * i;
                    pAliens[i].x() = 0 + pAliens[i].w() * i;
                }
            }
            aliensSpeed *= -1;
        }

        for (int i = 0; i < 10; ++i)
        {
            rAliens[i].move();
            bAliens[i].move();
            pAliens[i].move();
        }

//#############################################################################
//
//                      moves alien lasers
//
//#############################################################################

        for (int i = 0; i < 10; ++i)
        {
            if (enemyLasers[i].isAlive() && !immune)
            {
                enemyLasers[i].move();
                player.DetectCollision(enemyLasers[i]);
                enemyLasers[i].draw();
            }
        }

//#############################################################################
//       
//        detecting collision between aliens and lasers
// 
//#############################################################################

        for (int i = 0; i < 5; ++i)
        {
            if (playerLaser[i].isAlive())
            {
                
                for(int k = 0; k < 10; ++k)
                {
                    bAliens[k].DetectCollision(playerLaser[i], player.score());
                }
                for(int k = 0; k < 10; ++k)
                {
                    pAliens[k].DetectCollision(playerLaser[i], player.score());
                }
                for(int k = 0; k < 10; ++k)
                {
                    rAliens[k].DetectCollision(playerLaser[i], player.score());
                }
            }
        }
//#############################################################################
//       
//        detecting collision between aliens and players
// 
//#############################################################################

        if (!immune)
            RedAlien_collision(player, rAliens, surface, immune);
        if (!immune)
            BlueAlien_collision(player, bAliens, surface, immune);
        if (!immune)
            PurpleAlien_collision(player, pAliens, surface, immune);


//#############################################################################
//       
//        puts the score, level and lives labels 
// 
//#############################################################################

        if (player.lives() == 3)
        surface.put_image(score, score_rect);
        surface.put_image(ScoreLable, score_lable_rect);
        surface.put_image(wave, wave_rect);
        surface.put_image(WaveLable, wave_lable_rect);
        surface.put_image(x, x_rect);
        switch (player.lives())
        {
            case 3: 
                surface.put_image(you_Lives1, you_Lives_rect1);
                surface.put_image(you_Lives2, you_Lives_rect2);
                surface.put_image(you_Lives3, you_Lives_rect3);
                break;
            case 2: 
                surface.put_image(you_Lives1, you_Lives_rect1);
                surface.put_image(you_Lives2, you_Lives_rect2);
                break;
            case 1: 
                surface.put_image(you_Lives1, you_Lives_rect1);
                break;
        }
        
//#############################################################################
//       
//                drawing the aliens and the player
// 
//#############################################################################

        for (int i = 0; i < 10; ++i)
        {
            rAliens[i].Draw();
            bAliens[i].Draw();
            pAliens[i].Draw();
        }
            
        player.Draw(); 


//#############################################################################
//       
//   advances to the next level if no aliens are left (or game over after 3'rd)
// 
//#############################################################################


        if (player.lives() == 0 && !gameOver)
        {
            gameOver = 1;
            surface.put_image(GameOver, gameOver_rect);
            stopT = getTicks() + 5000;       
        }
        
        if (gameOver)
        {
            surface.put_image(GameOver, gameOver_rect);
        }

        galaxy.draw();
        surface.unlock();
        surface.flip();

//#############################################################################
//       
//              restarts the timer
// 
//#############################################################################

        if (gameOver)
        {
            endTicks = getTicks();
            
                KeyPressed end = get_keypressed();
                if (end[UPARROW])
                    break;
                if (endTicks >= stopT)
                    break;
        }

//#############################################################################
//       
//         drawing the aliens and the player again for the next level
// 
//#############################################################################

            if (numberAliens == 0)
            {
                for(int i = 0; i < 10; ++i)
                {
                    if (i >= 0 && i <= 3 || i >= 7 && i <= 10)
                    {
                        rAliens[i].reset(i);
                        bAliens[i].reset(i);
                    }
                    pAliens[i].reset(i);
                    
                }
                Aliens.x = rAliens[0].x();
                ++Level;
            }
        
//#############################################################################
//       
//             sets the lasers to not alive
// 
//#############################################################################

        for (int i = 0; i < 5; ++i)
        {
            if (enemyLasers[i].y() > H)
            {
                enemyLasers[i].isAlive() = 0;
            }
        }
        canAttack = 0;
        
//#############################################################################
//       
//         revives the player if it's killed and has remaining lives
// 
//#############################################################################

        if (!player.isAlive() && player.lives() > 0)
        {
            immunityTick = getTicks();
            stopImmunity = getTicks() + 3500;
            immune = 1;
            player.revive();
        }
        
        if (immune)
        {
            immunityTick = getTicks();
            if (immunityTick >= stopImmunity)
            {
                immune = 0;
            }
        }
        
        delay(20);
    }
}
