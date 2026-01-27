#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dados.h"
#include "logs.h"

// include para poder criar uma funçao sleep q funcione tanto em windows, quanto em linux
// include para a função isatty
#ifdef _WIN64
#include <windows.h>
#include <io.h>
#elif __linux__
#include <unistd.h>
#endif

int funcaoIsatty() {
    #ifdef _WIN64
    return _isatty(STDIN_FILENO);
    #elif __linux__
    return isatty(STDIN_FILENO);
    #endif
}

void esperar(int ms)
{
#ifdef _WIN64
    Sleep(ms);
#elif __linux__
    sleep((float)(ms / 1000));
#endif
}

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
            (LOG_DADOS){
                .info_add = {
                    nova.id,
                    "ID Duplicado",
                    false}});
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
            (LOG_DADOS){
                .info_add = {
                    nova.id,
                    NULL,
                    true}});
        // INSERIR LOG DE SUCESSO AQUI
    }
    else
    {
        printf("\n[ERRO] Nao foi possivel acessar a base de dados.\n");
    }
    printf("===================================\n");
}

void listarItem(No *inicio, char *usuario)
{
    printf("\n=================================\n");
    printf("         LISTAR REGISTROS     \n");
    printf("=================================\n");


    No *atual = inicio;
    int posicao = 0;

    while (atual != NULL)
    {
        printf(
            "%d. Id: %d |  Origem: %s | Destino: %s | Codigo: %s\n",
            posicao,
            atual->dado.id,
            atual->dado.origem,
            atual->dado.destino,
            atual->dado.codigo_voo);

        atual = atual->proximo;
        posicao++;
    }

    if (posicao == 0)
    {
        printf("\n==== Sem registros na lista =====\n");
    }

    registrarLog(usuario, LIS_ITEM, (LOG_DADOS){0});
    registrarSaida(SAIDA_LIS_ITEM, (SAIDA_DADOS){.info_lis = inicio});
    printf("=================================\n");
    esperar(3000);
}

No *pesquisarItem(No *inicio, char *usuario)
{
    No *atual = inicio;

    VIAGEM viagem;
    bool viagemEncontrada = false;

    printf("\n=================================\n");
    printf("        PESQUISAR VIAGEM         \n");
    printf("=================================\n");
    printf("ID da Viagem: ");

    char buffer[32];
    int pesquisar;
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &pesquisar) != 1)
    {
        printf("\n[ERRO] Entrada invalida.\n");
        return NULL;
    }

    while (atual != NULL && pesquisar != atual->dado.id)
    {
        atual = atual->proximo;
    }

    if (atual != NULL)
    {
        printf(
            "\n======= VIAGEM ENCONTRADA =======\nID da Viagem: %d\nCodigo do voo: %s\nOrigem: %s\nDestino: %s \n",
            atual->dado.id,
            atual->dado.codigo_voo,
            atual->dado.origem,
            atual->dado.destino);

        viagem = atual->dado;
        viagemEncontrada = true;

        registrarLog(usuario, PESQ_ITEM, (LOG_DADOS) {.info_pesq = {viagem.id, true}});
        registrarSaida(SAIDA_PESQ_ITEM, (SAIDA_DADOS){.info_pesq = {viagem, viagemEncontrada}});
        printf("=================================\n");
        esperar(3000);

        return atual;
    }

    printf("\n====== Voo nao encontrado =======\n");
    registrarLog(usuario, PESQ_ITEM, (LOG_DADOS) {.info_pesq = {viagem.id, false}});
    registrarSaida(SAIDA_PESQ_ITEM, (SAIDA_DADOS){.info_pesq = {viagem, viagemEncontrada}});
    printf("=================================\n");
    esperar(3000);
    return NULL;
}

