#ifndef SPIC_ENGINE_JSONFACADE_HPP
#define SPIC_ENGINE_JSONFACADE_HPP

#include "JsonFacade.hpp"
//#include <cereal/archives/binary.hpp>
//#include <../cereal/archives/binary.hpp>
#include <cereal/cereal.hpp>

#include <vector>
#include <string>

class JsonFacade
{
    public:
        template<class T>
        T Deserialize(const std::string& jsonString)
        {

        }

        template<class T>
        static std::string Serialize(const T& object) {
            std::stringstream os;
            {
                cereal::JSONOutputArchive archive_out(os);
                archive_out(CEREAL_NVP(data));
            }

            return os.str();
        }
};


#endif
