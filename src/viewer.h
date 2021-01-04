#pragma once

#include <chrono>
#include <string>
#include <GLFW/glfw3.h>
#include "scene_manager.h"

namespace Hyhy {

    class Viewer {
    public:
        Viewer();
        Viewer(const std::string& title);
        ~Viewer();

        void init();

        void start();


        void set_renderer(SceneManager* rd) { scene_mgr = rd; }

    private:
        static void update();


        static void err_callback(int error, const char* description);
        static void resize_callback(GLFWwindow* window, int width, int height);

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void char_callback(GLFWwindow* window, unsigned int codepoint);
        static void cursor_callback(GLFWwindow* window, double xpos, double ypos);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


        static SceneManager* scene_mgr;

        static GLFWwindow* window;
        static size_t buffer_w;
        static size_t buffer_h;

        static int framecount;
        static std::chrono::time_point<std::chrono::system_clock> sys_last;
        static std::chrono::time_point<std::chrono::system_clock> sys_curr;

        std::string title;

    };
}
