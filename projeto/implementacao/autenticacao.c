#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "autenticacao.h"

bool login(){

    bool verificar = false; // variável de apoio para identificar se digitou o login correto

    Usuario digitado;
    Usuario arquivo;

    printf("Digite seu login: ");
    fgets(digitado.login, sizeof(digitado.login), stdin);
    digitado.login[strcspn(digitado.login, "\r\n")] = '\0';
    printf("Digite sua senha: ");
    fgets(digitado.senha, sizeof(digitado.senha), stdin);
    digitado.senha[strcspn(digitado.senha, "\r\n")] = '\0';

    FILE *fp = fopen("..\\dados\\usuarios.csv", "r"); // arquivo csv está em outra pasta
    if (!fp) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return false;
    }
    
    char linha[120];

    while (fgets(linha, sizeof(linha), fp)) { // laço de repetição que escaneia linha a linha do .csv e compara com o login e senha digitados
        sscanf(linha, "%49[^,],%49s", arquivo.login, arquivo.senha);

        if (strcmp(digitado.login, arquivo.login) == 0 && strcmp(digitado.senha, arquivo.senha) == 0) {
            verificar = true;
        }
    }

    if (verificar == false)
    {
        printf("\nLogin ou senha incorretos...\n");
    }
    else
    {
        printf("\n%s entrou no sistema!\n", digitado.login);
    }

    fclose(fp);
    return verificar; // para poder finalizar o laço de repetição no programa principal.
}