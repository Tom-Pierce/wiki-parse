#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void appendStr(char *str, int max, char c){
  int len = strlen(str);
  if(len + 1 < max){
    str[len] = c;
    str[len + 1] = '\0';
  } 
}

int main(int argc, char *argv[]) {

  printf("input file: %s\n", argv[1]);

  FILE *fptrin, *fptrout;
  int c;
  char prevChar;
  char buf[1000];
  bool atLink = false;

  fptrin = fopen(argv[1], "r");
  fptrout = fopen(argv[2], "w");

  if (fptrin == NULL) {
    printf("terminating, file could not be found\n");
    return 0;
  } else {
    while ((c = fgetc(fptrin)) != -1) {
      // at double [
      if (c == 91 && prevChar == 91) {
        if (atLink) {
          buf[0] = '\0';
        }
        appendStr(buf, sizeof(buf), c);
        atLink = true;
        // at double ]
      } else if (c == 93 && prevChar == 93 && atLink) {
        atLink = false;
        appendStr(buf, sizeof(buf), c);
        appendStr(buf, sizeof(buf), '\n');
        fputs(buf, fptrout);
        buf[0] = '\0';

      }
      if (atLink) {
        appendStr(buf, sizeof(buf), c);
      }
      prevChar = c;
    }
  }

  fclose(fptrin);
  fclose(fptrout);
  return 0;
}
