#ifndef SPIC_ENGINE_SDL2RUNTIMEERROR_HPP
#define SPIC_ENGINE_SDL2RUNTIMEERROR_HPP

#include <exception>
#include <string>

namespace engine
{
    class SDL2RuntimeError : public std::exception
    {
        private:
            std::string _message;

        public:
            explicit SDL2RuntimeError(const std::string& message);

            [[nodiscard]] const char* what() const override;
    };
}

#endif //SPIC_ENGINE_SDL2RUNTIMEERROR_HPP
