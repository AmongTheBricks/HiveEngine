//
// Created by mathe on 14/08/2024.
//

#ifdef HIVE_BACKEND_OPENGL
#include "RenderAPI.h"
#include <glad/glad.h>

namespace hive {

    void OpenGLRenderAPI::init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderAPI::setClearColor(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //TODO: add flags for specifing what buffer to clear
    }

    void OpenGLRenderAPI::drawVertexArray(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
}

#endif