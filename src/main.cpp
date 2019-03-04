#include "main.h"
#include "timer.h"
#include "ball.h"
#include "background.h"
#include "paraphernalia.h"
#include "enemies.h"

using namespace std;

GLMatrices Matrices, DBMatrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball plane;
Sea sea;
Island island;
vector<Island> islandarr;
Volcano volcano;
vector<Volcano> volcanoarr;
ScoreBoard UNITS, TENS, HUNDREDS, THOUSANDS, TTHOUSANDS, NEG, M;
Missile missile;
vector <Missile> missilearr;
Parachute chute;
vector <Parachute> chutearr;
SmokeRing ring;
vector <SmokeRing> ringarr;
Bomb bomb;
vector <Bomb> bombarr;
Arrow arrow;
Cannon cannon;
vector <Cannon> cannonarr;
Cannonball ball;
vector <Cannonball> ballarr;
HeatSeeker ball2;
vector <HeatSeeker> ball2arr;
FuelBar bar1;
FuelTank tank;
vector <FuelTank> tankarr;
Compass compass;

int units = 0, tens = 0, hundreds = 0, thousands = 0, tthousands = 0;

bounding_box_t planebb, volcanobb[50], seabb, missilebb[200], chutebb[500], ringbb[100], bombbb[200];
bounding_box_t cannonbb[20], ballbb[100], tankbb[30], ball2bb[100];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float eye_x = 2, eye_y = 0, eye_z = 25;
float target_x = 0, target_y = 0, target_z = 0;
float up_x = 0, up_y = 1, up_z = 0;
int planeview = 0, topview = 0, followview = 0, chopperview = 0, towerview = 0;
int lefttilt = 0, righttilt = 0, leftroll = 0, rightroll = 0;
int shootmissile = 0, droppinbomb = 0;
int loop = 0, barrel = 0;
int drawarrow = 0;
float chopper_y = 10, chopper_x = 0, chopper_z = 0;


//******************GAME SCOREBOARD******************//

