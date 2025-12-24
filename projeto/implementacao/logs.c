#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logs.h"

void registrarLog(char *usuario, LOG_TIPOS tipo, LOG_DADOS *dados) {
    FILE *arquivo = fopen("../dados/logs.csv", "a");

    char tempoFormatado[50];
    char msg[100];

    // pega o tempo atual
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(
        tempoFormatado, 
        sizeof(tempoFormatado), 
        "%d/%02d/%02d - %02d:%02d:%02d",
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec
    );
    
    switch (tipo) {
        case LIS_ITEM: 
            snprintf(msg, sizeof(msg), "O usuário %s listou todos os itens.\n", usuario);
            printf("[%s] %s", tempoFormatado, msg);
            break;
        }
        
    fprintf(arquivo, "%s,%s", tempoFormatado, msg);
    fclose(arquivo);
};
