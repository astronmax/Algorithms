/*
MIT License

Copyright (c) 2021 Max A. Jurankov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file
 * @brief Tests for singly-linked list implementation with googletest framework 
 * (https://github.com/google/googletest)
 * @author [astronmax](https://github.com/astronmax)
 */

#include <gtest/gtest.h>
#include <s_list.hpp>

/**
 * Tests of all methods for empty list
 */

TEST(empty_list, empty_test)
{
    alg::s_list<int> l {};
    EXPECT_TRUE(l.empty());
}

TEST(empty_list, find_test)
{
    alg::s_list<int> l {};

    try {
        l.find(10);
    } catch (const std::logic_error& e) {
        EXPECT_TRUE(true);
    }
}

TEST(empty_list, push_back_test)
{
    alg::s_list<int> l {};
    alg::s_list<int> res { 1, 2, 3 };

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    auto j = res.begin();
    for (auto i = l.begin(); i != l.end(); ++i, ++j) {
        EXPECT_EQ(*i, *j);
    }
}

TEST(empty_list, push_front_test)
{
    alg::s_list<int> l {};
    alg::s_list<int> res { 1, 2, 3 };

    l.push_front(3);
    l.push_front(2);
    l.push_front(1);

    auto j = res.begin();
    for (auto i = l.begin(); i != l.end(); ++i, ++j) {
        EXPECT_EQ(*i, *j);
    }
}

TEST(empty_list, erase_test)
{
    alg::s_list<int> l {};

    try {
        l.erase(1);
    } catch (const std::logic_error& e) {
        EXPECT_TRUE(true);
    }
}

TEST(empty_list, insert_test)
{
    alg::s_list<int> l {};
    try {
        l.insert_after(10, 11);
    } catch (const std::logic_error& e) {
        EXPECT_TRUE(true);
    }
}

TEST(empty_list, clear_test)
{
    alg::s_list<int> l {};
    l.clear();
    EXPECT_TRUE(l.empty());
}

TEST(empty_list, size_test)
{
    alg::s_list<int> l {};
    EXPECT_EQ(l.size(), 0);
}

TEST(empty_list, front_test)
{
    alg::s_list<int> l {};

    try {
        l.front();
    } catch (const std::logic_error& e) {
        EXPECT_TRUE(true);
    }
}

TEST(empty_list, back_test)
{
    alg::s_list<int> l {};

    try {
        l.back();
    } catch (const std::logic_error& e) {
        EXPECT_TRUE(true);
    }
}

/**
 * Tests of all methods for filled list
 */

TEST(filled_list, empty_test)
{
    alg::s_list<int> l { 1, 2, 3 };

    EXPECT_FALSE(l.empty());
}

TEST(filled_list, find_test)
{
    alg::s_list<int> l { 1, 27, -3, 100, 5 };

    EXPECT_EQ((l.find(27))->get(), 27);
    EXPECT_EQ((l.find(1))->get(), 1);
    EXPECT_EQ((l.find(5))->get(), 5);
    EXPECT_EQ((l.find(-3))->get(), -3);
    EXPECT_EQ((l.find(100))->get(), 100);
    EXPECT_EQ(l.find(101), nullptr);
}

TEST(filled_list, push_back_test)
{
    alg::s_list<int> l { 1, 2, 3 };
    alg::s_list<int> res { 1, 2, 3, 4, 5, 6 };
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);

    auto j = res.begin();
    for (auto i = l.begin(); i != l.end(); ++i, ++j) {
        EXPECT_EQ(*i, *j);
    }
}

TEST(filled_list, push_front_test)
{
    alg::s_list<int> l { 4, 5, 6 };
    alg::s_list<int> res { 1, 2, 3, 4, 5, 6 };
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);

    auto j = res.begin();
    for (auto i = l.begin(); i != l.end(); ++i, ++j) {
        EXPECT_EQ(*i, *j);
    }
}

TEST(filled_list, erase_test)
{
    alg::s_list<int> l { 1, 2, 3, 4, 5 };
    alg::s_list<int> res { 1, 3, 5 };

    l.erase(4);
    l.erase(2);

    auto j = res.begin();
    for (auto i = l.begin(); i != l.end(); ++i, ++j) {
        EXPECT_EQ(*i, *j);
    }
}

TEST(filled_list, insert_after_test)
{
    alg::s_list<int> l { 1, -3, 100, 3, 5 };
    alg::s_list<int> res { 1, 1000, -3, 1000, 100, 1000, 3, 1000, 5, 1000 };

    l.insert_after(1, 1000);
    l.insert_after(-3, 1000);
    l.insert_after(100, 1000);
    l.insert_after(3, 1000);
    l.insert_after(5, 1000);

    auto j = res.begin();
    for (auto i = l.begin(); i != l.end(); ++i, ++j) {
        EXPECT_EQ(*i, *j);
    }
}

TEST(filled_list, clear_test)
{
    alg::s_list<int> l { 1, 2, 3, 4, 5 };
    l.clear();
    EXPECT_TRUE(l.empty());

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    EXPECT_FALSE(l.empty());
}

TEST(filles_list, size_test)
{
    alg::s_list<int> l {};
    for (auto i = 0; i < 100; ++i)
        l.push_back(i);

    EXPECT_EQ(l.size(), 100);
}

TEST(filled_list, front_test)
{
    alg::s_list<int> l { 1, 2, 3, 4, 5 };

    EXPECT_EQ(l.front(), 1);
}

TEST(filled_list, back_test)
{
    alg::s_list<int> l { 1, 2, 3, 4, 5 };

    EXPECT_EQ(l.back(), 5);
}