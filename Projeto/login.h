#ifndef LOGIN_H
#define LOGIN_H
#define TAM 50
#include <stdbool.h>

typedef struct {
    char login[TAM];
    char senha[TAM];
} Usuario;

bool login(void);

#endif