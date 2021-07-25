#ifndef SPAIR_HPP
#define SPAIR_HPP

namespace scarlet
{
    template<typename T1, typename T2>    
    struct SPair
    {
    public:
        T1 first;
        T2 second;

    public:
        SPair() = default;
        SPair(T1 first, T2 second) : 
            first(first), second(second) {}
    };
}

#endif