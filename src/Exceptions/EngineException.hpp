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
            explicit EngineException(const std::string& message, const std::string& innerMessage = "");

            const char* what() const throw()
            {
                return _message.c_str();
            }
    };
}

#endif //SPIC_ENGINE_ENGINEEXCEPTION_HPP
