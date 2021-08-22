#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdlib.h>

#include "scarlet/debug/Assert.hpp"

namespace scarlet
{
    namespace container
    {
        template <typename T>
        class Vector
        {
        private:
            T* data;
            size_t size;
            size_t capacity;

        public:
            Vector()
            {
                this->data = nullptr;
                this->size = 0;
                this->capacity = 0;
            }                
            Vector(size_t intialCapacity)
            {
                this->data = (T*)malloc(intialCapacity * sizeof(T));
                this->size = 0;
                this->capacity = intialCapacity;
            }
            Vector(int size, T& intialData)
            {
                this->data = (T*)malloc(size * sizeof(T));
                this->size = size;
                this->capacity = size;

                for(int i = 0; i < this->size; i++)
                    *(this->data + i) = intialData;
            }
            Vector(int size, T&& intialData)
            {
                 this->data = (T*)malloc(size * sizeof(T));
                this->size = size;
                this->capacity = size;

                for(int i = 0; i < this->size; i++)
                    *(this->data + i) = intialData;
            }
            Vector(const Vector<T>& other)
            {
                this->data = (T*)malloc(other.capacity * sizeof(T));
                this->size = other.size;
                this->capacity = other.capacity;

                for(int i = 0; i < size; i++)
                    *(this->data + i) = *(other.data + i);
            }
            ~Vector()
            {
                delete[] this->data;
            }   

        public:
            T& operator [](int index)
            {
                SCARLET_CORE_ASSERT(index < capacity, "Index out of bounds.");
                return *(this->data + index);
            }
            Vector<T>& operator =(const Vector<T>& other)
            {
                this->data = (T*)malloc(other.capacity * sizeof(T));
                this->size = other.size;
                this->capacity = other.capacity;

                for(int i = 0; i < size; i++)
                    *(this->data + i) = *(other.data + i);

                return *this;
            }

        public:
            size_t GetSize()
            {
                return this->size;
            }
            size_t GetCapacity()
            {
                return this->capacity;
            }

        public:
            void PushBack(T& data)
            {
                if(!this->capacity)
                    this->Resize(2);

                if(this->size >= this->capacity)
                    this->Resize(this->capacity * 2);

                *(this->data + this->size) = data;
                this->size++;
            }
            void PushBack(T&& data)
            {
                if(!this->capacity)
                    this->Resize(2);

                if(this->size >= this->capacity)
                    this->Resize(this->capacity * 2);

                *(this->data + this->size) = data;
                this->size++;
            }
            void PopBack()
            {
                if(this->size > 0)
                {
                    this->size--;
                    this->data[this->size].~T();
                }
            }

        public:
            void Resize(size_t newCapacity)
            {
                T* newBlock = (T*)malloc(newCapacity * sizeof(T));
                this->capacity = newCapacity;

                if(newCapacity < this->size)
                {
                    for(int i = newCapacity; i < this->size; i++)
                        this->data[i].~T();
                    
                    this->size = newCapacity;
                }

                for(int i = 0; i < this->size; i++)
                    *(newBlock + i) = *(this->data + i);

                delete[] this->data;
                this->data = newBlock;
            }
            void Clear()
            {
                for(int i = 0; i < this->size; i++)
                    this->data[i].~T();

                this->size = 0;
            }
        };
    }
}

#endif