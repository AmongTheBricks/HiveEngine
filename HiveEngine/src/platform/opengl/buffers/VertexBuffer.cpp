
#include "VertexBuffer.h"

#include <glad/glad.h>

namespace hive {

    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
        glGenBuffers(1, &bufferID_);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID_);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &bufferID_);
    }
    
    void OpenGLVertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, bufferID_);
    }

    void OpenGLVertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}
