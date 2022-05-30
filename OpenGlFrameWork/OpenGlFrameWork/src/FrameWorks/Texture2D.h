#pragma once
#include "BaseFrameWork.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>


namespace BFW
{
	class Texture2D : public BaseFrameWork
	{
	public:
		Texture2D();
		~Texture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:

		VertexArray m_VAO;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		Shader m_Shader;
		Texture m_Texture;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;
	};
}