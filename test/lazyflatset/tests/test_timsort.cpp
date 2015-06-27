#include "test_timsort.h"

CPPUNIT_TEST_SUITE_REGISTRATION(test_timsort);

test_timsort::test_timsort() {
}

test_timsort::~test_timsort() {
}

void test_timsort::setUp() {
}

void test_timsort::tearDown() {
}

void test_timsort::test1() {
    rs::LazyFlatSet<unsigned, std::less<unsigned>, std::equal_to<unsigned>, LazyFlatSetTimsort<unsigned>> set;
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

void test_timsort::test2() {
    rs::LazyFlatSet<unsigned, std::less<unsigned>, std::equal_to<unsigned>, LazyFlatSetTimsort<unsigned>> set;
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

void test_timsort::test3() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned, std::less<unsigned>, std::equal_to<unsigned>, LazyFlatSetTimsort<unsigned>> set;
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

void test_timsort::test4() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned, std::less<unsigned>, std::equal_to<unsigned>, LazyFlatSetTimsort<unsigned>> set;
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

void test_timsort::test5() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned, std::less<unsigned>, std::equal_to<unsigned>, LazyFlatSetTimsort<unsigned>> set;
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

void test_timsort::test6() {
    std::vector<unsigned> data;
    for (unsigned i = 0; i < 10000; ++i) {
        data.push_back(i);
    }
    
    std::random_shuffle(data.begin(), data.end());
    
    rs::LazyFlatSet<unsigned, std::less<unsigned>, std::equal_to<unsigned>, LazyFlatSetTimsort<unsigned>> set;
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