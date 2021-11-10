#include "Api.hpp"
#include "ForceBehaviour.h"

using namespace spic;

static std::shared_ptr<GameObject> create_boundary(const std::string& name, float width, float height, float x, float y, bool is_vertical, bool flip_y = false, bool flip_x = false) {
    auto boundary = std::make_shared<GameObject>(name + "Boundary", "default", 0);
    boundary->Transform().position.x = x;
    boundary->Transform().position.y = y;

    auto collider = std::make_shared<BoxCollider>(width, height);
    boundary->AddComponent<BoxCollider>(collider);
    collider->GameObject(boundary);

    auto rigidBody = std::make_shared<RigidBody>(0,0, BodyType::staticBody);
    boundary->AddComponent<RigidBody>(rigidBody);
    rigidBody->GameObject(boundary);

    auto ballTexture = std::make_shared<Sprite>(is_vertical ? "resources/side.png"  : "resources/top.png", flip_y, flip_x, 1, 1);
    boundary->AddComponent<Sprite>(ballTexture);
    ballTexture->GameObject(boundary);

    return boundary;
}

int main(int argc, char* args[]) {
    Engine& engine = Engine::Instance();
    EngineConfig engineConfig{WindowConfig{"Engine Test Window", 1366, 768, false}};
    engine.Init(engineConfig);

    auto scene = std::make_shared<Scene>();
    engine.PushScene(scene);

    float screenWidth = 1366;
    float screenHeight = 768;
    //float boundaryWidth = 127;
    float boundaryHeight = 139;
    float ballScale = 0.1;
    float ballSize = 1100 * ballScale;

    auto bottomBoundary = create_boundary("bottom", screenWidth, boundaryHeight, 0, screenHeight - boundaryHeight, false, true, false);
    scene->Contents().push_back(bottomBoundary);

    auto ball = std::make_shared<GameObject>("ball", "default", 0);
    ball->Transform().position.x = screenWidth / 2;
    ball->Transform().position.y = screenHeight / 2;
    ball->Transform().scale = ballScale;

    auto script = std::make_shared<ForceBehaviour>();
    script->GameObject(ball);
    ball->AddComponent(script);

    auto sprite = std::make_shared<Sprite>("resources/ball.png", false, false, 1, 1);
    ball->AddComponent<Sprite>(sprite);
    sprite->GameObject(ball);

    auto circleCollider = std::make_shared<CircleCollider>(ballSize / 2);
    ball->AddComponent<CircleCollider>(circleCollider);
    circleCollider->GameObject(ball);

    auto rigidBody = std::make_shared<RigidBody>(500, 1, BodyType::dynamicBody);
    ball->AddComponent<RigidBody>(rigidBody);
    rigidBody->GameObject(ball);

    scene->Contents().push_back(ball);

    engine.Start();

    return 0;
}
