#include <stdio.h>
#include <stdbool.h>
#include "autenticacao.h"
#include "logs.h"

int main(){
    
    Validar usuario; // puxar o usuário da sessão por aqui
    do
    {
        usuario = login(); //função de autenticação em autenticacao.c
    } while (!usuario.status);

    //menu

    int escolha = 0; // Inicializei para evitar lixo de memória

    while (escolha != 6) {
        printf("\n1. Cadastrar novo item\n2. Listar registros\n3. Pesquisar registro\n");
        printf("4. Editar registro\n5. Excluir registro\n6. Encerrar o programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                // cadastrar
                break;
            case 2:
                // listar
                break;
            case 3:
                // pesquisar
                break;
            case 4:
                // editar
                break;
            case 5:
                // excluir
                break;
            case 6:
                // encerrar
               
                break;
            default:
                break;
        }
    }
}