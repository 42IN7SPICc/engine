#include "Debug.hpp"
#include "../Structs/DebugLines.hpp"
#include <iostream>

using namespace spic;

void Debug::DrawLine(const Point& start, const Point& end, const Color& color)
{
    engine::DebugLines::Lines().emplace_back(start, end, color);
}

void Debug::Log(const std::string& message, const std::string& caller, const std::string& file, int line)
{
    std::cout << "INFO | " << caller << " | " << file << ":" << line << " | " << message << "\n";
}

void Debug::LogError(const std::string& error, const std::string& caller, const std::string& file, int line)
{
    std::cerr << "ERROR | " << caller << " | " << file << ":" << line << " | " << error << std::endl;
}

void Debug::LogWarning(const std::string& warning, const std::string& caller, const std::string& file, int line)
{
    std::cerr << "WARNING | " << caller << " | " << file << ":" << line << " | " << warning << std::endl;
}
