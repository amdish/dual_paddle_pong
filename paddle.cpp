//
//  paddle.cpp
//  pingPong2
//
//  Created by AMOL SHAH on 8/29/16.
//  Copyright © 2016 AMOL SHAH. All rights reserved.
//

#include "paddle.hpp"
#include "pong.hpp"
#include "ball.hpp"

const int Paddle::HEIGHT = 90;
const int Paddle::WIDTH = 10;
const int Paddle::OFFSET = 15;
const int Paddle::PADDLE_VEL = 5;

Paddle::Paddle(int x, int y)
{
    vy = 0;
    vx = 0;
    this->x = x;
    this->y = y;
}

Paddle::~Paddle(){}

int Paddle::distToBall(int ballPos, int paddlePos)
{
    int distance = ballPos - (paddlePos+HEIGHT/2);
    return distance;
}

void Paddle::AI_move(int yBall, int xBall, int ballVx, int ballVy, int which)
{
    //0=right
    //1=top
    //2=left
    //3=bottom
    if (which == 0)
    {
        //Returns paddle to center
        if (ballVx < 0)
        {
            if (this->y < Pong::SCREEN_HEIGHT/2-HEIGHT/2)
                vx = PADDLE_VEL;
            else if (this->y == Pong::SCREEN_WIDTH/2-HEIGHT/2)
                vx = 0;
            else
                vx = -PADDLE_VEL;
        }
        else if (ballVx > 0 && xBall > (Pong::SCREEN_WIDTH/2))
        {
            if (distToBall(yBall, this->y) < -75)
                vy = -PADDLE_VEL;
            else if (distToBall(yBall, this->y) > 75)
                vy = PADDLE_VEL;
        }
    }
    else if (which == 1)
    {
        if (ballVy < 0)
        {
            if (distToBall(xBall, this->x) < -50)
                vx = -PADDLE_VEL;
            else if (distToBall(xBall, this->x) > 50)
                vx = PADDLE_VEL;
        }
        //Returns paddle to center
        else if (ballVy > 0)
        {
            if (this->x < Pong::SCREEN_WIDTH/2-HEIGHT/2)
                vx = PADDLE_VEL;
            else if (this->x <= (Pong::SCREEN_WIDTH/2+HEIGHT/2) && this->x >= (Pong::SCREEN_WIDTH/2-HEIGHT/2))
                vx = 0;
            else
                vx = -PADDLE_VEL;
        }
    }
    else if (which == 2)
    {
        //Returns paddle to center
        if (ballVx > 0)
        {
            if (this->y < Pong::SCREEN_HEIGHT/2-HEIGHT/2)
                vx = PADDLE_VEL;
            else if (this->y == Pong::SCREEN_WIDTH/2-HEIGHT/2)
                vx = 0;
            else
                vx = -PADDLE_VEL;
        }
        
        else if (ballVx < 0)
        {
            if (distToBall(yBall, this->y) < -75)
                vy = -PADDLE_VEL;
            else if (distToBall(yBall, this->y) > 75)
                vy = PADDLE_VEL;
        }
    }
    else if (which == 3)
    {
        if (ballVy > 0)
        {
            if (distToBall(xBall, this->x) < -70)
                vx = -PADDLE_VEL;
            else if (distToBall(xBall, this->x) > 70)
                vx = PADDLE_VEL;
        }
        //Returns paddle to center
        else if (ballVy < 0)
        {
            if (this->x < Pong::SCREEN_WIDTH/2-HEIGHT/2)
                vx = PADDLE_VEL;
            else if (this->x <= (Pong::SCREEN_WIDTH/2+HEIGHT/2) && this->x >= (Pong::SCREEN_WIDTH/2-HEIGHT/2))
                vx = 0;
            else
                vx = -PADDLE_VEL;
        }
    }
}

void Paddle::move()
{
    y+=vy;
    if (y < Paddle::OFFSET + 15 || y > (Pong::SCREEN_HEIGHT-Paddle::HEIGHT-Paddle::OFFSET-15))
        y-=vy;
    
    x+=vx;
    if (x < Paddle::OFFSET + 15 || x > (Pong::SCREEN_WIDTH-Paddle::HEIGHT-Paddle::OFFSET-15))
        x-=vx;
}
