#pragma once

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <string>

class Geometry;

class Game {
public:
    bool Init(const std::string& windowName, const int& width, const int& height);
    bool Load();
    void UnLoad();
    void Loop();
    void Shutdown();

    Game();
    ~Game();

    static void GLFWErrorHandle(int errorCode, const char* text);
    static void Log(const std::string& text);
protected:
    GLFWwindow* _window;
    Geometry* _geom;
};
