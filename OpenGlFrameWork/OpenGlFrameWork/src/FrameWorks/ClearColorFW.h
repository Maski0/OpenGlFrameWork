#pragma once
#include "BaseFrameWork.h"


namespace BFW
{
	class ClearColorFW : public BaseFrameWork
	{
	public:
		ClearColorFW();
		~ClearColorFW();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ClearColor[4];

	};
}