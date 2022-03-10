#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float celsius_to_fahrenheit(float);
float celsius_to_kelvin(float);
float fahrenheit_to_celsius(float);
float fahrenheit_to_kelvin(float);
float kelvin_to_celsius(float);
float kelvin_to_fahrenheit(float);

void main(int argc, char *argv[]) {
  int temperature;

  if (argc < 3) {
    printf("Not enough parameters\n");
    exit(1);
  }

  if (!isalpha(argv[1][0])) {
    printf("Format specifier is not a character!\n");
    exit(1);
  }

  for (size_t i = 0; i < strlen(argv[2]); i++) {
    if (!isdigit(argv[2][i])) {
      printf("Specified temperature is not a number!\n");
      exit(1);
    }
  }

  temperature = atoi(argv[2]);

  if (!strcmp(argv[1], "c")) {
    printf("Fahrenheit: %.02f\n", celsius_to_fahrenheit(temperature));
    printf("Kelvin: %.02f\n", celsius_to_kelvin(temperature));
  } else if (!strcmp(argv[1], "f")) {
    printf("Celsius: %.02f\n", fahrenheit_to_celsius(temperature));
    printf("Kelvin: %.02f\n", fahrenheit_to_kelvin(temperature));
  } else if (!strcmp(argv[1], "k")) {
    printf("Celsius: %.02f\n", kelvin_to_celsius(temperature));
    printf("Fahrenheit: %.02f\n", kelvin_to_fahrenheit(temperature));
  } else {
    printf("Specified format is not one of \"c\", \"k\", or \"f\"\n");
  }
}

float celsius_to_fahrenheit(float temperature) {
  return (temperature * (9.0 / 5.0)) + 32;
}

float celsius_to_kelvin(float temperature) { return temperature + 273.15; }

float fahrenheit_to_celsius(float temperature) {
  return ((temperature - 32) * (5.0 / 9.0));
}

float fahrenheit_to_kelvin(float temperature) {
  return celsius_to_kelvin(fahrenheit_to_celsius(temperature));
}

float kelvin_to_celsius(float temperature) { return temperature - 273.15; }

float kelvin_to_fahrenheit(float temperature) {
  return celsius_to_fahrenheit(kelvin_to_celsius(temperature));
}
