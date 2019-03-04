#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z, color_t color) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = glm::vec3(x, y, z);
    this->speed_z = 2.0f;
    this->speed_y = 0.0f;

    this->z_ref = glm::vec4(0, 0, 1, 0);
    this->y_ref = glm::vec4(0, 1, 0, 0);
    this->x_ref = glm::vec4(1, 0, 0, 0);

    this->fuel = 599;
    this->dead = 0;
    // this->local_rotation = glm::mat4(1.0f);
    // this->length_x, this->length_y, this->length_z;
    // this->translate_z = glm::vec3(x, y, z);
    this->rotation_angle = 2;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data_hull[] = {
        //xy plane

        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,        

        1.0f, 1.0f, -7.0f,
        1.0f, -1.0f, -7.0f,
        -1.0f, -1.0f, -7.0f,

        1.0f, 1.0f, -7.0f,
        -1.0f, 1.0f, -7.0f,
        -1.0f, -1.0f, -7.0f, 

        //xz plane

        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -7.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -7.0f,
        -1.0f, 1.0f, -7.0f, 

        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, -7.0f,

        1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, -7.0f,
        -1.0f, -1.0f, -7.0f, 

        //yz plane

        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, -7.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -7.0f,
        1.0f, -1.0f, -7.0f,   

        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, -7.0f,

        -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -7.0f,
        -1.0f, -1.0f, -7.0f,      
    };

    static const GLfloat vertex_buffer_data_torso[] = {
        //xy plane

        1.0f, 1.5f, 3.5f,
        1.0f, -1.0f, 3.5f,
        -1.0f, -1.0f, 3.5f,

        1.0f, 1.5f, 3.5f,
        -1.0f, 1.5f, 3.5f,
        -1.0f, -1.0f, 3.5f,        

        1.0f, 1.5f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, 1.5f, 1.0f,
        -1.0f, 1.5f, 1.0f,
        -1.0f, -1.0f, 1.0f, 

        //xz plane

        1.0f, 1.5f, 3.5f,
        -1.0f, 1.5f, 3.5f,
        -1.0f, 1.5f, 1.0f,

        1.0f, 1.5f, 3.5f,
        1.0f, 1.5f, 1.0f,
        -1.0f, 1.5f, 1.0f, 

        1.0f, -1.0f, 3.5f,
        -1.0f, -1.0f, 3.5f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, 3.5f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 

        //yz plane

        1.0f, 1.5f, 3.5f,
        1.0f, -1.0f, 3.5f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.5f, 3.5f,
        1.0f, 1.5f, 1.0f,
        1.0f, -1.0f, 1.0f,   

        -1.0f, 1.5f, 3.5f,
        -1.0f, -1.0f, 3.5f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.5f, 3.5f,
        -1.0f, 1.5f, 1.0f,
        -1.0f, -1.0f, 1.0f,      
    };

    static const GLfloat vertex_buffer_data_frustum[] = {
        //xy plane

        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,        

        1.0f, 1.5f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, 1.5f, 1.0f,
        -1.0f, 1.5f, 1.0f,
        -1.0f, -1.0f, 1.0f, 

        //xz plane

        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, 1.5f, 1.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.5f, 1.0f,
        -1.0f, 1.5f, 1.0f, 

        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 

        //yz plane

        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.5f, 1.0f,
        1.0f, -1.0f, 1.0f,   

        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, 0.0f,
        -1.0f, 1.5f, 1.0f,
        -1.0f, -1.0f, 1.0f,      
    };

    static const GLfloat vertex_buffer_data_cockpit[] = {

        1.0f, 1.5f, 3.5f,
        1.0f, -1.0f, 3.5f,
        0.0f, -1.0f, 7.5f,

        -1.0f, 1.5f, 3.5f,
        -1.0f, -1.0f, 3.5f,
        0.0f, -1.0f, 7.5f,
     
        1.0f, -1.0f, 3.5f,
        -1.0f, -1.0f, 3.5f,
        0.0f, -1.0f, 7.5f,

        1.0f, 1.5f, 3.5f,
        -1.0f, 1.5f, 3.5f,
        0.0f, -1.0f, 7.5f,

    };   

    static const GLfloat vertex_buffer_data_wings[] = {

        1.0f, -1.0f, 2.5f,
        1.0f, -1.0f, -3.5f,
        8.0f, -1.0f, -4.0f,

        -1.0f, -1.0f, 2.5f,
        -1.0f, -1.0f, -3.5f,
        -8.0f, -1.0f, -4.0f,

    };  

    static const GLfloat vertex_buffer_data_axle[] = {

        -0.05f, 1.0f, -5.0f,
        -0.05f, 1.0f, -6.8f,
        -0.05f, 3.8f, -7.0f,

        -0.05f, 1.0f, -5.0f,
        -0.05f, 3.8f, -6.3f,
        -0.05f, 3.8f, -7.0f,

        0.05f, 1.0f, -5.0f,
        0.05f, 1.0f, -6.8f,
        0.05f, 3.8f, -7.0f,

        0.05f, 1.0f, -5.0f,
        0.05f, 3.8f, -6.3f,
        0.05f, 3.8f, -7.0f,

        -0.05f, 1.0f, -6.8f,
        -0.05f, 3.8f, -7.0f,
        0.05f, 1.0f, -6.8f,

        0.05f, 3.8f, -7.0f,
        -0.05f, 3.8f, -7.0f,
        0.05f, 1.0f, -6.8f,

        -0.05f, 1.0f, -5.0f,
        -0.05f, 3.8f, -6.3f,
        0.05f, 1.0f, -5.0f,

        0.05f, 3.8f, -6.3f,
        -0.05f, 3.8f, -6.3f,
        0.05f, 1.0f, -5.0f,  

        -0.05f, 3.8f, -6.3f,
        -0.05f, 3.8f, -7.0f,
        0.05f, 3.8f, -6.3f,

        0.05f, 3.8f, -7.0f,
        -0.05f, 3.8f, -7.0f,
        0.05f, 3.8f, -6.3f,      

        //side axles

        1.0f, -1.0f, -5.0f,
        1.0f, -1.0f, -6.8f,
        3.1f, -1.0f, -6.8f,

        1.0f, -1.0f, -5.0f,
        3.1f, -1.0f, -6.0f,
        3.1f, -1.0f, -6.8f,

        -1.0f, -1.0f, -5.0f,
        -1.0f, -1.0f, -6.8f,
        -3.1f, -1.0f, -6.8f,

        -1.0f, -1.0f, -5.0f,
        -3.1f, -1.0f, -6.0f,
        -3.1f, -1.0f, -6.8f,       

    };   

    float initx = 0.33f, inity = 0.33f;
    const int n = 200;
    static GLfloat vertex_buffer_data_exhaust[9*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_exhaust[9*i] = 0.0f;
       vertex_buffer_data_exhaust[9*i + 1] = 0.0f;
        vertex_buffer_data_exhaust[9*i + 2] = -7.0f;
         vertex_buffer_data_exhaust[9*i + 3] = initx;
          vertex_buffer_data_exhaust[9*i + 4] = inity;
           vertex_buffer_data_exhaust[9*i + 5] = -7.0f;
            vertex_buffer_data_exhaust[9*i + 6] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
             vertex_buffer_data_exhaust[9*i + 7] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);
              vertex_buffer_data_exhaust[9*i + 8] = -7.0f;

              initx = vertex_buffer_data_exhaust[9*i + 6];
              inity = vertex_buffer_data_exhaust[9*i + 7];
    }

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_hull, COLOR_GREYISH_BLUE, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_torso, COLOR_GREY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_frustum, COLOR_GREY, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_cockpit, COLOR_LIGHT_BLUE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_wings, COLOR_GREY, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data_axle, COLOR_GREY, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_exhaust, COLOR_FIRE, GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 temp  = rotatex * rotatey * rotatez;
    this->x_ref = temp[0];
    this->y_ref = temp[1];
    this->z_ref = temp[2];
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotatex * rotatey * rotatez);
    // Matrices.model *= (translate * this->local_rotation);

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);

}

