#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

void init() {
  printf("Initializing...");
  fflush(stdout);
  sleep(3);
  putchar('\n');
}

void create_robot() {
  printf("Creating new robot...");
  fflush(stdout);
  sleep(6);
  putchar('\n');
}

void train_robot() {
  puts("Training robot...");
  fflush(stdout);
  sleep(1);
  const char* program = getenv("TRAIN_PROG");
  if (program == NULL) {
    puts("Environment variable TRAIN_PROG was not specified, check programs/ folder.");
    printf("Meanwhile, this robot might not be so bright...");
    fflush(stdout);
    putchar('\n');
  } else {
    printf("Executing training program \"%s\"\n", program);
    fflush(stdout);
    system(program);
  }
}

void finish() {
  sleep(5);
  puts("Done! Your robot is ready to use.");
}

int main() {
  init();
  create_robot();
  train_robot();
  finish();
  
  return 0;
}