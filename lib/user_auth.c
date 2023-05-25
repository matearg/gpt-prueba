#include "user_auth.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int authenticateUser(const char *username, const char *password) {
  FILE *file = fopen("users.dat", "rb");
  if (file == NULL) {
    printf("Error al abrir el archivo de usuarios.\n");
    return 0;
  }

  User user;
  while (fread(&user, sizeof(User), 1, file) == 1) {
    if (strcmp(user.username, username) == 0 &&
        strcmp(user.password, password) == 0) {
      fclose(file);
      return 1; // Usuario y contraseña coinciden
    }
  }

  fclose(file);
  return 0; // Usuario o contraseña incorrectos
}

void createUser(const char *username, const char *password) {
  FILE *file = fopen("users.dat", "ab");
  if (file == NULL) {
    printf("Error al abrir el archivo de usuarios.\n");
    return;
  }

  User user;
  strncpy(user.username, username, MAX_USERNAME_LENGTH);
  strncpy(user.password, password, MAX_PASSWORD_LENGTH);

  fwrite(&user, sizeof(User), 1, file);
  fclose(file);

  printf("Usuario creado exitosamente.\n");
  printf("\nPresione Enter para continuar...");
  getchar(); // Capturar el salto de línea anterior
  getchar(); // Esperar a que el usuario presione Enter
}

static int validateInput(const char *input, const char *pattern) {
  regex_t regex;
  int reti = regcomp(&regex, pattern, REG_EXTENDED);
  if (reti != 0) {
    printf("Error al compilar la expresión regular.\n");
    return 0;
  }

  reti = regexec(&regex, input, 0, NULL, 0);
  regfree(&regex);
  return (reti == 0);
}

int menuAuth() {
  char username[MAX_USERNAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
  while (1) {
    printf("Ingrese su nombre de usuario (o 'salir' para terminar): ");
    scanf("%s", username);

    if (strcmp(username, "salir") == 0) {
      printf("Hasta luego.\n");
      printf("\nPresione Enter para continuar...");
      getchar(); // Capturar el salto de línea anterior
      getchar(); // Esperar a que el usuario presione Enter
      return 0;
      break;
    }

    if (!validateInput(username, "^[a-zA-Z0-9]+$")) {
      printf(
          "Nombre de usuario inválido. Solo se permiten letras y números.\n");
      printf("\nPresione Enter para continuar...");
      getchar(); // Capturar el salto de línea anterior
      getchar(); // Esperar a que el usuario presione Enter
      continue;
    }

    printf("Ingrese su contraseña: ");
    scanf("%s", password);

    if (!validateInput(password, "^[a-zA-Z0-9]+$")) {
      printf("Contraseña inválida. Solo se permiten letras y números.\n");
      printf("\nPresione Enter para continuar...");
      getchar(); // Capturar el salto de línea anterior
      getchar(); // Esperar a que el usuario presione Enter
      continue;
    }

    if (authenticateUser(username, password)) {
      printf("¡Bienvenido, %s!\n", username);
      printf("\nPresione Enter para continuar...");
      getchar(); // Capturar el salto de línea anterior
      getchar(); // Esperar a que el usuario presione Enter
      break;
    } else {
      printf(
          "Usuario o contraseña incorrectos. ¿Desea crear una cuenta? (s/n): ");
      char response;
      scanf(" %c", &response);

      if (response == 's' || response == 'S') {
        createUser(username, password);
        break;
      }
    }
  }
  return 1;
}
