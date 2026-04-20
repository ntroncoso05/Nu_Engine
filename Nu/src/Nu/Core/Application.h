#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Nu {

	class NU_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate() {}
	private:
		std::unique_ptr<Window> m_Window;
	};

	// Implemented by CLIENT
	Application* CreateApplication();
}