#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){
    
    // Some cross-platform compatimility stuff
    
    std::cout<< "GAME CONTROL" << std::endl;
    std::cout<< "W - moves up" << std::endl;
    std::cout<< "A - moves left" << std::endl;
    std::cout<< "S - moves down" << std::endl;
    std::cout<< "D - moves right" << std::endl;
    std::cout<< "F - toggle fullscreen" << std::endl;
    std::cout<< "P - pause game" << std::endl;
    std::cout<< "R - resumes game" << std::endl;
    std::cout<< "Z - restart" << std::endl;
    std::cout<< "ESC - quit" << std::endl;
    
    const char* enemyShip1;
    const char* explodeAnimation;
    const char* backgroundFileName;
    const char* playerShip;
    const char* ammo;
    const char* playerExhaust;
    const char* E1Exhaust;
    const char* OverSign;
    const char* Aamount;
    const char* enemyShip2;
    
    // In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
    // In other environments the image files are in the same folder as the project
    
#if defined WIN32
    shroomFileName = "../mushroom.png";
    fireballFileName = "../fireball.bmp";
#else
    enemyShip1 = "assets/ship+explosion/ship6.png";
    explodeAnimation = "assets/ship+explosion/Explosion.png";
    backgroundFileName = "bg1.png";
    playerShip = "assets/ship+explosion/ship2.png";
    ammo = "assets/Ship+explosion/shot2.png";
    playerExhaust = "assets/Ship+explosion/Ship1_turbol_flight_001.png";
    E1Exhaust = "assets/Ship+explosion/Ship6_normal_flight_000.png";
    OverSign = "assets/PinClipart.com_game-over-clipart_1505126-2.png";
    Aamount = "assets/ammo_3.png";
    enemyShip2 = "assets/Ship+explosion/ship3.png";
#endif
    
    enemy1 = new TexRect(enemyShip1, -0.25, 0.8, 0.4, 0.4);
    explosion = new AnimatedRect(explodeAnimation, 4, 3, 64, false, false, -0.25, 0.8, 0.5, 0.5);
    back = new TexRect(backgroundFileName,-2, 1, 4, 2);
    player = new TexRect(playerShip, -0.05, -0.5, 0.7, 0.5);
    projectile = new TexRect(ammo, 0.15, -0.7, 0.27, 0.3);
    projectile2 = new TexRect(ammo, 0.15, -0.7, 0.27, 0.3);
    exhaust = new AnimatedRect(playerExhaust, 2, 2, 64, true, true, 0.04, -0.88, 0.5, 0.1);
    Enemy1Exhaust = new AnimatedRect(E1Exhaust, 2, 2, 64, true, true, 0.25, -0.5, 0.3, 0.9);
    GameOver = new TexRect(OverSign, -0.5, 0.5, 1, 0.8);
    amount1 = new TexRect(Aamount, -1.75, -0.8, 0.4, 0.15);
    amount2 = new TexRect(Aamount, -1.55, -0.8, 0.4, 0.15);
    enemy2 = new NewEnemy(enemyShip2, -0.45, 0.8, 0.4, 0.4);
    
    up = false;
    enemyVisible = true;
    left = false;
    right = false;
    down = false;
    playerUp = false;
    playerHit = false;
    shot1 = true;
    shot2 = true;
    
    
    projectileVisible = true;
    mushroomVisible = true;
    theta = 0;
    deg = 0;
    hit = false;
    
    setRate(1);
    start();
    
}

