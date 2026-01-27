#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "autenticacao.h"
#include "logs.h"

Validar login(){

    Usuario digitado;
    Usuario arquivo;
    Validar validar; // variável de apoio para identificar se digitou o login correto e retornar o usuario
    validar.status = false;

    printf("Digite seu login: ");
    fgets(digitado.login, sizeof(digitado.login), stdin);
    digitado.login[strcspn(digitado.login, "\r\n")] = '\0';
    printf("Digite sua senha: ");
    fgets(digitado.senha, sizeof(digitado.senha), stdin);
    digitado.senha[strcspn(digitado.senha, "\r\n")] = '\0';
    strcpy(validar.usuario, digitado.login);

    FILE *fp = fopen("../dados/usuarios.csv", "r"); // arquivo csv está em outra pasta
    if (!fp) {
        printf("[ERRO] Nao foi possivel abrir o arquivo para leitura.\n");
        return validar;
    }
    
    char linha[120];

    while (fgets(linha, sizeof(linha), fp)) { // laço de repetição que escaneia linha a linha do .csv e compara com o login e senha digitados
        sscanf(linha, "%49[^,],%49s", arquivo.login, arquivo.senha);

        if (strcmp(digitado.login, arquivo.login) == 0 && strcmp(digitado.senha, arquivo.senha) == 0) {
            validar.status = true;
        }
    }

    if (validar.status == false)
    {
        printf("\n[AVISO] Login ou senha incorretos...\n\n");
        registrarLog(validar.usuario, AUTENTICACAO, (LOG_DADOS){.info_auth = validar.status});
    }
    else
    {
        printf("\n%s entrou no sistema!\n", digitado.login);
        registrarLog(validar.usuario, AUTENTICACAO, (LOG_DADOS){.info_auth = validar.status});
    }

    fclose(fp);
    return validar; // para poder finalizar o laço de repetição no programa principal.
}