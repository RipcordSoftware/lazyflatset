#ifndef CLASS_OPERATIONS_H
#define	CLASS_OPERATIONS_H

#include <cppunit/extensions/HelperMacros.h>

class class_operations : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(class_operations);

    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);
    CPPUNIT_TEST(test4);
    CPPUNIT_TEST(test5);
    CPPUNIT_TEST(test6);
    CPPUNIT_TEST(test7);
    CPPUNIT_TEST(test8);

    CPPUNIT_TEST_SUITE_END();

public:
    class_operations();
    virtual ~class_operations();
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
};

#endif	/* CLASS_OPERATIONS_H */

