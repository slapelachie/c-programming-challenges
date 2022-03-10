#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FIRSTNAME_FILE "firstnames.txt"
#define LASTNAME_FILE "lastnames.txt"

int get_names_from_file(char **, char *);
const char *rand_string(char **, int);
const char *username_generator(char *, char *);

void main(void) {
  srand((unsigned)time(NULL));

  char **first_names = (char **)malloc(sizeof(char *) * 32);
  char **last_names = (char **)malloc(sizeof(char *) * 32);
  int nfirst_names = get_names_from_file(first_names, FIRSTNAME_FILE);
  int nlast_names = get_names_from_file(last_names, LASTNAME_FILE);

  // Need to assign the length of the string, set to 32 char
  char *first_name = (char *)malloc(sizeof(char) * 32);
  char *last_name = (char *)malloc(sizeof(char) * 32);

  // Convert from const char* to char* safely
  strcpy(first_name, rand_string(first_names, nfirst_names));
  strcpy(last_name, rand_string(last_names, nlast_names));

  printf("Name: %s %s\n", first_name, last_name);
  printf("Username: %s\n", username_generator(first_name, last_name));
}

int get_names_from_file(char **namesptr, char *filename) {
  int nnames = 0;

  FILE *fin = fopen(filename, "r");
  if (fin == NULL) {
    printf("ERROR: Could not open file\n");
    exit(-1);
  }

  // Read line and get rid of the newline char
  size_t len = 0;
  char *line = NULL;
  while ((getline(&line, &len, fin)) != -1) {
    char *newline = strchr(line, '\n');
    if (newline) {
      *newline = '\0';
    }

    // Allocate space and copy the string to that line, might have been cleaned
    // up?
    *(namesptr + nnames) = (char *)malloc(sizeof(line));
    strcpy(*(namesptr + (nnames++)), line);
  }

  return nnames - 1;
}

const char *rand_string(char **strings, int length) {
  return strings[(rand() % length)];
}

const char *username_generator(char *first_name, char *last_name) {
  char *username = (char *)malloc(sizeof(char) * 32);
  strncpy(username, first_name, 1);
  strcat(username, last_name);

  for (size_t i = 0; i < strlen(username); ++i) {
    username[i] = tolower(username[i]);
  }

  return username;
}
