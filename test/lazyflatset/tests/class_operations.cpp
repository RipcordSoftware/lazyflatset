#include "class_operations.h"

#include "../../../lazyflatset.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(class_operations);

struct Test {
    struct Less {
        bool operator()(const Test& x, const Test& y) const {
            return x.data_ < y.data_;
        }
    };
    
    struct Equals {
        bool operator()(const Test& x, const Test& y) const {
            return x.data_ == y.data_;
        }
    };
    
    struct Hash {
        std::size_t operator()(const Test& t) const {
            return t.data_;
        }
    };
    
    Test(unsigned data) : data_(data) {}
    Test(const Test& other) {
        data_ = other.data_;
    }
    
    unsigned value() const { return data_; }
    
private:
    unsigned data_;
};

using LazyFlatSetTest = rs::LazyFlatSet<Test, Test::Less, Test::Equals>;

class_operations::class_operations() {
}

class_operations::~class_operations() {
}

void class_operations::setUp() {
}

void class_operations::tearDown() {
}

void class_operations::test1() {
    LazyFlatSetTest set;
    set.emplace(42);
    
    CPPUNIT_ASSERT_EQUAL(1ul, set.size());
    CPPUNIT_ASSERT_EQUAL(42u, set[0].value());
}

void class_operations::test2() {
    LazyFlatSetTest set;
    set.emplace(42);
    set.emplace(69);
    
    CPPUNIT_ASSERT_EQUAL(2ul, set.size());
    CPPUNIT_ASSERT_EQUAL(42u, set[0].value());
    CPPUNIT_ASSERT_EQUAL(69u, set[1].value());
}

