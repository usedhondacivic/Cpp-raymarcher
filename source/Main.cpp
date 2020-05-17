#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <map>

#include "Shader.h"

std::map<int, bool> keys ={
    {GLFW_KEY_W, false},
    {GLFW_KEY_S, false},
    {GLFW_KEY_A, false},
    {GLFW_KEY_D, false},
    {GLFW_KEY_Q, false},
    {GLFW_KEY_E, false},
    {GLFW_KEY_UP, false},
    {GLFW_KEY_DOWN, false},
    {GLFW_KEY_LEFT, false},
    {GLFW_KEY_RIGHT, false}
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        if(keys.find(key) != keys.end()){
            keys.at(key) = true;
            std::cout << "Pressed keycode: " << key << std::endl;
        }
    }

    if(action == GLFW_RELEASE){
        if(keys.find(key) != keys.end()){
            keys.at(key) = false;
            std::cout << "Released keycode: " << key << std::endl;
        }
    }
}

int main(int argc, char* args[]){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Raymarcher", NULL, NULL); 
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" <<std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetKeyCallback(window, keyCallback);

    Shader myShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
    };   
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float position[] = {8.0, 5.0, 7.0};
    float cameraRotation[] = {0.0, 0.0, 0.0};
    float speed = 1.0 / 60.0;
    float rotationSpeed = 1.0 / 60.0;

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        float time = glfwGetTime();
        GLint m_viewport[4];
        glGetIntegerv(GL_VIEWPORT, m_viewport);
        GLint resolution[] = {m_viewport[2], m_viewport[3]};
        myShader.setFloat("iTime", time);
        myShader.set2f("iResolution", resolution[0], resolution[1]);
        myShader.set3f("position", position[0], position[1], position[2]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}