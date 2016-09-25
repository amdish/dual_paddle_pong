//
//  pong.cpp
//  pingPong2
//
//  Created by AMOL SHAH on 8/29/16.
//  Copyright © 2016 AMOL SHAH. All rights reserved.
//

#include "pong.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

using namespace std;

const int Pong::SCREEN_WIDTH = 650;
const int Pong::SCREEN_HEIGHT = 400;
const int Pong::WINDOW_HEIGHT = 550;

Pong::Pong()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        cout << "SDL Initialization Error: " << SDL_GetError() << endl;
    else
    {
        gameWindow = SDL_CreateWindow ("Ping Pong",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SCREEN_WIDTH,WINDOW_HEIGHT,
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        
        if (gameWindow == NULL)
            cerr << "Error creating game window: " << SDL_GetError();
        else
        {
            TTF_Init();
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            }
            
            gameRenderer = SDL_CreateRenderer (gameWindow,
                                               -1,
                                               SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            
            if (gameRenderer == NULL)
                cerr << "Error creating renderer: " << SDL_GetError();
            else
            {
                SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gameRenderer);
                    
                left = new Paddle(Paddle::OFFSET,((SCREEN_HEIGHT/2)-(Paddle::HEIGHT/2)));
                right = new Paddle((SCREEN_WIDTH - (Paddle::OFFSET+Paddle::WIDTH)),((SCREEN_HEIGHT/2)-(Paddle::HEIGHT/2)));
                top = new Paddle(SCREEN_WIDTH/2, Paddle::WIDTH + Paddle::OFFSET);
                bottom = new Paddle(SCREEN_WIDTH/2, (SCREEN_HEIGHT - (Paddle::WIDTH + Paddle::OFFSET)));
                
                ballOne = new Ball();
                ballTexture = ballOne->loadBall(gameRenderer);
             
                sceneOne = new gameScene();
            }
        }
    }
    SDL_Delay(1000);
}

void Pong::execute()
{
    SDL_Event event;
    
    bool quit = false;
    
    while(!quit)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            handleInput(event);
        }
        update();
        render();
    }
    close();
}

void Pong::renderBall()
{
    SDL_Rect quad = {ballOne->x,ballOne->y,ballOne->width, ballOne->height};
    SDL_RenderCopyEx(gameRenderer, ballTexture, NULL, &quad, 0,NULL, SDL_FLIP_NONE);
}

void Pong::renderPaddle(Paddle* paddle)
{
    SDL_Rect fillRect = {paddle->x, paddle->y, Paddle::WIDTH, Paddle::HEIGHT};
    SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderFillRect(gameRenderer, &fillRect);
}

void Pong::renderHorzPaddle(Paddle* paddle)
{
    SDL_Rect fillRect = {paddle->x, paddle->y, Paddle::HEIGHT, Paddle::WIDTH};
    SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderFillRect(gameRenderer, &fillRect);
}

void Pong::renderStats()
{
    string forPlayerOne;
    string forPlayerTwo;
    
    forPlayerOne = playerOneText + ": " + to_string(playerOneScore);
    forPlayerTwo = playerTwoText + ": " + to_string(playerTwoScore);
    
    pOneScoreTexture = sceneOne->getTexture(gameRenderer, forPlayerOne, 0);
    pTwoScoreTexture = sceneOne->getTexture(gameRenderer, forPlayerTwo, 0);
    

    SDL_Rect quad = {70,SCREEN_HEIGHT+20,50,50};
    SDL_QueryTexture(pOneScoreTexture, NULL, NULL, &quad.w, &quad.h);
    SDL_RenderCopy(gameRenderer, pOneScoreTexture, NULL, &quad);
    
    SDL_Rect quad2 = {SCREEN_WIDTH-230,SCREEN_HEIGHT+20,50,50};
    SDL_QueryTexture(pTwoScoreTexture, NULL, NULL, &quad2.w, &quad2.h);
    SDL_RenderCopy(gameRenderer, pTwoScoreTexture, NULL, &quad2);
    
    /*
    gameStats = sceneOne->loadText(gameRenderer, ballOne->y);
    SDL_Rect quad = {15,SCREEN_HEIGHT,50,50};
    SDL_QueryTexture(gameStats,NULL,NULL, &quad.w, &quad.h);
    SDL_RenderCopy(gameRenderer, gameStats, NULL, &quad);
     */
}

