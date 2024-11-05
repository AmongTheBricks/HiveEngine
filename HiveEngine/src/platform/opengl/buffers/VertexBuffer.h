#pragma once
#ifdef HIVE_BACKEND_OPENGL

#include "core/rendering/buffers/VertexBuffer.h"
#include "core/rendering/buffers/BufferUtils.h"

namespace hive {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float *vertices, uint32_t size);

        ~OpenGLVertexBuffer();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual const BufferLayout& getLayout() const override { return layout_; }
        virtual void setLayout(const BufferLayout& layout) override { layout_ = layout; }

    private:
        uint32_t bufferID_;
        BufferLayout layout_;
    };
}

#endif