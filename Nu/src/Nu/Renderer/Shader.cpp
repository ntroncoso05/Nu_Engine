#include "nupch.h"
#include "Shader.h"

#include "Nu/Platform/OpenGL/OpenGLShader.h"

namespace Nu {

	std::vector<Shader*> Shader::s_AllShaders;

	Shader* Shader::Create(const std::string& filepath)
	{
		Shader* result = nullptr;

		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: result = new OpenGLShader(filepath);
		}
		s_AllShaders.push_back(result);
		return result;
	}

}