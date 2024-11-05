//
// Created by mathe on 14/08/2024.
//

#pragma once
#ifdef HIVE_BACKEND_OPENGL

#include <core/rendering/buffers/VertexArray.h>
#include <glm/glm.hpp>

namespace hive
{
    class RenderAPI
    {
        public:
        virtual ~RenderAPI() = default;

        enum class API
            {
                None = 0, OpenGL = 1
            };

            virtual void setClearColor(glm::vec4) = 0;
            virtual void clear() = 0;
            virtual void drawVertexArray(const std::shared_ptr<VertexArray>& vertexArray) = 0;
            virtual void init() = 0;

            static API getAPI() { return api_; }
            static void setAPI(API api) { api_ = api; }

        private:
            static API api_;
    };
}

#endif