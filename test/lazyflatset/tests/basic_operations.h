#ifndef BASIC_OPERATIONS_H
#define	BASIC_OPERATIONS_H

#include <cppunit/extensions/HelperMacros.h>

class basic_operations : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(basic_operations);

    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);
    CPPUNIT_TEST(test4);
    CPPUNIT_TEST(test5);
    CPPUNIT_TEST(test6);
    CPPUNIT_TEST(test7);
    CPPUNIT_TEST(test8);
    CPPUNIT_TEST(test9);
    CPPUNIT_TEST(test10);
    CPPUNIT_TEST(test11);
    CPPUNIT_TEST(test12);
    CPPUNIT_TEST(test13);
    CPPUNIT_TEST(test14);
    CPPUNIT_TEST(test15);
    CPPUNIT_TEST(test16);
    CPPUNIT_TEST(test17);

    CPPUNIT_TEST_SUITE_END();

public:
    basic_operations();
    virtual ~basic_operations();
    void setUp();
    void tearDown();

private:
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7();
    void test8();
    void test9();
    void test10();
    void test11();
    void test12();
    void test13();
    void test14();
    void test15();
    void test16();
    void test17();
};

#endif	/* BASIC_OPERATIONS_H */

