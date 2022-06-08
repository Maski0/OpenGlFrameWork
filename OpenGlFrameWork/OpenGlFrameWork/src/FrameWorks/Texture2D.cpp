#include "Texture2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace BFW
{
    Texture2D::Texture2D()
        :m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0),
        m_Shader("res/shaders/Basic.shader"), m_VAO(), m_Texture("res/Textures/BabyYoda.png"),
        m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{

        float positions[] = {
       -50.0f, -50.0f, 0.0f, 0.0f, //0
        50.0f, -50.0f, 1.0f, 0.0f, //1
        50.0f,  50.0f, 1.0f, 1.0f, //2
       -50.0f,  50.0f, 0.0f, 1.0f  //3
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);


        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VAO.AddBuffer(*m_VertexBuffer, layout);

        m_IB = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader.Bind();
        m_Shader.SetUniform1i("u_Texture", 0);
	}
	Texture2D::~Texture2D()
	{

	}
	void Texture2D::OnUpdate(float deltaTime)
	{

	}
	void Texture2D::OnRender()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        Renderer renderer;
        m_Texture.Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader.Bind();
            m_Shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(m_VAO, *m_IB, m_Shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader.Bind();
            m_Shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(m_VAO, *m_IB, m_Shader);
        }
	}
	void Texture2D::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
	}
}