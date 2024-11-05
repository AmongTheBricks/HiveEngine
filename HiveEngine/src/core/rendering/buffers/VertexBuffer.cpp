
#include "VertexBuffer.h"
#include <core/rendering/pipeline/Renderer.h>

#include "core/rendering/backend/RenderAPI.h"
#include "platform/opengl/buffers/VertexBuffer.h"

namespace hive {
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getApi())
		{
			case RenderAPI::API::None:   Logger::log("RendererAPI::None is not supported", LogLevel::Warning); return nullptr;
            case RenderAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

        Logger::log("This API is not supported", LogLevel::Error);
		return nullptr;
	}
}
