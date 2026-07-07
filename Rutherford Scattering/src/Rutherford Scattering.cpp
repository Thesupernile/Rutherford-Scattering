#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

// Include Rutherford Simulation
#include "Simulation.h"
#include "Particle.h"

// Include glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Include ImGUI
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void)
{
    const float WINDOW_SCALE_FACTOR = 1;
    float cameraScaleFactor = 1;

    const float WINDOW_WIDTH = 1280;
    const float WINDOW_HEIGHT = 720;

    GLFWwindow* window;

    // Initialize glfw 
    if (!glfwInit())
        return -1;

    // Enable Anti Aliasing (via MSAA)
    glfwWindowHint(GLFW_SAMPLES, 8);
    // Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rutherford Scattering Simulator", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the openGL context
    glfwMakeContextCurrent(window);
    glEnable(GL_MULTISAMPLE);
    glfwSwapInterval(1);

    // Include the openGL functions using GLEW
    if (glewInit() != GLEW_OK) {
        return -1;
    }
    {
        glm::vec3 cameraPos = glm::vec3(-350, -350, 0);

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Create projection matrix
        // Put this in a separate class...
        glm::mat4 proj = glm::ortho(0.0f, WINDOW_WIDTH / WINDOW_SCALE_FACTOR, 0.0f, WINDOW_HEIGHT / WINDOW_SCALE_FACTOR, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), -cameraPos);

        // Setup ImGUI
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        io.Fonts->AddFontDefault();
        io.Fonts->Build();

        Renderer renderer;

        RutherfordScattering::Simulation sim = RutherfordScattering::Simulation();

        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            // Render here 
            renderer.Clear();

            // New ImGUI frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            view = glm::translate(glm::mat4(1.0f), -cameraPos);
            view = view * glm::scale(glm::mat4(1.0f), glm::vec3(cameraScaleFactor));
            glm::mat4 VP = proj * view;

            sim.DrawElements(VP, renderer);

            // ImGui window
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Control Pannel");

            ImGui::SliderFloat2("Camera Position", &cameraPos.x, -WINDOW_WIDTH, WINDOW_WIDTH);
            ImGui::SliderFloat("Zoom Level", &cameraScaleFactor, 1.0f/10.0f, 100);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();


            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
