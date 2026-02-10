# Flight Data Manager - AED2

Sistema de informação para gestão de transporte aéreo desenvolvido como Trabalho Prático para a disciplina de **Algoritmos e Estruturas de Dados II** (UFMT).

## 🛠 Estrutura do Projeto

O projeto segue a hierarquia de diretórios exigida:

* **/implementacao**: Código-fonte em C com modularização por TADs (.h e .c).
* **/dados**: Arquivos de persistência (.csv) para registros, usuários e logs.
* **/testes**: Casos de teste (CT) para execução automatizada.
* **/saida**: Arquivo `saida.csv` para persistência de resultados de consulta.

## 🚀 Compilação e Execução

Para compilar o projeto no Linux utilizando o `gcc`:

```bash
cd implementacao
gcc -o programa programa.c logs.c dados.c autenticacao.c -Wall
