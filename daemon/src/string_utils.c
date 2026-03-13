#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strip(char *input) {

  if (input == NULL || strlen(*input) == 0) {
    return "";
  }
  char *result;
  result = malloc((strlen(*input) + 1) * sizeof(char));
  if (result == NULL) {
    printf("ERROR allocating");
  }

  int begin_pos = 0;
  int end_pos = strlen(*input);

  /* search for first non whitespace char */
  while (isspace(*input + begin_pos)) {
    begin_pos++;
  }

  /* search for last non whitespace char */
  while (isspace(*input + end_pos)) {
    end_pos--;
  }

  /* copy string to result between begin and end */
  strncpy( *result, *input+begin_pos, end_pos-begin_pos );;

}