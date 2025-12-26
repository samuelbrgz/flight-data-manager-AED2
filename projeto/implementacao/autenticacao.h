#ifndef LOGIN_H
#define LOGIN_H
#define TAM 50
#include <stdbool.h>

typedef struct {
    char login[TAM];
    char senha[TAM];
} Usuario; // declaração da struct que armazenará os dados digitados pelo usuário e lidos no csv

bool login(void);

#endif