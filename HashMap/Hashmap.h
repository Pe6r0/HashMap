#pragma once

#include <list>
#include <vector>
#include <optional>

namespace kron
{
    template<typename Key, typename Type, typename HashFunct = std::hash<Key>>
    class Hashmap
    {
        //used the very nice write up on https://jbseg.medium.com/c-unordered-map-under-the-hood-9540cec4553a as inspiration

    public:

        Hashmap()
        {
            _d.resize(8);
        } // add one for non default hash

        std::optional<Type> operator[](const Key& k)
        {
            size_t hash = _hasher(k);

            auto& bucket = _d[hash % _d.size()];

            for (auto& elem : bucket)
            {
                if (elem.first == hash)
                {
                    return elem.second;
                }
            }
            return std::nullopt;
        }

        size_t size() { return _s; }

        //operator << etc check out the std page to keep adding functions

        void insert(Key k, Type t)
        {
            size_t hash = _hasher(k);

            auto& bucket = _d[hash % _d.size()];

            auto pair = std::pair<size_t, Type>{ hash, t };

            for (auto& elem : bucket)
            {
                if (elem.first == hash)
                {
                    elem.second = t;
                    return;
                }
            }

            bucket.push_front(pair);
            _s++;
        }

        bool erase(const Key& k)
        {
            size_t hash = _hasher(k);

            auto& bucket = _d[hash % _d.size()];

            for (auto it = bucket.begin(); it != bucket.end();)
            {
                if ((*it).first == hash)
                {
                    bucket.erase(it);
                    _s--;
                    return true;
                }
                
                ++it;
            }
            return false;
        }

    private:

        //trick is the size does change. rehashing does this. we can add capacity changes to it...

        void rehash()
        {
            return;
        }

        size_t _s = 0;

        size_t _rehashterm = 10;

        std::vector<std::list<std::pair<size_t, Type>>> _d; //ideally we'd use a C array but that can be the next iteration of it

        HashFunct _hasher;
    };

};