
#pragma once

#include <map>
#include <stdexcept>
#include <string_view>

#include <GLFW/glfw3.h>

class Window {
public:
    using FramebufferSizeCallbackType = void(*)(int width, int height);

    Window(int width, int height, std::string_view title);
    ~Window();

    void makeContextCurrent() const noexcept {
        glfwMakeContextCurrent(window);
    }

    void setFramebufferSizeCallback(FramebufferSizeCallbackType callback) noexcept;

    bool shouldClose() const noexcept {
        return glfwWindowShouldClose(window);
    }

    void swapBuffers() const noexcept {
        glfwSwapBuffers(window);
    }

    void pollEvents() const noexcept {
        glfwPollEvents();
    }

    bool isKeyPressed(int key) noexcept {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    void setShouldClose(bool shouldClose) noexcept {
        glfwSetWindowShouldClose(window, shouldClose);
    }

    template <typename Action>
    void eventLoop(Action action) noexcept;

private:
    inline static std::map<GLFWwindow*, Window*> windows;

    GLFWwindow* window;
    FramebufferSizeCallbackType sizeCallback = nullptr;

    static void init();
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};


template <typename Action>
void Window::eventLoop(Action action) noexcept {
    while (!shouldClose()) {
        action(this);
        swapBuffers();
        pollEvents();
    }
    glfwTerminate();
}


class WindowError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

