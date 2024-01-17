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
}
