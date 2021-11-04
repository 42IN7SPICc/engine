#include "Engine.hpp"

using namespace spic;

void Engine::Init(const EngineConfig& config) {
    _config = config;
}

EngineConfig& Engine::Config() {
    return _config;
}