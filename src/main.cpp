#include "config.h"
#include "triangle_mesh.h"
#include "material.h"
#include "linear_algebruh.h"

unsigned int make_shader(const string& vertex_filepath, const string& fragment_filepath);
unsigned int make_module(const string& filepath, unsigned int module_type);

int main() {

    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(800, 600, "Genesis", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glClearColor(0.25f,0.5f,0.75f,1.0f);

    int w,h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    TriangleMesh* triangle = new TriangleMesh();
    Material* material = new Material("../img/mical.jpg");
    Material* mask = new Material("../img/josiggle.jpeg");

    unsigned int shader = make_shader(
        "../src/shaders/vertex.txt",
        "../src/shaders/fragment.txt"
    );

    //set texture units
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "material"), 0);
    glUniform1i(glGetUniformLocation(shader, "mask"), 1);

    vec3 quad_position = {0.1f, -0.4f, 0.0f};
    unsigned int model_location = glGetUniformLocation(shader, "model");

    //enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        mat4 model = create_model_transform(quad_position, 10 * glfwGetTime());
        glUniformMatrix4fv(model_location, 1, GL_FALSE, model.entries);

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);

        material->use(0);
        mask->use(1);
        triangle->draw();

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    delete triangle;
    delete material;
    delete mask;
    glfwTerminate();
    return 0;
}

unsigned int make_shader(const string& vertex_filepath, const string& fragment_filepath) {
    vector<unsigned int> modules;
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();
    for (unsigned int shaderModule : modules) {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        cout << "ERROR::SHADER::LINKING_FAILURE\n" << errorLog << endl;
    }

    for (unsigned int shaderModule : modules) {
        glDeleteShader(shaderModule);
    }

    return shader;
}

unsigned int make_module(const string& filepath, unsigned int module_type) {
    ifstream file;
    stringstream bufferedLines;
    string line;
    // Read shader source code from file and buffer into a stringsrtream
    file.open(filepath);
    while (getline(file, line)) {
        bufferedLines << line << "\n";
    }
    string shaderSource = bufferedLines.str();
    
    //Convert from a C++ string to a C-style string
    const char* shaderSrc = shaderSource.c_str();
    bufferedLines.str(""); // Clear the buffer
    file.close();

    //Create shader module and compile
    unsigned int shaderModule = glCreateShader(module_type);
    // The NULL parameter represents the length but it should handle itself
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        cout << "ERROR::SHADER::COMPILATION_FAILURE\n" << errorLog << endl;
    }
    
    return shaderModule;
}