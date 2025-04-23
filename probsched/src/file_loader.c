#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/process.h"

Process* read_processes_from_file(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o ficheiro");
        exit(EXIT_FAILURE);
    }

    int capacity = 10;
    *count = 0;
    Process* processes = malloc(capacity * sizeof(Process));

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n' || line[0] == '#') continue; // ignora linhas vazias e comentários

        if (*count >= capacity) {
            capacity *= 2;
            processes = realloc(processes, capacity * sizeof(Process));
        }

        Process p;
        if (sscanf(line, "%d %d %d %d %d", &p.id, &p.arrival_time, &p.burst_time, &p.priority, &p.deadline) == 5) {
            p.remaining_time = p.burst_time;
            p.start_time = -1;
            p.end_time = -1;
            processes[(*count)++] = p;
        }
    }

    fclose(file);
    return processes;
}
