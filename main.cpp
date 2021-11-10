#include <BoxCollider.hpp>
#include "Api.hpp"
#include <memory>

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

static std::shared_ptr<GameObject> create_dynamic_shape(const std::string& name, float radius, float ball_scale, float ball_size, float x, float y, bool is_box = false, float mass = 400, bool is_static = false) {
    auto ball = std::make_shared<GameObject>(name, "default", 0);
    ball->Transform().position.x = x;
    ball->Transform().position.y = y;
    ball->Transform().scale = ball_scale;

    auto sprite = std::make_shared<Sprite>(is_box ? "resources/ball_2.png" : "resources/ball.png", false, false, 1, 1);
    ball->AddComponent<Sprite>(sprite);
    sprite->GameObject(ball);

    if(is_box) {
        auto boxCollider = std::make_shared<BoxCollider>(ball_size, ball_size);
        ball->AddComponent<BoxCollider>(boxCollider);
        boxCollider->GameObject(ball);
    } else {
        auto circleCollider = std::make_shared<CircleCollider>(ball_size / 2);
        ball->AddComponent<CircleCollider>(circleCollider);
        circleCollider->GameObject(ball);
    }

    auto rigidBody = std::make_shared<RigidBody>(mass, 1, is_static ? BodyType::staticBody : BodyType::dynamicBody);
    ball->AddComponent<RigidBody>(rigidBody);
    rigidBody->GameObject(ball);

    return ball;
}


int main(int argc, char *args[]) {
    Engine &engine = Engine::Instance();

    EngineConfig engineConfig{WindowConfig{"Engine Test Window", 1366, 768, false}};

    engine.Init(engineConfig);

    auto scene = std::make_shared<Scene>();
    engine.PushScene(scene);

    float screenWidth = 1366;
    float screenHeight = 768;
    float boundaryWidth = 127;
    float boundaryHeight = 139;
    float ballScale = 0.2;
    float ballSize = 1100 * ballScale;

    //auto topBoundary = create_boundary("top", screenWidth, boundaryHeight, 0, 0, false);
    auto bottomBoundary = create_boundary("bottom", screenWidth, boundaryHeight, 0, screenHeight - boundaryHeight, false, true, false);
    auto leftBoundary = create_boundary("left", boundaryWidth, screenHeight, 0, 0, true);
    auto rightBoundary = create_boundary("right", boundaryWidth, screenHeight, screenWidth - boundaryWidth, 0, true, false, true);

    auto ball = create_dynamic_shape("ball0", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2,0);
    auto ball1 = create_dynamic_shape("ball1", ballSize / 2, 1, ballSize,  0,-0, false, 400, true);
//    auto ball2 = create_dynamic_shape("ball2", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 - 10,(screenHeight / 2 - ballSize / 2) - 600);
//    auto ball3 = create_dynamic_shape("ball3", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 + 15,(screenHeight / 2 - ballSize / 2) - 900);
//    auto ball4 = create_dynamic_shape("ball4", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 - 15,(screenHeight / 2 - ballSize / 2) - 1200);
//    auto ball5 = create_dynamic_shape("ball5", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 + 5,(screenHeight / 2 - ballSize / 2) - 1500);
//
    auto box = create_dynamic_shape("ball5", ballSize / 2, ballScale, ballSize, screenWidth / 2 - ballSize / 2 + 5,(screenHeight / 2 - ballSize / 2) - 1800, true, 999999);
    ball1->Parent(std::weak_ptr<GameObject>(ball));
    ball->AddChild(ball1);

    //scene->contents.push_back(topBoundary);
    scene->Contents().push_back(bottomBoundary);
    scene->Contents().push_back(leftBoundary);
    scene->Contents().push_back(rightBoundary);
    scene->Contents().push_back(ball);
    //scene->Contents().push_back(ball1);
//    scene->Contents().push_back(ball2);
//    scene->Contents().push_back(ball3);
//    scene->Contents().push_back(ball4);
//    scene->Contents().push_back(ball5);
//    scene->Contents().push_back(box);

    engine.Start();

    return 0;
}
