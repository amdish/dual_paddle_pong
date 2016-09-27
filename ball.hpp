//
//  ball.hpp
//  pingPongbeta
//
//  Created by AMOL SHAH on 8/31/16.
//  Copyright © 2016 AMOL SHAH. All rights reserved.
//

#ifndef ball_hpp
#define ball_hpp

#include <SDL2/SDL.h>

class Ball
{
    public:
    
        Ball();
        ~Ball();
    
    //Control ball movement and locations
        int move();
        int checkEdge();
        void xBounce();
        void yBounce();
        void reset();
    
    //Loads ball image to surface and converts to texture
        SDL_Texture* loadBall(SDL_Renderer*);
    
    //Ball attributes
        int x, y, width, height;
        int vx, vy;
        static const int BALL_VEL;
        static const int SPIN_ADJ;
};
#endif /* ball_hpp */
