#include "shader.h"
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "console.h"
#include "misc.h"

using string = std::string;

namespace Hyhy {


    Shader::~Shader() {
        glDetachShader(program, vert_Shader);
        glDetachShader(program, frag_shader);
        glDeleteProgram(program);
        glDeleteShader(vert_Shader);
        glDeleteShader(frag_shader);
    }

    GLuint Shader::load_shader_file(const char* file, int type) {
        string str = readFileIntoString(file);
        const char* source = str.c_str();

        GLuint id = glCreateShader(type);
        glShaderSource(id, 1, &source, NULL);
        glCompileShader(id);

        //Check to make sure there were no errors
        GLint isCompiled = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
        if (!isCompiled) {
            GLint logLength;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> log;
            log.resize(logLength);
            glGetShaderInfoLog(id, logLength, &logLength, log.data());

            out_err(string("compiled error:") + string(log.data()));
            return 0;
        }

        //Save variable bindings
        if (type == GL_VERTEX_SHADER) {
            size_t ix = 0;
            while (true) {
                ix = str.find("\nin ", ix);
                if (ix == -1) {
                    break;
                }
                ix = str.find(";", ix);
                size_t start_ix = ix;
                while (str[--start_ix] != ' ');
                string fn = str.substr(start_ix + 1, ix - start_ix - 1);
                attrs.push_back(fn);
            }
        }

        return id;
    }

    Shader::Shader(string dir, string name) {
        string fn = dir + name;
        string vert_path = fn + ".vert";
        string frag_path = fn + ".frag";

        vert_Shader = load_shader_file(vert_path.c_str(), GL_VERTEX_SHADER);
        frag_shader = load_shader_file(frag_path.c_str(), GL_FRAGMENT_SHADER);

        program = glCreateProgram();
        glAttachShader(program, vert_Shader);
        glAttachShader(program, frag_shader);

        //bind
        for (size_t i = 0; i < attrs.size(); ++i) {
            glBindAttribLocation(program, (GLuint) i, attrs[i].c_str());
        }

        glLinkProgram(program);

        //Check for linking errors
        GLint isLinked;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (!isLinked) {
            GLint logLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> log;
            log.resize(logLength);
            glGetProgramInfoLog(program, logLength, &logLength, log.data());

            out_err(string("link error:") + string(log.data()));
            program = 0;
            return;
        }

        //Get global variable locations
        mvpId = glGetUniformLocation(program, "mvp");
        mvId = glGetUniformLocation(program, "mv");

        glDeleteShader(vert_Shader);
        glDeleteShader(frag_shader);
    }

    void Shader::use() {
        glUseProgram(program);
    }

    GLuint Shader::load_shader_source(const char* source, int type) {
        GLuint id = glCreateShader(type);
        glShaderSource(id, 1, &source, NULL);
        glCompileShader(id);

        //Check to make sure there were no errors
        GLint isCompiled = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
        if (!isCompiled) {
            GLint logLength;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> log;
            log.resize(logLength);
            glGetShaderInfoLog(id, logLength, &logLength, log.data());

            out_err(string("compiled error:") + string(log.data()));
            return 0;
        }

        return id;
    }

    void Shader::SetMVP(const float* mvp, const float* mv) {
        if (mvp) glUniformMatrix4fv(mvpId, 1, GL_TRUE, mvp);
        if (mv) glUniformMatrix4fv(mvId, 1, GL_TRUE, mv);
    }
}
