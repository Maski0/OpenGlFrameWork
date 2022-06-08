#pragma once


#include "BaseFrameWork.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


namespace BFW
{
	class Cube2D : public BaseFrameWork
	{
	public:
		Cube2D();
		~Cube2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
		VertexArray m_VAO;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		Shader m_Shader;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_Translation;
	};
}