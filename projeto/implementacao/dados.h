#ifndef DADOS_H
#define DADOS_H

typedef struct {
    int id; 
    char codigo_voo[10];
    char origem[31];
    char destino[31];
} VIAGEM;

typedef struct No {
    VIAGEM dado;
    struct No* proximo;
} No;


void listarItem(No *inicio, char *usuario);
No* pesquisarItem(No *inicio, char *usuario);
void carregarDados(No **inicio);
void cadastrarViagem(No** inicio, char *usuario);
int verificarDuplicado(No* inicio, int id_procurado);
bool editarItem(No *inicio, char *usuario);
void liberarLista(No **inicio);

#endif