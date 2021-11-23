#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameObject.hpp"
#include "Scene.hpp"
#include "BehaviourScript.hpp"

auto ballObject = std::make_shared<spic::GameObject>("ball", "main", 0);
auto leftWall = std::make_shared<spic::GameObject>("leftWall", "main", 12);
auto rightWall = std::make_shared<spic::GameObject>("righWall", "main", 0);

TEST(GameObjectTest, TestActiveProperty)
{
    ballObject->Active(false);
    ASSERT_FALSE(ballObject->Active());
    ballObject->Active(true);
    ASSERT_TRUE(ballObject->Active());
}

TEST(GameObjectTest, CheckAddChildMethod)
{
    leftWall->AddChild(ballObject);
    ASSERT_EQ(ballObject->Name(), leftWall->Children()[0]->Name());
}

TEST(GameObjectTest, RemoveChildMethod)
{
    leftWall->AddChild(ballObject);
    leftWall->RemoveChild(ballObject);
    ASSERT_EQ(0, leftWall->Children().size());
}

TEST(GameObjectTest, CheckTagProperty)
{
    ASSERT_EQ("main", rightWall->Tag());
}

TEST(GameObjectTest, CheckLayerProperty)
{
    ASSERT_EQ(12, leftWall->Layer());
}

TEST(GameObjectTest, CheckTransformProperty)
{
    ballObject->Transform().scale = 0.2;
    ballObject->Transform().rotation = 90;
    ballObject->Transform().position.x = 12.5;
    ballObject->Transform().position.y = 50;
    ASSERT_EQ(0.2, ballObject->Transform().scale);
    ASSERT_EQ(90, ballObject->Transform().rotation);
    ASSERT_EQ(12.5, ballObject->Transform().position.x);
    ASSERT_EQ(50, ballObject->Transform().position.y);
}

TEST(GameObjectTest, CheckComponentMethods)
{
    auto component = std::make_shared<spic::BehaviourScript>();
    ballObject->AddComponent(component);
    ASSERT_EQ(ballObject->GetComponent<spic::BehaviourScript>(), component);
    ballObject->RemoveComponent(component);
    ASSERT_EQ(0, ballObject->GetComponents<spic::BehaviourScript>().size());
}

TEST(GameObjectTest, CheckParentMethods)
{
    ballObject->Parent(rightWall);
    ASSERT_EQ(ballObject->Parent().lock().get()->Name(), rightWall->Name());
}

TEST(GameObjectTest, CheckAbsoluteTransform)
{
    rightWall->Parent(leftWall);
    leftWall->AddChild(rightWall);

    rightWall->Transform().position.x = 20;
    rightWall->Transform().position.y = 20;

    leftWall->Transform().position.x = 19;
    leftWall->Transform().position.y = 21;

    auto absolute = rightWall->AbsoluteTransform();
    ASSERT_EQ(39, absolute.position.x);
    ASSERT_EQ(41, absolute.position.y);

    //TODO Expand to test scale and rotation
}