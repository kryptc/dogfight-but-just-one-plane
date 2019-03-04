#include "main.h"

#ifndef PARAPHERNALIA_H
#define PARAPHERNALIA_H


class ScoreBoard {
public:
    ScoreBoard() {}
    ScoreBoard(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;

    void draw(glm::mat4 VP, int i);
    void set_position(float x, float y, float z);

private:
    VAO *object0;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;
    VAO *objectneg;
    VAO *objectm;
};

class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
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

class FuelBar {
public:
    FuelBar() {}
    FuelBar(float x, float y, float z);
    int width, height;

    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, int i);
    void set_position(float x, float y, float z);
    void tick();
    float speed;
    bounding_box_t def_bounding_box();

private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

class FuelTank {
public:
    FuelTank() {}
    FuelTank(float x, float y, float z);
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

class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float rot, float other);
    float speed;

private:
    VAO *object1;
    VAO *object2;
};

#endif // PARAPHERNALIA_H
