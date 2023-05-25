#ifndef USER_AUTH_H
#define USER_AUTH_H

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

typedef struct {
  char username[MAX_USERNAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char *username, const char *password);
void createUser(const char *username, const char *password);
int menuAuth();

#endif // USER_AUTH_H
