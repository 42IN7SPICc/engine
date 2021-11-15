#include "BehaviourScript.hpp"

#include <sstream>
#include <stdexcept>

using namespace spic;

BehaviourScript::BehaviourScript() : _started{false}
{
}

void BehaviourScript::OnStart()
{
    std::stringstream ss{};
    ss << __FUNCTION__ << " not implemented";
    throw std::runtime_error(ss.str());
}

void BehaviourScript::OnUpdate()
{
    std::stringstream ss{};
    ss << __FUNCTION__ << " not implemented";
    throw std::runtime_error(ss.str());
}

void BehaviourScript::OnTriggerEnter2D(const Collider& collider)
{
    std::stringstream ss{};
    ss << __FUNCTION__ << " not implemented";
    throw std::runtime_error(ss.str());
}

void BehaviourScript::OnTriggerExit2D(const Collider& collider)
{
    std::stringstream ss{};
    ss << __FUNCTION__ << " not implemented";
    throw std::runtime_error(ss.str());
}

void BehaviourScript::OnTriggerStay2D(const Collider& collider)
{
    std::stringstream ss{};
    ss << __FUNCTION__ << " not implemented";
    throw std::runtime_error(ss.str());
}

bool BehaviourScript::Started() const
{
    return _started;
}

void BehaviourScript::Started(bool started)
{
    _started = started;
}