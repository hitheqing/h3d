//
// Created by heqhe on 2021/1/4.
//

#include "meshrender.h"

#include "console.h"

namespace Hyhy {
    void MeshRender::prepare_for_rendering() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);


        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_mesh->vertices->size(), m_mesh->vertices->data(),
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_mesh->indices->size(), m_mesh->indices->data(),
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

        glEnableVertexAttribArray(0);


        // glBindVertexArray(0);

        prepared = true;
    }

    void MeshRender::rendering() const {
        if (!prepared) {
            out_err("MeshRender is not ready for rendering");
            return;
        }

        if (m_shader) {
            m_shader->use();
        }
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);
    }

}