void class_operations::test3() {
    LazyFlatSetTest set;
    for (unsigned i = 0; i < 10000; ++i) {
        set.emplace(i);
        CPPUNIT_ASSERT(set.size() == i + 1);
        CPPUNIT_ASSERT(set.count(i) == 1);
        CPPUNIT_ASSERT(set.count(i + 1) == 0);        
    }
    
    for (unsigned i = 0; i < 10000; ++i) {
        CPPUNIT_ASSERT_EQUAL(i, set[i].value());
    }
    
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void class_operations::test4() {
    LazyFlatSetTest set;
    const unsigned max = 10000;
    for (unsigned i = 0; i < max; ++i) {
        unsigned k = max - i - 1;
        set.emplace(k);
        CPPUNIT_ASSERT(set.size() == i + 1);
        CPPUNIT_ASSERT(set.count(k) == 1);
        CPPUNIT_ASSERT(set.count(k - 1) == 0);
    }
    
    for (unsigned i = 0; i < max; ++i) {
        CPPUNIT_ASSERT_EQUAL(i, set[i].value());
    }
    
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void class_operations::test5() {
    LazyFlatSetTest set;
    
    set.emplace(42);
    CPPUNIT_ASSERT_EQUAL(1ul, set.size());
    
    set.emplace(42);
    CPPUNIT_ASSERT_EQUAL(1ul, set.size());
    CPPUNIT_ASSERT_EQUAL(42u, set[0].value());
}

void class_operations::test6() {
    LazyFlatSetTest set;
    
    set.emplace(42);
    CPPUNIT_ASSERT_EQUAL(1ul, set.size());
    CPPUNIT_ASSERT_EQUAL(42u, set[0].value());
    
    set.emplace(42);
    CPPUNIT_ASSERT_EQUAL(1ul, set.size());
    CPPUNIT_ASSERT_EQUAL(42u, set[0].value());
}

void class_operations::test7() {
    LazyFlatSetTest set;
    const unsigned max = 10000;
    const unsigned maxItems = 100;
    for (unsigned i = 0; i < max; ++i) {
        unsigned k = i % maxItems;
        set.emplace(k);
        CPPUNIT_ASSERT_EQUAL(static_cast<LazyFlatSetTest::size_type>(i >= maxItems ? maxItems : i + 1), set.size());
    }
    
    for (unsigned i = 0; i < maxItems; ++i) {
        CPPUNIT_ASSERT_EQUAL(i, set[i].value());
    }
    
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void class_operations::test8() {
    LazyFlatSetTest set;
    const unsigned max = 10000;
    const unsigned maxItems = 100;
    for (unsigned i = 0; i < max; ++i) {
        unsigned k = maxItems - (i % maxItems) - 1;
        set.emplace(k);
        CPPUNIT_ASSERT_EQUAL(static_cast<LazyFlatSetTest::size_type>(i >= maxItems ? maxItems : i + 1), set.size());
    }
    
    for (unsigned i = 0; i < maxItems; ++i) {
        CPPUNIT_ASSERT_EQUAL(i, set[i].value());
    }
    
    set.clear();
    CPPUNIT_ASSERT(set.size() == 0);
    CPPUNIT_ASSERT(set.count(0) == 0);
}

void class_operations::test9() {
    LazyFlatSetTest set;
    
    set.emplace(1);
    set.emplace(4);
    set.emplace(7);
    
    const unsigned value = 42;
    set.emplace(value);
        
    auto func = [=](const Test& t) { 
        return value - t.value(); 
    };
    
    CPPUNIT_ASSERT_EQUAL(1ul, set.count_fn(func));
    CPPUNIT_ASSERT_EQUAL(0ul, set.count_fn([](const Test& t){ return 99 - t.value(); } ));
    CPPUNIT_ASSERT_EQUAL(0ul, set.count_fn([](const Test& t){ return 0 - t.value(); } ));
}

void class_operations::test10() {
    LazyFlatSetTest set;
        
    for (unsigned i = 0; i < 1000; i++) {
        set.emplace(i);
    }
    
    const unsigned value = 42;    
    auto func = [=](const Test& t) { 
        return value - t.value(); 
    };
    
    CPPUNIT_ASSERT_EQUAL(1ul, set.count_fn(func));
}

void class_operations::test11() {
    LazyFlatSetTest set;
        
    for (unsigned i = 0; i < 1000; i++) {
        set.emplace(i);
    }    

    set.shrink_to_fit();
    
    const unsigned value = 42;    
    auto func = [=](const Test& t) { 
        return value - t.value(); 
    };
    
    CPPUNIT_ASSERT_EQUAL(1ul, set.count_fn(func));
}

void class_operations::test12() {
    LazyFlatSetTest set;
    
    set.emplace(1);
    set.emplace(4);
    set.emplace(7);
    
    const unsigned value = 42;
    set.emplace(value);
    
    auto func = [=](const Test& t) { 
        return value - t.value(); 
    };
    
    auto v = set.find_fn(func);
    CPPUNIT_ASSERT(v != nullptr);
    CPPUNIT_ASSERT_EQUAL(42u, v->value());
    
    CPPUNIT_ASSERT(nullptr == set.find_fn([](const Test& t){ return 99 - t.value(); } ));
    CPPUNIT_ASSERT(nullptr == set.find_fn([](const Test& t){ return 0 - t.value(); } ));
}

void class_operations::test13() {
    LazyFlatSetTest set;
        
    for (unsigned i = 0; i < 1000; i++) {
        set.emplace(i);
    }    
    
    const unsigned value = 42;    
    auto func = [=](const Test& t) { 
        return value - t.value(); 
    };
    
    auto v = set.find_fn(func);
    CPPUNIT_ASSERT(v != nullptr);
    CPPUNIT_ASSERT_EQUAL(42u, v->value());
}

void class_operations::test14() {
    LazyFlatSetTest set;
        
    for (unsigned i = 0; i < 1000; i++) {
        set.emplace(i);
    }
    
    set.shrink_to_fit();
    
    const unsigned value = 42;    
    auto func = [=](const Test& t) { 
        return value - t.value(); 
    };
    
    auto v = set.find_fn(func);
    CPPUNIT_ASSERT(v != nullptr);
    CPPUNIT_ASSERT_EQUAL(42u, v->value());
}