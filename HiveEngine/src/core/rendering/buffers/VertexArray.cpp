

#include "VertexArray.h"
#include "core/rendering/pipeline/Renderer.h"
#include <platform/opengl/buffers/VertexArray.h>

#include "core/rendering/backend/RenderAPI.h"

namespace hive {

    VertexArray *VertexArray::create() {
        switch (Renderer::getApi()) {
            case RenderAPI::API::None:    Logger::log("RendererAPI::None is not supported", LogLevel::Warning); return nullptr;
            case RenderAPI::API::OpenGL:
                return new OpenGLVertexArray();
        }

        Logger::log("This API is not supported", LogLevel::Error);
        return nullptr;
    }

}
