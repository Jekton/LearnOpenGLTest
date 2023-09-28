
#pragma once

#include <string>

#include <glad/glad.h>

#include "util/GLError.h"


class GLShader {
public:
    enum class ShaderType { VERTEX, FRAGMENT };

    GLShader(const char* source, ShaderType type) {
        auto glType = type == ShaderType::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
        shader = glCreateShader(glType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, sizeof(GLError::infoLog), nullptr, GLError::infoLog);
            glDeleteShader(shader);
            throw GLError{GLError::infoLog};
        }
    }

    ~GLShader() {
        glDeleteShader(shader);
    }

    auto get() const { return shader; }

private:
    GLuint shader;
};