#ifndef SPIC_ENGINE_ENGINEEXCEPTION_HPP
#define SPIC_ENGINE_ENGINEEXCEPTION_HPP

#include <exception>
#include <string>

namespace engine
{
    class EngineException : public std::exception
    {
        private:
            std::string _message;

        public:
            EngineException(const std::string& message);

            const char* what() const override;

            virtual std::string InnerMessage() = 0;
    };
}

#endif //SPIC_ENGINE_ENGINEEXCEPTION_HPP
