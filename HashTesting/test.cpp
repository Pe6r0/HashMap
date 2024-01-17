#include "pch.h"
#include "../HashMap/Hashmap.h"

#include <optional>

namespace kron
{
    struct HashTestFixture : public testing::Test
    {
        Hashmap<char, int> simpleOne;
    };

    TEST_F(HashTestFixture, simpleTest) {
        EXPECT_EQ(0, simpleOne.size());
    }

    TEST_F(HashTestFixture, insertion) {
        simpleOne.insert('p', 20);
        EXPECT_EQ(1, simpleOne.size());
    }

    TEST_F(HashTestFixture, retrieval) {
        simpleOne.insert('p', 20);
        EXPECT_EQ(20, simpleOne['p']);
    }

    TEST_F(HashTestFixture, badRetrieval) {
        simpleOne.insert('p', 20);
        EXPECT_EQ(std::nullopt, simpleOne['o']);
    }

    TEST_F(HashTestFixture, erase) {
        simpleOne.insert('p', 20);
        EXPECT_EQ(1, simpleOne.size());
        EXPECT_TRUE(simpleOne.erase('p'));
        EXPECT_EQ(0, simpleOne.size());
    }

    TEST_F(HashTestFixture, badErase) {
        simpleOne.insert('p', 20);
        EXPECT_EQ(1, simpleOne.size());
        EXPECT_FALSE(simpleOne.erase('c'));
        EXPECT_EQ(1, simpleOne.size());
    }

    TEST_F(HashTestFixture, overwrite) {
        simpleOne.insert('p', 20);
        EXPECT_EQ(1, simpleOne.size());
        simpleOne.insert('p', 244);
        EXPECT_EQ(244, simpleOne['p']);
        EXPECT_EQ(1, simpleOne.size());
    }

    TEST_F(HashTestFixture, rehash) {
        simpleOne.insert('q', 20);
        simpleOne.insert('w', 1);
        simpleOne.insert('e', 4);
        simpleOne.insert('r', 220);
        simpleOne.insert('t', 204);
        simpleOne.insert('y', 201);
        simpleOne.insert('u', 2120);
        simpleOne.insert('i', 204);
        simpleOne.insert('o', 202);
        simpleOne.insert('p', 202);
        simpleOne.insert('a', 4);
        simpleOne.insert('s', 0);
        simpleOne.insert('d', 220);
        simpleOne.insert('f', 250);
        simpleOne.insert('g', 26);
        simpleOne.insert('h', 280);
        simpleOne.insert('j', 820);
        simpleOne.insert('k', 20);
        simpleOne.insert('l', 920);
        simpleOne.insert('z', 1);
        simpleOne.insert('x', 28);
        simpleOne.insert('c', 243);
        simpleOne.insert('v', 90);
        simpleOne.insert('b', 9);
        simpleOne.insert('n', 9);
        EXPECT_EQ(25, simpleOne.size());
        EXPECT_EQ(20, simpleOne['q']);
        EXPECT_EQ(1, simpleOne['z']);
        EXPECT_EQ(250, simpleOne['f']);
    }
}
