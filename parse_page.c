#include "file_utils.h"
#include "string_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  printf("input file: %s\n", argv[1]);

  FILE *fptrin, *fptrout;
  char *line;
  char buf[1000];
  char *tag = NULL;
  bool inLink = false;
  bool inText = false;

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
  while ((line = read_line(fptrin)) != NULL) {
    tag = NULL;
    // only take links within text tag
    if (!inText && strstr(line, "<text ") != NULL) {
      inText = true;
    }
    if (inText && (tag = strstr(line, "</text>")) != NULL) {
      // prevents taking links after text close tag on the same line
      tag[0] = '\0';
    }
    if (!inText) {
      continue;
    }
    int len = strlen(line);
    for (int i = 0; i < len; i++) {
      // search for open link
      if (line[i] == '[' && line[i + 1] == '[') {
        inLink = true;
        buf[0] = '\0';
      }
      // search for close link
      if (line[i] == ']' && line[i + 1] == ']' && inLink) {
        inLink = false;
        str_append(buf, sizeof(buf), line[i]);
        str_append(buf, sizeof(buf), line[i + 1]);
        str_append(buf, sizeof(buf), '\n');
        fputs(buf, fptrout);
        buf[0] = '\0';
      }
      if (inLink) {
        str_append(buf, sizeof(buf), line[i]);
      }
    }
    // if a close text tag was found above set inText to false. this is to allow
    // text before the close tag on the same line to be read
    if (tag != NULL) {
      inText = false;
      tag = NULL;
    }
    free(line);
  }
  fclose(fptrin);
  fclose(fptrout);
  return 0;
}