void Ball::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() 
{
    this->fuel-=0.1;
    this->position.x += this->z_ref[0]*this->speed_z + this->y_ref[0]*this->speed_y;
    this->position.y += this->z_ref[1]*this->speed_z + this->y_ref[1]*this->speed_y;
    this->position.z += this->z_ref[2]*this->speed_z + this->y_ref[2]*this->speed_y;
    // if (this->speed_z > 2.0)
    if (this->speed_z > 0.0)

        this->speed_z -= 0.1;
    if (this->speed_y > 0.0)
        this->speed_y -= 0.1;
    else if (this->speed_y < 0.0)
        this->speed_y += 0.1;

    if (this->position.y < -20)
        this->dead = 1;
    if (this->fuel <= 0)
        this->dead = 1;
    if (this->dead)
        exit(0);
}

void Ball::tilt(int x)
{
    if (x == 1) //left
    {
        this->rotation.y += this->rotation_angle;
    }
    else if (x == 2) //right
    {
        this->rotation.y -= this->rotation_angle;
    }
}

void Ball::roll(int x)
{
    if (x == 2) //left
    {
        this->rotation.z += this->rotation_angle;
    }
    else if (x == 1) //right
    {
        this->rotation.z -= this->rotation_angle;
    }
}

void Ball::thrust()
{
    if (this->speed_z < 5.0)
    {
        this->speed_z += 0.2f;
    } 

}

