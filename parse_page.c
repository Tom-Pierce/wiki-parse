#include "string_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO only take links from within the <text> tags, might be able to reuse the
// page_split functions

int main(int argc, char *argv[]) {

  printf("input file: %s\n", argv[1]);

  FILE *fptrin, *fptrout;
  int c;
  char prevChar;
  char buf[1000];
  bool atLink = false;

  fptrin = fopen(argv[1], "r");
  fptrout = fopen(argv[2], "w");

  if (!fptrin) {
    perror(argv[1]);
    return 1;
  }
  if (!fptrout) {
    perror(argv[2]);
    return 1;
  }
  while ((c = fgetc(fptrin)) != -1) {
    // at double [
    if (c == 91 && prevChar == 91) {
      if (atLink) {
        buf[0] = '\0';
      }
      str_append(buf, sizeof(buf), c);
      atLink = true;
      // at double ]
    } else if (c == 93 && prevChar == 93 && atLink) {
      atLink = false;
      str_append(buf, sizeof(buf), c);
      str_append(buf, sizeof(buf), '\n');
      fputs(buf, fptrout);
      buf[0] = '\0';
    }
    if (atLink) {
      str_append(buf, sizeof(buf), c);
    }
    prevChar = c;
  }

  fclose(fptrin);
  fclose(fptrout);
  return 0;
}
