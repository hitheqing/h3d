#pragma once

#include <string>

namespace Hyhy {


    class SceneManager {
    public:
        SceneManager() {}
        virtual ~SceneManager() {}


        virtual void init() {}


        virtual void rendering(void) = 0;

        virtual void resize(size_t w, size_t h) = 0;


        virtual std::string name() = 0;


        virtual std::string info() = 0;

        // -------------------------------------------------------------------------------
        // events

        virtual void cursor_event(float x, float y) {}
        virtual void scroll_event(float offset_x, float offset_y) {}
        virtual void mouse_event(int button, int action, unsigned char mods) {}
        virtual void keyboard_event(int key, int event, unsigned char scancode) {}
        virtual void char_event(unsigned int codepoint) {}
        // events
        // -------------------------------------------------------------------------------


    };

}