#include "Debug.hpp"
#include <iostream>
#include <chrono>

using namespace spic;

void Debug::DrawLine(const Point& start, const Point& end, const Color& color) {
    // TODO: Cannot be implemented if the render subsystem is not done
}

void Debug::Log(const std::string& message, const std::string& caller,  const std::string& file, const int& line) {
    std::cout << "INFO|" << caller << "|" << file << ":" << line << "|" << message << std::endl;
}

void Debug::LogError(const std::string& error, const std::string& caller,  const std::string& file, const int& line) {
    std::cerr << "ERROR|" << caller << "|" << file << ":" << line << "|" << error << std::endl;
}

void Debug::LogWarning(const std::string& warning, const std::string& caller,  const std::string& file, const int& line) {
    std::cerr << "WARNING|" << caller << "|" << file << ":" << line << "|" << warning << std::endl;
}
