//
//  ball.cpp
//  pingPongbeta
//
//  Created by AMOL SHAH on 8/31/16.
//  Copyright © 2016 AMOL SHAH. All rights reserved.
//

#include "ball.hpp"
#include "pong.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <cstdlib>
#include <time.h>

const int Ball::BALL_VEL = 1;
const int Ball::SPIN_ADJ = 2;

Ball::Ball()
{
    vx = -BALL_VEL*2;
    vy = BALL_VEL;
    x = Pong::SCREEN_WIDTH/2;
    y = Pong::SCREEN_HEIGHT/2;
}

SDL_Texture* Ball::loadBall(SDL_Renderer* gameRenderer)
{
    SDL_Surface* tempSurface;
    SDL_Texture* theBall;
    
    tempSurface = IMG_Load("dot.bmp");
    
    SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format,0,0xFF,0xFF));
    theBall = SDL_CreateTextureFromSurface(gameRenderer, tempSurface);
    
    this->width = tempSurface->w;
    this->height = tempSurface->h;
    
    return theBall;
}

Ball::~Ball()
{
   
}

int Ball::move()
{
    x+=vx;
    y+=vy;
    return(checkEdge());
}

void Ball::reset()
{
    x = Pong::SCREEN_WIDTH/2;
    y = Pong::SCREEN_HEIGHT/2;
    vx = BALL_VEL*3;
    vy = BALL_VEL;
}

int Ball::checkEdge()
{
     if (x >= (Pong::SCREEN_WIDTH - width) || y <= 0)
     {
         reset();
         return 1;
         // xBounce();
     }
    else if (y >= (Pong::SCREEN_HEIGHT - height) || x <= 0)
    {
        reset();
        return 2;
        //yBounce();
    }
    return 0;
}

void Ball::xBounce()
{
    vx = -vx;
    //x+=vx;
    
}

void Ball::yBounce()
{
    vy = -vy;
  //  y+=vy;
}