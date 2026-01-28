#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "autenticacao.h"
#include "logs.h"
#include "dados.h"

int main(void)
{
    No *lista = NULL;
    carregarDados(&lista); // carrega os dados do arquivo base e insere na lista
    int escolha = 0;

    Validar usuario; // puxar o usuário da sessão por aqui

    printf("\n=============================================\n");
    printf("       PROGRAMA DE TRANSPORTE AEREO          \n");
    printf("=============================================\n");

    do
    {
        usuario = login(); // função de autenticação em autenticacao.c
        if (!funcaoIsatty() && !usuario.status) exit(0); // verificação se o arquivo foi executado
                                                                // no modo input interativo, ou via .txt
                                                                // caso seja via .txt para a execução ao errar login
    } while (!usuario.status);
    
    // menu

    while (escolha != 6)
    {

        printf("\n=================================\n");
        printf("           MENU PRINCIPAL        \n");
        printf("=================================\n");
        printf(" 1 - Cadastrar viagem\n");
        printf(" 2 - Listar registros\n");
        printf(" 3 - Pesquisar registro\n");
        printf(" 4 - Editar registro\n");
        printf(" 5 - Excluir registro\n");
        printf(" 6 - Encerrar o programa\n");
        printf("=================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &escolha) != 1)
        {
            printf("Opcao invalida.\n");
            while (getchar() != '\n')
                ; // limpa buffer
            continue;
        }
        getchar();

        switch (escolha)
        {
        case 1:
            cadastrarViagem(&lista, usuario.usuario);
            break;

        case 2:
            // especifico para casos de testes
            if (!funcaoIsatty()) {
                int listaVazia;  // 1 = lista vazia
                                 // 0 = lista preenchida

                scanf("%d", &listaVazia);
                
                if (listaVazia == 1) {
                    liberarLista(&lista);
                }
            }

            listarItem(lista, usuario.usuario);
            break;

        case 3:
            pesquisarItem(lista, usuario.usuario);
            break;

        case 4:
            editarItem(lista, usuario.usuario);
            liberarLista(&lista);
            carregarDados(&lista);
            break;

        case 5:
            excluirViagem(&lista, usuario.usuario);
            break;

        case 6:
            printf("Encerrando o programa...\n");
            registrarLog(usuario.usuario, ENCERRAR, (LOG_DADOS) {0});
            break;

        default:
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}
