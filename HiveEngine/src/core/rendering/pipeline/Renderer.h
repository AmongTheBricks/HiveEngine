#pragma once
#ifdef HIVE_BACKEND_OPENGL

#include <hvpch.h>
#include "core/rendering/buffers/VertexArray.h"
#include "core/rendering/resources/Shader.h"
#include "core/rendering/backend/RenderCommand.h"
#include "core/rendering/cameras/OrthographicCamera.h"
#include <glm/glm.hpp>

namespace hive {

	class Renderer
	{
	public:

		static void init();

        static void beginScene(OrthographicCamera& camera, glm::vec4 backgroundColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        static void endScene();

        static void submitGeometryToDraw(const std::shared_ptr<VertexArray>& vertexArray);

        static void submitGeometryToDraw(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RenderAPI::API getApi() { return RenderAPI::getAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 viewProjectionMatrix;
        };

        static SceneData* sceneData_;
	}
}

#endif