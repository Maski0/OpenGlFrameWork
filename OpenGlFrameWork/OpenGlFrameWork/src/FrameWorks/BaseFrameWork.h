#pragma once
#include <functional>
#include <string>
#include <vector>
#include<iostream>

namespace BFW 
{
	class BaseFrameWork
	{
	public:
		BaseFrameWork() {}
		virtual ~BaseFrameWork() {}

		virtual void OnUpdate(float deltatime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class BaseMenu : public BaseFrameWork
	{
	public:
		BaseMenu(BaseFrameWork*& currentBFWPointer);
		~BaseMenu();

		void OnImGuiRender() override;

		template<typename T>
		void RegisterFw(const std::string& name)
		{
			std::cout << "Registering FrameWork " << name << std::endl;
			m_BaseFrameWorks.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		BaseFrameWork*& m_Currentframework;
		std::vector<std::pair<std::string, std::function<BaseFrameWork* ()>>> m_BaseFrameWorks;
	};

}