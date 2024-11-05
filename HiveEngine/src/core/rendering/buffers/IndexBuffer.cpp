
#include "IndexBuffer.h"
#include "platform/opengl/buffers/IndexBuffer.h"

#include <core/rendering/pipeline/Renderer.h>
#include "core/rendering/backend/RenderAPI.h"

namespace hive {
    IndexBuffer* IndexBuffer::create(uint32_t * indices, uint32_t count)
    {
        switch (Renderer::getApi())
        {
            case RenderAPI::API::None:   Logger::log("RendererAPI::None is not supported", LogLevel::Warning); return nullptr;
            case RenderAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, count);
        }

        Logger::log("This API is not supported", LogLevel::Error);
        return nullptr;
    }
}
