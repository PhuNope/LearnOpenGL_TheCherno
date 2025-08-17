//
// Created by ADMIN on 8/9/2025.
//

#include "TestTexture2D.h"

#include "../vendor/imgui/imgui.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"

namespace test {
    TestTexture2D::TestTexture2D() :
        m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_TranslationA(200, 200, 0),
        m_TranslationB(400, 200, 0) {

        float positions[] = {
                -50.0f, -50.0f, 0.0f, 0.0f,
                50.0f, -50.0f, 1.0f, 0.0f,
                50.0f, 50.0f, 1.0f, 1.0f,
                -50.0f, 50.0f, 0.0f, 1.0f
        };
        uint32_t indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VBO, layout);
        m_IBO = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));

        m_Shader = std::make_unique<Shader>("res/Shaders/Basic.shader");
        m_Shader->Bind();
        m_Texture = std::make_unique<Texture>("res/textures/fire.png");
        m_Shader->SetUniform1i("u_Texture", 0);
    }

    void TestTexture2D::OnUpdate(float deltaTime) {}

    void TestTexture2D::OnRender() {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        m_Texture->Bind();

        //
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        }
        //
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        }
    }

    void TestTexture2D::OnImGuiRender() {
        ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
    }
} // namespace test
