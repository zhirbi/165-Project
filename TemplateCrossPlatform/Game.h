#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"

class Game: public AppComponent, private Timer{
    TexRect* enemy1;
    TexRect* back;
    TexRect* player;
    TexRect* projectile;
    TexRect* GameOver;
    
    bool projectileVisible;
    bool mushroomVisible;
    bool up;
    
    bool enemyVisible;
    bool left;
    bool right;
    bool playerUp;
    bool down;
    bool playerHit;
    
    bool hit;
    float theta;
    float deg;
    
    bool enAlive;
public:
    AnimatedRect* explosion;
    AnimatedRect* exhaust;
    AnimatedRect* Enemy1Exhaust;
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    void handleKeyUp(unsigned char, float, float);
    
    void action();

    ~Game();

};

#endif 
