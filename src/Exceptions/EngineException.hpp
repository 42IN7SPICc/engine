#ifndef SPIC_ENGINE_ENGINEEXCEPTION_HPP
#define SPIC_ENGINE_ENGINEEXCEPTION_HPP

#include <exception>
#include <string>

namespace engine
{
    /**
     * @brief An exception to throw when something errors in the engine.
     */
    class EngineException : public std::exception
    {
        private:
            std::string _message;

        public:
            /**
             *
             * @param message The message describing the error.
             * @param innerMessage The inner message for developers (empty to disable).
             */
            explicit EngineException(const std::string& message, const std::string& innerMessage = "");

            /**
             * @brief The what part of the exception.
             * @return The message of the exception.
             */
            const char* what() const throw()
            {
                return _message.c_str();
            }
    };
}

#endif //SPIC_ENGINE_ENGINEEXCEPTION_HPP
