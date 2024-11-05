
#ifdef HIVE_PLATFORM_OPENGL
#include "Texture.h"

#include "core/rendering/backend/RenderAPI.h"
#include "core/rendering/pipeline/Renderer.h"
#include "platform/opengl/resources/Texture2D.h"


namespace hive {

    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::getApi())
        {
            case RenderAPI::API::None:    Logger::log("RendererAPI::None is not supported", LogLevel::Warning); return nullptr;
            case RenderAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
        }

        Logger::log("This API is not supported", LogLevel::Error);
        return nullptr;
    }

}
#endif