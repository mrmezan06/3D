
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h" // assignment lagbe
#include "basic_camera.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// basic camera
float eyeX = 0.0, eyeY = -3.0, eyeZ = 2.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment 2", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");


    float wallC1[] = {0.6f, 0.4f, 0.0f};
    float wallC2[] = { 0.6f, 0.4f, 0.4f };
    float harmony[] = { 0.13f,0.13f,0.13f };
    float hShade[] = { 0.38f,0.38f,0.38f };
    float wood[] = { 1.0f,0.6f,0.2f };
    float woodD[] = { 0.6f, 0.3f, 0.0f };
    float silverD[] = { 0.5f,0.5f,0.5f };
    float yWhite[] = { 1.0f,1.0f,0.8f };
    float black[] = { 0.0f, 0.0f, 0.0f };
    float sofa[] = { 0.7f, 0.3f, 0.2f };
    float blue[] = { 0.0f, 0.0f, 1.0f };
    float blueL[] = { 0.0f, 0.4f, 1.0f };
    float ground[] = { 0.9,0.9,0.9 };



    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cube_vertices[] = {
        
        // Bottom plane 0,1,2,3,4,5
         -2.0f, -2.0f, 0.0f, ground[0], ground[1], ground[2],
         2.0f, -2.0f, 0.0f, ground[0], ground[1], ground[2],
         2.0f, 2.0f, 0.0f, ground[0], ground[1], ground[2],
         2.0f, 2.0f, 0.0f, ground[0], ground[1], ground[2],
         -2.0f, 2.0f, 0.0f, ground[0], ground[1], ground[2],
         -2.0f, -2.0f, 0.0f, ground[0], ground[1], ground[2],

         // Top plane 
         /*-2.0f, -2.0f, 2.0f, ground[0], ground[1], ground[2],
         2.0f, -2.0f, 2.0f, ground[0], ground[1], ground[2],
         2.0f, 2.0f, 2.0f, ground[0], ground[1], ground[2],
         2.0f, 2.0f, 2.0f, ground[0], ground[1], ground[2],
         -2.0f, 2.0f, 2.0f, ground[0], ground[1], ground[2],
         -2.0f, -2.0f, 2.0f, ground[0], ground[1], ground[2],*/

         // Right Plane 6,7,8,9,10,11,
         2.0f, -2.0f, 0.0f, wallC2[0], wallC2[1], wallC2[2],
         2.0f, -2.0f, 2.0f, wallC2[0], wallC2[1], wallC2[2],
         2.0f, 2.0f, 2.0f, wallC2[0], wallC2[1], wallC2[2],
         2.0f, 2.0f, 2.0f, wallC2[0], wallC2[1], wallC2[2],
         2.0f, 2.0f, 0.0f, wallC2[0], wallC2[1], wallC2[2],
         2.0f, -2.0f, 0.0f, wallC2[0], wallC2[1], wallC2[2],

         // Left Plane 12,13,14,15,16,17
         -2.0f, -2.0f, 0.0f, wallC2[0], wallC2[1], wallC2[2],
         -2.0f, -2.0f, 2.0f, wallC2[0], wallC2[1], wallC2[2],
         -2.0f, 2.0f, 2.0f, wallC2[0], wallC2[1], wallC2[2],
         -2.0f, 2.0f, 2.0f, wallC2[0], wallC2[1], wallC2[2],
         -2.0f, 2.0f, 0.0f, wallC2[0], wallC2[1], wallC2[2],
         -2.0f, -2.0f, 0.0f, wallC2[0], wallC2[1], wallC2[2],

         // back plane 18,19,20,21,22,23
         -2.0f, 2.0f, 0.0f, wallC1[0], wallC1[1], wallC1[2],
         2.0f, 2.0f, 0.0f, wallC1[0], wallC1[1], wallC1[2],
         2.0f, 2.0f, 2.0f, wallC1[0], wallC1[1], wallC1[2],
         2.0f, 2.0f, 2.0f, wallC1[0], wallC1[1], wallC1[2],
         -2.0f, 2.0f, 2.0f, wallC1[0], wallC1[1], wallC1[2],
         -2.0f, 2.0f, 0.0f, wallC1[0], wallC1[1], wallC1[2],

        // Table
        // Table top 24-29
        -1.0f, -1.5f, 0.5f, wood[0], wood[1], wood[2],
        1.0f, -1.5f, 0.5f, wood[0], wood[1], wood[2],
        1.0f, -0.5f, 0.5f, wood[0], wood[1], wood[2],
        1.0f, -0.5f, 0.5f, wood[0], wood[1], wood[2],
        -1.0f, -0.5f, 0.5f, wood[0], wood[1], wood[2],
        -1.0f, -1.5f, 0.5f, wood[0], wood[1], wood[2],
        // Table top bottom face 612-617
        -1.0f, -1.5f, 0.42f, wood[0], wood[1], wood[2],
        1.0f, -1.5f, 0.42f, wood[0], wood[1], wood[2],
        1.0f, -0.5f, 0.42f, wood[0], wood[1], wood[2],
        1.0f, -0.5f, 0.42f, wood[0], wood[1], wood[2],
        -1.0f, -0.5f, 0.42f, wood[0], wood[1], wood[2],
        -1.0f, -1.5f, 0.42f, wood[0], wood[1], wood[2],

        // Table 1st Leg
        // 1st side of leg 30-35
        -0.98f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.98f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.98f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        // 2nd side of leg 36,37,38,39,40,41
        -0.98f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        -0.98f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],
        -0.98f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.98f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.98f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.98f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],

        //// 3rd side of leg 42-47
        -0.98f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.98f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.98f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],

        //// 4th side of leg 48-53
        -0.96f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        -0.96f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],

        // Table 4th Leg
        // 1st side of leg 54-59
        0.96f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.96f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.96f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        // 2nd side of leg 60-65
        0.96f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        0.96f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],
        0.96f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.96f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.96f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.96f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],

        //// 3rd side of leg 66-71
        0.96f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.96f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.96f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],

        //// 4th side of leg 72-77
        0.98f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.52f, 0.0f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.52f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.54f, 0.5f, woodD[0], woodD[1], woodD[2],
        0.98f, -0.54f, 0.0f, woodD[0], woodD[1], woodD[2],

        // Table 3rd Leg 

        // 1st side of leg 78-83
             0.96f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.96f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.96f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
             // 2nd side of leg 84-89
             0.96f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
             0.96f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],
             0.96f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.96f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.96f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.96f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],

             //// 3rd side of leg 90-95
             0.96f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.96f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.96f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],

             //// 4th side of leg 96-101
             0.98f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
             0.98f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],

         // Table 2nd Leg 

        // 1st side of leg 102-107
            -0.98f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
            -0.96f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
            -0.96f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
            -0.96f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
            -0.98f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
            -0.98f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
            // 2nd side of leg 108-113
            -0.98f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
            -0.98f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],
            -0.98f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
            -0.98f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
            -0.98f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
            -0.98f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
            // 3rd side of leg 114-119
             -0.98f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],
             -0.96f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],
             -0.96f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
             -0.96f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
             -0.98f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
             -0.98f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],

             // 4th side of leg 120-125
            -0.96f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],
            -0.96f, -1.46f, 0.0f, woodD[0], woodD[1], woodD[2],
            -0.96f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
            -0.96f, -1.46f, 0.5f, woodD[0], woodD[1], woodD[2],
            -0.96f, -1.48f, 0.5f, woodD[0], woodD[1], woodD[2],
            -0.96f, -1.48f, 0.0f, woodD[0], woodD[1], woodD[2],

            // Table sides of front side 126-131
            -1.0f, -1.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            1.0f, -1.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            1.0f, -1.5f, 0.5f, woodD[0], woodD[1], woodD[2],
            1.0f, -1.5f, 0.5f, woodD[0], woodD[1], woodD[2],
            -1.0f, -1.5f, 0.5f, woodD[0], woodD[1], woodD[2],
            -1.0f, -1.5f, 0.4f, woodD[0], woodD[1], woodD[2],

            // Table right side 132-137
            1.0f, -1.5f, 0.5f, woodD[0], woodD[1], woodD[2],
            1.0f, -1.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            1.0f, -0.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            1.0f, -0.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            1.0f, -0.5f, 0.5f, woodD[0], woodD[1], woodD[2],
            1.0f, -1.5f, 0.5f, woodD[0], woodD[1], woodD[2],

            // Table back side 138-143
            1.0f, -0.5f, 0.5f, woodD[0], woodD[1], woodD[2],
            1.0f, -0.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            -1.0f, -0.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            -1.0f, -0.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            -1.0f, -0.5f, 0.5f, woodD[0], woodD[1], woodD[2],
            1.0f, -0.5f, 0.5f, woodD[0], woodD[1], woodD[2],

            // Table left side 144-149
            -1.0f, -0.5f, 0.5f, woodD[0], woodD[1], woodD[2],
            -1.0f, -0.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            -1.0f, -1.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            -1.0f, -1.5f, 0.4f, woodD[0], woodD[1], woodD[2],
            -1.0f, -1.5f, 0.5f, woodD[0], woodD[1], woodD[2],
            -1.0f, -0.5f, 0.5f, woodD[0], woodD[1], woodD[2],

            // Sofa bottom side 150-155
            1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            // Sofa foam bottom side 156-161
            1.3f, -1.4f, 0.3f, blue[0], blue[1], blue[2],
            1.8f, -1.4f, 0.3f, blue[0], blue[1], blue[2],
            1.8f, -0.5f, 0.3f, blue[0], blue[1], blue[2],
            1.8f, -0.5f, 0.3f, blue[0], blue[1], blue[2],
            1.3f, -0.5f, 0.3f, blue[0], blue[1], blue[2],
            1.3f, -1.4f, 0.3f, blue[0], blue[1], blue[2],

            // Sofa foam top side 600-605
            1.3f, -1.4f, 0.5f, blue[0], blue[1], blue[2],
            1.8f, -1.4f, 0.5f, blue[0], blue[1], blue[2],
            1.8f, -0.5f, 0.5f, blue[0], blue[1], blue[2],
            1.8f, -0.5f, 0.5f, blue[0], blue[1], blue[2],
            1.3f, -0.5f, 0.5f, blue[0], blue[1], blue[2],
            1.3f, -1.4f, 0.5f, blue[0], blue[1], blue[2],

            // Sofa foam front side 606-611
            1.3f, -0.5f, 0.3f, blue[0], blue[1], blue[2],
            1.3f, -0.5f, 0.5f, blue[0], blue[1], blue[2],
            1.3f, -1.4f, 0.5f, blue[0], blue[1], blue[2],
            1.3f, -1.4f, 0.5f, blue[0], blue[1], blue[2],
            1.3f, -1.4f, 0.3f, blue[0], blue[1], blue[2],
            1.3f, -0.5f, 0.3f, blue[0], blue[1], blue[2],

            // Sofa back side  back face 162-167
            1.3f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            //  back side front face 168-173
            1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            //  back handle top 174-179
            1.3f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            //   back handle front 180-185
            1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            //  back handle back 186-191
            1.8f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],

            // front handle front face 192-197
            1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            // front handle back face 198-203
            1.3f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            // front handle top face 204-209
            1.3f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            // front handle front face 210-215
            1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            // front handle back face 216-221
            1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            // front sofa front face 222-227
            1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.4f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.3f, -1.4f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.5f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],

            // back sofa back face 228-233
            1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],

            // back sofa front face 234-239
            1.7f, -0.5f, 0.3f, blueL[0], blueL[1], blueL[2],
            1.7f, -1.4f, 0.3f, blueL[0], blueL[1], blueL[2],
            1.7f, -1.4f, 1.0f, blueL[0], blueL[1], blueL[2],
            1.7f, -1.4f, 1.0f, blueL[0], blueL[1], blueL[2],
            1.7f, -0.5f, 1.0f, blueL[0], blueL[1], blueL[2],
            1.7f, -0.5f, 0.3f, blueL[0], blueL[1], blueL[2],
            // back sofa front face right front 240-245
            1.7f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.7f, -0.5f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.7f, -0.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -0.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],

            // back sofa front face left front 246-251
            1.7f, -1.4f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.7f, -1.5f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -1.4f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -1.4f, 0.3f, sofa[0], sofa[1], sofa[2],

            // left handle left face 252-257
            1.8f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],

            // right handle right face 258-263
            1.8f, -1.5f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -1.5f, 0.3f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 0.3f, sofa[0], sofa[1], sofa[2],
            // back top face 264-269
            1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.8f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.8f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
            1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],

            // TV Box Stand 
                //bottom 270-275
                1.0f, 1.2f, 0.001f, woodD[0], woodD[1], woodD[2],
                1.3f, 0.8f, 0.001f, woodD[0], woodD[1], woodD[2],
                1.6f, 1.2f, 0.001f, woodD[0], woodD[1], woodD[2],
                1.6f, 1.2f, 0.001f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.6f, 0.001f, woodD[0], woodD[1], woodD[2],
                1.0f, 1.2f, 0.001f, woodD[0], woodD[1], woodD[2],

                // 1st wrapper box 276-281
                1.0f, 1.2f, 0.0f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.6f, 0.0f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.6f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.6f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.0f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.0f, 1.2f, 0.0f, woodD[0], woodD[1], woodD[2],

                // 2nd wrapper box 282-287
                1.0f, 1.2f, 0.0f, woodD[0], woodD[1], woodD[2],
                1.0f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 0.8f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 0.8f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 0.8f, 0.0f, woodD[0], woodD[1], woodD[2],
                1.0f, 1.2f, 0.0f, woodD[0], woodD[1], woodD[2],

                // 3rd wrapper box 288-293
                1.3f, 0.8f, 0.4f, wood[0], wood[1], wood[2],
                1.6f, 1.2f, 0.4f, wood[0], wood[1], wood[2],
                1.6f, 1.2f, 0.0f, wood[0], wood[1], wood[2],
                1.6f, 1.2f, 0.0f, wood[0], wood[1], wood[2],
                1.3f, 0.8f, 0.0f, wood[0], wood[1], wood[2],
                1.3f, 0.8f, 0.4f, wood[0], wood[1], wood[2],

                // 4th wrapper box 294-299
                1.6f, 1.2f, 0.0f, woodD[0], woodD[1], woodD[2],
                1.6f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.6f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.6f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.6f, 0.0f, woodD[0], woodD[1], woodD[2],
                1.6f, 1.2f, 0.0f, woodD[0], woodD[1], woodD[2],

                // TV BOX Top Plate bottom sheet 300-305
                0.9f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 0.7f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.7f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.7f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.7f, 0.4f, woodD[0], woodD[1], woodD[2],
                0.9f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                // TV BOX Top Plate top sheet 306-311
                0.9f, 1.2f, 0.45f, wood[0], wood[1], wood[2],
                1.3f, 0.7f, 0.45f, wood[0], wood[1], wood[2],
                1.7f, 1.2f, 0.45f, wood[0], wood[1], wood[2],
                1.7f, 1.2f, 0.45f, wood[0], wood[1], wood[2],
                1.3f, 1.7f, 0.45f, wood[0], wood[1], wood[2],
                0.9f, 1.2f, 0.45f, wood[0], wood[1], wood[2],
                // bottom to top 1st wrapper 312-317
                0.9f, 1.2f, 0.45f, woodD[0], woodD[1], woodD[2],
                0.9f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 0.7f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 0.7f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 0.7f, 0.45f, woodD[0], woodD[1], woodD[2],
                0.9f, 1.2f, 0.45f, woodD[0], woodD[1], woodD[2],

                // bottom to top 2nd wrapper 318-323
                1.3f, 0.7f, 0.4f, wood[0], wood[1], wood[2],
                1.7f, 1.2f, 0.4f, wood[0], wood[1], wood[2],
                1.7f, 1.2f, 0.45f, wood[0], wood[1], wood[2],
                1.7f, 1.2f, 0.45f, wood[0], wood[1], wood[2],
                1.3f, 0.7f, 0.45f, wood[0], wood[1], wood[2],
                1.3f, 0.7f, 0.4f, wood[0], wood[1], wood[2],

                // bottom to top 3rd wrapper 324-329
                1.7f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.7f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.7f, 0.45f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.7f, 0.45f, woodD[0], woodD[1], woodD[2],
                1.7f, 1.2f, 0.45f, woodD[0], woodD[1], woodD[2],
                1.7f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],

                // bottom to top 4th wrapper 330-335
                0.9f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.7f, 0.4f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.7f, 0.45f, woodD[0], woodD[1], woodD[2],
                1.3f, 1.7f, 0.45f, woodD[0], woodD[1], woodD[2],
                0.9f, 1.2f, 0.45f, woodD[0], woodD[1], woodD[2],
                0.9f, 1.2f, 0.4f, woodD[0], woodD[1], woodD[2],

                // TV handle bottom 336-341
                1.2f, 1.3f, 0.46f, black[0], black[1], black[2],
                1.2f, 1.1f, 0.46f, black[0], black[1], black[2],
                1.4f, 1.1f, 0.46f, black[0], black[1], black[2],
                1.4f, 1.1f, 0.46f, black[0], black[1], black[2],
                1.4f, 1.3f, 0.46f, black[0], black[1], black[2],
                1.2f, 1.3f, 0.46f, black[0], black[1], black[2],

                // TV handle wrapper 342-347
                1.4f, 1.1f, 0.46f, black[0], black[1], black[2],
                1.4f, 1.1f, 0.5f, black[0], black[1], black[2],
                1.4f, 1.3f, 0.5f, black[0], black[1], black[2],
                1.4f, 1.3f, 0.5f, black[0], black[1], black[2],
                1.4f, 1.3f, 0.46f, black[0], black[1], black[2],
                1.4f, 1.1f, 0.46f, black[0], black[1], black[2],

                // // TV handle wrapper 348-353
                1.4f, 1.3f, 0.46f, black[0], black[1], black[2],
                1.4f, 1.3f, 0.5f, black[0], black[1], black[2],
                1.2f, 1.3f, 0.5f, black[0], black[1], black[2],
                1.2f, 1.3f, 0.5f, black[0], black[1], black[2],
                1.2f, 1.3f, 0.46f, black[0], black[1], black[2],
                1.4f, 1.3f, 0.46f, black[0], black[1], black[2],

                //// TV handle wrapper 354-359
                1.2f, 1.3f, 0.46f, black[0], black[1], black[2],
                1.2f, 1.3f, 0.5f, black[0], black[1], black[2],
                1.2f, 1.1f, 0.5f, black[0], black[1], black[2],
                1.2f, 1.1f, 0.5f, black[0], black[1], black[2],
                1.2f, 1.1f, 0.46f, black[0], black[1], black[2],
                1.2f, 1.3f, 0.46f, black[0], black[1], black[2],

                //// TV handle wrapper 360-365
                1.2f, 1.1f, 0.46f, black[0], black[1], black[2],
                1.2f, 1.1f, 0.5f, black[0], black[1], black[2],
                1.4f, 1.1f, 0.5f, black[0], black[1], black[2],
                1.4f, 1.1f, 0.5f, black[0], black[1], black[2],
                1.4f, 1.1f, 0.46f, black[0], black[1], black[2],
                1.2f, 1.1f, 0.46f, black[0], black[1], black[2],
                //// TV handle top 366-371
                1.2f, 1.3f, 0.5f, silverD[0], silverD[1], silverD[2],
                1.2f, 1.1f, 0.5f, silverD[0], silverD[1], silverD[2],
                1.4f, 1.1f, 0.5f, silverD[0], silverD[1], silverD[2],
                1.4f, 1.1f, 0.5f, silverD[0], silverD[1], silverD[2],
                1.4f, 1.3f, 0.5f, silverD[0], silverD[1], silverD[2],
                1.2f, 1.3f, 0.5f, silverD[0], silverD[1], silverD[2],

                // TV Bottom face 372-377
                0.75f, 1.35f, 0.51f, black[0], black[1], black[2],
                1.75f, 0.95f, 0.51f, black[0], black[1], black[2],
                1.8f, 1.0f, 0.51f, black[0], black[1], black[2],
                1.8f, 1.0f, 0.51f, black[0], black[1], black[2],
                0.8f, 1.4f, 0.51f, black[0], black[1], black[2],
                0.75f, 1.35f, 0.51f, black[0], black[1], black[2],

                // TV Top face 378-383
                0.75f, 1.35f, 1.0f, black[0], black[1], black[2],
                1.75f, 0.95f, 1.0f, black[0], black[1], black[2],
                1.8f, 1.0f, 1.0f, black[0], black[1], black[2],
                1.8f, 1.0f, 1.0f, black[0], black[1], black[2],
                0.8f, 1.4f, 1.0f, black[0], black[1], black[2],
                0.75f, 1.35f, 1.0f, black[0], black[1], black[2],

                // TV Left Side Face 384-389
                1.75f, 0.95f, 0.51f, black[0], black[1], black[2],
                1.75f, 0.95f, 1.0f, black[0], black[1], black[2],
                1.8f, 1.0f, 1.0f, black[0], black[1], black[2],
                1.8f, 1.0f, 1.0f, black[0], black[1], black[2],
                1.8f, 1.0f, 0.51f, black[0], black[1], black[2],
                1.75f, 0.95f, 0.51f, black[0], black[1], black[2],

                // TV Right Side Face 390-395
                0.8f, 1.4f, 0.51f, black[0], black[1], black[2],
                0.8f, 1.4f, 1.0f, black[0], black[1], black[2],
                0.75f, 1.35f, 1.0f, black[0], black[1], black[2],
                0.75f, 1.35f, 1.0f, black[0], black[1], black[2],
                0.75f, 1.35f, 0.51f, black[0], black[1], black[2],
                0.8f, 1.4f, 0.51f, black[0], black[1], black[2],

                // TV Back Face 396-401
                1.8f, 1.0f, 0.51f, black[0], black[1], black[2],
                1.8f, 1.0f, 1.0f, black[0], black[1], black[2],
                0.8f, 1.4f, 1.0f, black[0], black[1], black[2],
                0.8f, 1.4f, 1.0f, black[0], black[1], black[2],
                0.8f, 1.4f, 0.51f, black[0], black[1], black[2],
                1.8f, 1.0f, 0.51f, black[0], black[1], black[2],

                // TV Back Face 402-407
                0.75f, 1.35f, 0.51f, black[0], black[1], black[2],
                0.75f, 1.35f, 1.0f, black[0], black[1], black[2],
                1.75f, 0.95f, 1.0f, black[0], black[1], black[2],
                1.75f, 0.95f, 1.0f, black[0], black[1], black[2],
                1.75f, 0.95f, 0.51f, black[0], black[1], black[2],
                0.75f, 1.35f, 0.51f, black[0], black[1], black[2],

                // TV Glass Face 408-413
                0.77f, 1.33f, 0.54f, silverD[0], silverD[1], silverD[2],
                0.77f, 1.33f, 0.97f, silverD[0], silverD[1], silverD[2],
                1.73f, 0.93f, 0.97f, silverD[0], silverD[1], silverD[2],
                1.73f, 0.93f, 0.97f, silverD[0], silverD[1], silverD[2],
                1.73f, 0.93f, 0.54f, silverD[0], silverD[1], silverD[2],
                0.77f, 1.33f, 0.54f, silverD[0], silverD[1], silverD[2],

                // Piano bottom plane 414-419
                -0.6, 1.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.4f, black[0], black[1], black[2],

                 // Piano top plane 420-425
                -0.6, 1.8f, 0.5f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.5f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.5f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.5f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.5f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.5f, black[0], black[1], black[2],

                 // Piano back plane 426-431
                -0.6, 1.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.5f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.5f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.5f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.4f, black[0], black[1], black[2],

                // Piano left plane 432-437
                -1.6, 1.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.5f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.5f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.5f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.4f, black[0], black[1], black[2],

                // Piano right plane 438-443
                -0.6, 0.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.5f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.5f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.5f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.4f, black[0], black[1], black[2],

                // Piano back plane 444-449
                -1.6, 0.8f, 0.4f, silverD[0], silverD[1], silverD[2],
                -1.6f, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],
                -0.6f, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],
                -0.6f, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],
                -0.6f, 0.8f, 0.4f, silverD[0], silverD[1], silverD[2],
                -1.6f, 0.8f, 0.4f, silverD[0], silverD[1], silverD[2],

                // Piano Keyboard bottom face 450-455
                -1.6, 0.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.6f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.6f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.6f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.4f, black[0], black[1], black[2],

                // Piano Keyboard top face 456-461
                -1.6, 0.8f, 0.43f, black[0], black[1], black[2],
                -1.6f, 0.6f, 0.43f, black[0], black[1], black[2],
                -0.6f, 0.6f, 0.43f, black[0], black[1], black[2],
                -0.6f, 0.6f, 0.43f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.43f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.43f, black[0], black[1], black[2],

                // Piano Keyboard front face 462-467
                -1.6, 0.6f, 0.4f, silverD[0], silverD[1], silverD[2],
                -1.6f, 0.6f, 0.43f, silverD[0], silverD[1], silverD[2],
                -0.6f, 0.6f, 0.43f, silverD[0], silverD[1], silverD[2],
                -0.6f, 0.6f, 0.43f, silverD[0], silverD[1], silverD[2],
                -0.6f, 0.6f, 0.4f, silverD[0], silverD[1], silverD[2],
                -1.6f, 0.6f, 0.4f, silverD[0], silverD[1], silverD[2],

                // Piano Keyboard right face 468-473
                -0.6, 0.6f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.6f, 0.43f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.43f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.43f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.6f, 0.4f, black[0], black[1], black[2],

                // Piano Keyboard left face 474-479
                -1.6, 0.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.43f, black[0], black[1], black[2],
                -1.6f, 0.6f, 0.43f, black[0], black[1], black[2],
                -1.6f, 0.6f, 0.43f, black[0], black[1], black[2],
                -1.6f, 0.6f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.4f, black[0], black[1], black[2],

                // left triangle connected piano with keyboard face 480-485
                -1.6, 0.8f, 0.43f, black[0], black[1], black[2],
                -1.6f, 0.6f, 0.43f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.5f, black[0], black[1], black[2],
                -1.55, 0.8f, 0.43f, black[0], black[1], black[2],
                -1.55f, 0.6f, 0.43f, black[0], black[1], black[2],
                -1.55f, 0.8f, 0.5f, black[0], black[1], black[2],

                // right triangle connected piano with keyboard face 486-491
                -0.65f, 0.8f, 0.43f, black[0], black[1], black[2],
                -0.65f, 0.6f, 0.43f, black[0], black[1], black[2],
                -0.65f, 0.8f, 0.5f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.43f, black[0], black[1], black[2],
                -0.6f, 0.6f, 0.43f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.5f, black[0], black[1], black[2],

                // left triangle top face 492-497
                -1.55, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],
                -1.6f, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],
                -1.6f, 0.6f, 0.43f, silverD[0], silverD[1], silverD[2],
                -1.6f, 0.6f, 0.43f, silverD[0], silverD[1], silverD[2],
                -1.55f, 0.6f, 0.43f, silverD[0], silverD[1], silverD[2],
                -1.55f, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],

                // right triangle top face 498-503
                -0.6, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],
                -0.65f, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],
                -0.65f, 0.6f, 0.43f, silverD[0], silverD[1], silverD[2],
                -0.65f, 0.6f, 0.43f, silverD[0], silverD[1], silverD[2],
                -0.6, 0.6f, 0.43f, silverD[0], silverD[1], silverD[2],
                -0.6, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],

                // Pian Upper Plane Bottom Triangle Shape 504-509
                    // 1st triangle
                -1.6, 1.8f, 0.5f, silverD[0], silverD[1], silverD[2],
                -1.6f, 0.8f, 0.5f, silverD[0], silverD[1], silverD[2],
                -0.6f, 0.6f, 0.9f, silverD[0], silverD[1], silverD[2],


                // Piano Legs
                // 1st leg wrapper 510-515
                -1.6f, 1.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.0f, black[0], black[1], black[2],
                -1.6f, 1.78f, 0.0f, black[0], black[1], black[2],
                -1.6f, 1.78f, 0.0f, black[0], black[1], black[2],
                -1.6f, 1.78f, 0.4f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.4f, black[0], black[1], black[2],

                // 1st leg wrapper 516-521
                -1.6f, 1.78f, 0.4f, black[0], black[1], black[2],
                -1.6f, 1.78f, 0.0f, black[0], black[1], black[2],
                -1.58f, 1.78f, 0.0f, black[0], black[1], black[2],
                -1.58f, 1.78f, 0.0f, black[0], black[1], black[2],
                -1.58f, 1.78f, 0.4f, black[0], black[1], black[2],
                -1.6f, 1.78f, 0.4f, black[0], black[1], black[2],

                // 1st leg wrapper 516-521
                -1.58f, 1.78f, 0.4f, black[0], black[1], black[2],
                -1.58f, 1.78f, 0.0f, black[0], black[1], black[2],
                -1.58f, 1.8f, 0.0f, black[0], black[1], black[2],
                -1.58f, 1.8f, 0.0f, black[0], black[1], black[2],
                -1.58f, 1.8f, 0.4f, black[0], black[1], black[2],
                -1.58f, 1.78f, 0.4f, black[0], black[1], black[2],

                // 1st leg wrapper 522-527
                -1.58f, 1.8f, 0.4f, black[0], black[1], black[2],
                -1.58f, 1.8f, 0.0f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.0f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.0f, black[0], black[1], black[2],
                -1.6f, 1.8f, 0.4f, black[0], black[1], black[2],
                -1.58f, 1.8f, 0.4f, black[0], black[1], black[2],

                // 2nd leg wrapper 528-533
                -1.6f, 0.82f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.82f, 0.0f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.0f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.0f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.82f, 0.4f, black[0], black[1], black[2],

                 // 2nd leg wrapper 534-539
                -1.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.0f, black[0], black[1], black[2],
                -1.58f, 0.8f, 0.0f, black[0], black[1], black[2],
                -1.58f, 0.8f, 0.0f, black[0], black[1], black[2],
                -1.58f, 0.8f, 0.4f, black[0], black[1], black[2],
                -1.6f, 0.8f, 0.4f, black[0], black[1], black[2],

                 // 2nd leg wrapper 540-545
                -1.58f, 0.8f, 0.4f, black[0], black[1], black[2],
                -1.58f, 0.8f, 0.0f, black[0], black[1], black[2],
                -1.58f, 0.82f, 0.0f, black[0], black[1], black[2],
                -1.58f, 0.82f, 0.0f, black[0], black[1], black[2],
                -1.58f, 0.82f, 0.4f, black[0], black[1], black[2],
                -1.58f, 0.8f, 0.4f, black[0], black[1], black[2],

                // 2nd leg wrapper 546-551
                -1.58f, 0.82f, 0.4f, black[0], black[1], black[2],
                -1.58f, 0.82f, 0.0f, black[0], black[1], black[2],
                -1.6f, 0.82f, 0.0f, black[0], black[1], black[2],
                -1.6f, 0.82f, 0.0f, black[0], black[1], black[2],
                -1.6f, 0.82f, 0.4f, black[0], black[1], black[2],
                -1.58f, 0.82f, 0.4f, black[0], black[1], black[2],

                // 3rd leg wrapper 552-557
                -0.62f, 0.82f, 0.4f, black[0], black[1], black[2],
                -0.62f, 0.82f, 0.0f, black[0], black[1], black[2],
                -0.62f, 0.8f, 0.0f, black[0], black[1], black[2],
                -0.62f, 0.8f, 0.0f, black[0], black[1], black[2],
                -0.62f, 0.8f, 0.4f, black[0], black[1], black[2],
                -0.62f, 0.82f, 0.4f, black[0], black[1], black[2],

                // 3rd leg wrapper 558-563
                -0.62f, 0.8f, 0.4f, black[0], black[1], black[2],
                -0.62f, 0.8f, 0.0f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.0f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.0f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -0.62f, 0.8f, 0.4f, black[0], black[1], black[2],

                // 3rd leg wrapper 564-569
                -0.6f, 0.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.0f, black[0], black[1], black[2],
                -0.6f, 0.82f, 0.0f, black[0], black[1], black[2],
                -0.6f, 0.82f, 0.0f, black[0], black[1], black[2],
                -0.6f, 0.82f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.8f, 0.4f, black[0], black[1], black[2],

                // 3rd leg wrapper 570-575
                -0.6f, 0.82f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.82f, 0.0f, black[0], black[1], black[2],
                -0.62f, 0.82f, 0.0f, black[0], black[1], black[2],
                -0.62f, 0.82f, 0.0f, black[0], black[1], black[2],
                -0.62f, 0.82f, 0.4f, black[0], black[1], black[2],
                -0.6f, 0.82f, 0.4f, black[0], black[1], black[2],

                // 4th leg wrapper 576-581
                -0.62f, 1.8f, 0.4f, black[0], black[1], black[2],
                -0.62f, 1.8f, 0.0f, black[0], black[1], black[2],
                -0.62f, 1.78f, 0.0f, black[0], black[1], black[2],
                -0.62f, 1.78f, 0.0f, black[0], black[1], black[2],
                -0.62f, 1.78f, 0.4f, black[0], black[1], black[2],
                -0.62f, 1.8f, 0.4f, black[0], black[1], black[2],

                // 4th leg wrapper 582-587
                -0.62f, 1.78f, 0.4f, black[0], black[1], black[2],
                -0.62f, 1.78f, 0.0f, black[0], black[1], black[2],
                -0.6f, 1.78f, 0.0f, black[0], black[1], black[2],
                -0.6f, 1.78f, 0.0f, black[0], black[1], black[2],
                -0.6f, 1.78f, 0.4f, black[0], black[1], black[2],
                -0.62f, 1.78f, 0.4f, black[0], black[1], black[2],

                // 4th leg wrapper 588-593
                -0.6f, 1.78f, 0.4f, black[0], black[1], black[2],
                -0.6f, 1.78f, 0.0f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.0f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.0f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 1.78f, 0.4f, black[0], black[1], black[2],

                // 4th leg wrapper 594-599
                -0.6f, 1.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.0f, black[0], black[1], black[2],
                -0.62f, 1.8f, 0.0f, black[0], black[1], black[2],
                -0.62f, 1.8f, 0.0f, black[0], black[1], black[2],
                -0.62f, 1.8f, 0.4f, black[0], black[1], black[2],
                -0.6f, 1.8f, 0.4f, black[0], black[1], black[2],

                // Left Side Sofa
                // Sofa bottom side 618-623
                    -1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    // Sofa foam bottom side 624-629
                    -1.3f, -1.4f, 0.3f, blue[0], blue[1], blue[2],
                    -1.8f, -1.4f, 0.3f, blue[0], blue[1], blue[2],
                    -1.8f, -0.5f, 0.3f, blue[0], blue[1], blue[2],
                    -1.8f, -0.5f, 0.3f, blue[0], blue[1], blue[2],
                    -1.3f, -0.5f, 0.3f, blue[0], blue[1], blue[2],
                    -1.3f, -1.4f, 0.3f, blue[0], blue[1], blue[2],

                    // Sofa foam top side 630-635
                    -1.3f, -1.4f, 0.5f, blue[0], blue[1], blue[2],
                    -1.8f, -1.4f, 0.5f, blue[0], blue[1], blue[2],
                    -1.8f, -0.5f, 0.5f, blue[0], blue[1], blue[2],
                    -1.8f, -0.5f, 0.5f, blue[0], blue[1], blue[2],
                    -1.3f, -0.5f, 0.5f, blue[0], blue[1], blue[2],
                    -1.3f, -1.4f, 0.5f, blue[0], blue[1], blue[2],

                    // Sofa foam front side 636-641
                    -1.3f, -0.5f, 0.3f, blue[0], blue[1], blue[2],
                    -1.3f, -0.5f, 0.5f, blue[0], blue[1], blue[2],
                    -1.3f, -1.4f, 0.5f, blue[0], blue[1], blue[2],
                    -1.3f, -1.4f, 0.5f, blue[0], blue[1], blue[2],
                    -1.3f, -1.4f, 0.3f, blue[0], blue[1], blue[2],
                    -1.3f, -0.5f, 0.3f, blue[0], blue[1], blue[2],

                    // Sofa back side  back face 642-647
                    -1.3f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    //  back side front face 648-653
                    -1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    //  back handle top 654-659
                    -1.3f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    //   back handle front 660-665
                    -1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    //  back handle back 666-671
                    -1.8f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],

                    // front handle front face 672-677
                    -1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    // front handle back face 678-683
                    -1.3f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    // front handle top face 684-689
                    -1.3f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    // front handle front face 690-695
                    -1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    // front handle back face 696-701
                    -1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.4f, 0.7f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    // front sofa front face 702-707
                    -1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.4f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -1.4f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.5f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.3f, -0.5f, 0.01f, sofa[0], sofa[1], sofa[2],

                    // back sofa back face 708-713
                    -1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 0.01f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.01f, sofa[0], sofa[1], sofa[2],

                    // back sofa front face 714-719
                    -1.7f, -0.5f, 0.3f, blueL[0], blueL[1], blueL[2],
                    -1.7f, -1.4f, 0.3f, blueL[0], blueL[1], blueL[2],
                    -1.7f, -1.4f, 1.0f, blueL[0], blueL[1], blueL[2],
                    -1.7f, -1.4f, 1.0f, blueL[0], blueL[1], blueL[2],
                    -1.7f, -0.5f, 1.0f, blueL[0], blueL[1], blueL[2],
                    -1.7f, -0.5f, 0.3f, blueL[0], blueL[1], blueL[2],
                    // back sofa front face right front 720-725
                    -1.7f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -0.5f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -0.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -0.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],

                    // back sofa front face left front 726-731
                    -1.7f, -1.4f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -1.5f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -1.4f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -1.4f, 0.3f, sofa[0], sofa[1], sofa[2],

                    // left handle left face 732-737
                    -1.8f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 0.3f, sofa[0], sofa[1], sofa[2],

                    // right handle right face 738-743
                    -1.8f, -1.5f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -1.5f, 0.3f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 0.3f, sofa[0], sofa[1], sofa[2],
                    // back top face 744-749
                    -1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.8f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -0.4f, 1.0f, sofa[0], sofa[1], sofa[2],
                    -1.7f, -1.5f, 1.0f, sofa[0], sofa[1], sofa[2],

                    // Front Chair Left Side
                    // Bottom face 750-755
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // Bottom face 756-761
                    -0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],

                    // chair wrapper 762-767
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair wrapper 768-773
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair wrapper 774-779
                    -0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair wrapper 780-785
                    -0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 786-791
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.78f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.78f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.78f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 792-797
                    -0.8f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.58f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 798-803
                    -0.62f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.62f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.62f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    
                    // chair legs 804-809
                    -0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.58f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 810-815
                    -0.6f, -1.42f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.42f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.42f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 816-821
                    -0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.62f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.62f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.62f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 822-827
                    -0.78f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.78f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.78f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                   
                    // chair legs 828-833
                    -0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.42f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.42f, 0.0f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.42f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair upper part back face 834-839
                    -0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair upper part front face 840-845
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                     // chair upper part wrapper 846-851
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                     // chair upper part wrapper 852-857
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair upper part wrapper 858-863
                    -0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.6f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    -0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],

                    // Front Chair Right Side
                    // Bottom face 864-869
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // Bottom face 870-875
                    0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],

                    // chair wrapper 876-881
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair wrapper 882-887
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair wrapper 888-893
                    0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair wrapper 894-899
                    0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.33f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 900-905
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.78f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.78f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.78f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 906-911
                    0.8f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.58f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 912-917
                    0.62f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.62f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.62f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    
                    // chair legs 918-923
                    0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.58f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 924-929
                    0.6f, -1.42f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.42f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.42f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 930-935
                    0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.62f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.62f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.62f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair legs 936-941
                    0.78f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.78f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.78f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                   
                    // chair legs 942-947
                    0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.42f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.42f, 0.0f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.42f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.4f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair upper part back face 948-953
                    0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair upper part front face 954-959
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                     // chair upper part wrapper 960-965
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                     // chair upper part wrapper 966-971
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.58f, 0.3f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.3f, silverD[0], silverD[1], silverD[2],

                    // chair upper part wrapper 972-977
                    0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.6f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.6f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],
                    0.8f, -1.58f, 0.7f, silverD[0], silverD[1], silverD[2],




                                

    };

    // table top bottom face +6 and sofa foam top and front side +12 + top plane +6

    const int total = 984;
    
    unsigned int cube_indices[total] = {
        /*0, 1, 2, 3, 4, 5,

        6, 7, 8, 9, 10, 11,

        12, 13, 14, 15, 16, 17,

        18, 19, 20, 21, 22, 23,

        24, 25, 26, 27, 28, 29,

        30, 31, 32, 33, 34, 35,

        36, 37, 38, 39, 40, 41,

        42, 43, 44, 45, 46, 47,

        48, 49, 50, 51, 52, 53,

        54, 55, 56, 57, 58, 59,

        60, 61, 62, 63, 64, 65,

        66, 67, 68, 69, 70, 71,

        72, 73, 74, 75, 76, 77,
        78,79,80,81,82,83,
        84,85,86,87,88,89,
        90,91,92,93,94,95,
        96,97,98,99,100,101,102,
        103,104,105,106,107,108,
        109,110,111,112,113,114,
        115,116,117,118,119,
        120,121,122,123,124,125*/
       
    };

    for (int i = 0; i < total; i++) {
        cube_indices[i] = i;
    }
    
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // position attribute
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 view = basic_camera.createViewMatrix();
        ourShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, total, GL_UNSIGNED_INT, 0);


        // render boxes
        //for (unsigned int i = 0; i < 10; i++)
        //{
        //    // calculate the model matrix for each object and pass it to shader before drawing
        //    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //    model = glm::translate(model, cubePositions[i]);
        //    float angle = 20.0f * i;
        //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //    ourShader.setMat4("model", model);

        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        translate_Y -= 0.001;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        translate_Y += 0.001;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        translate_X -= 0.001;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        translate_X += 0.001;
        //camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        translate_Z -= 0.001;
        //std::cout << translate_X << translate_Y << translate_Z << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        translate_Z += 0.001;

        //std::cout << translate_X << translate_Y << translate_Z << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        rotateAngle_Z += 0.01;
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        eyeZ = 7.0;
        eyeY = -4.0;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        eyeZ = 2.0;
        eyeY = -3.0;
        eyeX = 0.0;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }





    /*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 1;
        else if (rotateAxis_Y) rotateAngle_Y -= 1;
        else rotateAngle_Z -= 1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;
    */

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    /*if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        lookAtX += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        lookAtX -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        lookAtY += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        lookAtY -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        lookAtZ += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        lookAtZ -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(0.0f, 0.0f, 1.0f));
    }*/

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
