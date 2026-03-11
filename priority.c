#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char pid[10];
    int at, bt, pr;
    int remaining;
    int wt, tat;
    int completed;
} Process;

int main() {
    int n;
    scanf("%d", &n);

    Process p[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].remaining = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
        p[i].completed = 0;
    }

    int time = 0, done = 0;
    int finish_time[MAX];

    // Find total time needed (max possible end time)
    int total_bt = 0;
    for (int i = 0; i < n; i++) total_bt += p[i].bt;

    while (done < n) {
        // Find highest priority process that has arrived and is not completed
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time) {
                if (idx == -1 || p[i].pr > p[idx].pr) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // No process available, advance time
            time++;
            continue;
        }

        // Run the selected process for 1 unit
        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {
            p[idx].completed = 1;
            finish_time[idx] = time;
            p[idx].tat = finish_time[idx] - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done++;
        }
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].wt);
    }

    printf("\nTurnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].tat);
    }

    double avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
