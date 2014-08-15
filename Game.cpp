#include "Game.hpp"
#include "Buffers.hpp"

#include <iostream>

void Game::GLFWErrorHandle(int errorCode, const char* text){
    Log("GLFW Error[" + std::to_string(errorCode) + "] : " + std::string(text));
}

void Game::Log(const std::string& text){
    std::cout << text << std::endl;
}

bool Game::Init(const std::string& windowName, const int& width, const int& height){
    glfwSetErrorCallback(GLFWErrorHandle);

    if(!glfwInit()) {
        Log("GLFW Init - failed");
        return false;
    } else {
        Log("GLFW Init - ok");
    }

    // <-- glfw hints -->
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if(!_window){
        Log("GLFW CreateWindow - failed");
        glfwTerminate(); //release glfw
        return false;
    }

    glfwMakeContextCurrent(_window);

    GLenum error;
    if((error = glewInit()) != GLEW_OK) {
        Log("GLEW Init - failed");
        Log("GLEW Error : " + std::string((const char*)glewGetErrorString(error)));
        glfwTerminate();
        return false;
    } else {
        Log("GLEW Init - ok");
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    return true;
}

bool Game::Load(){
    float tri[9] {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    unsigned int tri_index[3] { 0, 1, 2 };

    VertexBuffer* vertexBuffer = new VertexBuffer();
    vertexBuffer->Buffer(&tri[0], 9*(int)sizeof(float), GL_STATIC_DRAW);
    vertexBuffer->SetInfo(GL_TRIANGLES, GL_FLOAT, 3);

    IndexBuffer* indexBuffer  = new IndexBuffer();
    indexBuffer->Buffer(&tri_index[0], 3*(int)sizeof(unsigned int), GL_STATIC_DRAW);
    indexBuffer->SetInfo(GL_TRIANGLES, GL_UNSIGNED_INT, 3);

    _geom = new Geometry(vertexBuffer, nullptr, true);

    return true;
}

void Game::UnLoad(){
    delete _geom;
}

void Game::Loop(){
    _geom->BeginDraw();

    while(!glfwWindowShouldClose(_window)){
        glClear(GL_COLOR_BUFFER_BIT);

        _geom->Draw();

        glfwPollEvents();
        glfwSwapBuffers(_window);
    }

    _geom->EndDraw();
}

void Game::Shutdown(){
    if(_window != nullptr){
        UnLoad();
        glfwTerminate();
        _window = nullptr;
    }
}

Game::Game() : _window(nullptr) {
}

Game::~Game(){
    Shutdown();
}
