#include "unity.h"
#include "getMask.h"

void setUp(void)
{
}

void tearDown(void)
{
}


/*
 *  Eg. if bitPosition is 16
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                       ^
 *                       |
 *                      16
 *
 */
void test_getMask_given_bitPosition_16_should_return_0x0001ffff()
{
  unsigned int mask;
  mask = getMask(16);

  TEST_ASSERT_EQUAL(0x0001ffff,mask);
}



/*
 *  Eg. if bitPosition is 17
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                      ^
 *                      |
 *                     17
 *
 */
void test_getMask_given_bitPosition_17_should_return_0x0003ffff()
{
  unsigned int mask;
  mask = getMask(17);

  TEST_ASSERT_EQUAL(0x0003ffff,mask);
}


/*
 *  Eg. if bitPosition is 18
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                     ^
 *                     |
 *                    18
 *
 */
void test_getMask_given_bitPosition_18_should_return_0x0007ffff()
{
  unsigned int mask;
  mask = getMask(18);

  TEST_ASSERT_EQUAL(0x0007ffff,mask);
}



/*
 *  Eg. if bitPosition is 19
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                    ^
 *                    |
 *                   19
 *
 */
void test_getMask_given_bitPosition_19_should_return_0x000fffff()
{
  unsigned int mask;
  mask = getMask(19);

  TEST_ASSERT_EQUAL(0x000fffff,mask);
}



//boundary test
/*
 *  Eg. if bitPosition is 31
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *  ^
 *  |
 * 31
 *
 */
void test_getMask_given_bitPosition_31_should_return_0xffffffff()
{
  unsigned int mask;
  mask = getMask(31);

  TEST_ASSERT_EQUAL(0xffffffff,mask);
}



//boundary test
/*
 *  Eg. if bitPosition is 3
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                                            ^
 *                                            |
 *                                            3
 *
 */
void test_getMask_given_bitPosition_3_should_return_0x0000000f()
{
  unsigned int mask;
  mask = getMask(3);
  
  TEST_ASSERT_EQUAL(0x0000000f,mask);
}


//boundary test
/*
 *  Eg. if bitPosition is 0
 *  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  XXXX  ---> this is a 32 bits integer
 *                                               ^
 *                                               |
 *                                               0
 *
 */
void test_getMask_given_bitPosition_0_should_return_0x00000001()
{
  unsigned int mask;
  mask = getMask(0);

  TEST_ASSERT_EQUAL(0x00000001,mask);
}


