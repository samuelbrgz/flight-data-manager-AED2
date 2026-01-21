#include <stdio.h>
#include <time.h>
#include "logs.h"

void registrarLog(char *usuario, LOG_TIPOS tipo, LOG_DADOS dados) {
    FILE *arquivo = fopen("../dados/logs.csv", "a");

    if (!arquivo) {
        printf("Erro ao abrir arquivo de logs.\n");
        return;
    }

    char tempoFormatado[50];
    char msg[180];

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
        case ADD_ITEM:
            if (dados.info_add.status) {
                snprintf(msg, sizeof(msg), "O usuário %s cadastrou uma nova viagem com o id %d.\n", usuario, dados.info_add.id);
            } else {
                snprintf(
                    msg, 
                    sizeof(msg), 
                    "O usuário %s tentou realizar um cadastro da viagem de id %d, porém sem sucesso. (Motivo: %s)\n", 
                    usuario, 
                    dados.info_add.id, 
                    dados.info_add.motivoDeFalha
                );
            }
            break;
        case LIS_ITEM: 
            snprintf(msg, sizeof(msg), "O usuário %s listou todas as viagens.\n", usuario);
            break;
        case PESQ_ITEM:
            if (dados.info_pesq.status) {
                snprintf(
                    msg, 
                    sizeof(msg), 
                    "O usuário %s procurou pela viagem de código \"%s\". A viagem foi encontrada com sucesso!\n", 
                    usuario, 
                    dados.info_pesq.codigo
                );
            } else {
                snprintf(
                    msg, 
                    sizeof(msg), 
                    "O usuário %s procurou pela viagem de código \"%s\". Nenhum resultado encontrado.\n", 
                    usuario, 
                    dados.info_pesq.codigo
                );
            }
            break;
        case EDIT_ITEM:
            if (dados.info_edit.status) {
                snprintf(
                    msg, 
                    sizeof(msg),
                    "O usuário %s editou a viagem de código \"%s\".\n",
                    usuario,
                    dados.info_edit.codigo_voo
                );
            } else {
                snprintf(
                    msg, 
                    sizeof(msg),
                    "O usuário %s tentou editar uma viagem, no entanto inseriu o id \"%d\". (%s).\n",
                    usuario,
                    dados.info_edit.id,
                    dados.info_edit.motivoDeFalha
                ); 
            }
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

void registrarSaida(SAIDA_TIPOS tipo, SAIDA_DADOS dados) {
    FILE *arquivo = fopen("../saida/saida.csv", "w");

    if (!arquivo) {
        printf("Erro ao abrir arquivo de saída.\n");
        return;
    }

    switch (tipo) {
        case SAIDA_LIS_ITEM:
            No *atual = dados.info_lis.inicio;
            int posicao = 0;
            
            while(atual != NULL){
                fprintf(
                    arquivo, 
                    "%d. Id: %d |  Origem: %s | Destino: %s | Codigo: %s\n",
                    posicao, 
                    atual->dado.id,
                    atual->dado.origem,
                    atual->dado.destino,
                    atual->dado.codigo_voo
                );

                atual=atual->proximo;
                posicao++;
            }

            if(posicao == 0){
                fprintf(arquivo, "\n===Sem registros na lista===\n");
            }

            break;
        case SAIDA_PESQ_ITEM:
            if (!dados.info_pesq.status) {
                fprintf(arquivo, "===Voo não encontrado===\n");
                break;
            }

            fprintf(
                arquivo,
                "ID: %d\nOrigem: %s\nDestino: %s \nCodigo: %s\n", 
                dados.info_pesq.viagem.id,
                dados.info_pesq.viagem.origem,
                dados.info_pesq.viagem.destino,
                dados.info_pesq.viagem.codigo_voo
            );

            break;
    }

    fclose(arquivo);
};