#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/process.h"

#include "../include/timeline.h"

TimelineEntry timeline[MAX_TIMELINE];
int timeline_count = 0;


void print_gantt_chart() {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < timeline_count; i++) {
        printf("| P%d ", timeline[i].process_id);
    }
    printf("|\n");

    printf("%d", timeline[0].start);
    for (int i = 0; i < timeline_count; i++) {
        printf("    %d", timeline[i].end);
    }
    printf("\n");
}

void simulate_fcfs(Process *processes, int n) {
    timeline_count = 0;

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        processes[i].start_time = current_time;
        processes[i].end_time = current_time + processes[i].burst_time;
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].end_time - processes[i].arrival_time;

        timeline[timeline_count++] = (TimelineEntry){processes[i].id, processes[i].start_time, processes[i].end_time};

        current_time = processes[i].end_time;

        printf("Processo %d:\n", processes[i].id);
        printf("  Tempo de início: %d\n", processes[i].start_time);
        printf("  Tempo de fim: %d\n", processes[i].end_time);
        printf("  Tempo de espera: %d\n", processes[i].waiting_time);
        printf("  Turnaround time: %d\n\n", processes[i].turnaround_time);
    }
    int deadlines_falhados = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].end_time > processes[i].deadline) {
            deadlines_falhados++;
        }
    }
    printf("❗ Processos fora do prazo (deadline): %d\n", deadlines_falhados);
    
    print_gantt_chart();
}

void simulate_round_robin(Process *processes, int n, int quantum) {
    timeline_count = 0;

    int current_time = 0;
    int done = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
    }

    while (!done) {
        done = 1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].start_time == -1) {
                    processes[i].start_time = current_time;
                }

                int exec_time = (processes[i].remaining_time > quantum) ? quantum : processes[i].remaining_time;

                timeline[timeline_count].process_id = processes[i].id;
                timeline[timeline_count].start = current_time;
                current_time += exec_time;
                timeline[timeline_count].end = current_time;
                timeline_count++;

                processes[i].remaining_time -= exec_time;

                if (processes[i].remaining_time == 0) {
                    processes[i].end_time = current_time;
                    processes[i].waiting_time = processes[i].end_time - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].turnaround_time = processes[i].end_time - processes[i].arrival_time;
                } else {
                    done = 0;
                }
            }
        }

        if (!done) {
            int earliest = -1;
            for (int i = 0; i < n; i++) {
                if (processes[i].remaining_time > 0) {
                    if (earliest == -1 || processes[i].arrival_time < earliest) {
                        earliest = processes[i].arrival_time;
                    }
                }
            }
            if (current_time < earliest) {
                current_time = earliest;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("Processo %d:\n", processes[i].id);
        printf("  Tempo de início: %d\n", processes[i].start_time);
        printf("  Tempo de fim: %d\n", processes[i].end_time);
        printf("  Tempo de espera: %d\n", processes[i].waiting_time);
        printf("  Turnaround time: %d\n\n", processes[i].turnaround_time);
    }
    int deadlines_falhados = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].end_time > processes[i].deadline) {
            deadlines_falhados++;
        }
    }
    printf("❗ Processos fora do prazo (deadline): %d\n", deadlines_falhados);
    
    print_gantt_chart();
}

void simulate_sjf(Process *processes, int n) {
    timeline_count = 0;

    int current_time = 0, completed = 0;
    bool *visited = calloc(n, sizeof(bool));

    while (completed < n) {
        int idx = -1;
        int shortest = 1e9;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].arrival_time <= current_time && processes[i].burst_time < shortest) {
                shortest = processes[i].burst_time;
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        processes[idx].start_time = current_time;
        current_time += processes[idx].burst_time;
        processes[idx].end_time = current_time;
        processes[idx].waiting_time = processes[idx].start_time - processes[idx].arrival_time;
        processes[idx].turnaround_time = processes[idx].end_time - processes[idx].arrival_time;

        timeline[timeline_count++] = (TimelineEntry){processes[idx].id, processes[idx].start_time, processes[idx].end_time};

        visited[idx] = true;
        completed++;
    }

    free(visited);

    for (int i = 0; i < n; i++) {
        printf("Processo %d:\n", processes[i].id);
        printf("  Tempo de início: %d\n", processes[i].start_time);
        printf("  Tempo de fim: %d\n", processes[i].end_time);
        printf("  Tempo de espera: %d\n", processes[i].waiting_time);
        printf("  Turnaround time: %d\n\n", processes[i].turnaround_time);
    }
    int deadlines_falhados = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].end_time > processes[i].deadline) {
            deadlines_falhados++;
        }
    }
    printf("❗ Processos fora do prazo (deadline): %d\n", deadlines_falhados);
    
    print_gantt_chart();
}
