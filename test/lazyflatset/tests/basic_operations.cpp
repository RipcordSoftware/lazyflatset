#include "basic_operations.h"

#include <vector>
#include <algorithm>

#include "../../../lazyflatset.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(basic_operations);

basic_operations::basic_operations() {
}

basic_operations::~basic_operations() {
}

void basic_operations::setUp() {
}

void basic_operations::tearDown() {
}

void basic_operations::test1() {
    rs::LazyFlatSet<unsigned> set;
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.empty());
    set.insert(0);
    CPPUNIT_ASSERT(set.size() == 1);
    CPPUNIT_ASSERT(!set.empty());
    CPPUNIT_ASSERT(set.count(0) == 1);
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.empty());
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void basic_operations::test2() {
    rs::LazyFlatSet<unsigned> set;
    set.insert(0);
    CPPUNIT_ASSERT(set.size() == 1);
    set.insert(1);
    CPPUNIT_ASSERT(set.size() == 2);
    set.insert(2);
    CPPUNIT_ASSERT(set.size() == 3);
    set.insert(3);
    CPPUNIT_ASSERT(set.size() == 4);
    set.insert(4);
    CPPUNIT_ASSERT(set.size() == 5);
    CPPUNIT_ASSERT(set.count(0) == 1);
    CPPUNIT_ASSERT(set.count(1) == 1);
    CPPUNIT_ASSERT(set.count(2) == 1);
    CPPUNIT_ASSERT(set.count(3) == 1);
    CPPUNIT_ASSERT(set.count(4) == 1);
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void basic_operations::test3() {
    rs::LazyFlatSet<unsigned> set;
    set.insert(0);
    CPPUNIT_ASSERT(set.size() == 1);
    set.insert(1);
    CPPUNIT_ASSERT(set.size() == 2);
    set.insert(2);
    CPPUNIT_ASSERT(set.size() == 3);
    set.insert(3);
    CPPUNIT_ASSERT(set.size() == 4);
    set.insert(4);
    CPPUNIT_ASSERT(set.size() == 5);
    CPPUNIT_ASSERT(set.count(0) == 1);
    CPPUNIT_ASSERT(set.count(1) == 1);
    CPPUNIT_ASSERT(set.count(2) == 1);
    CPPUNIT_ASSERT(set.count(3) == 1);
    CPPUNIT_ASSERT(set.count(4) == 1);
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
    set.insert(0);
    CPPUNIT_ASSERT(set.size() == 1);
    set.insert(1);
    CPPUNIT_ASSERT(set.size() == 2);
    set.insert(2);
    CPPUNIT_ASSERT(set.size() == 3);
    set.insert(3);
    CPPUNIT_ASSERT(set.size() == 4);
    set.insert(4);
    CPPUNIT_ASSERT(set.size() == 5);
    CPPUNIT_ASSERT(set.count(0) == 1);
    CPPUNIT_ASSERT(set.count(1) == 1);
    CPPUNIT_ASSERT(set.count(2) == 1);
    CPPUNIT_ASSERT(set.count(3) == 1);
    CPPUNIT_ASSERT(set.count(4) == 1);
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void basic_operations::test4() {
    rs::LazyFlatSet<unsigned> set;
    set.insert(0);
    CPPUNIT_ASSERT(set.size() == 1);
    set.insert(0);
    CPPUNIT_ASSERT(set.size() == 1);
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void basic_operations::test5() {
    rs::LazyFlatSet<unsigned> set;
    for (unsigned i = 0; i < 10000; ++i) {
        set.insert(i);
        CPPUNIT_ASSERT(set.size() == i + 1);
        CPPUNIT_ASSERT(set.count(i) == 1);
        CPPUNIT_ASSERT(set.count(i + 1) == 0);
        
        unsigned value = -1;
        CPPUNIT_ASSERT(set.find(i, value));
        CPPUNIT_ASSERT(i == value);
    }
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void basic_operations::test6() {
    rs::LazyFlatSet<unsigned> set;
    const unsigned max = 10000;
    for (unsigned i = 0; i < max; ++i) {
        unsigned k = max - i - 1;
        set.insert(k);
        CPPUNIT_ASSERT(set.size() == i + 1);
        CPPUNIT_ASSERT(set.count(k) == 1);
        CPPUNIT_ASSERT(set.count(k - 1) == 0);
        
        unsigned value = -1;
        CPPUNIT_ASSERT(set.find(k, value));
        CPPUNIT_ASSERT(k == value);
    }
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void basic_operations::test7() {
    rs::LazyFlatSet<unsigned> set;
    set.insert(0);
    CPPUNIT_ASSERT(set.size() == 1);
    CPPUNIT_ASSERT(!set.empty());
    CPPUNIT_ASSERT(set.count(0) == 1);
    CPPUNIT_ASSERT(set.count(1) == 0);
    CPPUNIT_ASSERT(set.erase(0) == 1);
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.empty());
    CPPUNIT_ASSERT(set.count(0) == 0);
    CPPUNIT_ASSERT(set.count(1) == 0);
}

void basic_operations::test8() {
    rs::LazyFlatSet<unsigned> set;
    set.insert(0);
    set.insert(1);   
    set.insert(2);
    set.insert(3);
    set.insert(4);
    CPPUNIT_ASSERT_EQUAL(5ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(0));
    CPPUNIT_ASSERT_EQUAL(4ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(1));
    CPPUNIT_ASSERT_EQUAL(3ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(2));
    CPPUNIT_ASSERT_EQUAL(2ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(3));
    CPPUNIT_ASSERT_EQUAL(1ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(4));
    CPPUNIT_ASSERT_EQUAL(0ul, set.size());
    CPPUNIT_ASSERT_EQUAL(0ul, set.erase(99));
    CPPUNIT_ASSERT(set.empty());
}

void basic_operations::test9() {
    rs::LazyFlatSet<unsigned> set;
    set.insert(0);
    set.insert(1);   
    set.insert(2);
    set.insert(3);
    set.insert(4);
    CPPUNIT_ASSERT_EQUAL(5ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(0));
    set.insert(0);
    CPPUNIT_ASSERT_EQUAL(5ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(1));  
    set.insert(1);
    CPPUNIT_ASSERT_EQUAL(5ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(2));  
    set.insert(2);
    CPPUNIT_ASSERT_EQUAL(5ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(3));  
    set.insert(3);
    CPPUNIT_ASSERT_EQUAL(5ul, set.size());    
    CPPUNIT_ASSERT_EQUAL(1ul, set.erase(4));
    set.insert(4);
    CPPUNIT_ASSERT_EQUAL(5ul, set.size());    
    CPPUNIT_ASSERT(!set.empty());
}

void basic_operations::test10() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned> set;
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        set.insert(k);
        CPPUNIT_ASSERT(set.size() == i + 1);
        CPPUNIT_ASSERT(set.count(k) == 1);
        
        unsigned value = -1;
        CPPUNIT_ASSERT(set.find(k, value));
        CPPUNIT_ASSERT(k == value);
    }
    set.clear();
    CPPUNIT_ASSERT_EQUAL(0ul, set.size());
    CPPUNIT_ASSERT_EQUAL(0ul, set.count(0));
}

void basic_operations::test11() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned> set;
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        set.insert(k);
        CPPUNIT_ASSERT_EQUAL(i + 1ul, set.size());
        CPPUNIT_ASSERT_EQUAL(1ul, set.count(k));
        
        unsigned value = -1;
        CPPUNIT_ASSERT(set.find(k, value));
        CPPUNIT_ASSERT_EQUAL(k, value);
    }
    
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        
        unsigned value = -1;
        CPPUNIT_ASSERT(set.find(k, value));
        CPPUNIT_ASSERT_EQUAL(k, value);
        
        CPPUNIT_ASSERT_EQUAL(1ul, set.count(k));
        CPPUNIT_ASSERT_EQUAL(1ul, set.erase(k));
        CPPUNIT_ASSERT_EQUAL(0ul, set.count(k));
        CPPUNIT_ASSERT_EQUAL(data.size() - i - 1, set.size());
    }
    
    CPPUNIT_ASSERT_EQUAL(0ul, set.size());
    CPPUNIT_ASSERT(set.empty());
}

