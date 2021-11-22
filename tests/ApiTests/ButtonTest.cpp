#include <gtest/gtest.h>
#include "Button.hpp"

spic::Button button {"test_btn", "test", 1, 0,0};

TEST(ButtonTest, TestInteractableProperty) {
    button.Interactable(false);
    ASSERT_FALSE(button.Interactable());
}

TEST(ButtonTest, TestOnClickMethod) {
    int buttonTestVar = 1;
    button.OnClick([&buttonTestVar]() {
        buttonTestVar++;
    });
    button.Click();
    ASSERT_EQ(2, buttonTestVar);
}