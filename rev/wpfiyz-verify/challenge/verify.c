#include "stdbool.h"
#include "stdio.h"
#include "string.h"

#define BUFFER_SIZE 256

char S01[] = {-98, 26, 76, -121, -19, -12, -31, 15, -84, 127, 68, 118, -51, -47, 0, 95, 78, 92, -91, -100, -54, -128, 42, -107, 124, -125, -29, -81, -82, 98, 12, 111, -85, 99, 19, 111, 115, -71, -72, -10, 65, 10, 49, -117, 92, 26, 72, -64, -87, 98, -69, 35, 111, 21, -79, -18};

bool login() {
  size_t right_len = sizeof(S01) - 1;
  char buffer[BUFFER_SIZE];
  char mask[] = {-69, -72, -120, -13, -26, -1, -36, -84, -116, 57, 36, 61, 22, -115, -30, -84, -7, -94, 3, -87, 60, -97, 87, 0, 29, -13, 67, 80, -19, -65, 82, 107, -5, 29, 75, 95, 77, 116, -111, 8, -113, 37, 52, 39, -77, -127, -99, -46, 0, -32, -24, 78, 115, 20, 35, -38};

  printf("Insert password: ");
  scanf("%255s", buffer);

  for (int i = right_len - 1; i >= 0; i--)
    S01[i] = S01[i] ^ (S01[i + 1] - 23);

  for (int i = 15, j = 0; ; j += 2) {
    S01[i % (right_len + 1)] ^= mask[i % (right_len + 1)];
    i += 9;
    if (!(i % (right_len + 1) - 15))
      break;
  }

  for (int i = 0; i < right_len + 1; i++)
    S01[i] = (S01[i] + 20 * i) % 128;

  size_t len = strlen(buffer);
  if (len == right_len) {
    if (strcmp(buffer, S01) == 0)
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