void basic_operations::test12() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned> set;
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        set.insert(k);
        CPPUNIT_ASSERT_EQUAL(i + 1ul, set.size());
        CPPUNIT_ASSERT_EQUAL(1ul, set.count(k));
        
        unsigned value = -1;
        CPPUNIT_ASSERT(set.find(k, value));
        CPPUNIT_ASSERT_EQUAL(k, value);
    }
    
    std::reverse(data.begin(), data.end());
    
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        
        unsigned value = -1;
        CPPUNIT_ASSERT(set.find(k, value));
        CPPUNIT_ASSERT_EQUAL(k, value);
        
        CPPUNIT_ASSERT_EQUAL(1ul, set.count(k));
        CPPUNIT_ASSERT_EQUAL(1ul, set.erase(k));
        CPPUNIT_ASSERT_EQUAL(0ul, set.count(k));
        CPPUNIT_ASSERT_EQUAL(data.size() - i - 1, set.size());
    }
    
    CPPUNIT_ASSERT_EQUAL(0ul, set.size());
    CPPUNIT_ASSERT(set.empty());
}

void basic_operations::test13() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned> set;
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        set.insert(k);
        CPPUNIT_ASSERT_EQUAL(i + 1ul, set.size());
        CPPUNIT_ASSERT_EQUAL(1ul, set.count(k));
        
        unsigned value = -1;
        CPPUNIT_ASSERT(set.find(k, value));
        CPPUNIT_ASSERT_EQUAL(k, value);
    }   
    
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        set.insert(k);
        CPPUNIT_ASSERT_EQUAL(data.size(), set.size());
        CPPUNIT_ASSERT_EQUAL(1ul, set.count(k));
        
        unsigned value = -1;
        CPPUNIT_ASSERT(set.find(k, value));
        CPPUNIT_ASSERT_EQUAL(k, value);
    }
}

