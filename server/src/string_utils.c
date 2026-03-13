#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strip(char *input) {

  if (input == NULL || strlen(input) == 0) {
    return strdup("");
  }


  char *begin = input;
  /* strlen from begin address till end of string  */
  const char *end = begin + strlen(begin);

  /* search for first non whitespace char */
  while (*begin && isspace(*begin )) {
    begin++;
  }
  /* remove trailing whitespace */
  while (end > begin && isspace((unsigned char)*(end - 1)))
      end--;

  size_t len = end - begin;

  char *result = malloc(len + 1);
  if (!result)
      return NULL;

  memcpy(result, begin, len);
  result[len] = '\0';

  return result;
}


char *lower(char* input ) {

  char* result = malloc(strlen(input)+1);
  int i = 0;
  while (*input )
  {
    result[i] = tolower((unsigned char) *input);
    i++;
    input++;
  }
  return result;
}
