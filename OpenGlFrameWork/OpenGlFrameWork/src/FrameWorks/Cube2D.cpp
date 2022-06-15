#include "Cube2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace BFW
{
	Cube2D::Cube2D() :
		m_VAO(), m_Shader("res/shaders/Color.shader"), m_Translation(200, 200, 0), m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
		, m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_ClearColor{ 0.5f,0.3f,0.8f,1.0f }
	{

		float positions[] = {
		-50.5f, -50.5f,
		 50.5f, -50.5f,
		 50.5f,  50.5f,
		-50.5f,  50.5f,
		};
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		m_VAO.AddBuffer(*m_VertexBuffer, layout);

		m_IB = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader.Bind();

		m_Shader.SetUniform4f("u_Color", m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);

	}
	Cube2D::~Cube2D()
	{
	}
	void Cube2D::OnUpdate(float deltaTime)
	{
	}

	void Cube2D::OnRender()
	{
		glClearColor(0.88725f, 0.887246f, 0.887255f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer renderer;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader.Bind();
		m_Shader.SetUniform4f("u_Color", m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		m_Shader.SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(m_VAO, *m_IB, m_Shader);
		//std::cout << m_ClearColor[0] << " " << m_ClearColor[1] << " " << m_ClearColor[2] << std::endl;
	}

	void Cube2D::OnImGuiRender()
	{
		ImGui::ColorEdit4("Color of Cube", m_ClearColor);
		ImGui::SliderFloat3("Translation A", &m_Translation.x, 0.0f, 960.0f);
	}

}