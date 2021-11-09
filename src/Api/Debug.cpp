#include "Debug.hpp"
#include <iostream>
#include <chrono>

using namespace spic;

void Debug::DrawLine(const Point& start, const Point& end, const Color& color) {
    // TODO: Cannot be implemented if the render subsystem is not done
}

void Debug::Log(const std::string& message) {
    std::cout << "INFO|" << message << std::endl;
}

void Debug::LogError(const std::string& error) {
    std::cerr << "ERROR|" << error << std::endl;
}

void Debug::LogWarning(const std::string& warning) {
    std::cerr << "WARNING|" << warning << std::endl;
}
