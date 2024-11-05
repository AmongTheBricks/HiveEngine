#pragma once

#include "core/rendering/buffers/IndexBuffer.h"

namespace hive {
    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);

        ~OpenGLIndexBuffer();

        void bind() const override;

        void unbind() const override;

        virtual uint32_t getCount() const { return count_; }

    private:
        uint32_t bufferID_;
        uint32_t count_;
    };
}