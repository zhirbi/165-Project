#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff

	const char* shroomFileName;
	const char* fireballFileName;
    const char* backgroundFileName;

	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	shroomFileName = "../mushroom.png";
	fireballFileName = "../fireball.bmp";
	#else
	shroomFileName = "/Users/zhirbi/Documents/Documents/CSE165/Final Proj/assets/ship + explosion/ship6.png";
	fireballFileName = "/Users/zhirbi/Documents/Documents/CSE165/Final Proj/assets/ship + explosion/Explosion.png";
    backgroundFileName = "/Users/zhirbi/Documents/Documents/CSE165/Final Proj/TemplateCrossPlatform/bg1.png";
	#endif

    mushroom = new TexRect(shroomFileName, -0.25, 0.5, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    explosion = new AnimatedRect(fireballFileName, 4, 3, 64, false, false, -0.25, 0.8, 0.5, 0.5);
    back = new TexRect(backgroundFileName,-2, 1, 4, 2);
    
    up = false;
    left = false;
    right = false;
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
    
    

    if(left){
        projectile->setX(projectile->getX()- 0.0002);
    }
    if(right){
        projectile->setX(projectile->getX() + 0.0002);
    }
    
    mushroom->setX(mx - mushroom->getW()/2);
    mushroom->setY(my + mushroom->getH()/2);
    
    theta += 0.001;
    deg += 0.1;
    
    
    if (!hit && up){
        float ypos = projectile->getY();
        ypos +=0.005;
        projectile->setY(ypos);

        if (mushroom->contains(0, ypos-0.005)){
            up = false;
            hit = true;
            projectileVisible = false;
            mushroomVisible = false;
            explosion->setX(mushroom->getX());
            explosion->setY(mushroom->getY());
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
        mushroom->draw(0.1);
    }
    back->draw(0);
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
}

void Game::handleKeyUp(unsigned char key, float x, float y){
    if (key == 'a'){
        left = false;
    }
    else if (key == 'd'){
        right = false;
    }
}

Game::~Game(){
    stop();
    delete mushroom;
    delete explosion;
    delete projectile;
    delete back;
}
