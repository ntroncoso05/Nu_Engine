#pragma once

#ifdef NM_PLATFORM_WINDOWS

extern Nu::Application* Nu::CreateApplication();

int main(int argc, char** argv)
{
	Nu::Application* app = Nu::CreateApplication();
	app->Run();
	delete app;
}
#else
#error Nu only supports Windows
#endif
