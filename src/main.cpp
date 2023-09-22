
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/Window.h"

constexpr auto WIDTH = 800;
constexpr auto HEIGHT = 600;

static void framebufferSizeCallback(int width, int height);
static void processInput(Window& window);

int main() {
    Window window{WIDTH, HEIGHT, "LearnOpenGLTest"};
    window.makeContextCurrent();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        fprintf(stderr, "fail to init GLAD\n");
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    window.setFramebufferSizeCallback(framebufferSizeCallback);

    window.eventLoop([](Window* w) {
        processInput(*w);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });
    return 0;
}

static void framebufferSizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
}

static void processInput(Window& window) {
    if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
        window.setShouldClose(true);
    }
}