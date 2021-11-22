#include <gtest/gtest.h>
#include "Engine.hpp"
#include "EngineConfig.hpp"
#include "Scene.hpp"

spic::EngineConfig config {"test window", 45,25,false};
spic::Engine& engine = spic::Engine::Instance();

TEST(EngineTest, EngineConfigTest) {
    engine.Init(config);
    ASSERT_EQ("test window",engine.Config().window.title);
    ASSERT_EQ(45,engine.Config().window.width);
    ASSERT_EQ(25,engine.Config().window.height);
    ASSERT_EQ(false,engine.Config().window.fullscreen);
}

