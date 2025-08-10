//
// Created by ADMIN on 7/23/2025.
//

#include <vector>

#include "Renderer.h"
#include "GL/glew.h"

struct VertexBufferElement {
    uint32_t type;
    uint32_t count;
    uint_least8_t normalized;

    static uint32_t GetSizeOfType(uint32_t type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    uint32_t m_Stride;

public:
    VertexBufferLayout(): m_Stride(0) {}

    ~VertexBufferLayout() = default;

    template<typename T>
    void Push(uint32_t count) {
        // static_assert(false);
    }

    template<>
    void Push<float>(uint32_t count) {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<uint32_t>(uint32_t count) {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<uint_least8_t>(uint32_t count) {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    inline uint32_t GetStride() const { return m_Stride; }
};
