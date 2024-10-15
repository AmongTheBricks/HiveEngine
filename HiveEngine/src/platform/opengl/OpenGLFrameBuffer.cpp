//
// Created by wstap on 9/30/2024.
//

#include "OpenGLFrameBuffer.h"

#include <cassert>

#include "OpenGlTexture2D.h"

namespace hive {


    static GLenum toGLFormat(OpenGLAttachmentFormat format)
    {
        switch(format) {
            case OpenGLAttachmentFormat::RGBA8:                                 return GL_RGBA8;
            case OpenGLAttachmentFormat::RED_INTEGER:                           return GL_RED_INTEGER;
            default: Logger::log("Unsupported Color Attachment Format", LogLevel::Error);    return 0;
        }
    }

    OpenGLFrameBuffer::OpenGLFrameBuffer(const FramebufferSpecification &spec)
        : spec_(spec)
    {
        for(auto attachment : spec.attachments_.attachments_) {
            switch(attachment.textureFormat_) {
                case OpenGLAttachmentFormat::RGBA8:
                case OpenGLAttachmentFormat::RED_INTEGER:
                    colorAttachments_.emplace_back(attachment);
                    break;
                case OpenGLAttachmentFormat::DEPTH24STENCIL8:
                    depthAttachment_ = attachment;
                    stencilAttachment_ = attachment;
                    break;
                case OpenGLAttachmentFormat::DEPTH24:
                    depthAttachment_ = attachment;
                    break;
                case OpenGLAttachmentFormat::STENCIL8:
                    stencilAttachment_ = attachment;
                    break;
                default:
                    Logger::log("Unhandled texture format, ignoring the attachment...", LogLevel::Error);
            }
        }

        create();
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &framebufferID_);
        glDeleteTextures(colorAttachments_.size(), colorAttachmentsID_.data());
        glDeleteTextures(1, &depthAttachmentID_);
    }

    void OpenGLFrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID_);
        glViewport(0, 0, spec_.width_, spec_.height_);
    }

    void OpenGLFrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }



    static GLenum textureTarget(bool multisampled)
    {
        return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
    }

    static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
    {
        glCreateTextures(textureTarget(multisampled), count, outID);
    }

    void OpenGLFrameBuffer::resize(int width, int height)
    {
        spec_.width_ = width;
        spec_.height_ = height;
        create();
    }

    void OpenGLFrameBuffer::create()
    {
        if (framebufferID_)
        {
            glDeleteFramebuffers(1, &framebufferID_);
            glDeleteTextures(static_cast<int>(colorAttachmentsID_.size()), colorAttachmentsID_.data());
            glDeleteTextures(1, &depthAttachmentID_);

            colorAttachmentsID_.clear();
            depthAttachmentID_ = 0;
        }

        glCreateFramebuffers(1, &framebufferID_);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID_);

        bool multisample = spec_.samples_ > 1;

        if (colorAttachments_.size()) {
            colorAttachmentsID_.resize(colorAttachments_.size());
            CreateTextures(multisample, colorAttachmentsID_.data(), colorAttachmentsID_.size());

            for(int i = 0; i < colorAttachmentsID_.size(); i++) {
                glBindTexture(textureTarget(multisample), colorAttachmentsID_[i]);
                addAttachment(colorAttachments_[i], i);
            }
        }

        // For a depth texture attachment
        switch(depthAttachment_.textureFormat_) {
            case OpenGLAttachmentFormat::DEPTH24:
                CreateTextures(multisample, &depthAttachmentID_, 1);
                glBindTexture(textureTarget(multisample), depthAttachmentID_);
                addAttachment(depthAttachment_, 0);
                break;
            case OpenGLAttachmentFormat::DEPTH24STENCIL8:
                CreateTextures(multisample, &depthAttachmentID_, 1);
                glBindTexture(textureTarget(multisample), depthAttachmentID_);
                addAttachment(depthAttachment_, 0);
                break;
            default:
                Logger::log("Texture format is not defined...", LogLevel::Error);
        }

        // For a separate stencil texture attachment
        if(stencilAttachment_.textureFormat_ == OpenGLAttachmentFormat::STENCIL8) {
            CreateTextures(multisample, &stencilAttachmentID_, 1);
            glBindTexture(textureTarget(multisample), stencilAttachmentID_);

            addAttachment(stencilAttachment_, 0);
        }

    }

    void OpenGLFrameBuffer::clearColorAttachment(uint32_t attachmentIndex, int value)
    {
        auto& colorAttachment = colorAttachments_[attachmentIndex];

        glClearTexImage(colorAttachmentsID_[attachmentIndex], 0,
            toGLFormat(colorAttachment.textureFormat_), GL_INT, &value);

    }


    void OpenGLFrameBuffer::addAttachment(OpenGLAttachmentSpecification attachment, int index)
    {
        bind();
        switch(attachment.textureFormat_) {
            case OpenGLAttachmentFormat::None:
                break;
            case OpenGLAttachmentFormat::RGBA8:
                attachColorTexture(colorAttachmentsID_[index], GL_RGBA8, GL_RGBA, index);
                break;
            case OpenGLAttachmentFormat::RED_INTEGER:
                attachColorTexture(colorAttachmentsID_[index], GL_R32I, GL_RED_INTEGER, index);
                break;
            case OpenGLAttachmentFormat::DEPTH24STENCIL8:
                attachTexture(depthAttachmentID_, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
                break;
            case OpenGLAttachmentFormat::DEPTH24:
                attachTexture(depthAttachmentID_, GL_DEPTH_COMPONENT24, GL_DEPTH_ATTACHMENT);
                break;
            case OpenGLAttachmentFormat::STENCIL8:
                attachTexture(depthAttachmentID_, GL_STENCIL_INDEX8, GL_STENCIL_ATTACHMENT);
                break;
        }

        unbind();
    }

    void OpenGLFrameBuffer::attachColorTexture(uint32_t id, GLenum internalFormat, GLenum format, int index) const
    {
        const bool multisampled = spec_.samples_ > 1;
        if (multisampled)
        {
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, spec_.samples_, internalFormat,
                spec_.width_, spec_.height_, GL_FALSE);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, spec_.width_, spec_.height_, 0, format, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, textureTarget(multisampled), id, 0);
    }

    void OpenGLFrameBuffer::attachTexture(uint32_t id, GLenum internalFormat, GLenum attachmentType) const
    {
        bool multisampled = spec_.samples_ > 1;
        if (multisampled)
        {
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, spec_.samples_, internalFormat,
                spec_.width_, spec_.height_, GL_FALSE);
        }
        else
        {
            glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, spec_.width_, spec_.height_);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, textureTarget(multisampled), id, 0);
    }
} // namespace hive