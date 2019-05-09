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
	#endif

    enemy1 = new TexRect(enemyShip1, -0.25, 0.5, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    //projectile should be an AnimatedRect that follows the player ship and visibility and animation on false, but when space bar is hit, it becomes visible
    
    player = new TexRect(playerShip, -0.05, -0.5, 0.5, 0.5);
    explosion = new AnimatedRect(explodeAnimation, 4, 3, 64, false, false, -0.25, 0.8, 0.5, 0.5);
    back = new TexRect(backgroundFileName,-2, 1, 4, 2);
    
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
    
    theta += 0.001;
    deg += 0.1;
    
    //player movement
    if(left == true){
        player->setX(player->getX() - 0.002);
    }
    if(right == true){
        player->setX(player->getX() + 0.002);
    }
    if(playerUp == true){
        player->setY(player->getY() + 0.002);
    }
    if(down == true){
        player->setY(player->getY() - 0.002);
    }
    
    if (!hit && up){
        float ypos = projectile->getY();
        ypos +=0.005;
        projectile->setY(ypos);

        if (enemy1->contains(0, ypos-0.005)){
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
        projectile->draw();
        back->draw(0);
    }
    if (mushroomVisible){
        enemy1->draw(0.1);
    }
    back->draw(0);
    player->draw(0.2);
    explosion->draw(0.1);
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == ' '){
        up = true;
    }
    else if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
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
    delete explosion;
    delete projectile;
    delete back;
    delete player;
}
