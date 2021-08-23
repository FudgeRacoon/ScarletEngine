#ifndef PAIR_HPP
#define PAIR_HPP

namespace scarlet
{
    namespace container
    {
        template<typename T1, typename T2>    
        struct Pair
        {
        public:
            T1 first;
            T2 second;

        public:
            Pair() = default;
            Pair(T1 first, T2 second) : 
                first(first), second(second) {}
        };
    }
}

#endif