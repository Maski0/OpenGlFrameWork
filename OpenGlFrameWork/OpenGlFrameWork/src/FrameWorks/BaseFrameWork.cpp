#include "BaseFrameWork.h"
#include "imgui/imgui.h"

namespace BFW
{
	BaseMenu::BaseMenu(BaseFrameWork*& currentBFWPointer)
		:m_Currentframework(currentBFWPointer)
	{

	}
	BaseMenu::~BaseMenu()
	{
	}
	void BaseMenu::OnImGuiRender()
	{
		for (auto& BaseFrameWork : m_BaseFrameWorks)
		{
			if (ImGui::Button(BaseFrameWork.first.c_str()))
			{
				m_Currentframework = BaseFrameWork.second();
			}
		}
	}
}