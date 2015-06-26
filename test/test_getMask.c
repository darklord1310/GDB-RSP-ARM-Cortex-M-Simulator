#include "unity.h"
#include "getMask.h"
#include <stdint.h>

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
void test_getMaskforGetBits_given_bitPosition_16_should_return_0x0001ffff()
{
  uint32_t mask;
  mask = getMaskforGetBits(16);

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
void test_getMaskforGetBits_given_bitPosition_17_should_return_0x0003ffff()
{
  uint32_t mask;
  mask = getMaskforGetBits(17);

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
void test_getMaskforGetBits_given_bitPosition_18_should_return_0x0007ffff()
{
  uint32_t mask;
  mask = getMaskforGetBits(18);

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
void test_getMaskforGetBits_given_bitPosition_19_should_return_0x000fffff()
{
  uint32_t mask;
  mask = getMaskforGetBits(19);

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
void test_getMaskforGetBits_given_bitPosition_31_should_return_0xffffffff()
{
  uint32_t mask;
  mask = getMaskforGetBits(31);

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
void test_getMaskforGetBits_given_bitPosition_3_should_return_0x0000000f()
{
  uint32_t mask;
  mask = getMaskforGetBits(3);
  
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
void test_getMaskforGetBits_given_bitPosition_0_should_return_0x00000001()
{
  uint32_t mask;
  mask = getMaskforGetBits(0);

  TEST_ASSERT_EQUAL(0x00000001,mask);
}


void test_getMaskforSetBits_given_bitPosition_3_and_0110_should_return_0xfffffff6()
{
  uint32_t mask;
  mask = getMaskforSetBits(3 , 0b0110);

  TEST_ASSERT_EQUAL(0xfffffff6,mask);
  
}

