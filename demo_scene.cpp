#include "demo_scene.h"
#include <GLFW/glfw3.h>
#include <misc.h>
#include "meshrender.h"
#include "vector3.h"

namespace Hyhy {


    MeshRender* mr1;
    MeshRender* mr2;

    DemoScene::~DemoScene() {
        delete mr1;
        delete mr2;
    }

    void DemoScene::init() {

        Mesh mesh;
        std::vector<Vector3> vertices;
        vertices.emplace_back(-0.8f, -0.4f, 0);
        vertices.emplace_back(0.5f, 0, 0);
        vertices.emplace_back(0, 0.6f, 0);
        mesh.vertices = &vertices;

        std::vector<GLuint> indices;
        indices.emplace_back(0);
        indices.emplace_back(1);
        indices.emplace_back(2);
        mesh.indices = &indices;

        // 注意相对路径为可执行文件同目录。所以这里要../
        Shader* shader = new Shader(cwd + string("res/shaders/"), string("unit_color"));


        mr1 = new MeshRender(&mesh);
        mr1->set_shader(shader);

        Mesh mesh2;
        std::vector<Vector3> vertices2;
        for (const Vector3& vertex : vertices) {
            vertices2.push_back(vertex / 2 + Vector3(0.5, 0, 0));
        }
        mesh2.vertices = &vertices2;

        std::vector<GLuint> indices2;
        indices2.emplace_back(0);
        indices2.emplace_back(1);
        indices2.emplace_back(2);
        mesh2.indices = &indices2;

        mr2 = new MeshRender(&mesh2);
//		mr2->set_shader(shader);

        render_list.push_back(mr1);
        render_list.push_back(mr2);

        for (auto* renderer : render_list)
            renderer->prepare_for_rendering();
    }


    void DemoScene::rendering() {
        for (auto* renderer : render_list)
            renderer->rendering();

    }

    void DemoScene::resize(size_t w, size_t h) {
    }

    std::string DemoScene::name() {
        return "FuckOpenGL!";
    }

    std::string DemoScene::info() {
        return "DESC";
    }

    void DemoScene::cursor_event(float x, float y) {

    }

    void DemoScene::scroll_event(float x, float y) {

    }

    void DemoScene::mouse_event(int button, int action, unsigned char mods) {

    }

    void DemoScene::keyboard_event(int key, int event, unsigned char scancode) {

    }

    void DemoScene::char_event(unsigned codepoint) {
    }
}
