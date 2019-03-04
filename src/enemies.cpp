
#include "enemies.h"
#include "main.h"


Parachute::Parachute(float x, float y, float z, color_t color) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 180;
    this->speed = 1.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    const int n = 200;
    
    static const GLfloat vertex_buffer_data_lines[] = {
        10.0f, 0.0f, 10.0f,
        10.0f, 0.0f, -10.0f,
        0.0f, 40.0f, 0.0f,

        -10.0f, 0.0f, -10.0f,
        10.0f, 0.0f, -10.0f,
        0.0f, 40.0f, 0.0f,

        -10.0f, 0.0f, 10.0f,
        -10.0f, 0.0f, -10.0f,
        0.0f, 40.0f, 0.0f,

        -10.0f, 0.0f, 10.0f,
        10.0f, 0.0f, 10.0f,
        0.0f, 40.0f, 0.0f,
    }; 

    static const GLfloat vertex_buffer_data_cover[] = {
        10.0f, 0.0f, 10.0f,
        10.0f, 0.0f, -10.0f,
        -10.0f, 0.0f, -10.0f,

        10.0f, 0.0f, 10.0f,
        -10.0f, 0.0f, 10.0f,
        -10.0f, 0.0f, -10.0f,
    }; 

    static const GLfloat vertex_buffer_data[] = {
        -1.0f,40.0f,-1.0f, // triangle 1 : begin
        -1.0f, 40.0f, 1.0f,
        -1.0f, 41.0f,1.0f, // triangle 1 : end
        1.0f, 41.0f,-1.0f, // triangle 2 : begin
        -1.0f,40.0f,-1.0f,
        -1.0f, 41.0f,-1.0f, // triangle 2 : end
        1.0f,40.0f, 1.0f,
        -1.0f,40.0f,-1.0f,
        1.0f, 40.0f,-1.0f,
        1.0f, 41.0f,-1.0f,
        1.0f, 40.0f,-1.0f,
        -1.0f,40.0f,-1.0f,
        -1.0f,40.0f,-1.0f,
        -1.0f, 41.0f,1.0f,
        -1.0f, 41.0f,-1.0f,
        1.0f,40.0f, 1.0f,
        -1.0f, 40.0f, 1.0f,
        -1.0f,40.0f,-1.0f,
        -1.0f, 41.0f,1.0f,
        -1.0f, 40.0f, 1.0f,
        1.0f,40.0f, 1.0f,
        1.0f, 41.0f,1.0f,
        1.0f, 40.0f,-1.0f,
        1.0f, 41.0f,-1.0f,
        1.0f, 40.0f,-1.0f,
        1.0f, 41.0f,1.0f,
        1.0f,40.0f, 1.0f,
        1.0f, 41.0f,1.0f,
        1.0f, 41.0f,-1.0f,
        -1.0f, 41.0f,-1.0f,
        1.0f, 41.0f,1.0f,
        -1.0f, 41.0f,-1.0f,
        -1.0f, 41.0f,1.0f,
        1.0f, 41.0f,1.0f,
        -1.0f, 41.0f,1.0f,
        1.0f,40.0f, 1.0f
    };

    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_lines, COLOR_RED, GL_LINE);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_cover, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_FOREST, GL_FILL);

}

void Parachute::draw(glm::mat4 VP) {
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

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick() 
{   
  this->position.y -= 1.0;
}
bounding_box_t Parachute::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 20.0f;
    bb.height = 40.0f;
    bb.depth = 20.0f;

    return bb;
}


/**********CANNON***********/


Cannon::Cannon(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 45;
    this->speed = 5.0;
    this->fire = 0;

    this->timer = 80;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float initx = 3.0f, inity = 3.0f;
    float inita = 2.5f, initb = 2.5f;

    const int n = 80;

    static GLfloat vertex_buffer_data_cylinder[18*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_cylinder[18*i] = inita;
       vertex_buffer_data_cylinder[18*i + 1] = 15.0f;
        vertex_buffer_data_cylinder[18*i + 2] = initb;
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
                     vertex_buffer_data_cylinder[18*i + 15] = inita*cos(2*3.14159/n) - initb*sin(2*3.14159/n);
                      vertex_buffer_data_cylinder[18*i + 16] = 15.0f;
                       vertex_buffer_data_cylinder[18*i + 17] = inita*sin(2*3.14159/n) + initb*cos(2*3.14159/n);

              initx = vertex_buffer_data_cylinder[18*i + 6];
              inity = vertex_buffer_data_cylinder[18*i + 8];
              inita = vertex_buffer_data_cylinder[18*i + 15];
              initb = vertex_buffer_data_cylinder[18*i + 17];
    }

    this->object1 = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data_cylinder, COLOR_MAROON, GL_LINE);

}

