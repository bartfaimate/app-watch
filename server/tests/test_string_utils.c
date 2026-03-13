
#include "string_utils.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

static void test_strip() {
  printf("test_strip...\n");
  char *s = strip("   hello world   ");

  if (s) {
      assert(strcmp("hello world", s) == 0);
      free(s);
  }

  s = strip("hello world   ");

  if (s) {
      assert(strcmp("hello world", s) == 0);
      free(s);
  }

  s = strip("hello world \n  ");

  if (s) {
      assert(strcmp("hello world", s) == 0);
      free(s);
  }
  
}

static void test_lower() {
  printf("test_lower...\n");

  char *res;
  res = lower("HELLO WORLD");

  if(res) {
    assert(strcmp("hello world", res) == 0);
    free(res);
  }

  res = lower("hello world");

  if(res) {
    assert(strcmp("hello world", res) == 0);
    free(res);

  }

  res = lower("heLlo wORLd");

  if(res) {
    assert(strcmp("hello world", res) == 0);
    free(res);
  }

}


int main() {

  test_strip();
  test_lower();
  return 0;
}