void Pong::clearRenderer()
{
    SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gameRenderer);
}

void Pong::update()
{
    int whoScored;
    
    left->move();
    left->AI_move(ballOne->y, ballOne->x, ballOne->vx, ballOne->vy, 2);
    right->move();
    right->AI_move(ballOne->y, ballOne->x, ballOne->vx, ballOne->vy, 0);
    top->move();
    top->AI_move(ballOne->y, ballOne->x, ballOne->vx, ballOne->vy, 1);
    bottom->move();
    bottom->AI_move(ballOne->y, ballOne->x, ballOne->vx, ballOne->vy, 3);
    checkCollisions();
    whoScored = ballOne->move();
     if (whoScored == 1)
            playerOneScore++;
        else if (whoScored == 2)
            playerTwoScore++;
        else{}

}

void Pong::checkCollisions()
{
    
//REMOVE THIS *******************************
    int leftTop, leftBottom, rightTop, rightBottom;
    leftTop = left->y;
    leftBottom = left->y + Paddle::HEIGHT;
    rightTop = right->y;
    rightBottom = right->y + Paddle::HEIGHT;
    
    if (ballOne->y+ballOne->height >= leftTop && ballOne->y <= leftBottom && ballOne->x <= (left->x+Paddle::WIDTH))
    {
        ballOne->xBounce();
        if (left->vy > 0)
            ballOne->vy-=Ball::SPIN_ADJ;
        else if (left->vy < 0)
            ballOne->vy-=Ball::SPIN_ADJ;
    }
    //Collision "spin"
    if ((ballOne->y+ballOne->width) > right->y && ballOne->y <= (right->y+Paddle::HEIGHT) && (ballOne->x+ballOne->width) >= right->x && ballOne->vx > 0)
    {
        ballOne->xBounce();
        if (right->vy > 0)
            ballOne->vy-=Ball::SPIN_ADJ;
        else if (right->vy < 0)
            ballOne->vy-=Ball::SPIN_ADJ;
    }
    //Collision ball and bottom paddle
    if ((ballOne->y+ballOne->height) > bottom->y && (ballOne->x+ballOne->width) >= bottom->x && ballOne->x <= (bottom->x + Paddle::HEIGHT))
    {
        ballOne->yBounce();
        if (bottom->vx > 0)
            ballOne->vx-=Ball::SPIN_ADJ;
        else if (bottom->vx < 0)
            ballOne->vx-=Ball::SPIN_ADJ;
    }
    
    //Collision ball and top paddle
    if (ballOne->y < (top->y+Paddle::WIDTH) && ballOne->y > Paddle::OFFSET+5 && (ballOne->x+ballOne->width) > top->x && ballOne->x < (top->x+Paddle::HEIGHT))
        ballOne->yBounce();
}

void Pong::handleInput(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_UP:
                left->vy -= Paddle::PADDLE_VEL;
                break;
            case SDLK_DOWN:
                left->vy += Paddle::PADDLE_VEL;
                break;
            case SDLK_LEFT:
                bottom->vx -= Paddle::PADDLE_VEL;
                break;
            case SDLK_RIGHT:
                bottom->vx += Paddle::PADDLE_VEL;
                break;
        }
    }
    else if(event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
                left->vy += Paddle::PADDLE_VEL;
                break;
            case SDLK_DOWN:
                left->vy -= Paddle::PADDLE_VEL;
                break;
            case SDLK_LEFT:
                bottom->vx += Paddle::PADDLE_VEL;
                break;
            case SDLK_RIGHT:
                bottom->vx -= Paddle::PADDLE_VEL;
                break;
        }
    }
}

void Pong::render()
{
    clearRenderer();
    renderStats();
    renderPaddle(left);
    renderPaddle(right);
    renderHorzPaddle(top);
    renderHorzPaddle(bottom);
    renderBall();
    SDL_RenderPresent(gameRenderer);
}

void Pong::close()
{
    SDL_DestroyWindow(gameWindow);
    IMG_Quit();
    gameWindow = NULL;
    SDL_Quit();
}

Pong::~Pong(){}

