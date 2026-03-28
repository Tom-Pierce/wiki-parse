#include "file_utils.h"
#include "string_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  const char *open_tag = "<title>";
  const char *close_tag = "</title>";
  FILE *fptr;
  char *line;
  char *title = NULL;
  char *title_start, *title_end;

  fptr = fopen(argv[1], "r");
  if (!fptr) {
    perror(argv[1]);
  }

  while ((line = read_line(fptr)) != NULL && !title) {
    title_start = strstr(line, open_tag);
    if (title_start) {
      title_end = strstr(line, close_tag);
      if (!title_end) {
        printf("multi line title in file: %s\n", argv[1]);
        return 0;
      }
      char *temp;
      temp = str_slice(title_start, title_end);
      title = temp + strlen(open_tag);
      printf("page title: %s\n", title);
      close_file(fptr, argv[1]);
      rename(argv[1], title);
      perror("help");
      free(temp);
    }
  }
  return 0;
}
