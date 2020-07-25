#ifndef PROJECT_KAPPA_ENGINE_VERTEX_BUFFER_LAYOUT_H
#define PROJECT_KAPPA_ENGINE_VERTEX_BUFFER_LAYOUT_H

#include <GL/glew.h>
#include <vector>
#include "debug.h"

namespace engine {
    struct VertexBufferElement {
        uint32_t type;
        uint32_t count;
        unsigned char normalized;

        static uint32_t get_size_of_type(uint32_t type) {
            switch (type) {
                case GL_FLOAT: return 4;
                case GL_UNSIGNED_INT: return 4;
                case GL_UNSIGNED_BYTE: return 1;
                default:
                    ASSERT(false)
            }
        }
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout()
                : stride_(0) {}

        template<typename T>
        void push(uint32_t count);

        inline uint32_t get_stride() const { return stride_; }

        inline std::vector<VertexBufferElement> get_elements() const { return elements_; }

    private:
        std::vector<VertexBufferElement> elements_;
        uint32_t stride_;
    };

    template<>
    inline void VertexBufferLayout::push<float>(uint32_t count) {
        elements_.push_back({GL_FLOAT, count, GL_FALSE});
        stride_ += VertexBufferElement::get_size_of_type(GL_FLOAT) * count;
    }

    template<>
    inline void VertexBufferLayout::push<uint32_t>(uint32_t count) {
        elements_.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        stride_ += VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT) * count;

    }

    template<>
    inline void VertexBufferLayout::push<unsigned char>(uint32_t count) {
        elements_.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        stride_ += VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE) * count;
    }
}


#endif //PROJECT_KAPPA_ENGINE_VERTEX_BUFFER_LAYOUT_H
