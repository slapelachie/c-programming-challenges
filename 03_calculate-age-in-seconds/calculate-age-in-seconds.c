#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Date {
  int year;
  int month;
  int day;
} Date;

char *get_formatted_dob(char *);
int is_leap_year(int);
int get_max_days_in_month(int, int);
int check_valid_date(Date);
Date get_date_from_string(char *);
int check_valid_dob(Date);
Date get_current_date(void);
int get_max_days_year(int);
int get_days_over_span_years(int, int);
int get_days_since_start_year(Date);
int calculate_age(Date);

char *get_formatted_dob(char *date_of_birth) {
  char *buffer = NULL;
  int buffer_position = 0;
  for (int i = 0; i < strlen(date_of_birth); i++) {
    if (date_of_birth[i] != '-') {
      buffer = (char *)realloc(buffer, buffer_position + 1);
      *(buffer + (buffer_position++)) = date_of_birth[i];
    }
    *(buffer + buffer_position) = '\0';
  }

  if (strlen(buffer) != 8) {
    return NULL;
  }

  for (int i = 0; i < strlen(buffer); i++) {
    if (!isdigit(buffer[i])) {
      return NULL;
    }
  }

  return buffer;
}

int is_leap_year(int year) { return (year % 4 == 0) && !(year % 100 == 0); }

int get_max_days_in_month(int month, int leap_year) {
  if (leap_year && month == 2) {
    return 29;
  }

  return 28 + ((month + (int)(month / 8)) % 2) + (2 % month) +
         (2 * (int)(1 / month));
}

int check_valid_date(Date date) {
  int leap_year = is_leap_year(date.year);
  int max_month_days = get_max_days_in_month(date.month, leap_year);

  if (date.month < 0 || date.month > 12) {
    return 0;
  }

  if (date.day < 0 || date.day > max_month_days) {
    return 0;
  }

  return 1;
}

Date get_date_from_string(char *date_of_birth) {
  char *year_buffer = (char *)malloc(sizeof(char) * 4);
  char *month_buffer = (char *)malloc(sizeof(char) * 2);
  char *day_buffer = (char *)malloc(sizeof(char) * 2);
  Date date;

  strncpy(year_buffer, date_of_birth, sizeof(char) * 4);
  strncpy(month_buffer, date_of_birth + (sizeof(char) * 4), sizeof(char) * 2);
  strncpy(day_buffer, date_of_birth + (sizeof(char) * 6), sizeof(char) * 2);

  date.year = atoi(year_buffer);
  date.month = atoi(month_buffer);
  date.day = atoi(day_buffer);

  if (!date.year || !date.month || !date.day) {
    printf("Not a valid string!\n");
    exit(1);
  }

  return date;
}

Date get_current_date(void) {
  Date date;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  date.year = tm.tm_year + 1900;
  date.month = tm.tm_mon + 1;
  date.day = tm.tm_mday;

  return date;
}

int get_days_since_start_year(Date date) {
  int days = 0;
  for (int i = 1; i < date.month; i++) {
    days += get_max_days_in_month(i, is_leap_year(date.year));
  }
  days += (date.day - 1);
  return days;
}

int get_max_days_year(int year) { return is_leap_year(year) ? 366 : 365; }

int get_days_over_span_years(int start_year, int end_year) {
  int days = 0;
  for (int i = start_year + 1; i < end_year; i++) {
    days += get_max_days_year(i);
  }
  return days;
}

int calculate_age(Date date_of_birth) {
  Date current_date = get_current_date();

  int dob_year_max_days = get_max_days_year(date_of_birth.year);
  int dob_year_days =
      dob_year_max_days - get_days_since_start_year(date_of_birth);
  int current_year_days = get_days_since_start_year(current_date);

  if ((current_date.year - date_of_birth.year) == 0) {
    return current_year_days - get_days_since_start_year(date_of_birth);
  } else if ((current_date.year - date_of_birth.year) == 1) {
    return current_year_days + dob_year_days;
  } else if ((current_date.year - date_of_birth.year) > 1) {
    return get_days_over_span_years(date_of_birth.year, current_date.year) +
           dob_year_days + current_year_days;
  } else {
    return 0;
  }
}

int main(int argc, char *argv[]) {
  Date date_of_birth;
  int age;

  do {
    char buffer[12];
    char *formatted_dob;

    printf("What is your date of birth? ");
    if (fgets(buffer, 12, stdin)) {
      buffer[strcspn(buffer, "\n")] = '\0';
      formatted_dob = get_formatted_dob(buffer);
      if (!formatted_dob) {
        continue;
      }
      date_of_birth = get_date_from_string(formatted_dob);
    }
  } while (!check_valid_date(date_of_birth));

  age = calculate_age(date_of_birth) * 24 * 60 * 60;

  printf("Seconds since %d-%02d-%02d: %d\n", date_of_birth.year,
         date_of_birth.month, date_of_birth.day, age);

  return 0;
}
