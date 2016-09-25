//
//  paddle.hpp
//  pingPong2
//
//  Created by AMOL SHAH on 8/29/16.
//  Copyright © 2016 AMOL SHAH. All rights reserved.
//

#ifndef paddle_hpp
#define paddle_hpp

class Paddle
{
    public:
    
        Paddle(int, int);
        ~Paddle();
    
        void move();
        void AI_move(int, int, int, int, int);
    
        int distToBall(int, int);
        int x, y;
        int vx, vy;
    
        static const int WIDTH;
        static const int HEIGHT;
        static const int PADDLE_VEL;
        static const int OFFSET;
    
    private:
};

#endif /* paddle_hpp */
