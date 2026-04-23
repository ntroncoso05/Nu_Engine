#include "nupch.h"

#include "Nu/Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Nu {

	IndexBuffer* IndexBuffer::Create(unsigned int size)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:    return nullptr;
			case RendererAPIType::OpenGL:  return new OpenGLIndexBuffer(size);
		}
		return nullptr;

	}

}