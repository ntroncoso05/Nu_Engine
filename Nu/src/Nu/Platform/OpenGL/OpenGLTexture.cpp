#include "nupch.h"
#include "OpenGLTexture.h"

#include "Nu/Renderer/RendererAPI.h"
#include "Nu/Renderer/Renderer.h"

#include <Glad/glad.h>

namespace Nu {

	static GLenum NuToOpenGLTextureFormat(TextureFormat format)
	{
		switch (format)
		{
		case Nu::TextureFormat::RGB:     return GL_RGB;
		case Nu::TextureFormat::RGBA:    return GL_RGBA;
		}
		return 0;
	}

	OpenGLTexture2D::OpenGLTexture2D(TextureFormat format, unsigned int width, unsigned int height)
		: m_Format(format), m_Width(width), m_Height(height)
	{
		auto self = this;
		NM_RENDER_1(self, {
			glGenTextures(1, &self->m_RendererID);
			glBindTexture(GL_TEXTURE_2D, self->m_RendererID);
			glTexImage2D(GL_TEXTURE_2D, 0, NuToOpenGLTextureFormat(self->m_Format), self->m_Width, self->m_Height, 0, NuToOpenGLTextureFormat(self->m_Format), GL_UNSIGNED_BYTE, nullptr);
			glBindTexture(GL_TEXTURE_2D, 0);
			});
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		auto self = this;
		NM_RENDER_1(self, {
			glDeleteTextures(1, &self->m_RendererID);
			});
	}

}