void Cannon::draw(glm::mat4 VP) 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate =  glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));;

    // glm::mat4 rotatex    = glm::rotate((float) (this->rot.x * this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // glm::mat4 rotatey    = glm::rotate((float) (this->rot.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // glm::mat4 rotatez    = glm::rotate((float) (this->rot.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // printf("rotn =%f, %f, %f\n", rot.x, rot.y, rot.z);

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotatex * rotatey * rotatez);
    Matrices.model *= (translate * rotate);

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Cannon::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() 
{
  int arr[] = {30, 45, 60, 75, 90, 105};
  this->timer--;

  if (this->timer > 0)
    this->fire = 0;
  // printf("timer=%d\n", this->timer);
  if (this->timer == 0)
  {
    this->fire = 1;
    this->timer = 60 + rand()%50;
    this->rotation = arr[rand()%6];
  }
}

bounding_box_t Cannon::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 50.0f;
    bb.height = 30.0f;
    bb.depth = 50.0f;

    return bb;
}


/**********Cannonball***********/


Cannonball::Cannonball(float x, float y, float z, int angle) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 5.0;
    this->fire = 0;
    this->jumpStatus = 1;
    this->jumpTime = 0;
    this->angle = angle;

    static const GLfloat vertex_buffer_data[] = {
        -3.0f,-3.0f,-3.0f, // triangle 1 : begin
        -3.0f,-3.0f, 3.0f,
        -3.0f, 3.0f, 3.0f, // triangle 1 : end
        3.0f, 3.0f,-3.0f, // triangle 2 : begin
        -3.0f,-3.0f,-3.0f,
        -3.0f, 3.0f,-3.0f, // triangle 2 : end
        3.0f,-3.0f, 3.0f,
        -3.0f,-3.0f,-3.0f,
        3.0f,-3.0f,-3.0f,
        3.0f, 3.0f,-3.0f,
        3.0f,-3.0f,-3.0f,
        -3.0f,-3.0f,-3.0f,
        -3.0f,-3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
        -3.0f, 3.0f,-3.0f,
        3.0f,-3.0f, 3.0f,
        -3.0f,-3.0f, 3.0f,
        -3.0f,-3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
        -3.0f,-3.0f, 3.0f,
        3.0f,-3.0f, 3.0f,
        3.0f, 3.0f, 3.0f,
        3.0f,-3.0f,-3.0f,
        3.0f, 3.0f,-3.0f,
        3.0f,-3.0f,-3.0f,
        3.0f, 3.0f, 3.0f,
        3.0f,-3.0f, 3.0f,
        3.0f, 3.0f, 3.0f,
        3.0f, 3.0f,-3.0f,
        -3.0f, 3.0f,-3.0f,
        3.0f, 3.0f, 3.0f,
        -3.0f, 3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
        3.0f, 3.0f, 3.0f,
        -3.0f, 3.0f, 3.0f,
        3.0f,-3.0f, 3.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices


}

void Cannonball::draw(glm::mat4 VP) 
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
    draw3DObject(this->object);
}

void Cannonball::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void Cannonball::jump()
{
    float tottime = abs((2*this->speed*10*sin(this->angle))/9.8);
    float range = abs(((this->speed*this->speed*10*10)*sin(2*this->angle))/9.8);
    float disx = range/tottime;

    float maxht = ((this->speed*this->speed*10*10)*sin(this->angle)*sin(this->angle))/(2*9.8);
    float disy = (maxht*2)/tottime; 

    if (this->jumpTime == (int)tottime * 5)
    {
        this->jumpStatus = 0;
        this->jumpTime = 0;
    }
    else
    {
        this->jumpStatus = 1;
        this->position.y += disy;
        this->position.x += disx/10;
        this->position.z += disx;
        this->jumpTime += 1;
    }
}

