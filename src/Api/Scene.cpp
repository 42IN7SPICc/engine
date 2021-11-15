#include <Scene.hpp>

using namespace spic;

Scene::Scene() : _contents{}
{
}

void Scene::RenderScene()
{
    // Stub method
}

std::vector<std::shared_ptr<GameObject>>& Scene::Contents()
{
    return _contents;
}
