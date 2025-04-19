#include <stdio.h>
#include "scheduler.h"
#include "generator.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <ficheiro_config>\n", argv[0]);
        return 1;
    }

    // TODO: Ler ficheiro de configuração
    // TODO: Gerar/processar lista de processos
    // TODO: Invocar algoritmo de escalonamento
    // TODO: Apresentar estatísticas

    printf("Simulador ProbSched iniciado com config: %s\n", argv[1]);
    return 0;
}
