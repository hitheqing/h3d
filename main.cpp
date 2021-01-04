#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "demo_scene.h"
#include "viewer.h"
#include "console.h"

using namespace std;
using namespace Hyhy;

int main() {
    out_msg("~~~")
    out_wrn("~~~")
    out_err("~~~")
    Viewer* viewer = new Viewer();
    SceneManager* renderer = new DemoScene();
    viewer->set_renderer(renderer);
    viewer->init();
    viewer->start();

    return 0;
}




