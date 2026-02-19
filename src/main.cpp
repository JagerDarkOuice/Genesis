#include "config.h"
#include "controller/app.h"

int main() {
    App* app = new App();

    unsigned int squareEntity = app->make_entity();

    Render2DComponent render;
    render.mesh = app->make_square_mesh({0.25f,0.25f});
    app->renderComponents[squareEntity] = render;

    app->set_up_opengl();
    app->make_systems();

    app->run();

    delete app;
    return 0;
}
