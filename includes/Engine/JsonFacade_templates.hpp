#include "JsonFacade.hpp"
#include <cereal/archives/json.hpp>
#include <sstream>

template<class T>
T spic::JsonFacade::Deserialize(const std::string& jsonString)
{
    std::stringstream is(jsonString);

    T object;
    {
        cereal::JSONInputArchive archive_in(is);
        archive_in(object);
        return object;
    }
}

template<class T>
std::string spic::JsonFacade::Serialize(const T& object)
{
    std::stringstream os;
    {
        cereal::JSONOutputArchive archive_out(os);
        archive_out(CEREAL_NVP(object));
    }
    return os.str();
}