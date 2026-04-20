#include "Nu.h"

class Sandbox : public Nu::Application
{
public:
	Sandbox()
	{
		NM_TRACE("Hello!");
	}
};

Nu::Application* Nu::CreateApplication()
{
	return new Sandbox();
}