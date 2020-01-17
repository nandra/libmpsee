#include <stdarg.h>
#include <stddef.h>
#include <limits.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>

#include "support.h"

static void test_frequency_manipulation(void **state)
{
  int system_clock = TWELVE_MHZ;
  int frequency = ONE_HUNDRED_KHZ;
  int divisor;
  int frequency_expected;

  divisor = freq2div(system_clock, frequency);
  frequency_expected = div2freq(system_clock, divisor);

  assert_int_equal(frequency, frequency_expected);
}

static void test_check_timeouts(void **state)
{
  struct mpsse_context mpsse;
  int timeout;
  mpsse.mode = 1;

  // test valid write
  set_timeouts(&mpsse, 5);
  get_timeouts(&mpsse, &timeout);
  
  assert_int_equal(timeout, 5);

  // test invalid write (mode is not set)
  mpsse.mode = 0;

  set_timeouts(&mpsse, 5);
  get_timeouts(&mpsse, &timeout);
  
  assert_int_equal(timeout, -1);
}

static void test_context(void **state)
{
  struct mpsse_context *mpsse_ptr = NULL;
  struct mpsse_context mpsse;

  assert_int_equal(is_valid(mpsse_ptr), 0);

  assert_int_equal(is_valid(&mpsse), 1);

  // context is valid only when we have object and it is opened
  mpsse.open = 1;
  assert_int_equal(is_valid_context(&mpsse), 1);
}

int main()
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_frequency_manipulation),
    cmocka_unit_test(test_check_timeouts),
     cmocka_unit_test(test_context),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
