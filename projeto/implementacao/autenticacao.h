#ifndef LOGIN_H
#define LOGIN_H
#define TAM 50
#include <stdbool.h>

typedef struct {
    char login[TAM];
    char senha[TAM];
} Usuario; // declaração da struct que armazenará os dados digitados pelo usuário e lidos no csv

typedef struct{
    bool status;
    char usuario[TAM];
} Validar; // para verificar o status do login e salvar o usuário logado


Validar login(void);

#endif