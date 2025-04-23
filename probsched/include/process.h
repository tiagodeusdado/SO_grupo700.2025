#ifndef F53D5A2C_2CBE_4341_AEC0_A2E332B5C88B
#define F53D5A2C_2CBE_4341_AEC0_A2E332B5C88B

// Exemplo de definição correta da struct Process
typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int start_time;
    int end_time;         
    int waiting_time;       
    int turnaround_time;  
    int deadline;
} Process;


#endif /* F53D5A2C_2CBE_4341_AEC0_A2E332B5C88B */
