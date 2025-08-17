﻿//
// Created by ADMIN on 8/9/2025.
//

#pragma once
#include "Test.h"
#include "vec3.hpp"

#include "../Renderer.h"
#include "../Texture.h"
#include "../VertexBufferLayout.h"

namespace test {
    class TestTexture2D : public Test {
    public:
        TestTexture2D();

        ~TestTexture2D() override = default;

        void OnUpdate(float deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj, m_View;
        glm::vec3 m_TranslationA, m_TranslationB;
    };
} // namespace test
