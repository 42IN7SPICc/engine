#include <Scene.hpp>

using namespace spic;

void Scene::RenderScene() {
    // Stub method
}

std::vector<std::shared_ptr<GameObject>> &Scene::Contents() {
    return _contents;
}