bounding_box_t Ball::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 4.0f;
    bb.height = 2.0f;
    bb.depth = 14.5f;

    return bb;
}

void Ball::moveup()
{
    if (this->position.y < 350.0)
    {
        this->speed_y += 0.2f;
    }
}

void Ball::movedown()
{
    this->speed_y -= 0.2f;
    if (this->position.y < -20)
        this->dead = 1;
}

void Ball::pitch(int x)
{
    if (x == 1)  this->rotation.x += rotation_angle/2;
    else if (x == -1)  this->rotation.x -= rotation_angle/2;
}


void Ball::barrel()
{
    float speedy = 0.0f, speedz = 2.0f;
    this->rotation.z += rotation_angle;
    this->position.x += this->z_ref[0]*speedz + this->y_ref[0]*speedy;
    this->position.y += this->z_ref[1]*speedz + this->y_ref[1]*speedy;
    this->position.z += this->z_ref[2]*speedz + this->y_ref[2]*speedy;
    if (this->position.y < -20)
        this->dead = 1;
    if (this->fuel <= 0)
        this->dead = 1;
    if (this->dead)
        exit(0);
}


void Ball::loop()
{
    float speedy = 1.0f, speedz = 2.0f;
    this->rotation.x -= rotation_angle;
    this->position.x += this->z_ref[0]*speedz + this->y_ref[0]*speedy;
    this->position.y += this->z_ref[1]*speedz + this->y_ref[1]*speedy;
    this->position.z += this->z_ref[2]*speedz + this->y_ref[2]*speedy;

    if (this->position.y < -20)
        this->dead = 1;
    if (this->fuel <= 0)
        this->dead = 1;
    if (this->dead)
        exit(0);
}

 
//************MISSILE*************


