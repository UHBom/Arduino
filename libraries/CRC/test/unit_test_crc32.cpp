//
//    FILE: unit_test_crc32.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-03-31
// PURPOSE: unit tests for the CRC library
//          https://github.com/RobTillaart/CRC
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)


#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "CRC32.h"


char str[24] = "123456789";
uint8_t * data = (uint8_t *) str;


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_crc32_getters)
{
  fprintf(stderr, "TEST CRC32 GETTERS\n");

  CRC32 crc;
  crc.setPolynome(0x04C11DB7);
  crc.setStartXOR(0xFFFFFFFF);
  crc.setEndXOR(0xFFFFFFFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  
  assertEqual(0x04C11DB7, crc.getPolynome());
  assertEqual(0xFFFFFFFF, crc.getStartXOR());
  assertEqual(0xFFFFFFFF, crc.getEndXOR());
  assertTrue(crc.getReverseIn());
  assertTrue(crc.getReverseOut());

  crc.reset();
  crc.setPolynome(0x1EDC6F41);
  crc.setStartXOR(0x00000000);
  crc.setEndXOR(0x00000000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);

  assertEqual(0x1EDC6F41, crc.getPolynome());
  assertEqual(0x00000000, crc.getStartXOR());
  assertEqual(0x00000000, crc.getEndXOR());
  assertFalse(crc.getReverseIn());
  assertFalse(crc.getReverseOut());
}


unittest(test_crc32)
{
  fprintf(stderr, "TEST CRC32\n");

  CRC32 crc;
  crc.setPolynome(0x04C11DB7);
  crc.setStartXOR(0xFFFFFFFF);
  crc.setEndXOR(0xFFFFFFFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0xCBF43926, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x04C11DB7);
  crc.setStartXOR(0xFFFFFFFF);
  crc.setEndXOR(0xFFFFFFFF);
  crc.add(data, 9);
  assertEqual(0xFC891918, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x1EDC6F41);
  crc.setStartXOR(0xFFFFFFFF);
  crc.setEndXOR(0xFFFFFFFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0xE3069283, crc.getCRC());

  crc.reset();
  crc.setPolynome(0xA833982B);
  crc.setStartXOR(0xFFFFFFFF);
  crc.setEndXOR(0xFFFFFFFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x87315576, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x04C11DB7);
  crc.setStartXOR(0xFFFFFFFF);
  crc.setEndXOR(0x00000000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0x0376E6E7, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x04C11DB7);
  crc.setStartXOR(0x00000000);
  crc.setEndXOR(0xFFFFFFFF);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0x765E7680, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x814141AB);
  crc.setStartXOR(0x00000000);
  crc.setEndXOR(0x00000000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0x3010BF7F, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x04C11DB7);
  crc.setStartXOR(0xFFFFFFFF);
  crc.setEndXOR(0x00000000);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  crc.add(data, 9);
  assertEqual(0x340BC6D9, crc.getCRC());

  crc.reset();
  crc.setPolynome(0x000000AF);
  crc.setStartXOR(0x00000000);
  crc.setEndXOR(0x00000000);
  crc.setReverseIn(false);
  crc.setReverseOut(false);
  crc.add(data, 9);
  assertEqual(0xBD0BE338, crc.getCRC());

  /*
  // DONE
  assertEqual(0xCBF43926, crc32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true));
  assertEqual(0xFC891918, crc32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false));
  assertEqual(0xE3069283, crc32(data, 9, 0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true));
  assertEqual(0x87315576, crc32(data, 9, 0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true));
  assertEqual(0x0376E6E7, crc32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false));
  assertEqual(0x765E7680, crc32(data, 9, 0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false));
  assertEqual(0x3010BF7F, crc32(data, 9, 0x814141AB, 0x00000000, 0x00000000, false, false));
  assertEqual(0x340BC6D9, crc32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true));
  assertEqual(0xBD0BE338, crc32(data, 9, 0x000000AF, 0x00000000, 0x00000000, false, false));
  */
}


unittest(test_crc32_param)
{
  fprintf(stderr, "TEST CRC32 PARAM\n");

  CRC32 crc(0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
  crc.add(data, 9);
  assertEqual(0xCBF43926, crc.getCRC());
}


unittest_main()

// --------
