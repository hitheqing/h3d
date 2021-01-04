
// make glad/glad.h at the top of other #include
#include <glad/glad.h>
#include "viewer.h"
#include <chrono>
#include "console.h"
#include "event.h"

using namespace std;
using namespace chrono;

#define DEFAULT_W 960
#define DEFAULT_H 640
#define DEBUG_EVENT 0

namespace Hyhy {
    Viewer::Viewer() {}

    Viewer::Viewer(const std::string& title) : title(title) {}

    Viewer::~Viewer() {
        glfwDestroyWindow(window);
        glfwTerminate();

        delete scene_mgr;
    }

    // Event index
    static unsigned int counter = 0;

    SceneManager* Viewer::scene_mgr;

    // window properties
    GLFWwindow* Viewer::window;
    size_t Viewer::buffer_w;
    size_t Viewer::buffer_h;

    // framecount & related timers
    int Viewer::framecount;
    time_point<system_clock> Viewer::sys_last;
    time_point<system_clock> Viewer::sys_curr;

    void Viewer::init() {
        // init error callback
        glfwSetErrorCallback(err_callback);

        // init glfw
        if (!glfwInit()) {
            out_err("glfwInit failed");
            exit(1);
        }

        // init version opengl3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // create window
        string title = scene_mgr->name();
        window = glfwCreateWindow(DEFAULT_W, DEFAULT_H, title.c_str(), NULL, NULL);
        if (!window) {
            out_err("Error: could not create window!");
            glfwTerminate();
            exit(1);
        }

        // set context
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        // framebuffer event callbacks
        glfwSetFramebufferSizeCallback(window, resize_callback);

        // key event callbacks
        glfwSetKeyCallback(window, key_callback);

        // character event callbacks
        glfwSetCharCallback(window, char_callback);

        // cursor event callbacks
        glfwSetCursorPosCallback(window, cursor_callback);

        // wheel event callbacks
        glfwSetScrollCallback(window, scroll_callback);

        // mouse button callbacks
        glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
        glfwSetMouseButtonCallback(window, mouse_button_callback);


        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(1);
        }

        // enable alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // resize components to current window size, get DPI
        glfwGetFramebufferSize(window, (int*) &buffer_w, (int*) &buffer_h);

        // init scene_mgr
        if (scene_mgr) {
            scene_mgr->init();
        }

        resize_callback(window, (int) buffer_w, (int) buffer_h);
    }

    void Viewer::start() {
        // start timer
        sys_last = system_clock::now();

        // run update loop
        while (!glfwWindowShouldClose(window)) {
            update();
        }
    }

    void Viewer::update() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // clear frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // do rendering
        scene_mgr->rendering();

        // swap buffers
        glfwSwapBuffers(window);

        // poll events
        glfwPollEvents();
    }

    void Viewer::err_callback(int error, const char* description) {
        out_err("GLFW Error: " << description);
    }

    void Viewer::resize_callback(GLFWwindow* window, int width, int height) {
        // get framebuffer size
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);

        // update buffer size
        buffer_w = w;
        buffer_h = h;
        glViewport(0, 0, w, h);

        scene_mgr->resize(buffer_w, buffer_h);
    }

    void Viewer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
#if DEBUG_EVENT
        const char* name = glfwGetKeyName(key, scancode);
        if (name)
        {
            printf("%08x to %i at %0.3f: Key 0x%04x Scancode 0x%04x (%s) (%s) (with%s) was %s\n",
                counter++, 1, glfwGetTime(), key, scancode,
                get_key_name(key),
                name,
                get_mods_name(mods),
                get_action_name(action));
        }
        else
        {
            printf("%08x to %i at %0.3f: Key 0x%04x Scancode 0x%04x (%s) (with%s) was %s\n",
                counter++, 1, glfwGetTime(), key, scancode,
                get_key_name(key),
                get_mods_name(mods),
                get_action_name(action));
        }
#endif
        scene_mgr->keyboard_event(key, action, mods);
    }

    void Viewer::char_callback(GLFWwindow* window, unsigned codepoint) {
#if DEBUG_EVENT
        printf("%08x to %i at %0.3f: Character 0x%08x (%s) input\n",
            counter++, 1, glfwGetTime(), codepoint,
            get_character_string(codepoint));
#endif
        scene_mgr->char_event(codepoint);
    }

    void Viewer::cursor_callback(GLFWwindow* window, double xpos, double ypos) {
#if DEBUG_EVENT
        printf("%08x to %i at %0.3f: Cursor position: %f %f\n",
            counter++, 1, glfwGetTime(), xpos, ypos);
#endif
        scene_mgr->cursor_event(xpos, ypos);
    }

    void Viewer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
#if DEBUG_EVENT

        printf("%08x to %i at %0.3f: Scroll: %0.3f %0.3f\n",
            counter++, 1, glfwGetTime(), xoffset, yoffset);
#endif
        scene_mgr->scroll_event(xoffset, yoffset);
    }

    void Viewer::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
#if DEBUG_EVENT
        printf("%08x to %i at %0.3f: Mouse button %i (%s) (with%s) was %s\n",
            counter++, 1, glfwGetTime(), button,
            get_button_name(button),
            get_mods_name(mods),
            get_action_name(action));
#endif


        scene_mgr->mouse_event(button, action, mods);
    }

}
