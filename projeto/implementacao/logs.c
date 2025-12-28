#include <stdio.h>
#include <time.h>
#include "logs.h"

void registrarLog(char *usuario, LOG_TIPOS tipo, LOG_DADOS dados) {
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
        case AUTENTICACAO:
            // verificação se o login foi realizado com sucesso
            if (dados.info_auth.status) {
                snprintf(msg, sizeof(msg), "O usuário logou-se como \"%s\" com sucesso!\n", usuario);
            } else {
                snprintf(msg, sizeof(msg), "Houve uma tentativa de login como \"%s\", porém sem sucesso.\n", usuario);
            };
            break;
        case LIS_ITEM: 
            snprintf(msg, sizeof(msg), "O usuário %s listou todos os itens.\n", usuario);
            break;
        case ENCERRAR:
            snprintf(msg, sizeof(msg), "O usuário %s encerrou o programa.\n", usuario);
            break;
    }

    // opção para printar no terminal (opcional)
    // printf("[%s] %s", tempoFormatado, msg);
        
    // o log será armazenado no seguinte formato .csv
    // [data],[mensagem do log]
    fprintf(arquivo, "%s,%s", tempoFormatado, msg);
    fclose(arquivo);
};
