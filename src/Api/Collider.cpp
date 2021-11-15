#include <Collider.hpp>

spic::Collider::Collider() : _isTrigger{false}
{
}

bool spic::Collider::IsTrigger() const
{
    return _isTrigger;
}

void spic::Collider::IsTrigger(bool newIsTrigger)
{
    _isTrigger = newIsTrigger;
}