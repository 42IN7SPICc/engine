#include "Text.hpp"

using namespace spic;

Text::Text(const std::string& name, const std::string& tag, int layer, double width, double height) : Text(name, tag, layer, width, height, "", "resources/fonts/arial.ttf", 18, Alignment::left, Color::black())
{
}

Text::Text(const std::string& name, const std::string& tag, int layer, double width, double height, const std::string& text, const std::string& font, int size, Alignment alignment, const Color& color) : UIObject(name, tag, layer, width, height),
                                                                                                                                                                                                           text{text},
                                                                                                                                                                                                           font{font},
                                                                                                                                                                                                           size{size},
                                                                                                                                                                                                           alignment(alignment),
                                                                                                                                                                                                           color{color}
{
}

const std::string& Text::Content() const
{
    return text;
}

void Text::Content(const std::string& text)
{
    this->text = text;
}

const std::string& Text::Font() const
{
    return font;
}

void Text::Font(const std::string& font)
{
    this->font = font;
}

int Text::Size() const
{
    return size;
}

void Text::Size(int size)
{
    this->size = size;
}

Alignment Text::TextAlignment() const
{
    return alignment;
}

void Text::TextAlignment(Alignment alignment)
{
    this->alignment = alignment;
}

const Color& Text::TextColor() const
{
    return color;
}

void Text::TextColor(const Color& color)
{
    this->color = color;
}
