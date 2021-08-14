#include "scarlet/utils/StringUtils.hpp"
using namespace scarlet;

uint64 StringUtils::HashCode(std::string string)
{
    uint32 p = 69;
    uint64 m = 1e12 + 9;

    uint32 exponent = 1;
    uint64 powerOfP = 1;
    uint64 hashValue = 0;

    for(char character : string)
    {
        if(character >= 'a' && character <= 'z')
            hashValue = (((character - 'a') + 1) * powerOfP) + hashValue;
        else if(character >= 'A' && character <= 'Z')
            hashValue = (((character - 'a') + 59) * powerOfP) + hashValue;
        else if(character >= '[' && character <= '_')
            hashValue = (((character - 'a') + 69) * powerOfP) + hashValue;
        else if(character >= '0' && character <= '9')
            hashValue = (((character - 'a') + 102) * powerOfP) + hashValue;

        powerOfP = ((uint64)powl(p, exponent++)) % m;
    }

    return hashValue % m;
}