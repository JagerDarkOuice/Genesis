#pragma once
#include "../config.h"

#include "../components/render2D_component.h"
#include "../components/transform2D_component.h"

class RenderSystem2D {
    public:
        RenderSystem2D(unsigned int shader, GLFWwindow* window);

        void update(
            std::unordered_map<unsigned int, Transform2DComponent> &transformComponents,
            std::unordered_map<unsigned int, Render2DComponent> &renderComponents);
    private:
    GLFWwindow* window;

};