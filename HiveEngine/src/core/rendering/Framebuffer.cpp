//
// Created by wstap on 9/30/2024.
//

#include "Framebuffer.h"

#include "Renderer.hpp"
#include "platform/opengl/OpenGLFrameBuffer.h"

namespace hive {

    static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec)
    {
        switch (Renderer::getApi())
        {
            case RenderAPI::API::OpenGL: return std::make_shared<OpenGLFrameBuffer>(spec);
            default:
                return nullptr;
        }
    }
}
