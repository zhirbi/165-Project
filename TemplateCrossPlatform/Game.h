#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"
#include "NewEnemy.h"

class Game: public AppComponent, private Timer{
    TexRect* enemy1;
    TexRect* back;
    TexRect* player;
    TexRect* projectile;
    TexRect* projectile2;
    TexRect* GameOver;
    TexRect* amount1;
    TexRect* amount2;
    NewEnemy* enemy2;
    
    bool projectileVisible;
    bool projectileVisible2;
    bool enemy2Vis;
    bool mushroomVisible;
    bool up;
    
    bool enemyVisible;
    bool left;
    bool right;
    bool playerUp;
    bool down;
    bool playerHit;
    bool shot1;
    bool shot2;
    bool hit2;
    
    bool hit;
    float theta;
    float deg;
    
    bool enAlive;
public:
    AnimatedRect* explosion;
    AnimatedRect* exhaust;
    AnimatedRect* Enemy1Exhaust;
    AnimatedRect* Enemy2Exhaust;
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    void handleKeyUp(unsigned char, float, float);
    
    void action();

    ~Game();

};

#endif 
