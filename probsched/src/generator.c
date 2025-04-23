#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "generator.h"
#include "../include/process.h"

// Distribuição Exponencial
static double exponencial(double lambda) {
    double u = (double) rand() / RAND_MAX;
    return -log(1 - u) / lambda;
}

Process* generate_processes(int count) {
    Process* list = malloc(sizeof(Process) * count);
    int tempo_chegada = 0;
    for (int i = 0; i < count; i++) {
        list[i].id = i;

        double chegada = exponencial(0.5); // lambda menor = chegadas mais espaçadas
        tempo_chegada += (int)(chegada + 0.5);
        list[i].arrival_time = tempo_chegada;

        double burst = exponencial(0.3);
        list[i].burst_time = (int)(burst + 1); // mínimo de 1 unidade

        list[i].priority = rand() % 5;

        list[i].remaining_time = list[i].burst_time;
        list[i].start_time = -1;
        list[i].end_time = -1;
        list[i].deadline = list[i].arrival_time + list[i].burst_time + 10; // prazo fictício
    }
    return list;
}
