//
//  gameScene.hpp
//  pingPongbeta
//
//  Created by AMOL SHAH on 9/5/16.
//  Copyright © 2016 AMOL SHAH. All rights reserved.
//

#ifndef gameScene_hpp
#define gameScene_hpp

#include <string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class gameScene {

public:

    gameScene();
    ~gameScene();
    
//Scene attributes
    SDL_Texture* leftNum = NULL;
    SDL_Surface* tempSurface = NULL;
    TTF_Font* gFont = NULL;
    TTF_Font* gFont2 = NULL;
    SDL_Color color = {77,144,255,255};

//Rendering titles and scores
    SDL_Texture* loadText(SDL_Renderer*, int);
    SDL_Texture* getTexture(SDL_Renderer*, std::string, bool);
};


#endif /* gameScene_hpp */
