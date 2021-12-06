#include "EngineException.hpp"

engine::EngineException::EngineException(const std::string& message) : _message(message)
{
    auto innerMessage = InnerMessage();
    if (!innerMessage.empty())
    {
        _message += " (" + innerMessage + ")";
    }
}

const char* engine::EngineException::what() const
{
    return _message.c_str();
}
