#ifndef SPIC_ENGINE_FORCEBEHAVIOUR_H
#define SPIC_ENGINE_FORCEBEHAVIOUR_H

#include "BehaviourScript.hpp"
#include "Collider.hpp"

using namespace spic;

class ForceBehaviour : public BehaviourScript {
public:
    void OnStart() override;

    void OnUpdate() override;

    void OnTriggerEnter2D(const Collider& collider) override;

    void OnTriggerExit2D(const Collider& collider) override;

    void OnTriggerStay2D(const Collider& collider) override;
};


#endif //SPIC_ENGINE_FORCEBEHAVIOUR_H
