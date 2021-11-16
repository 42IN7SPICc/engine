#include "AnimatorSubsystem.hpp"

#include "Animator.hpp"
#include "GameObject.hpp"
#include "Time.hpp"

using namespace engine;
using namespace spic;

void AnimatorSubsystem::Update() {
    for (const std::shared_ptr<GameObject> &gameObject: GameObject::All()) {
        for (const std::shared_ptr<Animator> &animator: gameObject->GetComponents<Animator>()) {
            if (animator->Active() && animator->Playing) {
                animator->FrameTime += Time::DeltaTime();

                if (animator->FrameDuration <= 0) continue;

                if (animator->FrameTime > animator->FrameDuration) {
                    animator->ActivateFrame(animator->CurrentFrame);

                    animator->CurrentFrame++;
                    if (animator->CurrentFrame >= animator->Frames()) {
                        animator->CurrentFrame = 0;
                        animator->Playing = animator->Looping;
                    }
                    animator->FrameTime = 0;
                }
            }
        }
    }
}
