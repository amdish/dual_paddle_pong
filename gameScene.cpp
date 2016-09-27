//
//  gameScene.cpp
//  pingPongbeta
//
//  Created by AMOL SHAH on 9/5/16.
//  Copyright © 2016 AMOL SHAH. All rights reserved.
//

#include "gameScene.hpp"

using std::string;

/*********************Default constructor**********
 Loads up fonts to use in render
 **************************************************/
gameScene::gameScene()
{
    gFont = TTF_OpenFont( "Tinos-Bold.ttf", 28 );
    gFont2 = TTF_OpenFont( "Tinos-Bold.ttf", 36 );
}
gameScene::~gameScene(){}

/**************************************************
 Loads game scene
 **************************************************/
SDL_Texture* gameScene::getTexture(SDL_Renderer* gameRenderer, string toPrint, bool which){

   // string toPrint = to_string(score);
    SDL_Texture* tempTexture = NULL;
    
    tempSurface = TTF_RenderText_Solid(gFont2, toPrint.c_str(), color);
    tempTexture = SDL_CreateTextureFromSurface(gameRenderer, tempSurface);
    
    return tempTexture;
}

SDL_Texture* gameScene::loadText(SDL_Renderer* gameRenderer, int score){
/*
    string sr = to_string(score);
    tempSurface = TTF_RenderText_Solid(gFont,sr.c_str(),color);
    
    leftNum = SDL_CreateTextureFromSurface(gameRenderer, tempSurface);
 
    //SDL_Rect quad = {15,Pong::SCREEN_HEIGHT,50,50};
    //SDL_QueryTexture(leftNum,NULL,NULL, &quad.w, &quad.h);
    //SDL_RenderCopy(gameRenderer, leftNum, NULL, &quad);
 
    
//target = SDL_CreateTexture(target, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,100,100);
    */
    return leftNum;
}
