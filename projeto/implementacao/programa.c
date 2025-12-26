#include <stdio.h>
#include <stdbool.h>
#include "autenticacao.h"

int main(){
    
    bool verificar;
    do
    {
        verificar = login(); //função de autenticação em autenticacao.c
    } while (!verificar);

}