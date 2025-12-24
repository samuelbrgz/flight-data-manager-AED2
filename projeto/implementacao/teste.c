#include <stdlib.h>
#include "logs.h"

// funcao apenas para testar o log
int main() {
    // exemplos de como a funcao deve ser utilizada
    registrarLog("matheus", AUTENTICACAO, (LOG_DADOS){.info_auth = {true}}); // passar status do login (true ou false)
    registrarLog("matheus", LIS_ITEM, (LOG_DADOS){0}); // a union é passada vazia quando não há dados

    return 0;
}