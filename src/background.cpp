
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "background.h"
#include "main.h"

Sea::Sea(float x, float y, float z, color_t color) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 1.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1000.0f, 0.0f, -1000.0f,
        -1000.0f, 0.0f, 1000.0f, 
        1000.0f, 0.0f, 1000.0f,

        -1000.0f, 0.0f, -1000.0f,
        1000.0f, 0.0f, -1000.0f, 
        1000.0f, 0.0f, 1000.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLUE, GL_FILL);
    
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sea::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sea::tick() 
{

}

bounding_box_t Sea::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 4000.0f;
    bb.height = 0.0f;
    bb.depth = 4000.0f;

    return bb;
}


Island::Island(float x, float y, float z, color_t color) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 1.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float initx = 50.0f, inity = 50.0f;
    const int n = 200;
    static GLfloat vertex_buffer_data_beach[9*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_beach[9*i] = 0.0f;
       vertex_buffer_data_beach[9*i + 1] = 0.0f;
        vertex_buffer_data_beach[9*i + 2] = 0.0f;
         vertex_buffer_data_beach[9*i + 3] = initx;
          vertex_buffer_data_beach[9*i + 4] = 0.0f;
           vertex_buffer_data_beach[9*i + 5] = inity;
            vertex_buffer_data_beach[9*i + 6] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
             vertex_buffer_data_beach[9*i + 7] = 0.0f;
              vertex_buffer_data_beach[9*i + 8] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

              initx = vertex_buffer_data_beach[9*i + 6];
              inity = vertex_buffer_data_beach[9*i + 8];
    }

    initx = 40.0f, inity = 40.0f;
    static GLfloat vertex_buffer_data_forest[9*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_forest[9*i] = 0.0f;
       vertex_buffer_data_forest[9*i + 1] = 0.1f;
        vertex_buffer_data_forest[9*i + 2] = 0.0f;
         vertex_buffer_data_forest[9*i + 3] = initx;
          vertex_buffer_data_forest[9*i + 4] = 0.1f;
           vertex_buffer_data_forest[9*i + 5] = inity;
            vertex_buffer_data_forest[9*i + 6] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
             vertex_buffer_data_forest[9*i + 7] = 0.1f;
              vertex_buffer_data_forest[9*i + 8] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

              initx = vertex_buffer_data_forest[9*i + 6];
              inity = vertex_buffer_data_forest[9*i + 8];
    }

       static const GLfloat vertex_buffer_data_hill[] = {
        30.0f, 0.0f, 30.0f,
        30.0f, 0.0f, -30.0f,
        0.0f, 30.0f, 0.0f,

        -30.0f, 0.0f, -30.0f,
        30.0f, 0.0f, -30.0f,
        0.0f, 30.0f, 0.0f,

        -30.0f, 0.0f, 30.0f,
        -30.0f, 0.0f, -30.0f,
        0.0f, 30.0f, 0.0f,

        -30.0f, 0.0f, 30.0f,
        30.0f, 0.0f, 30.0f,
        0.0f, 30.0f, 0.0f,
    }; 

    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_beach, COLOR_SAND, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_forest, COLOR_FOREST, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_hill, COLOR_GREEN, GL_FILL);

}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);

}

void Island::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Island::tick() 
{

}


Volcano::Volcano(float x, float y, float z, color_t color) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 1.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float initx = 35.0f, inity = 35.0f;
    const int n = 200;
    static GLfloat vertex_buffer_data_beach[9*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_beach[9*i] = 0.0f;
       vertex_buffer_data_beach[9*i + 1] = 0.0f;
        vertex_buffer_data_beach[9*i + 2] = 0.0f;
         vertex_buffer_data_beach[9*i + 3] = initx;
          vertex_buffer_data_beach[9*i + 4] = 0.0f;
           vertex_buffer_data_beach[9*i + 5] = inity;
            vertex_buffer_data_beach[9*i + 6] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
             vertex_buffer_data_beach[9*i + 7] = 0.0f;
              vertex_buffer_data_beach[9*i + 8] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

              initx = vertex_buffer_data_beach[9*i + 6];
              inity = vertex_buffer_data_beach[9*i + 8];
    }

       static GLfloat vertex_buffer_data_rock[9*20];
       const int m = 15;
       initx = 30.0f, inity = 30.0f;
       for (int i=0; i<m; i++) 
       {
          vertex_buffer_data_rock[9*i] = 0.0f;
           vertex_buffer_data_rock[9*i + 1] = 30.0f;
            vertex_buffer_data_rock[9*i + 2] = 0.0f;
             vertex_buffer_data_rock[9*i + 3] = initx;
              vertex_buffer_data_rock[9*i + 4] = 0.0f;
               vertex_buffer_data_rock[9*i + 5] = inity;
                vertex_buffer_data_rock[9*i + 6] = initx*cos(2*3.14159/m) - inity*sin(2*3.14159/m);
                 vertex_buffer_data_rock[9*i + 7] = 0.0f;
                  vertex_buffer_data_rock[9*i + 8] = initx*sin(2*3.14159/m) + inity*cos(2*3.14159/m);

                  initx = vertex_buffer_data_rock[9*i + 6];
                  inity = vertex_buffer_data_rock[9*i + 8];
        }

        static GLfloat vertex_buffer_data_lava[9*20];
       // const int m = 15;
       initx = 5.0f, inity = 5.0f;
       for (int i=0; i<m; i++) 
       {
          vertex_buffer_data_lava[9*i] = 0.0f;
           vertex_buffer_data_lava[9*i + 1] = 30.0f;
            vertex_buffer_data_lava[9*i + 2] = 0.0f;
             vertex_buffer_data_lava[9*i + 3] = initx;
              vertex_buffer_data_lava[9*i + 4] = 25.0f;
               vertex_buffer_data_lava[9*i + 5] = inity;
                vertex_buffer_data_lava[9*i + 6] = initx*cos(2*3.14159/m) - inity*sin(2*3.14159/m);
                 vertex_buffer_data_lava[9*i + 7] = 25.0f;
                  vertex_buffer_data_lava[9*i + 8] = initx*sin(2*3.14159/m) + inity*cos(2*3.14159/m);

                  initx = vertex_buffer_data_lava[9*i + 6];
                  inity = vertex_buffer_data_lava[9*i + 8];
        }

    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_beach, COLOR_GREY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, m*3, vertex_buffer_data_rock, COLOR_BLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, m*3, vertex_buffer_data_lava, COLOR_FIRE, GL_FILL);

}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);

}

