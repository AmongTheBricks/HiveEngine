//
// Created by wstap on 9/17/2024.
//

#ifndef OPENGLFRAMEBUFFER_H
#define OPENGLFRAMEBUFFER_H

#include <glad/glad.h>

#include "core/rendering/Framebuffer.h"


namespace hive {

    enum class OpenGLAttachmentFormat
    {
        None = (uint32_t) 0,

        // Color attachments
        RGBA8,
        RED_INTEGER,

        // Depth attachment
        DEPTH24,
        // Stencil attachment
        STENCIL8,
        // Depth and stencil attachment
        DEPTH24STENCIL8,

    };

    struct OpenGLAttachmentSpecification
    {
        OpenGLAttachmentSpecification() = default;
        OpenGLAttachmentSpecification(OpenGLAttachmentFormat format, bool renderBuffer = false)
            : textureFormat_(format), renderBuffer_(renderBuffer) {}

        bool renderBuffer_ = false;
        OpenGLAttachmentFormat textureFormat_ = OpenGLAttachmentFormat::None;
    };

    struct FramebufferAttachmentSpecification
    {
        FramebufferAttachmentSpecification() = default;
        FramebufferAttachmentSpecification( std::initializer_list<OpenGLAttachmentSpecification> attachments)
            : attachments_(attachments) {}

        std::vector<OpenGLAttachmentSpecification> attachments_;
    };

    struct FramebufferSpecification
    {
        int width_ = 0, height_ = 0;
        FramebufferAttachmentSpecification attachments_;
        int samples_ = 1;
    };

    class OpenGLFrameBuffer : public Framebuffer {
    public:

        OpenGLFrameBuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFrameBuffer();

        void bind() override;
        void unbind() override;

        void resize(int width, int height);
        void create();
        void clearColorAttachment(uint32_t attachmentIndex, int value);

        void addAttachment(OpenGLAttachmentSpecification attachment, int index);
        void attachColorTexture(uint32_t id, GLenum internalFormat, GLenum format, int index) const;
        void attachTexture(uint32_t id, GLenum format, GLenum attachmentType) const;

    private:
        GLuint framebufferID_ = 0;

        std::vector<OpenGLAttachmentSpecification> colorAttachments_;
        OpenGLAttachmentSpecification depthAttachment_;
        OpenGLAttachmentSpecification stencilAttachment_;

        std::vector<uint32_t> colorAttachmentsID_;
        uint32_t depthAttachmentID_;
        uint32_t stencilAttachmentID_;

        FramebufferSpecification spec_;
    };

} // hive

#endif //OPENGLFRAMEBUFFER_H
