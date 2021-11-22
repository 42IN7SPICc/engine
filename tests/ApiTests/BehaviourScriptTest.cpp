#include <gtest/gtest.h>
#include "BehaviourScript.hpp"

spic::BehaviourScript script {};

TEST(BehaviourScriptTest, TestStartedProperty) {
    script.Started(true);
    ASSERT_EQ(true, script.Started());
}