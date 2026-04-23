#include "nupch.h"
#include "Shader.h"

#include "Nu/Platform/OpenGL/OpenGLShader.h"

namespace Nu {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return new OpenGLShader(filepath);
		}
		return nullptr;
	}

}