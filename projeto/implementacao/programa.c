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

}