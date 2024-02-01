#pragma once

namespace kron {

    template <typename T>
    class UniquePointer //simple pointer storage, doesn't work for new[]/delete[]
    {
    public:
        UniquePointer() {};


        ~UniquePointer()
        {
            delete _d;
        }

        UniquePointer(T* pointerAddress) : _d{ pointerAddress }
        {}

        UniquePointer(UniquePointer& other) = delete;
        UniquePointer& operator=(UniquePointer& other) = delete;

        UniquePointer& operator=(UniquePointer&& other) noexcept //empties content
        {
            if (other._d != _d)
            {
                delete _d;
                if (other._d)
                {
                    _d = other._d;
                    other._d = nullptr;
                }
                else
                {
                    _d = nullptr;
                }
            }
            return *this;
        }

        UniquePointer(UniquePointer&& other) noexcept
        {
            if (other._d)
            {
                _d = other._d;
                other._d = nullptr;
            }
        }

        T& operator*() //throws if not present
        {
            return *_d;
        }

        operator bool() const
        {
            return _d != nullptr;
        }

    private:

        T* _d = nullptr;
    };

    template <typename T>
    class SharedPointer //simple pointer storage, doesn't work for new[]/delete[]
    {
    public:
        SharedPointer() {};

        ~SharedPointer()
        {
            decrement();
        }

        SharedPointer(T* pointerAddress) : _d{ pointerAddress }
        {
            (*_counter)++;
        }

        SharedPointer(SharedPointer& other)
        {
            if (other._d != nullptr)
            {
                _d = other._d;
                _counter = other._counter;
                (*_counter)++;
            }
        }

        SharedPointer& operator=(SharedPointer& other)
        {
            if (_d != nullptr && _d != other._d)
            {
                decrement();
                _d = other._d;
                _counter = other._counter;
                (*_counter)++;
            }

            return *this;
        }

        SharedPointer& operator=(SharedPointer&& other) noexcept
        {

            if (_d != nullptr && _d != other._d)
            {
                decrement();
            }

            _d = other._d;
            _counter = other._counter;

            other.decrement();

            return *this;
        }

        SharedPointer(SharedPointer&& other) noexcept
        {
            if (other._d)
            {
                _d = other._d;
                other._d = nullptr;
            }
        }

        T& operator*() //throws if not present
        {
            return *_d;
        }

        operator bool() const
        {
            return _d != nullptr;
        }

        int counter()
        {
            return *_counter;
        }

    private:

        void decrement()
        {
            (*_counter)--;
            if (*_counter == 0)
            {
                delete _d;
                _d = nullptr;
            }
        }

        T* _d = nullptr;
        int* _counter = new int(0);
    };


    template <typename T>
    class EncapsulatedPointer //simple pointer storage, doesn't work for new[]/delete[]
    {
    public:
        EncapsulatedPointer() {};

        template <typename ... Param>
        EncapsulatedPointer(Param&&... params)
        {
            _d = new T(std::forward<Param>(params)...);
        }

        ~EncapsulatedPointer()
        {
            delete _d; 
        }

        T& operator*() //throws if not present
        {
            return *_d;
        }

        operator bool() const 
        { 
            return _d != nullptr; 
        }

    private:

        T* _d = nullptr;
    };

}
