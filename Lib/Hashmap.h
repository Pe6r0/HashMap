#pragma once

#include <list>
#include <vector>
#include <optional>
#include <iterator>

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
            if (_s > _rehashterm)
            {
                rehash();
                _rehashterm *= 2;
            }
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
            _d.resize(_d.size() * 2);

            for (size_t bucket = 0; bucket < _d.size(); ++bucket)
            {
                for (auto it = _d[bucket].begin(); it != _d[bucket].end(); ++it)
                {
                    auto newHash = (*it).first % _d.size();
                    if (newHash != bucket)
                    {
                        auto elementToMove = std::move(*it);

                        // Remove the element from the source container
                        it = _d[bucket].erase(it);

                        // Move the element to the destination container
                        _d[newHash].push_front(std::move(elementToMove));

                        if(it == _d[bucket].end())
                        {
                            break;
                        }
                    }
                }
            }
            return;
        }

        size_t _s = 0;

        size_t _rehashterm = 8;

        std::vector<std::list<std::pair<size_t, Type>>> _d; //ideally we'd use a C array but that can be the next iteration of it

        HashFunct _hasher;
    };

};