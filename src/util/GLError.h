
#pragma once

#include <stdexcept>

class GLError : public std::runtime_error {
public:
    static inline char infoLog[512];

    using std::runtime_error::runtime_error;
};