#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#include <GL/glew.h>

#if defined(_MSC_VER)

#define ASSERT(x) if (!(x)) __debugbreak();

#elif  defined(__GNUC__) || defined(__clang__)

#include <csignal>
#define ASSERT(x) if (!(x)) raise(SIGTRAP);

#else
#define ASSERT(x);
#endif

#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
