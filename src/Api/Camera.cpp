#include "Camera.hpp"

spic::Camera::Camera(const std::string& name, int layer, const Color& backgroundColor, double aspectWidth, double aspectHeight) : GameObject(name, "camera", layer),
                                                                                                                                                          backgroundColor(backgroundColor),
                                                                                                                                                          aspectHeight(aspectHeight),
                                                                                                                                                          aspectWidth(aspectWidth)
{

}

const spic::Color& spic::Camera::BackgroundColor() const
{
    return backgroundColor;
}

void spic::Camera::BackgroundColor(const spic::Color& newBackgroundColor)
{
    backgroundColor = newBackgroundColor;
}

double spic::Camera::AspectWidth() const
{
    return aspectWidth;
}

void spic::Camera::AspectWidth(double newAspectWidth)
{
    aspectWidth = newAspectWidth;
}

double spic::Camera::AspectHeight() const
{
    return aspectHeight;
}

void spic::Camera::AspectHeight(double newAspectHeight)
{
    aspectHeight = newAspectHeight;
}

void spic::Camera::Render() const
{
    // stub
}
