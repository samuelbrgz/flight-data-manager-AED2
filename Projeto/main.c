#include <stdio.h>
#include <stdbool.h>
#include "login.h"

int main(){
    
    bool verificar;

    do
    {
        verificar = login();
        if(verificar == true){
            printf("Deu CERTO!");
        }
    } while (!verificar);

}