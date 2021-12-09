#include "DebugLines.hpp"

engine::DebugLines engine::DebugLines::_instance{};

std::vector<engine::DebugLine>& engine::DebugLines::Lines()
{
    return _instance._lines;
}

void engine::DebugLines::Clear()
{
    _instance._lines.clear();
}