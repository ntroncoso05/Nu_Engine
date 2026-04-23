#pragma once

#include "Nu/Core/Input.h"

namespace Nu {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode);

		virtual bool IsMouseButtonPressedImpl(int button);
		virtual float GetMouseXImpl();
		virtual float GetMouseYImpl();
	};

}