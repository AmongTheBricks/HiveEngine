#ifdef HIVE_BACKEND_OPENGL

#include "core/rendering/pipeline/Renderer.h"
#include "core/rendering/backend/RenderAPI.h"

#include "VertexArray.h"
#include <platform/opengl/buffers/VertexArray.h>

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

#endif