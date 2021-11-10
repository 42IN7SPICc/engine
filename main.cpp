#include "Api.hpp"

using namespace spic;

static std::shared_ptr<GameObject> create_boundary(const std::string& name, float width, float height, float x, float y, bool is_vertical, bool flip_y = false, bool flip_x = false) {
    auto boundary = std::make_shared<GameObject>(name + "Boundary", "default", 0);
    boundary->Transform().position.x = x;
    boundary->Transform().position.y = y;

    auto collider = std::make_shared<BoxCollider>(width, height);
    boundary->AddComponent<BoxCollider>(collider);
    collider->GameObject(boundary);

    auto rigidBody = std::make_shared<RigidBody>(0, 0, BodyType::staticBody);
    boundary->AddComponent<RigidBody>(rigidBody);
    rigidBody->GameObject(boundary);

    auto ballTexture = std::make_shared<Sprite>(is_vertical ? "resources/side.png" : "resources/top.png", flip_y, flip_x, 1, 1);
    boundary->AddComponent<Sprite>(ballTexture);
    ballTexture->GameObject(boundary);

    return boundary;
}

static std::shared_ptr<GameObject> create_dynamic_shape(const std::string& name, float radius, float ball_scale, float ball_size, float x, float y, bool is_box = false, const std::string& tag = "default", bool trigger = false) {
    auto ball = std::make_shared<GameObject>(name, tag, 0);
    ball->Transform().position.x = x;
    ball->Transform().position.y = y;
    ball->Transform().scale = ball_scale;

    auto sprite = std::make_shared<Sprite>(is_box ? "resources/ball_2.png" : "resources/ball.png", false, false, 1, 1);
    ball->AddComponent<Sprite>(sprite);
    sprite->GameObject(ball);

    if (is_box) {
        auto boxCollider = std::make_shared<BoxCollider>(ball_size, ball_size);
        boxCollider->IsTrigger(trigger);
        ball->AddComponent<BoxCollider>(boxCollider);
        boxCollider->GameObject(ball);
    } else {
        auto circleCollider = std::make_shared<CircleCollider>(ball_size / 2);
        circleCollider->IsTrigger(trigger);
        ball->AddComponent<CircleCollider>(circleCollider);
        circleCollider->GameObject(ball);
    }

    auto rigidBody = std::make_shared<RigidBody>(400, 1, BodyType::dynamicBody);
    ball->AddComponent<RigidBody>(rigidBody);
    rigidBody->GameObject(ball);

    return ball;
}

int main(int argc, char* args[]) {
    Engine& engine = Engine::Instance();
    EngineConfig engineConfig{WindowConfig{"Engine Test Window", 1366, 768, false}};
    engine.Init(engineConfig);

    auto scene = std::make_shared<Scene>();

    float screenWidth = engineConfig.window.width;
    float screenHeight = engineConfig.window.height;
    float boundaryWidth = 127;
    float boundaryHeight = 139;
    float ballScale = 0.1;
    float ballSize = 1100 * ballScale;

    //auto topBoundary = create_boundary("top", screenWidth, boundaryHeight, 0, 0, false);
    auto bottomBoundary = create_boundary("bottom", screenWidth, boundaryHeight, 0, screenHeight - boundaryHeight, false, true, false);
    auto leftBoundary = create_boundary("left", boundaryWidth, screenHeight, 0, 0, true);
    auto rightBoundary = create_boundary("right", boundaryWidth, screenHeight, screenWidth - boundaryWidth, 0, true, false, true);

    auto ball = create_dynamic_shape("ball0", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2, screenHeight / 2 - ballSize / 2, false, "ball0", false);
    auto ball1 = create_dynamic_shape("ball1", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 + 10, (screenHeight / 2 - ballSize / 2) - 300, false, "ball1", false);
    auto ball2 = create_dynamic_shape("ball2", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 - 10, (screenHeight / 2 - ballSize / 2) - 600, false, "ball2", false);
    auto ball3 = create_dynamic_shape("ball3", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 + 15, (screenHeight / 2 - ballSize / 2) - 900, false, "ball3", false);
    auto ball4 = create_dynamic_shape("ball4", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 - 15, (screenHeight / 2 - ballSize / 2) - 1200, false, "ball4", false);
    auto ball5 = create_dynamic_shape("ball5", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 + 5, (screenHeight / 2 - ballSize / 2) - 1500, false, "ball5", true);

    auto box = create_dynamic_shape("ball6", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 + 5, (screenHeight / 2 - ballSize / 2) - 1800, true, "ball6");

    //scene->contents.push_back(topBoundary);
    scene->Contents().push_back(bottomBoundary);
    scene->Contents().push_back(leftBoundary);
    scene->Contents().push_back(rightBoundary);
    scene->Contents().push_back(ball);
    scene->Contents().push_back(ball1);
    scene->Contents().push_back(ball2);
    scene->Contents().push_back(ball3);
    scene->Contents().push_back(ball4);
    scene->Contents().push_back(ball5);
    scene->Contents().push_back(box);

    engine.PushScene(scene);
    engine.Start();

    auto test = new spic::RigidBody(69.0, 69.0, spic::BodyType::staticBody);
    return 0;
}
