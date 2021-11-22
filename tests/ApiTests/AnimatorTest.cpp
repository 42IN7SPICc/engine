#include <gtest/gtest.h>
#include "Animator.hpp"
#include <memory>
#include <vector>
#include "Sprite.hpp"

std::vector<std::shared_ptr<spic::Sprite>> sprites {
    std::make_shared<spic::Sprite>("https://media.istockphoto.com/photos/profile-of-a-toucan-picture-id139677202", false, false, 1, 1),
    std::make_shared<spic::Sprite>("https://media.istockphoto.com/photos/duck-picture-id139667500", false, false, 1, 1),
    std::make_shared<spic::Sprite>("https://media.istockphoto.com/photos/loon-on-sharbot-lake-picture-id139713643", false, false, 1, 1),
};
spic::Animator animator {3, sprites};

TEST(AnimatorTest, TestFramesMethod) {
    ASSERT_EQ(3, animator.Frames());
}

TEST(AnimatorTest, TestFPSProperty) {
    animator.FPS(2);
    ASSERT_EQ(2, animator.FPS());
}

TEST(AnimatorTest, PlayMethodWithLoop) {
    animator.Play(true);
    ASSERT_TRUE(animator.Playing);
    ASSERT_TRUE(animator.Looping);
}

TEST(AnimatorTest, PlayMethodWithoutLoop) {
    animator.Play(false);
    ASSERT_TRUE(animator.Playing);
    ASSERT_FALSE(animator.Looping);
}

TEST(AnimatorTest, StopMethod) {
    animator.Play(false);
    animator.Stop();
    ASSERT_FALSE(animator.Playing);
}