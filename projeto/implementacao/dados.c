#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "dados.h"
#include "logs.h"

No *criarNo(VIAGEM v)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
        return NULL;

    novo->dado = v;
    novo->proximo = NULL;

    return novo;
}

void inserirNoFinal(No **inicio, VIAGEM v)
{
    No *novo = criarNo(v);
    if (novo == NULL)
        return;

    if (*inicio == NULL)
    {
        *inicio = novo;
        return;
    }

    No *atual = *inicio;
    while (atual->proximo != NULL)
    {
        atual = atual->proximo;
    }

    atual->proximo = novo;
}

void carregarDados(No **inicio)
{
    // persistência em arquivo .csv
    FILE *arquivo = fopen("../dados/base.csv", "r");
    if (arquivo == NULL)
        return;

    VIAGEM v;
    // Transfere dados do arquivo para a memória principal
    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^\n]\n", &v.id, v.codigo_voo, v.origem, v.destino) != EOF)
    {
        inserirNoFinal(inicio, v);
    }
    fclose(arquivo);
}

int verificarDuplicado(No *inicio, int id_procurado)
{
    No *atual = inicio;
    while (atual != NULL)
    {
        if (atual->dado.id == id_procurado)
            return 1; // Chave deve ser única
        atual = atual->proximo;
    }
    return 0;
}

void cadastrarViagem(No **inicio, char *usuario)
{
    VIAGEM nova;

    printf("\n===================================\n");
    printf("       CADASTRO DE VIAGEM          \n");
    printf("===================================\n");

    printf("ID da Viagem: ");
    
    char buffer[32];
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &nova.id) != 1)
    {
        printf("\n[ERRO] Entrada invalida.\n");
        return;
    }
    

    if (verificarDuplicado(*inicio, nova.id))
    {
        printf("\n[AVISO] O ID %d ja esta em uso.\n", nova.id);
        // INSERIR LOG DE ERRO (ID DUPLICADO) AQUI
        registrarLog(
            usuario, 
            ADD_ITEM, 
            (LOG_DADOS) {
                .info_add = {
                    nova.id,
                    "Id Duplicado",
                    false
                }
            }
        );
        printf("===================================\n");
        return;
    }

    printf("Codigo do Voo: ");
    fgets(nova.codigo_voo, sizeof(nova.codigo_voo), stdin);
    nova.codigo_voo[strcspn(nova.codigo_voo, "\n")] = '\0';

    printf("Origem: ");
    fgets(nova.origem, sizeof(nova.origem), stdin);
    nova.origem[strcspn(nova.origem, "\n")] = '\0';

    printf("Destino: ");
    fgets(nova.destino, sizeof(nova.destino), stdin);
    nova.destino[strcspn(nova.destino, "\n")] = '\0';

    FILE *arquivo = fopen("../dados/base.csv", "a");
    if (arquivo != NULL)
    {
        fprintf(arquivo, "%d;%s;%s;%s\n", nova.id, nova.codigo_voo, nova.origem, nova.destino);
        fclose(arquivo);

        inserirNoFinal(inicio, nova); // Atualiza a lista na memória principal

        printf("\n[SUCESSO] Viagem registrada com sucesso!\n");
        registrarLog(
            usuario, 
            ADD_ITEM, 
            (LOG_DADOS) {
                .info_add = {
                    nova.id,
                    NULL,
                    true
                }
            }
        );
        // INSERIR LOG DE SUCESSO AQUI
    }
    else
    {
        printf("\n[ERRO] Nao foi possivel acessar a base de dados.\n");
    }
    printf("===================================\n");
}


void listaritem(No *inicio, char *usuario){
    No *atual = inicio;
    int posicao = 0;
    while(atual != NULL){
        printf("%d. |%d|  Origem: %s | Destino: %s | Codigo: %s\n",posicao, atual->dado.id,atual->dado.origem,atual->dado.destino,atual->dado.codigo_voo);
        atual=atual->proximo;
        posicao++;
    }
    Sleep(5000);
}

No* pesquisaritem(No *inicio, char *usuario){
    No *atual = inicio;
    char pesquisar[10];
    printf("===== Pesquisar Viagem =====\nCódigo do voo:");
    fgets(pesquisar, sizeof(pesquisar), stdin);
    pesquisar[strcspn(pesquisar, "\n")] = '\0';

    while(atual != NULL && strcmp(pesquisar,atual->dado.codigo_voo) != 0){
        atual=atual->proximo;
        }
    if(atual != NULL ){
        printf("===Voo encontrado===\nID:%d\nOrigem: %s\nDestino: %s \nCodigo: %s\n", atual->dado.id,atual->dado.origem,atual->dado.destino,atual->dado.codigo_voo);
        Sleep(5000);
        return atual;
    }
    printf("===Voo não encontrado===\n");
    Sleep(5000);
    
}