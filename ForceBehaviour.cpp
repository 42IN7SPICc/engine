#include "ForceBehaviour.h"
#include <iostream>
#include "Input.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"

void ForceBehaviour::OnStart() {
    std::cout << "On Start" << std::endl;
}

void ForceBehaviour::OnUpdate() {
    if(Input::GetKeyDown(Input::KeyCode::SPACE)) {
        if(!this->GameObject().expired()) {
            auto ball = this->GameObject().lock();
            auto rigidBody = ball->GetComponent<RigidBody>();
            rigidBody->AddForce({100,100});
        }
    }
}

void ForceBehaviour::OnTriggerEnter2D(const Collider &collider) {
    std::cout << "iets \n";
}

void ForceBehaviour::OnTriggerExit2D(const Collider &collider) {
    std::cout << "iets \n";
}

void ForceBehaviour::OnTriggerStay2D(const Collider &collider) {
    std::cout << "iets \n";
}
