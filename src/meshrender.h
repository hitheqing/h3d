//
// Created by heqhe on 2021/1/4.
//

#ifndef H3D_SRC_MESHRENDER_H
#define H3D_SRC_MESHRENDER_H

#pragma once

#include <vector>
#include <glad/glad.h>
#include "mesh.h"
#include "shader.h"
#include "vector3.h"

namespace Hyhy {

    class MeshRender {
    public:
        GLuint vbo, vao, ibo;

        MeshRender() {}

        MeshRender(Mesh* mesh)
                : m_mesh(mesh) {
        }

        ~MeshRender() {
            delete m_mesh;
            delete m_shader;
            vao = vbo = ibo = 0;
        }

        void prepare_for_rendering();

        void rendering() const;

        const Mesh* get_mesh() const { return m_mesh; }
        const Shader* get_shader() const { return m_shader; }
        void set_shader(Shader* shader) { m_shader = shader; }
    private:
        Mesh* m_mesh = nullptr;
        Shader* m_shader = nullptr;
        bool prepared;
    };
}


#endif //H3D_SRC_MESHRENDER_H
