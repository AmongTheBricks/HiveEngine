#ifdef HIVE_BACKEND_OPENGL

#include "IndexBuffer.h"
#include "glad/glad.h"

namespace hive {
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
        :count_(count) {
        glGenBuffers(1, &bufferID_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &bufferID_);
    }

    void OpenGLIndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID_);
    }

    void OpenGLIndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

#endif