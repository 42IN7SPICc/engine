#include "Utils/RandomUtil.hpp"

using namespace spic;

RandomUtil RandomUtil::_instance{};
const std::string PossibleRandomCharacters{"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};

RandomUtil::RandomUtil() : _randomDevice(std::random_device{}), _engine{_randomDevice()}
{
}

int RandomUtil::Next(int min, int max)
{
    std::uniform_int_distribution<int> dist{min, max};
    return dist(_instance._engine);
}

double RandomUtil::NextDouble(double min, double max)
{
    std::uniform_real_distribution<double> dist{min, max};
    return dist(_instance._engine);
}

std::string RandomUtil::NextString(int maxLength)
{
    std::uniform_int_distribution<> dist(0, PossibleRandomCharacters.size() - 1);
    std::string result{};
    result.reserve(maxLength);
    for (int i = 0; i < maxLength; i++)
    {
        int random_index = dist(_instance._engine); //get index between 0 and possible_characters.size()-1
        result += PossibleRandomCharacters[random_index];
    }
    return result;
}

bool RandomUtil::NextBool()
{
    return Next(0,1) == 1;
}
