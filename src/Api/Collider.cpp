#include <Collider.hpp>

bool spic::Collider::IsTrigger() const
{
    return _isTrigger;
}

void spic::Collider::IsTrigger(bool newIsTrigger)
{
    _isTrigger = newIsTrigger;
}