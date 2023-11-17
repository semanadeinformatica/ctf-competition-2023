#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define BUFFER_SIZE 256
#define CENTRAL_FILE "flag.txt"


typedef struct appStorage_ {
  char user_message[BUFFER_SIZE];
  char central_message[BUFFER_SIZE];
} appStorage;

appStorage *init_new_storage() {
  appStorage *storage = (appStorage*) malloc(sizeof(appStorage));

  FILE *file = fopen("flag.txt", "r");
  if (file == NULL)
    strcpy(storage->central_message, "");
  else
    fgets(storage->central_message, BUFFER_SIZE, file);
  fclose(file);

  strcpy(storage->user_message, "");
  return storage;
}

void load_messages(appStorage *storage, char *user_message, char *central_message) {
  strcpy(user_message, storage->user_message);
  strcpy(central_message, storage->central_message);
}

void save_user_message(appStorage *storage, char *user_message) {
  strcpy(storage->user_message, user_message);
}

void wait_for_input() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF) {}
  printf("Press ENTER to continue...");
  fflush(stdout);
  while ((c = getchar()) != '\n' && c != EOF) {}
}

void send_message(appStorage *storage) {
  char c;
  while ((c = getchar()) != '\n' && c != EOF) {}

  char message[BUFFER_SIZE];
  printf("Please enter the message you would like to send:\n");
  fflush(stdout);
  do {
    scanf("%[^\n]", &message);
  } while (message[0] == '\n');
  save_user_message(storage, message);
  
  printf("\nMessage sent sucessfully. ");
  wait_for_input();
  printf("\n\n");
}

void read_user_message(appStorage *storage) {
  char central_message[BUFFER_SIZE];
  char user_message[BUFFER_SIZE];
  load_messages(storage, user_message, central_message);

  if (user_message[0] == '\0') {
    printf("You haven't sent any messages yet.\n\n");
  } else {
    printf("Last message sent:\n");
    printf(user_message);
    printf("\n\n");
  }

  wait_for_input();
  printf("\n\n");
}

void read_central_message(appStorage *storage) {
  char central_message[BUFFER_SIZE];
  char user_message[BUFFER_SIZE];
  load_messages(storage, user_message, central_message);

  // TODO: make authentication.
  // Meanwhile, central_message should never be printed!!!

  printf("Central hasn't sent any messages yet.\n\n");
  wait_for_input();
  printf("\n\n");
}

bool main_menu(appStorage *storage) {
  int option = 0;

  printf("Please choose an option.\n\n");
  printf("[1]: Send message to Central\n");
  printf("[2]: See last message sent\n");
  printf("[3]: See last message from Central\n");
  printf("Enter anything else to exit.\n\n");
  printf("Your option: ");
  fflush(stdout);
  scanf("%d", &option);
  printf("\n\n");

  switch (option) {
    case 1:
      send_message(storage);
      return true;
    case 2:
      read_user_message(storage);
      return true;
    case 3:
      read_central_message(storage);
      return true;
    default:
      return false;
  }
}

int main() {
  appStorage *storage = init_new_storage();

  printf("Welcome to the Central Communication App!\n");
  while (main_menu(storage)) {}
  printf("Exiting the app. ");
  wait_for_input();

  free(storage);
  return 0;
}
