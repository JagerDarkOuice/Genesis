#pragma once
#include "../config.h"

#include "../components/render2D_component.h"
#include "../components/transform2D_component.h"

#include "../systems/render2D_system.h"

#include "../view/shader.h"

class App {
    public:
        App();
        ~App();

        void run();
        void set_up_opengl();
        void make_systems();

        unsigned int make_entity();
        unsigned int make_square_mesh(glm::vec2 size);

        // Components
        std::unordered_map<unsigned int, Transform2DComponent> transformComponents;
        std::unordered_map<unsigned int, Render2DComponent> renderComponents;

    private:
        void set_up_glfw();

        unsigned int entity_count = 0;

        GLFWwindow* window;

        std::vector<unsigned int> VAOs;
        std::vector<unsigned int> VBOs;

        unsigned int shader;

        RenderSystem2D* renderSystem2D;
};