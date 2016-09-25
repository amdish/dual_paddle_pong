//
//  ball.hpp
//  pingPongbeta
//
//  Created by AMOL SHAH on 8/31/16.
//  Copyright © 2016 AMOL SHAH. All rights reserved.
//

#ifndef ball_hpp
#define ball_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Ball
{
    public:
    
        Ball();
        ~Ball();
    
        int move();
        int checkEdge();
        void xBounce();
        void yBounce();
        void reset();
        SDL_Texture* loadBall(SDL_Renderer*);
    
        int x, y, width, height;
        int vx, vy;
    
        static const int BALL_VEL;
        static const int SPIN_ADJ;
};
#endif /* ball_hpp */
