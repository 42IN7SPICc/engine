#ifndef SPIC_ENGINE_ISUBSYSTEM_HPP
#define SPIC_ENGINE_ISUBSYSTEM_HPP

namespace engine {
    class ISubsystem {
    public:
        virtual void Update() = 0;
    };
}

#endif //SPIC_ENGINE_ISUBSYSTEM_HPP
