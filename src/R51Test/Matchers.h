#ifndef _R51_TEST_MATCHERS_H_
#define _R51_TEST_MATCHERS_H_

#include <Arduino.h>
#include <AUnit.h>

#define assertSize(container, value) \
    assertEqual((int)container.size(), (int)value)

#endif  // _R51_TEST_MATCHERS_H_
