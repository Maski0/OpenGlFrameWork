#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "FrameWorks/ClearColorFW.h"
#include "FrameWorks/Texture2D.h"
#include "FrameWorks/Cube2D.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "App", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsLight();

    BFW::BaseFrameWork* currentFw = nullptr;
    BFW::BaseMenu* mainMenu = new BFW::BaseMenu(currentFw);
    currentFw = mainMenu; 

    mainMenu->RegisterFw<BFW::ClearColorFW>("Clear Color");
    mainMenu->RegisterFw<BFW::Texture2D>(" 2D Texture");
    mainMenu->RegisterFw<BFW::Cube2D>("Cube 2D");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        /* Render here */
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();
        glm::vec2 pos(11, 12);
        //ImGui::SetNextWindowPos(pos);
        ImGui::Begin("Stats:");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        if (currentFw)
        {
            currentFw->OnUpdate(0.0f);
            currentFw->OnRender();
            ImGui::Begin("FrameWorks");
            if (currentFw != mainMenu && ImGui::Button("<-"))
            {
                delete currentFw;
                currentFw = mainMenu;
            }
            currentFw->OnImGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    if (currentFw != mainMenu)
    {
        delete mainMenu;
    }
    delete currentFw;

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}