#ifndef LOGS_H
#define LOGS_H
#include <stdbool.h>
#include "dados.h"

// indica qual tipo de log será printado
typedef enum {
    AUTENTICACAO,
    ADD_ITEM,
    LIS_ITEM,
    PESQ_ITEM,
    EDIT_ITEM,
    EXC_ITEM,
    ENCERRAR
} LOG_TIPOS;

typedef struct {
    bool status; // indica se a tentativa de login foi bem sucedida
} LOG_TIPO_AUTENTICACAO;

typedef struct {
    int id;
    char *motivoDeFalha; // mensagem para identificar o erro durante a ação
    bool status; // indica se o item foi adicionado com, ou sem sucesso
} LOG_TIPO_ADD_ITEM;

// typedef struct {
//     // não possui requisitos para printar
// } LOG_TIPO_LIS_ITEM;

typedef struct {
    char codigo[10];
    bool status;
} LOG_TIPO_PESQ_ITEM;

typedef struct {
    int id; // id do item a ser modificado
    bool status;
    char codigo_voo[10];
    char *motivoDeFalha;
} LOG_TIPO_EDIT_ITEM;

typedef struct {
    int id;
    bool status; // indica se o item foi excluído com, ou sem sucesso
} LOG_TIPO_EXC_ITEM;

// typedef struct {
//     // não possui requisitos para printar
// } LOG_TIPO_ENCERRAR;

typedef union {
    LOG_TIPO_AUTENTICACAO info_auth;
    LOG_TIPO_ADD_ITEM info_add;
    LOG_TIPO_PESQ_ITEM info_pesq;
    LOG_TIPO_EDIT_ITEM info_edit;
    LOG_TIPO_EXC_ITEM info_exc;
} LOG_DADOS;

typedef enum {
    SAIDA_LIS_ITEM,
    SAIDA_PESQ_ITEM
} SAIDA_TIPOS;

typedef struct {
    No *inicio;
} SAIDA_TIPO_LIS_ITEM;

typedef struct {
    VIAGEM viagem;
    bool status;
} SAIDA_TIPO_PESQ_ITEM;

typedef union {
    SAIDA_TIPO_LIS_ITEM info_lis;
    SAIDA_TIPO_PESQ_ITEM info_pesq;
} SAIDA_DADOS;

void registrarLog(char *usuario, LOG_TIPOS tipo, LOG_DADOS dados);
void registrarSaida(SAIDA_TIPOS tipo, SAIDA_DADOS dados);

#endif