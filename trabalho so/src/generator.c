#include <stdlib.h>
#include <stdio.h>
#include "generator.h"

Process* generate_processes(int count) {
    Process* list = malloc(sizeof(Process) * count);
    for (int i = 0; i < count; i++) {
        list[i].id = i;
        list[i].arrival_time = i * 2; // placeholder
        list[i].burst_time = 5 + rand() % 10;
        list[i].priority = rand() % 5;
    }
    return list;
}
