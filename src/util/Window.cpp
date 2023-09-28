
#include "util/Window.h"

#include <stdlib.h>

void Window::init() {
    static auto initialized = false;
    if (initialized) return;
    initialized = true;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}


Window::Window(int width, int height, std::string_view title) {
    init();
    window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (!window) {
        const char* info;
        glfwGetError(&info);
        throw WindowError(info);
    }
    windows[window] = this;
}


Window::~Window() {
    glfwDestroyWindow(window);
    windows.erase(window);
}


void Window::setFramebufferSizeCallback(FramebufferSizeCallbackType callback) noexcept {
    sizeCallback = callback;
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}


void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    auto wrapper = windows[window];
    if (wrapper) {
        wrapper->sizeCallback(width, height);
    }
}