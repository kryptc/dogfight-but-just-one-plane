#include "main.h"

#ifndef ENEMIES_H
#define ENEMIES_H

class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, color_t color);
    int width, height, nrChannels;
    unsigned char *data; 

    unsigned int texture;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float speed;
    bounding_box_t def_bounding_box();

private:
    VAO *object1;
    VAO *object2;
    VAO *object3;

};

class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    int width, height;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float speed;
    int timer;
    int fire;
    bounding_box_t def_bounding_box();

private:
    VAO *object1;
};

class Cannonball {
public:
    Cannonball() {}
    Cannonball(float x, float y, float z, int angle);
    int width, height;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void gravityEffect();
    void jump();
    float speed;
    int fire;
    int jumpStatus;
    int jumpTime;
    int angle;
    bounding_box_t def_bounding_box();

private:
    VAO *object;
};

class HeatSeeker {
public:
    HeatSeeker() {}
    HeatSeeker(float x, float y, float z, glm::vec3 planepos);
    int width, height;
    glm::vec3 position;
    glm::vec3 unitvec;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void gravityEffect();
    void jump();
    float speed;
    int fire;
    int jumpStatus;
    int jumpTime;
    bounding_box_t def_bounding_box();

private:
    VAO *object;
};

#endif // ENEMIES_H
