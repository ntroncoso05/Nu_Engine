#pragma once

#include "Base.h"
#include "Window.h"
#include "Nu/Core/LayerStack.h"

#include "Nu/Core/Events/ApplicationEvent.h"

#include "Nu/ImGui/ImGuiLayer.h"

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

		virtual void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void RenderImGui();

		inline Window& GetWindow() { return *m_Window; }

		static inline Application& Get() { return *s_Instance; }
	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		static Application* s_Instance;
	};

	// Implemented by CLIENT
	Application* CreateApplication();
}