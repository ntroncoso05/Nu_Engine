#pragma once

#include "Nu/Core/Core.h"

namespace Nu {

	class NU_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:

	};

	// Implemented by CLIENT
	Application* CreateApplication();
}