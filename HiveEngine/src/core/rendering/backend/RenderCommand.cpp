//
// Created by mathe on 12/08/2024.
//

#ifdef HIVE_BACKEND_OPENGL
#include "RenderCommand.h"
#include "platform/opengl/RenderAPI.h"


namespace hive
{
    RenderAPI* getRenderAPI()
    {
        switch(RenderAPI::getAPI())
        {
            case RenderAPI::API::OpenGL:
                return new OpenGLRenderAPI();
            default:
                return nullptr;
        }
    }

    RenderAPI* RenderCommand::renderAPI_ = getRenderAPI();
}
#endif