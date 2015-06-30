#ifndef TEST_TIMSORT_H
#define	TEST_TIMSORT_H

#include <cppunit/extensions/HelperMacros.h>

class test_timsort : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_timsort);

    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);
    CPPUNIT_TEST(test4);
    CPPUNIT_TEST(test5);
    CPPUNIT_TEST(test6);

    CPPUNIT_TEST_SUITE_END();

public:
    test_timsort();
    virtual ~test_timsort();
    void setUp();
    void tearDown();

private:
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
};

#endif	/* TEST_TIMSORT_H */

