#include <stdio.h>

char s[3][4];

int main() {
  for (int i = 0; i < 3; i++) {
    scanf("%s", s[i]);
  }
  printf("POMAK L\n");
  fflush(stdout);

  for (int i = 0; i < 3; i++) {
    scanf("%s", s[i]);
  }
  printf("POMAK D\n");
  fflush(stdout);

  for (int i = 0; i < 3; i++) {
    scanf("%s", s[i]);
  }
  printf("POMAK D\n");
  fflush(stdout);

  for (int i = 0; i < 3; i++) {
    scanf("%s", s[i]);
  }
  printf("POMAK R\n");
  fflush(stdout);

  for (int i = 0; i < 3; i++) {
    scanf("%s", s[i]);
  }
  printf("! 4\n");
  fflush(stdout);
  return 0;
}

