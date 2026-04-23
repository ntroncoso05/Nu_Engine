#pragma once

#ifdef NM_PLATFORM_WINDOWS

	extern Nu::Application* Nu::CreateApplication();

	int main(int argc, char** argv)
	{
		Nu::InitializeCore();
			Nu::Application* app = Nu::CreateApplication();
			NM_CORE_ASSERT(app, "Client Application is null!");
			app->Run();
			delete app;
		Nu::ShutdownCore();
	}

#endif