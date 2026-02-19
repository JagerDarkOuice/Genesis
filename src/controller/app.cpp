#include "app.h"

App::App() {
    set_up_glfw();
}

App::~App() {
    glDeleteBuffers(VBOs.size(), VBOs.data());
    glDeleteVertexArrays(VAOs.size(), VAOs.data());
    glDeleteProgram(shader);
    glfwTerminate();

    delete renderSystem2D;
}

unsigned int App::make_entity() {
    return entity_count++;
}

unsigned int App::make_square_mesh(glm::vec2 size) {
    // length
    float l = size.y;
    // width
    float w= size.x;

    std::vector<float> vertices = {
        -l,  w,
        -l, -w,
         l, -w,

         l, -w,
         l,  w,
        -l,  w

    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), 
        vertices.data(), GL_STATIC_DRAW);
    //position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}

void App::run() {
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        renderSystem2D->update(transformComponents, renderComponents);
    }
}

void App::set_up_glfw() {
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	
	window = glfwCreateWindow(800, 600, "Genesis", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
	}

}

void App::set_up_opengl() {
    glClearColor(0.25f,0.5f,0.75f,1.0f);

    int w,h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    shader = make_shader(
        "../src/shaders/vertex.txt",
        "../src/shaders/fragment.txt"
    );

    //enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(shader);
}

void App::make_systems() {
    renderSystem2D = new RenderSystem2D(shader, window);
}