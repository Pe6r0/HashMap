#pragma once
#include <utility>
#include <optional>

namespace kron
{
    template <typename Key, typename Value>
    class OrderedMap
    {
    public:
        OrderedMap()
        {
        }

        ~OrderedMap()
        {
            //this will be fun
        }

        size_t size() { return _s; }

        std::optional<Value> operator[](const Key& k)
        {
            
        }

        void insert(Key k, Value t)
        {
            //insert a normal insertion
            //make it red
            //fix the properties
        }

        bool erase(const Key& k)
        {
        }

    private:

        //root is black
        //
        //if red both children must be black
        //
        //for each node, all paths must contain the same number of black nodes

        void balance()
        {
            //direct color changes only on the root

        }

        struct Node
        {
            enum class Color { red, black };

            std::pair<Key, Value> _data;

            Color _color =  Color::black; //doublecheck
            Node* _parent = nullptr;
            Node* _left = nullptr; //count as black
            Node* _right = nullptr; //count as black
        };

        Node* _d = nullptr;

        size_t _s = 0;
    };
}