bool editarItem(No *inicio, char *usuario)
{

    No *atual = pesquisarItem(inicio, usuario);
    if (atual == NULL)
    {
        return false; // para caso a função pesquisar item não ache o item
    }

    VIAGEM viagemEditada, scan;
    char buffer[50]; // buffer temporário para armazenar dentro das structs os dados

    // Necessário para printar o log
    LOG_DADOS info;
    info.info_edit.status = false;

    printf("\n===================================\n");
    printf("       EDICAO DE VIAGEM          \n");
    printf("===================================\n");
    printf("ID da Viagem: ");
    scanf("%d", &viagemEditada.id);
    getchar();

    if (atual->dado.id != viagemEditada.id)
    { // Verificar se o id não está repetido em outro vôo, mas não impedindo de colocar o mesmo id do vôo atual a ser editado
        if (verificarDuplicado(inicio, viagemEditada.id))
        {
            printf("\n[AVISO] O ID %d ja esta em uso.\n", viagemEditada.id);

            info.info_edit.id = viagemEditada.id;
            info.info_edit.motivoDeFalha = "ID Duplicado";

            registrarLog(usuario, EDIT_ITEM, info);
            return false;
        }
    }

    printf("Codigo do Voo: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\r\n")] = '\0';
    strcpy(viagemEditada.codigo_voo, buffer);

    printf("Origem: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\r\n")] = '\0';
    strcpy(viagemEditada.origem, buffer);

    printf("Destino: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\r\n")] = '\0';
    strcpy(viagemEditada.destino, buffer);

    FILE *arquivo = fopen("../dados/base.csv", "r"); // arquivo original aberto para leitura
    FILE *temp = fopen("../dados/temp.csv", "w");    // criação de arquivo temporário para armazenar a edição e depois substitui-la
    if (arquivo != NULL && temp != NULL)
    {
        char linha[120];

        while (fgets(linha, sizeof(linha), arquivo))
        { // laço de repetição que escaneia linha a linha do .csv e compara com o id e codigo de voo
            sscanf(linha, "%d;%49[^;];%49[^;];%49[^\n]", &scan.id, scan.codigo_voo, scan.origem, scan.destino);

            if (scan.id == atual->dado.id && strcmp(scan.codigo_voo, atual->dado.codigo_voo) == 0)
            { // substituindo os dados pelos novos editados
                fprintf(temp, "%d;%s;%s;%s\n", viagemEditada.id, viagemEditada.codigo_voo, viagemEditada.origem, viagemEditada.destino);
            }
            else
            {
                fprintf(temp, "%d;%s;%s;%s\n", scan.id, scan.codigo_voo, scan.origem, scan.destino); // apenas copia os dados não editados
            }
        }
        fclose(temp);
        fclose(arquivo);
        remove("../dados/base.csv");                      // remove a base de dados antiga
        rename("../dados/temp.csv", "../dados/base.csv"); // renomeia o arquivo temporário e transforma na base de dados atual

        info.info_edit.status = true;
        strcpy(info.info_edit.codigo_voo, viagemEditada.codigo_voo);

        registrarLog(usuario, EDIT_ITEM, info);
    }
    else
    {
        printf("\n[ERRO] Nao foi possivel acessar a base de dados.\n");
        return false;
    }
    printf("===================================\n");

    return true;
}

void excluirViagem(No **inicio, char *usuario)
{
    if (!*inicio)
    {
        printf("\n=== Sem registros para excluir ===\n");
        return;
    }

    printf("\n=================================\n");
    printf("       EXCLUSAO DE VIAGEM          \n");
    printf("=================================\n");

    printf("Digite o ID da viagem que deseja remover: ");

    char buffer[32];
    int idAlvo;
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &idAlvo) != 1)
    {
        printf("\n[ERRO] Entrada invalida.\n");
        return;
    }

    No *atual = *inicio;
    No *anterior = NULL;

    // Busca na lista
    while (atual && atual->dado.id != idAlvo)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    // ID nao encontrado
    if (!atual)
    {
        printf("\n====== Voo nao encontrado =======\n");
        registrarLog(usuario, EXC_ITEM, (LOG_DADOS) {.info_exc = {idAlvo, false}});
        esperar(3000);
        return;
    }

    // remoçao na lista
    if (!anterior)
    {
        *inicio = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    free(atual);

    FILE *arquivo = fopen("../dados/base.csv", "w");

    if (arquivo)
    {
        No *temp = *inicio;

        while (temp)
        {
            fprintf(arquivo, "%d;%s;%s;%s\n",
                    temp->dado.id,
                    temp->dado.codigo_voo,
                    temp->dado.origem,
                    temp->dado.destino);
            temp = temp->proximo;
        }
        fclose(arquivo);
        printf("\n[SUCESSO] Registro removido e base atualizada!\n");
        registrarLog(usuario, EXC_ITEM, (LOG_DADOS) {.info_exc = {idAlvo, true}});
    }
    else
    {
        printf("\n[ERRO] Nao foi possivel acessar a base de dados para sobrescrita.\n");
    }
    printf("===================================\n");
}

void liberarLista(No **inicio)
{ // função para limpar a lista na memória do programa em funcionamento
    No *atual = *inicio;
    No *aux;

    while (atual)
    {
        aux = atual;
        atual = atual->proximo;
        free(aux);
    }

    *inicio = NULL; // lista agora está vazia
}