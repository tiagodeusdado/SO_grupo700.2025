#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generator.h"
#include "scheduler.h"
#include "file_loader.h"
#include "output_writer.h"

double calcular_cpu_utilization(Process* processes, int n, int tempo_total) {
    int tempo_ocupado = 0;
    for (int i = 0; i < n; i++) {
        tempo_ocupado += processes[i].burst_time;
    }
    return 100.0 * tempo_ocupado / tempo_total;
}

int calcular_tempo_total(Process* processes, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].end_time > max) {
            max = processes[i].end_time;
        }
    }
    return max;
}

void reset_processes(Process* dest, Process* src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        dest[i].remaining_time = src[i].burst_time;
        dest[i].start_time = -1;
        dest[i].end_time = -1;
    }
}

int main() {
    int count;
    int quantum = 4;
    char algoritmo[10];
    char modo[10];

    printf("Modo de geração (file/random): ");
    scanf("%s", modo);

    Process* base;

    if (strcmp(modo, "file") == 0) {
        base = read_processes_from_file("input.txt", &count);
        if (count == 0) {
            printf("❌ Nenhum processo foi carregado. Verifica o ficheiro input.txt.\n");
            return 1;
        }
        printf("\nProcessos lidos do ficheiro:\n");
    } else {
        printf("Quantos processos queres gerar? ");
        scanf("%d", &count);
        base = generate_processes(count);
        printf("\nProcessos gerados aleatoriamente:\n");
    }

    for (int i = 0; i < count; i++) {
        printf("P%d | Chegada: %d | Burst: %d | Prioridade: %d | Deadline: %d\n",
               base[i].id, base[i].arrival_time, base[i].burst_time, base[i].priority, base[i].deadline);
    }

    printf("\nEscolhe o algoritmo (fcfs, rr, sjf): ");
    scanf("%s", algoritmo);

    Process* processos = malloc(sizeof(Process) * count);
    reset_processes(processos, base, count);

    if (strcmp(algoritmo, "fcfs") == 0) {
        printf("\n== FCFS ==\n");
        simulate_fcfs(processos, count);
        write_output(processos, count, "FCFS");
    } else if (strcmp(algoritmo, "rr") == 0) {
        printf("\n== Round Robin ==\n");
        simulate_round_robin(processos, count, quantum);
        write_output(processos, count, "Round Robin");
    } else if (strcmp(algoritmo, "sjf") == 0) {
        printf("\n== SJF ==\n");
        simulate_sjf(processos, count);
        write_output(processos, count, "SJF");
    } else {
        printf("Algoritmo inválido.\n");
        free(base);
        free(processos);
        return 1;
    }

    int tempo_total = calcular_tempo_total(processos, count);
    double utilizacao = calcular_cpu_utilization(processos, count, tempo_total);
    printf("CPU Utilization: %.2f%%\n", utilizacao);

    double throughput = (double) count / tempo_total;
    printf("Throughput: %.2f processos por unidade de tempo\n", throughput);
    
    free(base);
    free(processos);
    return 0;
}
