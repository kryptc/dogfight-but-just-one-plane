#include "main.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H


class Sea {
public:
    Sea() {}
    Sea(float x, float y, float z, color_t color);
    int width, height;

    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float speed;
    bounding_box_t def_bounding_box();

private:
    VAO *object;

};

class Island {
public:
    Island() {}
    Island(float x, float y, float z, color_t color);
    int width, height;
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

class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z, color_t color);
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

class SmokeRing {
public:
    SmokeRing() {}
    SmokeRing(float x, float y, float z);
    int width, height;
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
};


#endif // BACKGROUND_H
