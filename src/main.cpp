
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/Window.h"
#include "util/GLProgram.h"
#include "util/GLShader.h"

constexpr auto WIDTH = 800;
constexpr auto HEIGHT = 600;

static void framebufferSizeCallback(int width, int height);
static void processInput(Window& window);

static const auto sVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

static const auto sFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";


int main() {
    Window window{WIDTH, HEIGHT, "LearnOpenGLTest"};
    window.makeContextCurrent();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        fprintf(stderr, "fail to init GLAD\n");
        return -1;
    }

    window.setFramebufferSizeCallback(framebufferSizeCallback);


    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // clear the previous bindings
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLProgram program{sVertexShaderSource, sFragmentShaderSource};

    window.eventLoop([&program, vertexArray](Window* w) {
        processInput(*w);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        glBindVertexArray(vertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 3);
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