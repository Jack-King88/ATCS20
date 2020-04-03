#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <stdbool.h>


# define NUM_BYTES 10000
# define BUFFER_SIZE 500000


bool clean(char* file, char* bf, int file_length){
  int j = 0;
  int paren_count = 0;
  for (int i = 0; i < file_length; i++) {
    char chr = file[i];
    if ((chr == '<') || (chr == '>') || (chr == '+') || (chr == '-') || (chr == '*') || (chr == ')') || (chr == '(')) {
      bf[j] = chr;
      j++;
      if (chr == '(') {
        paren_count++;
      }
      if (chr == ')') {
        paren_count--;
      }
      if (paren_count < 0){
        return false;
      }
    }
  }

  if (paren_count != 0) {
    return false;
  } else {
    return true;
  }
}


void interpret(char* bf){
  char bags[NUM_BYTES];
  int bf_index = 0;
  int bag_index = 0;

  char rune = bf[bf_index];
  while ((rune == '<') || (rune == '>') || (rune == '+') || (rune == '-') || (rune == '*') || (rune == ')') || (rune == '(')) {
    if (rune == '>'){
        if (bag_index == NUM_BYTES - 1) {
          printf("Wrapping Error\n");
          exit(1);
        }
				bf_index++;
        bag_index++;
		}
		else if(rune == '<') {
      if (bag_index == 0) {
        printf("Wrapping Error\n");
        exit(1);
      }
      bf_index++;
      bag_index--;
		}
		else if(rune == '+') {
			bags[bag_index]++;
      bf_index++;
    }
		else if(rune == '-') {
			bags[bag_index]--;
			bf_index++;
		}
		else if(rune == '(') {
			if ((int)bags[bag_index] == 0)	{
				while(rune != ')') {
					bf_index++;
          rune = bf[bf_index];
				}
			}
      bf_index++;
		}
		else if(rune == ')') {
			if((int)bags[bag_index] > 0)	{
				while(rune != '(') {
          bf_index--;
          rune = bf[bf_index];
				}
			}
			else {
				bf_index++;
			}
		}
		else if(rune == '*')
		{
			printf("%c", bags[bag_index]);
			bf_index++;
		}
    rune = bf[bf_index];
  }
}

int main(int argc, char** argv) {
  char file[BUFFER_SIZE];

  char* filename = argv[1];
  FILE* fp = fopen(filename, "r");
  if (fp == NULL)  {
    printf("Uh oh, couldn't open file! \n");
    exit(1);
  }

  fread(file, 1, BUFFER_SIZE, fp);
  fclose(fp);

  int file_length = strlen(file);
  char bf[file_length];

  if (!clean(file, bf, file_length)) {
    printf("Paranthesis error buddy");
    exit(1);
  } else {
    interpret(bf);
  }
}
