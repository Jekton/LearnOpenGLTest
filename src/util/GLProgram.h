
#pragma once

#include <glad/glad.h>

#include "util/GLError.h"
#include "util/GLShader.h"

class GLProgram {
public:
    GLProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
        GLShader vertexShader{vertexShaderSource, GLShader::ShaderType::VERTEX};
        GLShader fragemntShader{fragmentShaderSource, GLShader::ShaderType::FRAGMENT};
        program = glCreateProgram();
        glAttachShader(program, vertexShader.get());
        glAttachShader(program, fragemntShader.get());
        glLinkProgram(program);
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, sizeof(GLError::infoLog), nullptr, GLError::infoLog);
            glDeleteProgram(program);
            throw GLError{GLError::infoLog};
        }
    }

    ~GLProgram() {
        glDeleteProgram(program);
    }

    void use() const noexcept {
        glUseProgram(program);
    }

private:
    GLint program;
};