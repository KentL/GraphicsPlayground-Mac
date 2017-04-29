//
//  Game.cpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-03-26.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#include "Game.hpp"

ExampleBase* Game::example;

void Game::Init(int argc, char **argv){
    int exampleIndex = argc > 1 ? std::stoi(argv[1]) : 0;
    
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    
    glfwSetErrorCallback(error_callback);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1280, 720, "Graphics Playground", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glewExperimental = GL_TRUE;
    glewInit();
    
    // Leave this here! On windows machines in Lab, glewInit is generating some mysterious, but apparently
    // harmless, error - and we need it gone.
    glGetError();
    
    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);
    
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        exit(EXIT_FAILURE);
    }
    
    switch (exampleIndex)
    {
        case 0: example = InterpolationExample::getInstance(); break;
        case 1: example = RotateCubeExample::getInstance(); break;
        case 2: example = RotateTextureCubeExample::getInstance(); break;
        case 3: example = BlendExample::getInstance(); break;
        case 4: {
            CityModelExample* cityModelExample = CityModelExample::getInstance();
            cityModelExample->window = window;
            example=cityModelExample;
            break;
        }
        default:
            break;
    }
    
    example->Initialize();
}

void Game::Run(){
    do
    {
        // Clear color buffer to black
        glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        //render
        example->Render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while (!glfwWindowShouldClose(window));
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    exit(EXIT_SUCCESS);

}

void Game::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else
        example->HandleKeyInput(window, key, scancode, action, mods);
}
void Game::cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    example->HandleCursorPositionChange(window,xpos,ypos);
}