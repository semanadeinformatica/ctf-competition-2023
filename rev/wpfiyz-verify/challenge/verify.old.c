#include "stdbool.h"
#include "stdio.h"
#include "string.h"

#define BUFFER_SIZE 256

char S01[] = {-41, -54, 122, 47, -18, -93, -7, -26, -66, -46, -20, -23, -1, 11, 82, -14, -30, 121, -48, -83, -122, -32, 122, -28, 29, -5, -51, 121, -67, -110, 48, -29, -113, -18, -20, -44, 0};

bool login() {
  size_t right_len = sizeof(S01) - 1;
  char buffer[BUFFER_SIZE];
  char mask[] = {-41, 95, -111, -18, -111, 83, -39, -93, 106, -91, 75, -4, 83, -85, 70, 30, -39, 65, 81, -38, 43, -83, 11, 84, -69, -95, 29, -61, -24, 65, 96, 88, -125, 24, -26, 124};

  printf("Insert password: ");
  scanf("%256s", buffer);

  for (int i = right_len - 1; i >= 0; i--)
    S01[i] = S01[i] ^ (S01[i + 1] - 23);
  // for (int i = 0; i < right_len; i++)
  //   flag[i] = (flag[i] + 20) ^ ();

  for (int i = 14, j = 0; ; j += 2) {
    S01[i % right_len] ^= mask[i % right_len];
    i += 5;
    if (!(i % right_len - 14))
      break;
  }

  for (int i = 0; i < right_len; i++)
    S01[i] = (S01[i] + 20 * i) % 128;

  size_t len = strlen(buffer);
  if (len == right_len) {
    if (strcmp(S01, buffer) == 0)
      return true;
    else
      return false;
  } else {
    return false;
  }
}

int main() {
  puts(login() ? "Access granted" : "Access denied");
  return 0;
}