void Volcano::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Volcano::tick() 
{

}

bounding_box_t Volcano::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 40.0f;
    bb.height = 120.0f;
    bb.depth = 40.0f;

    return bb;
}

// Lava::Lava(float x, float y, float z, color_t color) 
// {
//     this->position = glm::vec3(x, y, z);
//     this->rotation = 0;
//     this->speed = 1.0;
//     // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
//     // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices


//     this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_beach, COLOR_SAND, GL_FILL);
//     this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_hill, COLOR_BLACK, GL_FILL);

// }

// void Lava::draw(glm::mat4 VP) {
//     Matrices.model = glm::mat4(1.0f);
//     glm::mat4 translate = glm::translate (this->position);    // glTranslatef
//     glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
//     // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
//     // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
//     Matrices.model *= (translate * rotate);
//     glm::mat4 MVP = VP * Matrices.model;
//     glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
//     draw3DObject(this->object1);
//     draw3DObject(this->object2);
//     // draw3DObject(this->object3);

// }

// void Lava::set_position(float x, float y, float z) {
//     this->position = glm::vec3(x, y, z);
// }

// void Lava::tick() 
// {

// }

SmokeRing::SmokeRing(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    this->speed = 5.0;
 
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float initx = 8.0f, inity = 8.0f;
    const int n = 200;

    static GLfloat vertex_buffer_data_cylinder[18*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_cylinder[18*i] = initx;
       vertex_buffer_data_cylinder[18*i + 1] = 1.0f;
        vertex_buffer_data_cylinder[18*i + 2] = inity;
         vertex_buffer_data_cylinder[18*i + 3] = initx;
          vertex_buffer_data_cylinder[18*i + 4] = 0.0f;
           vertex_buffer_data_cylinder[18*i + 5] = inity;
            vertex_buffer_data_cylinder[18*i + 6] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
             vertex_buffer_data_cylinder[18*i + 7] = 0.0f;
              vertex_buffer_data_cylinder[18*i + 8] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);
               vertex_buffer_data_cylinder[18*i + 9] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
                vertex_buffer_data_cylinder[18*i + 10] = 0.0f;
                 vertex_buffer_data_cylinder[18*i + 11] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);
                  vertex_buffer_data_cylinder[18*i + 12] = initx;
                   vertex_buffer_data_cylinder[18*i + 13] = 0.0f;
                    vertex_buffer_data_cylinder[18*i + 14] = inity;
                     vertex_buffer_data_cylinder[18*i + 15] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
                      vertex_buffer_data_cylinder[18*i + 16] = 1.0f;
                       vertex_buffer_data_cylinder[18*i + 17] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

              initx = vertex_buffer_data_cylinder[18*i + 6];
              inity = vertex_buffer_data_cylinder[18*i + 8];
    }

    static GLfloat vertex_buffer_data_innercylinder[18*n];
    initx = 7.4f, inity = 7.4f;
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_innercylinder[18*i] = initx;
       vertex_buffer_data_innercylinder[18*i + 1] = 1.0f;
        vertex_buffer_data_innercylinder[18*i + 2] = inity;
         vertex_buffer_data_innercylinder[18*i + 3] = initx;
          vertex_buffer_data_innercylinder[18*i + 4] = 0.0f;
           vertex_buffer_data_innercylinder[18*i + 5] = inity;
            vertex_buffer_data_innercylinder[18*i + 6] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
             vertex_buffer_data_innercylinder[18*i + 7] = 0.0f;
              vertex_buffer_data_innercylinder[18*i + 8] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);
               vertex_buffer_data_innercylinder[18*i + 9] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
                vertex_buffer_data_innercylinder[18*i + 10] = 0.0f;
                 vertex_buffer_data_innercylinder[18*i + 11] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);
                  vertex_buffer_data_innercylinder[18*i + 12] = initx;
                   vertex_buffer_data_innercylinder[18*i + 13] = 0.0f;
                    vertex_buffer_data_innercylinder[18*i + 14] = inity;
                     vertex_buffer_data_innercylinder[18*i + 15] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
                      vertex_buffer_data_innercylinder[18*i + 16] = 1.0f;
                       vertex_buffer_data_innercylinder[18*i + 17] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

              initx = vertex_buffer_data_innercylinder[18*i + 6];
              inity = vertex_buffer_data_innercylinder[18*i + 8];
    }
    this->object1 = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data_cylinder, COLOR_GREY, GL_LINE);
    this->object2 = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data_innercylinder, COLOR_GREY, GL_FILL);

}

void SmokeRing::draw(glm::mat4 VP) 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate =  glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));;

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotatex * rotatey * rotatez);
    Matrices.model *= (translate * rotate);

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void SmokeRing::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void SmokeRing::tick() 
{
}

bounding_box_t SmokeRing::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 16.0f;
    bb.height = 1.0f;
    bb.depth = 16.0f;

    return bb;
}