void Cannonball::gravityEffect()
{
      float v= 0;
      v = v  + (10)*((float)1/(float)60); // v = u + at;
      float dis = v * ((float)1/(float)60) + 5 * ((float)1/(float)60) * ((float)1/(float)60); // s = ut + 1/2 at^2;
      dis *= 1000; //for speed's sake
      this->position.y -= dis;
      this->position.x += dis;
}

void Cannonball::tick() 
{
    if (this->jumpStatus == 0)
    {
      // printf("fallin\n");
        this->gravityEffect();
    }
    else
    {
        // printf("jumping\n");
        this->jump();
    }
}

bounding_box_t Cannonball::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 8.0f;
    bb.height = 8.0f;
    bb.depth = 8.0f;

    return bb;
}


/**********HeatSeeker***********/


HeatSeeker::HeatSeeker(float x, float y, float z, glm::vec3 planepos) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 5.0;
    this->fire = 0;
    this->jumpStatus = 1;
    this->jumpTime = 0;
    this->unitvec;
    this->unitvec.x = planepos.x - this->position.x;
    this->unitvec.y = planepos.y - this->position.y;
    this->unitvec.z = planepos.z - this->position.z;
    int norm = sqrt(unitvec.x*unitvec.x + unitvec.y*unitvec.y + unitvec.z*unitvec.z);
    this->unitvec.x /=norm;
    this->unitvec.y /=norm;
    this->unitvec.z /=norm;

    static const GLfloat vertex_buffer_data[] = {
        -3.0f,-3.0f,-3.0f, // triangle 1 : begin
        -3.0f,-3.0f, 3.0f,
        -3.0f, 3.0f, 3.0f, // triangle 1 : end
        3.0f, 3.0f,-3.0f, // triangle 2 : begin
        -3.0f,-3.0f,-3.0f,
        -3.0f, 3.0f,-3.0f, // triangle 2 : end
        3.0f,-3.0f, 3.0f,
        -3.0f,-3.0f,-3.0f,
        3.0f,-3.0f,-3.0f,
        3.0f, 3.0f,-3.0f,
        3.0f,-3.0f,-3.0f,
        -3.0f,-3.0f,-3.0f,
        -3.0f,-3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
        -3.0f, 3.0f,-3.0f,
        3.0f,-3.0f, 3.0f,
        -3.0f,-3.0f, 3.0f,
        -3.0f,-3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
        -3.0f,-3.0f, 3.0f,
        3.0f,-3.0f, 3.0f,
        3.0f, 3.0f, 3.0f,
        3.0f,-3.0f,-3.0f,
        3.0f, 3.0f,-3.0f,
        3.0f,-3.0f,-3.0f,
        3.0f, 3.0f, 3.0f,
        3.0f,-3.0f, 3.0f,
        3.0f, 3.0f, 3.0f,
        3.0f, 3.0f,-3.0f,
        -3.0f, 3.0f,-3.0f,
        3.0f, 3.0f, 3.0f,
        -3.0f, 3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
        3.0f, 3.0f, 3.0f,
        -3.0f, 3.0f, 3.0f,
        3.0f,-3.0f, 3.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

}

void HeatSeeker::draw(glm::mat4 VP) 
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
    draw3DObject(this->object);
}

void HeatSeeker::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void HeatSeeker::jump()
{
    // printf("jumping\n");

}

void HeatSeeker::gravityEffect()
{
      float v= 0;
      v = v  + (10)*((float)1/(float)60); // v = u + at;
      float dis = v * ((float)1/(float)60) + 5 * ((float)1/(float)60) * ((float)1/(float)60); // s = ut + 1/2 at^2;
      dis *= 1000; //for speed's sake
      this->position.y -= dis;
      this->position.x += dis;
}

void HeatSeeker::tick() 
{
    if (this->jumpStatus == 0)
    {
      // printf("fallin\n");
        this->gravityEffect();
    }
    else
    {
        this->jump();
        this->position.x += this->speed*unitvec.x;
        this->position.y += this->speed*unitvec.y;
        this->position.z += this->speed*unitvec.z;

    }
}

bounding_box_t HeatSeeker::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 6.0f;
    bb.height = 6.0f;
    bb.depth = 6.0f;

    return bb;
}