void Game::action(){
    float mx = 0.5;
    float my = 0;
    
    if (theta >= 2* M_PI) theta = 0;
    if (deg >= 360) deg = 0;
    
    mx = 0.5 * cos(theta);
    my = 0.5 * sin(theta);
    
    float e2x = 0.8*cos(theta);
    float e2y = 0.8*sin(theta);
    
    
    enemy1->setX(mx - enemy1->getW()/2);
    enemy1->setY(my + enemy1->getH()/2);
    Enemy1Exhaust->setX(enemy1->getX()+0.05);
    Enemy1Exhaust->setY(enemy1->getY()+0.3);
    
    enemy2->setX(e2x - enemy2->getW()/2);
    enemy2->setY(e2y + enemy2->getH()/2);
    
    theta += 0.001;
    deg += 0.1;
    
    //player movement
    if(left == true){
        player->setX(player->getX() - 0.002);
        projectile->setX(projectile->getX() - 0.002);
        exhaust->setX(exhaust->getX() - 0.002);
    }
    if(right == true){
        player->setX(player->getX() + 0.002);
        projectile->setX(projectile->getX() + 0.002);
        exhaust->setX(exhaust->getX() + 0.002);
    }
    if(playerUp == true){
        player->setY(player->getY() + 0.002);
        projectile->setY(projectile->getY() + 0.002);
        exhaust->setY(exhaust->getY() + 0.002);
    }
    if(down == true){
        player->setY(player->getY() - 0.002);
        projectile->setY(projectile->getY() - 0.002);
        exhaust->setY(exhaust->getY() - 0.002);
    }
    
    
    if (!hit && up){
        float ypos = projectile->getY();
        ypos +=0.005;
        projectile->setY(ypos);
        if (enemy1->contains(projectile->getX(), projectile->getY()-0.005)){
            up = false;
            hit = true;
            projectileVisible = false;
            mushroomVisible = false;
            enemyVisible = false;
            explosion->setX(enemy1->getX()+.01);
            explosion->setY(enemy1->getY()-.2);
            explosion->playOnce();
        }
    }
    
    /*crashes at times when game over pops up, not sure if cause of the stop() or not
     */
    if(enemyVisible){
        if(player->contains(enemy1->getX()+.45, enemy1->getY()-.2)){
            stop();
            enemyVisible = false;
            projectileVisible = false;
            playerHit = true;
            explosion->setX(player->getX());
            explosion->setY(player->getY());
            explosion->playOnce();
        }
    }
    
    
    //gravity type animation
    if (hit){
        explosion->setY(explosion->getY()-0.0001);
    }
    
    
}

void Game::draw() const {
    if (projectileVisible){
        back->draw(0);
        enemy1->draw(0.3);
        enemy2->draw(0.31);
        projectile->draw(.39);
        amount1->draw(0.2);
        amount2->draw(0.21);
    }
    if (mushroomVisible){
        back->draw(0);
        enemy1->draw(0.3);
        enemy2->draw(0.31);
        Enemy1Exhaust->draw(0.29);
    }
    if (!playerHit) {
        back->draw(0);
        player->draw(0.4);
        exhaust->draw(0.41);
    }
    
    if(playerHit){
        back->draw(0);
        GameOver->draw(0.6);
    }
    
    back->draw(0);
    explosion->draw(0.5);
    
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == ' '){
        up = true;
    }
    else if (key == 'p'){
        stop();
        exhaust->pause();
        Enemy1Exhaust->pause();
    }
    else if (key == 'r'){
        start();
        exhaust->resume();
        Enemy1Exhaust->resume();
    }
    else if (key == 'a'){
        left = true;
    }
    else if (key == 'd'){
        right = true;
    }
    else if (key == 'w'){
        playerUp = true;
    }
    else if (key == 's'){
        down = true;
    }
}

void Game::handleKeyUp(unsigned char key, float x, float y){
    if (key == 'a'){
        left = false;
    }
    else if (key == 'd'){
        right = false;
    }
    else if (key == 'w'){
        playerUp = false;
    }
    else if (key == 's'){
        down = false;
    }
    
}

Game::~Game(){
    stop();
    delete enemy1;
    delete player;
    delete explosion;
    delete back;
    delete projectile;
    delete exhaust;
    delete Enemy1Exhaust;
    delete GameOver;
    delete amount1;
    delete amount2;
}
