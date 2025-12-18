#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "login.h"

bool login(){

    Usuario digitado;
    Usuario arquivo;

    printf("Digite seu login: ");
    fgets(digitado.login, sizeof(digitado.login), stdin);
    digitado.login[strcspn(digitado.login, "\r\n")] = '\0';
    printf("Digite sua senha: ");
    fgets(digitado.senha, sizeof(digitado.senha), stdin);
    digitado.senha[strcspn(digitado.senha, "\r\n")] = '\0';

    FILE *fp = fopen("usuarios.csv", "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return false;
    }
    
    char linha[120];

    while (fgets(linha, sizeof(linha), fp)) {
        sscanf(linha, "%49[^,],%49s", arquivo.login, arquivo.senha);

        if (strcmp(digitado.login, arquivo.login) == 0 && strcmp(digitado.senha, arquivo.senha) == 0) {
            return true;
            break;
        }
    }

    fclose(fp);
    return false;
}