#include <Scene.hpp>

using namespace spic;

Scene::Scene() : _contents{}
{
}

void Scene::RenderScene()
{
    // This will not be used by the engine, because the RenderSubsystem handles the rendering of the scene.
}

std::vector<std::shared_ptr<GameObject>>& Scene::Contents()
{
    return _contents;
}