int altitude = 1200;
int tsc = 0;
int score = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() 
{
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    if (planeview)
    {
        eye_x = plane.position.x + plane.z_ref[0]*7;
        eye_y = plane.position.y + plane.z_ref[1]*2;
        eye_z = plane.position.z + plane.z_ref[2]*7;

        target_x = plane.position.x + plane.z_ref[0]*50;
        target_y = plane.position.y + plane.z_ref[1]*50;
        target_z = plane.position.z + plane.z_ref[2]* 100; 
    }
    else if (topview)
    {
        eye_x = plane.position.x;
        eye_y = plane.position.y + 50;
        eye_z = plane.position.z - 7;

        target_x = plane.position.x;
        target_y = plane.position.y + 3;
        target_z = plane.position.z; 
    }
    else if (followview)
    {
        eye_x = plane.position.x - plane.z_ref[0]*15;
        eye_y = plane.position.y + plane.z_ref[1]*15;
        eye_z = plane.position.z - plane.z_ref[2]*15;

        target_x = plane.position.x + plane.z_ref[0]*50;
        target_y = plane.position.y + plane.z_ref[1]*50;
        target_z = plane.position.z + plane.z_ref[2]*50;  
    }
    else if (chopperview)
    {
        // eye_x = plane.position.x;
        // eye_y = plane.position.y + 20;
        // eye_z = plane.position.z - 7;

        // target_x = plane.position.x;
        // target_y = plane.position.y + 3;
        // target_z = plane.position.z; 

        eye_x = plane.position.x - plane.z_ref[0]*15 + chopper_x;
        eye_y = plane.position.y + plane.z_ref[1]*15 + chopper_y;
        eye_z = plane.position.z - plane.z_ref[2]*15 + chopper_z;

        target_x = plane.position.x + plane.z_ref[0]*30;
        target_y = plane.position.y + plane.z_ref[1]*30;
        target_z = plane.position.z + plane.z_ref[2]*30; 
    }
    // else if (towerview)
    // {

    // }

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( eye_x, eye_y, eye_z );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (up_x, up_y, up_z);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    //***********DASHBOARD************

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 DBeye ( 0, 0, 0 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // change if zoomed in or out, z axis should come closer/further
    glm::vec3 DBtarget (0, 0, 1);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 DBup (0, 1, 0);

    // Compute Camera matrix (view)
    DBMatrices.view = glm::lookAt( DBeye, DBtarget, DBup ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 DBVP = DBMatrices.projection * DBMatrices.view;


    // Scene render
    // plane.draw(VP);
    plane.draw(VP);


    //calculating and drawing altitude
    int temp = altitude;

    units = temp%10;
    temp /= 10;
    tens = temp%10;
    temp /= 10;
    hundreds = temp%10;
    temp /= 10;
    thousands = temp%10;
    temp /= 10;
    tthousands = temp%10;

    UNITS = ScoreBoard(0,3.25,0, COLOR_WHITE);
    UNITS.draw(DBVP, units);
    TENS = ScoreBoard(0.5,3.25,0, COLOR_WHITE);
    TENS.draw(DBVP, tens);
    HUNDREDS = ScoreBoard(1,3.25,0, COLOR_WHITE);
    HUNDREDS.draw(DBVP, hundreds);
    THOUSANDS = ScoreBoard(1.5,3.25,0, COLOR_WHITE);
    THOUSANDS.draw(DBVP, thousands);
    TTHOUSANDS = ScoreBoard(2,3.25,0, COLOR_WHITE);
    TTHOUSANDS.draw(DBVP, tthousands);
    M = ScoreBoard(-0.25,3.25,0, COLOR_WHITE);
    M.draw(DBVP, -2);


    //calculating and drawing score

    temp = score;
    // printf("alt=%d\n", altitude);
    if (temp < 0) 
    {
        temp *= -1;
        NEG = ScoreBoard(-2.5,3.25,0, COLOR_WHITE);
        NEG.draw(DBVP, -1);
    }
    units = temp%10;
    temp /= 10;
    tens = temp%10;
    temp /= 10;
    hundreds = temp%10;
    temp /= 10;
    thousands = temp%10;
    temp /= 10;
    tthousands = temp%10;

    UNITS = ScoreBoard(-5,3.25,0, COLOR_WHITE);
    UNITS.draw(DBVP, units);
    TENS = ScoreBoard(-4.5,3.25,0, COLOR_WHITE);
    TENS.draw(DBVP, tens);
    HUNDREDS = ScoreBoard(-4,3.25,0, COLOR_WHITE);
    HUNDREDS.draw(DBVP, hundreds);
    THOUSANDS = ScoreBoard(-3.5,3.25,0, COLOR_WHITE);
    THOUSANDS.draw(DBVP, thousands);
    TTHOUSANDS = ScoreBoard(-3,3.25,0, COLOR_WHITE);
    TTHOUSANDS.draw(DBVP, tthousands);

    //calculating and drawing fuel
    temp = plane.fuel;
    int lev = ceil(temp/100);
    bar1 = FuelBar(1,-3.7,1);
    bar1.draw(DBVP, lev);

    compass.draw(DBVP);
    // printf("bar1 =%f, %f,%f\n", bar1.position.x, bar1.position.y, bar1.position.z);

    // if (plane.position.x > 400) 
    //     sea = Sea(1100, -20, 0, COLOR_BLUE);
    // else if (plane.position.x < -400)
    //     sea = Sea(-1100, -20, 0, COLOR_BLUE);
    // else if (plane.position.x > 1300) 
    //     sea = Sea(2200, -20, 0, COLOR_BLUE);
    // else if (plane.position.x < -1300)
    //     sea = Sea(-2200, -20, 0, COLOR_BLUE);

    // if (plane.position.z > 400) 
    //     sea = Sea(0, -20, 1100, COLOR_BLUE);
    // else if (plane.position.z < -400)
    //     sea = Sea(0, -20, -1100, COLOR_BLUE);    
    // else if (plane.position.z > 1300) 
    //     sea = Sea(0, -20, 2200, COLOR_BLUE);
    // else if (plane.position.z < -1300)
    //     sea = Sea(0, -20, -2200, COLOR_BLUE);

    // else 
        sea = Sea(0, -20, 0, COLOR_BLUE);


    sea.draw(VP);
    for (int i = 0; i < islandarr.size(); ++i)
        islandarr[i].draw(VP);
    for (int i = 0; i < volcanoarr.size(); ++i)
        volcanoarr[i].draw(VP);
    for (int i = 0; i < ringarr.size(); ++i)
        ringarr[i].draw(VP);


    for (int i = 0; i < 1; ++i)
    {
        int xcoord = rand()%2000 - 1000;
        int zcoord = rand()%2000 - 1000;
        if (xcoord % 73+i == 0)
        {
            chute = Parachute(xcoord, 550, zcoord, COLOR_RED);
            chutearr.push_back(chute);
        }
    }

    for (int i = 0; i < cannonarr.size(); ++i)
    {
        cannonarr[i].draw(VP);
        // if (i == 0 && !drawarrow)
        if (i == 0)

        {
            arrow = Arrow(cannonarr[i].position.x, 70, cannonarr[i].position.z);
            arrow.draw(VP);
            drawarrow = 1;
            // printf("drew arrow at %f, %f, %f\n", arrow.position.x, arrow.position.y, arrow.position.z);
        }
    }
    // printf("we at %f, %f, %f\n", plane.position.x, plane.position.y, plane.position.z);

    for (int i = 0; i < ballarr.size(); ++i)
        ballarr[i].draw(VP);
     for (int i = 0; i < ball2arr.size(); ++i)
        ball2arr[i].draw(VP);
    
    for (int i = 0; i < chutearr.size(); ++i)
        chutearr[i].draw(VP);


    if (shootmissile % 80 == 5)
    {
        missile = Missile(plane.position.x, plane.position.y-2, plane.position.z, plane.z_ref, plane.rotation);
        missilearr.push_back(missile);
        shootmissile = 0;
    }

    for (int i = 0; i < missilearr.size(); ++i)
        missilearr[i].draw(VP);

    if (droppinbomb % 80 == 5)
    {
        bomb = Bomb(plane.position.x, plane.position.y-4, plane.position.z, COLOR_BLUE);
        bombarr.push_back(bomb);
        droppinbomb = 0;
    }

    for (int i = 0; i < bombarr.size(); ++i)
        bombarr[i].draw(VP);

    for (int i = 0; i < tankarr.size(); ++i)
        tankarr[i].draw(VP);

}

void tick_input(GLFWwindow *window) 
{
    int viewplane  = glfwGetKey(window, GLFW_KEY_P);
    int viewtop = glfwGetKey(window, GLFW_KEY_UP);
    int viewtower  = glfwGetKey(window, GLFW_KEY_LEFT);
    int viewchopper = glfwGetKey(window, GLFW_KEY_DOWN);
    int viewfollow  = glfwGetKey(window, GLFW_KEY_RIGHT);

    int forward = glfwGetKey(window, GLFW_KEY_W);
    int tiltleft = glfwGetKey(window, GLFW_KEY_A);
    int tiltright = glfwGetKey(window, GLFW_KEY_D);
    int rollleft = glfwGetKey(window, GLFW_KEY_Q);
    int rollright = glfwGetKey(window, GLFW_KEY_E);
    int hoverup = glfwGetKey(window, GLFW_KEY_SPACE);
    int hoverdown = glfwGetKey(window, GLFW_KEY_S);
    int moveup = glfwGetKey(window, GLFW_KEY_I);
    int movedown = glfwGetKey(window, GLFW_KEY_K);

    int loopdeloop = glfwGetKey(window, GLFW_KEY_L);
    int barrelroll = glfwGetKey(window, GLFW_KEY_B);

    int releasemissile = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int dropbomb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);


    if (viewplane) 
    {
        planeview = 1;
        topview = 0;
        towerview = 0;
        chopperview = 0;
        followview = 0;
    }
    if (viewtop) 
    {
        topview = 1;
        planeview = 0;
        towerview = 0;
        chopperview = 0;
        followview = 0;
    }
    if (viewfollow)
    {
        followview = 1;
        topview = 0;
        planeview = 0;
        towerview = 0;
        chopperview = 0;
    }
    if (viewtower) 
    {
        topview = 0;
        planeview = 0;
        towerview = 1;
        chopperview = 0;
        followview = 0;
        eye_x = plane.position.x + 30;
        eye_y = plane.position.y + 30;
        eye_z = plane.position.z;

        target_x = plane.position.x;
        target_y = plane.position.y;
        target_z = plane.position.z ; 
    }
    if (viewchopper)
    {
        followview = 0;
        topview = 0;
        planeview = 0;
        towerview = 0;
        chopperview = 1;
    }
    if (forward) plane.thrust();

    if (tiltleft)
    {
        lefttilt = 1;
        righttilt = 0;
        plane.tilt(1);
    }
    else if (tiltright)
    {
        righttilt = 1;
        lefttilt = 0;
        plane.tilt(2);
    }
    else
    {
        righttilt = 0;
        lefttilt = 0;
    }

    if (rollleft)
    {
        leftroll = 1;
        rightroll = 0;
        plane.roll(1);
    }
    else if (rollright)
    {
        rightroll = 1;
        leftroll = 0;
        plane.roll(2);
    }
    else
    {
        rightroll = 0;
        leftroll = 0;
    }

    if (hoverup) plane.moveup();
    else if (hoverdown) plane.movedown();
    if (movedown) plane.pitch(1);
    if (moveup) plane.pitch(-1);

    if (releasemissile) shootmissile++;
    if (dropbomb) droppinbomb++;

    if (barrelroll) barrel = 1;
    else if (loopdeloop) loop = 1;
}

void tick_elements() 
{
    if (barrel > 0)
    {
        plane.barrel();
        barrel++;
        if (barrel == 179)
            barrel = 0;
    }
    else if (loop > 0)
    {
        plane.loop();
        loop++;
        if (loop == 180)
            loop = 0;
    }
    else
        plane.tick();
    
    altitude = abs(plane.position.y - sea.position.y) * 50;

    planebb = plane.def_bounding_box();

    for (int i = 0; i < volcanoarr.size(); ++i)
    {
        volcanobb[i] = volcanoarr[i].def_bounding_box();
        if (detect_collision(planebb, volcanobb[i]))
            plane.dead = 1;
    }

    for (int i = 0; i < cannonarr.size(); ++i)
    {
        if ((abs(plane.position.x - cannonarr[i].position.x) < 100) ||
            (abs(plane.position.y - cannonarr[i].position.y) < 100) ||
            (abs(plane.position.z - cannonarr[i].position.z) < 100))
            {
                cannonarr[i].tick();
                if (cannonarr[i].fire)
                {
                    if (rand()%3 != 0)
                    {
                        ball = Cannonball(cannonarr[i].position.x, cannonarr[i].position.y+4, cannonarr[i].position.z, cannonarr[i].rotation);
                        ball.jumpStatus = 1;
                        ballarr.push_back(ball); 
                    }
                    else
                    {
                        ball2 = HeatSeeker(cannonarr[i].position.x, cannonarr[i].position.y+4, cannonarr[i].position.z, plane.position);
                        ball2.jumpStatus = 1;
                        ball2arr.push_back(ball2); 
                    }
                    
                }
            }
    }

    for (int i = 0; i < ballarr.size(); ++i)
    {
        ballarr[i].tick();
        if (ballarr[i].position.y < -20)
            ballarr.erase(ballarr.begin() + i);
        ballbb[i] = ballarr[i].def_bounding_box();
        if (detect_collision(ballbb[i], planebb))
        {
            score -= 50;
            printf("Ouch! SCORE: %d\n", score);
            plane.fuel -= 10;
        }
    }

    for (int i = 0; i < ball2arr.size(); ++i)
    {
        ball2arr[i].tick();
        if (ball2arr[i].position.y < -20)
            ball2arr.erase(ball2arr.begin() + i);
        ball2bb[i] = ball2arr[i].def_bounding_box();
        if (detect_collision(ball2bb[i], planebb))
        {
            score -= 50;
            printf("Ouch! SCORE: %d\n", score);
            plane.fuel -= 10;
        }
    }


    if (detect_collision(planebb, seabb))
        plane.dead = 1;
    

    arrow.tick();

    for (int i = 0; i < chutearr.size(); ++i)
    {
        chutearr[i].tick();
        chutebb[i] = chutearr[i].def_bounding_box();
        if (chutearr[i].position.y < -20)
            chutearr.erase(chutearr.begin() + i);
    }

    for (int j = 0; j < missilearr.size(); ++j)
    {
        missilearr[j].tick();
        missilebb[j] = missilearr[j].def_bounding_box();
        for (int i = 0; i < chutearr.size(); ++i)
        {
            if (detect_collision(chutebb[i], missilebb[j]))
            {
                score += 5;
                printf("Enemy shot! SCORE: %d\n", score);

                chutearr.erase(chutearr.begin() + i);
                missilearr.erase(missilearr.begin() + j);
            }
        }
        if (abs(missilearr[j].position.x - sea.position.x) > 1000)
            missilearr.erase(missilearr.begin() + j);
        else if (abs(missilearr[j].position.z - sea.position.z) > 1000)
            missilearr.erase(missilearr.begin() + j);
    }

    for (int j = 0; j < bombarr.size(); ++j)
    {
        bombarr[j].tick();
        // printf("bombpos: %f,%f,%f\n", bombarr[j].position.x, bombarr[j].position.y, bombarr[j].position.z);
        bombbb[j] = bombarr[j].def_bounding_box();
        for (int i = 0; i < chutearr.size(); ++i)
        {
            if (detect_collision(chutebb[i], bombbb[j]))
            {
                score += 5;
                printf("Enemy blasted! SCORE: %d\n", score);

                chutearr.erase(chutearr.begin() + i);
                bombarr.erase(bombarr.begin() + j);
            }
        }

        for (int i = 0; i < cannonarr.size(); ++i)
        {
            cannonbb[i] = cannonarr[i].def_bounding_box();
            if (detect_collision(cannonbb[i], bombbb[j]))
            {
                score += 30;
                printf("Outpost destroyed! SCORE: %d\n", score);
                if (i == 0) drawarrow = 0;
                cannonarr.erase(cannonarr.begin() + i);
                bombarr.erase(bombarr.begin() + j);
            }
        }

        if (bombarr[j].position.y < -20)
        {
            // printf("bommb ereasing\n");
            bombarr.erase(bombarr.begin() + j);
        }
    }

    for (int i = 0; i < ringarr.size(); ++i)
    {
        if (detect_collision(ringbb[i], planebb))
        {
            score += 10;
            printf("SCORE: %d\n", score);
            ringarr.erase(ringarr.begin() + i);
        }
    }

    for (int i = 0; i < tankarr.size(); ++i)
    {
        tankarr[i].tick();
        if (detect_collision(tankbb[i], planebb))
        {
            tankarr.erase(tankarr.begin() + i);
            plane.fuel = 599;
        }
    }

    compass.tick(plane.z_ref[2], plane.z_ref[0]);

    tsc += 1;
    if (floor(tsc/300)) 
    {
        score+=floor(tsc/300);
        tsc = 0;
    }
    camera_rotation_angle += 1;
        
}



/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) 
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Ball(0, 0, 0, COLOR_RED);

    sea = Sea(0, -20, 0, COLOR_BLUE);
    seabb = sea.def_bounding_box();

    compass = Compass(-3,-2.8,0);

    for (int i = 0; i < 10; ++i)
    {
        int xcoord = rand()%2000 - 1000;
        int zcoord = rand()%2000 - 1000;
        if (i%3==0)
        {
            volcano = Volcano(xcoord, -15, zcoord, COLOR_BLACK);
            volcanoarr.push_back(volcano);
        }
        else
        {
            island = Island(xcoord, -15, zcoord, COLOR_GREEN);
            islandarr.push_back(island);
            int x = rand()%100;
            if (x%2)
            {
                cannon = Cannon(xcoord + 50, -13, zcoord);
                cannonarr.push_back(cannon);
                printf("cannon leggo\n");
            }
        }
    }

    int xc = 0, yc = 0, zc = 60;

    for (int i = 0; i < 20; ++i)
    {
        ring = SmokeRing(xc, yc, zc);
        ringarr.push_back(ring);
        ringbb[i] = ringarr[i].def_bounding_box();
        xc = rand()%2000 - 1000;
        yc = rand()%40 - 10;
        zc = rand()%4000 - 2000;
    }

    for (int i = 0; i < 30; ++i)
    {
        xc = rand()%2000 - 1000;
        yc = rand()%40;
        zc = rand()%4000 - 2000;
        tank = FuelTank(xc, yc, zc);
        tankarr.push_back(tank);
        tankbb[i] = tankarr[i].def_bounding_box();
    }


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_SKY_BLUE.r / 256.0, COLOR_SKY_BLUE.g / 256.0, COLOR_SKY_BLUE.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    // UNITS = ScoreBoard(0,3.25,0, COLOR_WHITE);
    // // UNITS.draw(DBVP, units);
    // TENS = ScoreBoard(0.5,3.25,0, COLOR_WHITE);
    // // TENS.draw(DBVP, tens);
    // HUNDREDS = ScoreBoard(1,3.25,0, COLOR_WHITE);
    // // HUNDREDS.draw(DBVP, hundreds);
    // THOUSANDS = ScoreBoard(1.5,3.25,0, COLOR_WHITE);
    // // THOUSANDS.draw(DBVP, thousands);
    // TTHOUSANDS = ScoreBoard(2,3.25,0, COLOR_WHITE);
    // // TTHOUSANDS.draw(DBVP, tthousands);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            // reset_screen(); 
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::perspective(left, right, bottom, top, 0.1f, 500.0f);

    DBMatrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void reset_screen1() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    GLfloat fov = 90.0f;
    Matrices.projection = glm::perspective (fov, (GLfloat) (right-left) / (GLfloat) (top-bottom), 0.1f, 2000.0f);
}
