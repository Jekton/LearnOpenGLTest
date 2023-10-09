
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
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

uniform float offset;

out vec3 ourColor; // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}
)";

static const auto sFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
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


    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };
    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // clear the previous bindings
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLProgram program{sVertexShaderSource, sFragmentShaderSource};
    program.use();
    program.setUniform("offset", 0.4f);

    window.eventLoop([&program, vertexArray](Window* w) {
        processInput(*w);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        glBindVertexArray(vertexArray);
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