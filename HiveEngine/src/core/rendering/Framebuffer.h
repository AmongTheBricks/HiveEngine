//
// Created by wstap on 9/30/2024.
//

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <cstdint>

namespace hive {

    struct Attachment {};

    class Framebuffer
    {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}

#endif //FRAMEBUFFER_H
