#include "render2D_system.h"

RenderSystem2D::RenderSystem2D(unsigned int shader, GLFWwindow* window) {
    this->window = window;
}

void RenderSystem2D::update(
    std::unordered_map<unsigned int, Transform2DComponent> &transformComponents,
    std::unordered_map<unsigned int, Render2DComponent> &renderComponents) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (std::pair<unsigned int, Render2DComponent> entity : renderComponents) {
        glBindVertexArray(entity.second.mesh);
	    glDrawArrays(GL_TRIANGLES, 0, 36);
    }

	glfwSwapBuffers(window);
}