Missile::Missile(float x, float y, float z, glm::vec4 zaxis, glm::vec3 planerot) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    this->speed = 5.0;
    this->z_ref = zaxis;
    this->rot = planerot;
    direction_x = glm::vec3(1,0,0);
    direction_y = glm::vec3(0,1,0);
    direction_z = glm::vec3(0,0,1);


    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float initx = 0.5f, inity = 0.5f;
    const int n = 200;
    static GLfloat vertex_buffer_data_cone[9*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_cone[9*i] = 0.0f;
       vertex_buffer_data_cone[9*i + 1] = 7.0f;
        vertex_buffer_data_cone[9*i + 2] = 0.0f;
         vertex_buffer_data_cone[9*i + 3] = initx;
          vertex_buffer_data_cone[9*i + 4] = 4.0f;
           vertex_buffer_data_cone[9*i + 5] = inity;
            vertex_buffer_data_cone[9*i + 6] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
             vertex_buffer_data_cone[9*i + 7] = 4.0f;
              vertex_buffer_data_cone[9*i + 8] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

              initx = vertex_buffer_data_cone[9*i + 6];
              inity = vertex_buffer_data_cone[9*i + 8];
    }

    initx = 0.5f, inity = 0.5f;
    static GLfloat vertex_buffer_data_cylinder[18*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_cylinder[18*i] = initx;
       vertex_buffer_data_cylinder[18*i + 1] = 4.0f;
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
                      vertex_buffer_data_cylinder[18*i + 16] = 4.0f;
                       vertex_buffer_data_cylinder[18*i + 17] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

              initx = vertex_buffer_data_cylinder[18*i + 6];
              inity = vertex_buffer_data_cylinder[18*i + 8];
    }

    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_cone, COLOR_YELLOW, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data_cylinder, COLOR_BLACK, GL_FILL);

}

void Missile::draw(glm::mat4 VP) 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate;
    rotate[0] = glm::vec4(direction_x,0);
    rotate[1] = glm::vec4(direction_y,0);
    rotate[2] = glm::vec4(direction_z,0);
    rotate[3] = glm::vec4(0,0,0,1);
    rotate =  glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));;

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
    draw3DObject(this->object2);
}

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Missile::tick() 
{
    this->position.x += speed*z_ref.x;
    this->position.y += speed*z_ref.y;
    this->position.z += speed*z_ref.z;
}

bounding_box_t Missile::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 1.0f;
    bb.height = 14.0f;
    bb.depth = 1.0f;

    return bb;
}


/****************BOMB****************/


Bomb::Bomb(float x, float y, float z, color_t color) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    this->speed = 1.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float initx = 1.0f, inity = 1.0f;
    const int n = 50;
    static GLfloat vertex_buffer_data_cone[9*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_cone[9*i] = 0.0f;
       vertex_buffer_data_cone[9*i + 1] = 5.0f;
        vertex_buffer_data_cone[9*i + 2] = 0.0f;
         vertex_buffer_data_cone[9*i + 3] = initx;
          vertex_buffer_data_cone[9*i + 4] = 4.0f;
           vertex_buffer_data_cone[9*i + 5] = inity;
            vertex_buffer_data_cone[9*i + 6] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
             vertex_buffer_data_cone[9*i + 7] = 4.0f;
              vertex_buffer_data_cone[9*i + 8] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

              initx = vertex_buffer_data_cone[9*i + 6];
              inity = vertex_buffer_data_cone[9*i + 8];
    }

    initx = 1.0f, inity = 1.0f;
    static GLfloat vertex_buffer_data_cylinder[18*n];
    
   for (int i=0; i<n; i++) 
   {
      vertex_buffer_data_cylinder[18*i] = initx;
       vertex_buffer_data_cylinder[18*i + 1] = 4.0f;
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
                      vertex_buffer_data_cylinder[18*i + 16] = 4.0f;
                       vertex_buffer_data_cylinder[18*i + 17] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

              initx = vertex_buffer_data_cylinder[18*i + 6];
              inity = vertex_buffer_data_cylinder[18*i + 8];
    }

    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_cone, COLOR_RED, GL_LINE);
    this->object2 = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data_cylinder, COLOR_BLACK, GL_LINE);


}

void Bomb::draw(glm::mat4 VP) {
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
}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick() 
{
    this->position.y -= 0.8;
    // this->position.z -= 0.05; 
}

bounding_box_t Bomb::def_bounding_box()
{
    bounding_box_t bb;
    bb.x = this->position.x;
    bb.y = this->position.y;
    bb.z = this->position.z;

    bb.width = 10.0f;
    bb.height = 10.0f;
    bb.depth = 10.0f;

    return bb;
}
