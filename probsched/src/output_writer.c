#include <stdio.h>
#include "../include/process.h"
#include "../include/timeline.h"

void write_output(Process* processes, int n, const char* algoritmo) {
    FILE* file = fopen("output.txt", "w");
    if (!file) {
        perror("Erro ao abrir output.txt");
        return;
    }

    fprintf(file, "Algoritmo usado: %s\n\n", algoritmo);

    // Gantt Chart
    fprintf(file, "Gantt Chart:\n");
    for (int i = 0; i < timeline_count; i++) {
        fprintf(file, "╔════");
    }
    fprintf(file, "╗\n");

    for (int i = 0; i < timeline_count; i++) {
        fprintf(file, "║ P%-2d", timeline[i].process_id);
    }
    fprintf(file, "║\n");

    for (int i = 0; i < timeline_count; i++) {
        fprintf(file, "╚════");
    }
    fprintf(file, "╝\n");

    fprintf(file, "%d", timeline[0].start);
    for (int i = 0; i < timeline_count; i++) {
        fprintf(file, "    %d", timeline[i].end);
    }
    fprintf(file, "\n\n");

    // Médias
    double total_waiting = 0, total_turnaround = 0;
    for (int i = 0; i < n; i++) {
        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
    }

    fprintf(file, "Average Waiting Time: %.2f\n", total_waiting / n);
    fprintf(file, "Average Turnaround Time: %.2f\n", total_turnaround / n);
    double tempo_total = processes[0].end_time;
for (int i = 1; i < n; i++) {
    if (processes[i].end_time > tempo_total)
        tempo_total = processes[i].end_time;
}
double throughput = (double)n / tempo_total;
fprintf(file, "Throughput: %.2f processos/unidade de tempo\n", throughput);

int deadlines_falhados = 0;
for (int i = 0; i < n; i++) {
    if (processes[i].end_time > processes[i].deadline) {
        deadlines_falhados++;
    }
}
fprintf(file, "Processos fora do prazo (deadline): %d\n", deadlines_falhados);


    fclose(file);
    printf("\n✅ Resultados guardados em 'output.txt'.\n");
    
}
