#include "Color.hpp"

using namespace spic;

const Color& Color::purple() {
    return Color::_purple;
}

const Color& Color::lime() {
    return Color::_lime;
}

const Color& Color::orange() {
    return Color::_orange;
}

const Color& Color::transparent() {
    return Color::_transparent;
}

void Color::SetColor(double red, double green, double blue) {
    SetColor(red, green, blue, a);
}

void Color::SetColor(double red, double green, double blue, double alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

double Color::R() const {
    return r;
}

double Color::G() const {
    return g;
}

double Color::B() const {
    return b;
}

double Color::A() const {
    return a;
}

bool Color::operator==(const Color& rhs) const
{
    return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
}

bool Color::operator!=(const Color& rhs) const
{
    return !(rhs == *this);
}