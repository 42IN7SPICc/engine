#include <gtest/gtest.h>
#include "Scene.hpp"
#include "GameObject.hpp"

spic::Scene scene{};

TEST(SceneTest, TestContentProperty)
{
    scene.Contents().push_back(std::make_shared<spic::GameObject>("test1", "test", 0));
    scene.Contents().push_back(std::make_shared<spic::GameObject>("test2", "test", 0));
    ASSERT_EQ(2, scene.Contents().size());
}

