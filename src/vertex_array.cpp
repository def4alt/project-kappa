#include "vertex_array.h"
#include "vertex_buffer_layout.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &renderer_id_);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &renderer_id_);
}

void VertexArray::add_buffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    bind();
    vb.bind();

    const auto& elements = layout.get_elements();
    unsigned offset = 0;

    for (unsigned i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type,
                element.normalized, layout.get_stride(), reinterpret_cast<const void*>(offset));

        offset += element.count * VertexBufferElement::get_size_of_type(element.type);
    }
}

void VertexArray::bind() const {
    glBindVertexArray(renderer_id_);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
