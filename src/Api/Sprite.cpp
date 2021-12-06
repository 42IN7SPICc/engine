#include <Sprite.hpp>

using namespace spic;

Sprite::Sprite(const std::string& sprite, bool flipX, bool flipY, int sortingLayer, int orderLayer) : sprite{sprite},
                                                                                                      flipX{flipX},
                                                                                                      flipY{flipY},
                                                                                                      sortingLayer(sortingLayer),
                                                                                                      orderInLayer(orderLayer),
                                                                                                      color{Color::transparent()}
{
}

Sprite::Sprite(const std::string& sprite, const spic::Color& color, bool flipX, bool flipY, int sortingLayer, int orderInLayer) : sprite(sprite),
                                                                                                                                  color{color},
                                                                                                                                  flipX{flipX},
                                                                                                                                  flipY{flipY},
                                                                                                                                  sortingLayer(sortingLayer),
                                                                                                                                  orderInLayer(orderInLayer)
{
}

void Sprite::Texture(const std::string& sprite)
{
    this->sprite = sprite;
}

const std::string& Sprite::Texture() const
{
    return sprite;
}

void Sprite::Color(const spic::Color& color)
{
    this->color = color;
}

const Color& Sprite::Color() const
{
    return color;
}

void Sprite::FlipX(bool flipX)
{
    this->flipX = flipX;
}

void Sprite::FlipY(bool flipY)
{
    this->flipY = flipY;
}

bool Sprite::FlipX() const
{
    return flipX;
}

bool Sprite::FlipY() const
{
    return flipY;
}

void Sprite::SortingLayer(int sortingLayer)
{
    this->sortingLayer = sortingLayer;
}

int Sprite::SortingLayer() const
{
    return sortingLayer;
}

void Sprite::OrderInLayer(int orderInLayer)
{
    this->orderInLayer = orderInLayer;
}

int Sprite::OrderInLayer() const
{
    return orderInLayer;
}
