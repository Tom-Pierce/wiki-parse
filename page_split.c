#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"

void close_file(FILE *fptr, char *path) {
  if (fclose(fptr) != 0) {
    printf("error closing file %s\n", path);
  }
}

int main(int argc, char *argv[]) {

  const char *open_tag = "<page>";
  const char *close_tag = "</page>";

  if (argc < 3) {
    printf("Usage: page_split <filename> <output directory>");
    return 1;
  }
  printf("splitting %s, saving in %s\n", argv[1], argv[2]);

  FILE *fptrin, *fptrout;
  char *line;
  char *output_start = NULL;
  char *output_end = NULL;
  int in_page = 0;
  char path[512];
  int page_count = 1;

  fptrin = fopen(argv[1], "r");
  if (!fptrin) {
    perror(argv[1]);
    return 1;
  }

  while ((line = read_line(fptrin)) != NULL) {
    if (!in_page) {
      // search for first open tag
      output_start = strstr(line, open_tag);
      if (output_start) {
        path[0] = '\0';
        snprintf(path, sizeof(path), "%s/%i%s", argv[2], page_count, ".txt");
        fptrout = fopen(path, "w");
        if (!fptrout) {
          fclose(fptrin);
          perror(argv[2]);
          return 1;
        }
        fputs(output_start, fptrout);
        fputs("\n", fptrout);
        in_page = 1;
      }
    } else {
      // when in a page print search for close tag
      output_end = strstr(line, close_tag);
      if (output_end) {
        // if close tag found make sure to only print up to the close tag and
        // nothing past it on the same line
        in_page = 0;
        // get length between start of line and the end of the close tag
        size_t length = (output_end - line) + strlen(close_tag);
        char *temp = malloc(length + 1);
        if (!temp) {
          return 1;
        }
        memcpy(temp, line, length);
        temp[length] = '\0';
        fputs(temp, fptrout);
        free(temp);
        fputs("\n", fptrout);
        close_file(fptrout, path);
        page_count++;
      } else {
        // add current line to output file
        fputs(line, fptrout);
        fputs("\n", fptrout);
      }
    }
    free(line);
  }
  if (in_page) {
    printf("last file has no closing tag: %s - deleting file\n", path);
    close_file(fptrout, path);
    remove(path);
  } else {
    close_file(fptrout, path);
  }
  close_file(fptrin, argv[1]);
  return 0;
}
