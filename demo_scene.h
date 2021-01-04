#pragma once

#include "meshrender.h"
#include "scene_manager.h"

namespace Hyhy {
    class DemoScene : public SceneManager {

    public:
        DemoScene() : SceneManager() {}
        ~DemoScene() override;

        std::vector<MeshRender*> render_list;


        void init() override;
        void rendering() override;
        void resize(size_t w, size_t h) override;
        std::string name() override;
        std::string info() override;
        void cursor_event(float x, float y) override;
        void scroll_event(float offset_x, float offset_y) override;
        void mouse_event(int button, int action, unsigned char mods) override;
        void keyboard_event(int key, int event, unsigned char scancode) override;
        void char_event(unsigned codepoint) override;
    };

}

