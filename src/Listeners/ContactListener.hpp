#ifndef SPIC_ENGINE_CONTACTLISTENER_HPP
#define SPIC_ENGINE_CONTACTLISTENER_HPP

#include <box2d/box2d.h>
#include <Component.hpp>

class ContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact *contact) override;

    void EndContact(b2Contact *contact) override;
private:
    static bool GetEntities(b2Contact *contact, spic::Component *&entityA, spic::Component *&entityB) ;
};


#endif //SPIC_ENGINE_CONTACTLISTENER_HPP
