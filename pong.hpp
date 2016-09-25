//
//  pong.hpp
//  pingPong2
//
//  Created by AMOL SHAH on 8/29/16.
//  Copyright © 2016 AMOL SHAH. All rights reserved.
//Google favors this order: "Typedefs and Enums, Constants, Constructors, Destructor, Methods, including static methods, Data Members, including static data members."

#ifndef pong_hpp
#define pong_hpp

#include <string>
#include "pong.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "gameScene.hpp"
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>

class Pong
{
public:
    SDL_Renderer* gameRenderer;

    int playerOneScore = 0;
    int playerTwoScore = 0;

    std::string playerOneText = "Player 1";
    std::string playerTwoText = "Player 2";

    Paddle* left;
    Paddle* right;
    Paddle* top;
    Paddle* bottom;
    gameScene* sceneOne;
    
    Ball* ballOne;
    
    Pong();
    ~Pong();

    void execute();

    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const int WINDOW_HEIGHT;
    
private:
    SDL_Window* gameWindow;
    SDL_Texture* ballTexture;
    SDL_Texture* pOneScoreTexture;
    SDL_Texture* pTwoScoreTexture;
    
    bool input();
    void update();
    void render();
    void close();
    void checkCollisions();
    void handleInput(SDL_Event&);
    void renderBall();
    void renderPaddle(Paddle*);
    void renderHorzPaddle(Paddle*);
    void renderStats();
    void createStatsTexture();
    void clearRenderer();
    
    
    
};
#endif /* pong_hpp */
