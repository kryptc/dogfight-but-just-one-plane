#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec4 z_ref;
    glm::vec4 y_ref;
    glm::vec4 x_ref;

    // glm::mat4 local_rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void tilt(int x);
    void roll(int x);
    void thrust();
    void moveup();
    void movedown();
    void barrel();
    void loop();
    void pitch(int x);
    float speed_y, speed_z;
    int rotation_angle;
    float fuel;
    int dead;
    bounding_box_t def_bounding_box();

private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;

};

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, glm::vec4 zaxis, glm::vec3 planerot);
    int width, height;
    glm::vec3 position;
    glm::vec3 rot;
    glm::vec3 direction_x;
    glm::vec3 direction_y;
    glm::vec3 direction_z;

    glm::vec4 x_ref;
    glm::vec4 y_ref;
    glm::vec4 zzref;

    glm::vec4 z_ref;
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

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, color_t color);
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
#endif // BALL_H
