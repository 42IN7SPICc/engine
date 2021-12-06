#include "EngineException.hpp"

engine::EngineException::EngineException(const std::string& message, const std::string& innerMessage) : _message(message)
{
    if (!innerMessage.empty())
    {
        _message += " (" + innerMessage + ")";
    }
}

const char* engine::EngineException::what() const noexcept
{
    return _message.c_str();
}
