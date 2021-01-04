#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <vector>

#include "object.h"

namespace Hyhy {
    class Shader {
    public:

        Shader(string dir, string name);
        Shader(const Shader& shader) = default;

        ~Shader();

        GLuint vert_Shader, frag_shader, program;
        GLuint mvpId;
        GLuint mvId;

        GLuint load_shader_file(const char* file, int type);
        GLuint load_shader_source(const char* source, int type);
        void SetMVP(const float* mvp, const float* mv);

        void use();

    private:
        std::vector<std::string> attrs;

    };

}


