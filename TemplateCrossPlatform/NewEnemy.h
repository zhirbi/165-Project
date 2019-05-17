#ifndef NewEnemy_hpp
#define NewEnemy_hpp

#include <stdio.h>
#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <SOIL.h>
#else
#include <GL/freeglut.h>
#include <SOIL.h>
#endif

class NewEnemy: public Rect{
    
protected:
    GLuint texture_id;
    
public:
    void draw(float z) const;
    NewEnemy(const char*, float, float, float, float);
    void killFirst();
    ~NewEnemy();
    
    
    
};


#endif
