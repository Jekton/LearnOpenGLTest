
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
layout (location = 0) in vec2 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0, 1.0);
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

static const auto sFragmentShaderSource2 = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
)";


int main() try {
    Window window{WIDTH, HEIGHT, "LearnOpenGLTest"};
    window.makeContextCurrent();
    window.setFramebufferSizeCallback(framebufferSizeCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        fprintf(stderr, "fail to init GLAD\n");
        return -1;
    }


    GLfloat vertices[] = {
        // triangle in the left
        -0.5, 0,
        -0.25, 0.5,
        0, 0,

        // triangle in the right
        0, 0,
        0.25, 0.5,
        0.5, 0,
    };
    GLuint vertexArray[2];
    glGenVertexArrays(2, vertexArray);
    GLuint vertexBuffer[2];
    glGenBuffers(2, vertexBuffer);

    glBindVertexArray(vertexArray[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vertexArray[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
    auto offset = sizeof(vertices) / sizeof(*vertices) / 2;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + offset, GL_STATIC_DRAW);
    // If stride is 0, the generic vertex attributes are understood to be tightly packed
    // in the array.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(0);

    // clear the previous bindings
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLProgram program{sVertexShaderSource, sFragmentShaderSource};
    GLProgram program2{sVertexShaderSource, sFragmentShaderSource2};

    window.eventLoop([&program, &program2, vertexArray](Window* w) {
        processInput(*w);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        glBindVertexArray(vertexArray[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        program2.use();
        glBindVertexArray(vertexArray[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    });
    return 0;
} catch (const GLError& error) {
    fprintf(stderr, "%s\n", error.what());
}

static void framebufferSizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
}

static void processInput(Window& window) {
    if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
        window.setShouldClose(true);
    }
}