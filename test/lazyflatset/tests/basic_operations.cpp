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