#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff

	const char* enemyShip1;
	const char* explodeAnimation;
    const char* backgroundFileName;
    const char* playerShip;
    const char* ammo;
    const char* playerExhaust;
    const char* E1Exhaust;

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
	#endif

    enemy1 = new TexRect(enemyShip1, -0.25, 0.8, 0.4, 0.4);
    player = new TexRect(playerShip, -0.05, -0.5, 0.7, 0.5);
    explosion = new AnimatedRect(explodeAnimation, 4, 3, 64, false, false, -0.25, 0.8, 0.5, 0.5);
    back = new TexRect(backgroundFileName,-2, 1, 4, 2);
    projectile = new TexRect(ammo, 0.15, -0.7, 0.27, 0.3);
    //x + .2    y - .2
    exhaust = new AnimatedRect(playerExhaust, 2, 2, 64, true, true, 0.04, -0.88, 0.5, 0.1);
    Enemy1Exhaust = new AnimatedRect(E1Exhaust, 2, 2, 64, true, true, 0.25, -0.5, 0.3, 0.9);
    
    up = false;
    
    left = false;
    right = false;
    down = false;
    playerUp = false;
    
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
    
    enemy1->setX(mx - enemy1->getW()/2);
    enemy1->setY(my + enemy1->getH()/2);
    Enemy1Exhaust->setX(mx - Enemy1Exhaust->getW()/2);
    Enemy1Exhaust->setY(my + Enemy1Exhaust->getH()/2);
    
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
            explosion->setX(enemy1->getX());
            explosion->setY(enemy1->getY());
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
        projectile->draw(.39);
    }
    if (mushroomVisible){
        enemy1->draw(0.3);
        Enemy1Exhaust->draw(0.29);
    }
    back->draw(0);
    player->draw(0.4);
    exhaust->draw(0.41);
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
}
