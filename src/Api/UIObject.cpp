#include "UIObject.hpp"

using namespace spic;

UIObject::UIObject(const std::string& name, const std::string& tag, int layer, double width, double height) : GameObject(name, tag, layer) {
}

double UIObject::Width() const {
    return width;
}

void UIObject::Width(double newWidth) {
    width = newWidth;
}

double UIObject::Height() const {
    return height;
}

void UIObject::Height(double newHeight) {
    height = newHeight;
}