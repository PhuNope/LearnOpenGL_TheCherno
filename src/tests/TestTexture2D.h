//
// Created by ADMIN on 8/9/2025.
//

#pragma once
#include "Test.h"

namespace test {
    class TestTexture2D : public Test {
    public:
        ~TestTexture2D() override = default;

        void OnUpdate(float deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;
    };
}