void basic_operations::test14() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned> set;
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        set.insert(k);
    }   
    
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = set[i];
        CPPUNIT_ASSERT_EQUAL(i, k);
    }
}

void basic_operations::test15() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned> set;
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        set.insert(k);
    }   
    
    auto setData = set.data();
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = setData[i];
        CPPUNIT_ASSERT_EQUAL(i, k);
    }
}

void basic_operations::test16() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned> set;
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = data[i];
        set.insert(k);
    }   
    
    auto iter = set.cbegin();
    for (unsigned i = 0; i < data.size(); ++i) {
        auto k = *iter++;
        CPPUNIT_ASSERT_EQUAL(i, k);
    }
    
    CPPUNIT_ASSERT(set.cend() == iter);
}

void basic_operations::test17() {
    rs::LazyFlatSet<unsigned> set;
    for (unsigned i = 0; i < 10000; ++i) {
        set.insert(i + 1000);
    }
    
    CPPUNIT_ASSERT(set.find_fn([](unsigned v) { return -v; }) == nullptr);
    CPPUNIT_ASSERT(set.find_fn([](unsigned v) { return 100000 - v; }) == nullptr);
}

void basic_operations::test18() {
    rs::LazyFlatSet<unsigned> set(16);
    set.insert(4);
    set.insert(3);
    set.insert(2);
    set.insert(1);
    set.insert(0);                   
    
    std::vector<unsigned> copy1;
    set.copy(copy1, false);
    CPPUNIT_ASSERT(copy1.size() == set.size());
    CPPUNIT_ASSERT(copy1[0] == 4);
    CPPUNIT_ASSERT(copy1[1] == 3);
    CPPUNIT_ASSERT(copy1[2] == 2);
    CPPUNIT_ASSERT(copy1[3] == 1);
    CPPUNIT_ASSERT(copy1[4] == 0);
    
    std::vector<unsigned> copy2;
    set.copy(copy2, true);
    CPPUNIT_ASSERT(copy2.size() == set.size());
    CPPUNIT_ASSERT(copy2[0] == 0);
    CPPUNIT_ASSERT(copy2[1] == 1);
    CPPUNIT_ASSERT(copy2[2] == 2);
    CPPUNIT_ASSERT(copy2[3] == 3);
    CPPUNIT_ASSERT(copy2[4] == 4);
}

void basic_operations::test19() {    
    const auto unordered = 16;
    const auto nursery = 64;
    const auto count = 100;
    
    rs::LazyFlatSet<unsigned> set(unordered, nursery);
    for (auto i = 0; i < count; ++i) {
        set.insert(i);
    }
    
    std::vector<unsigned> copy1;
    set.copy(copy1, false);
    CPPUNIT_ASSERT(copy1.size() == set.size());
    for (auto i = 0; i < count; ++i) {
        CPPUNIT_ASSERT(copy1[i] == i);
    }
        
    std::vector<unsigned> copy2;
    set.copy(copy2, true);
    CPPUNIT_ASSERT(copy2.size() == set.size());
    for (auto i = 0; i < count; ++i) {
        CPPUNIT_ASSERT(copy2[i] == i);
    }
}

void basic_operations::test20() {    
    const auto unordered = 16;
    const auto nursery = 64;
    const auto count = 100;    
    
    rs::LazyFlatSet<unsigned> set(unordered, nursery);
    for (auto i = 0; i < count; ++i) {
        set.insert(count - i - 1);
    }
    
    std::vector<unsigned> copy1;        
    set.copy(copy1, false);
    
    // calculate the expected internal collection sizes so we can figure out
    // where the data should appear in the copy buffer
    auto unsortedSize = count % 16;
    auto mainSize = ((count - unsortedSize) / nursery) * nursery;
    auto nurserySize = count - mainSize - unsortedSize;
    
    CPPUNIT_ASSERT(copy1.size() == set.size());
    for (auto i = 0; i < mainSize; ++i) {
        CPPUNIT_ASSERT(copy1[i] == nurserySize + unsortedSize + i);
    }
    for (auto i = 0; i < nurserySize; ++i) {
        CPPUNIT_ASSERT(copy1[mainSize + i] == unsortedSize + i);
    }
    for (auto i = 0; i < unsortedSize; ++i) {
        CPPUNIT_ASSERT(copy1[mainSize + nurserySize + i] == unsortedSize - i - 1);
    }
        
    std::vector<unsigned> copy2;
    set.copy(copy2, true);
    CPPUNIT_ASSERT(copy2.size() == set.size());
    for (auto i = 0; i < count; ++i) {
        CPPUNIT_ASSERT(copy2[i] == i);
    }
}
