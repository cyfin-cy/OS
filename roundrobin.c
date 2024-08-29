#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int id, AT, BT, CT, TAT, WT, RT, remT, flag;
} pro;

pro p[15];

void roundRobin(int n) {
    int totalTAT = 0, totalWT = 0, totalRT = 0, curTime = 0, curIndex = 0, timeQuantum, remainingProcesses = n;
    float avgTAT, avgWT, avgRT;
    int queue[20], front = 0, rear = 0;

    // Add the first process to the queue
    queue[rear] = curIndex;
    rear = (rear + 1) % 20;

    // Get time quantum from the user
    printf("\nEnter the time quantum: ");
    scanf("%d", &timeQuantum);

    printf("\nGantt chart: \n0| ");

    while (remainingProcesses > 0) {
        // Wait until the queue has a process
        while (front == rear) {
            curTime++;
            printf(" ** %d| ", curTime);
            for (int i = 1; i < n && p[i].AT <= curTime; i++) {
                if (!p[i].flag && p[i].remT > 0) {
                    queue[rear] = i;
                    p[i].flag = 1;
                    rear = (rear + 1) % 20;
                }
            }
        }

        curIndex = queue[front];
        front = (front + 1) % 20;

        p[curIndex].flag = 1;

        if (p[curIndex].AT > curTime) {
            curTime = p[curIndex].AT;
            printf(" ** %d| ", curTime);
        }

        if (p[curIndex].remT == p[curIndex].BT) {
            p[curIndex].RT = curTime - p[curIndex].AT;
            totalRT += p[curIndex].RT;
        }

        if (p[curIndex].remT > timeQuantum) {
            curTime += timeQuantum;
            p[curIndex].remT -= timeQuantum;
            printf(" P%d  %d | ", p[curIndex].id, curTime);
        } else {
            curTime += p[curIndex].remT;
            p[curIndex].remT = 0;
            printf(" P%d  %d | ", p[curIndex].id, curTime);
        }

        for (int i = 1; i < n && p[i].AT <= curTime; i++) {
            if (!p[i].flag && p[i].remT > 0) {
                queue[rear] = i;
                p[i].flag = 1;
                rear = (rear + 1) % 20;
            }
        }

        if (p[curIndex].remT == 0) {
            p[curIndex].CT = curTime;
            p[curIndex].TAT = p[curIndex].CT - p[curIndex].AT;
            p[curIndex].WT = p[curIndex].TAT - p[curIndex].BT;
            totalWT += p[curIndex].WT;
            totalTAT += p[curIndex].TAT;
            remainingProcesses--;
        } else {
            queue[rear] = curIndex;
            rear = (rear + 1) % 20;
        }
    }

    avgTAT = (float)totalTAT / n;
    avgWT = (float)totalWT / n;
    avgRT = (float)totalRT / n;

    // Print the results
    printf("\n\nObservation table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT, p[i].RT);
    }

    printf("\nAverage TAT: %.2f\nAverage WT: %.2f\nAverage RT: %.2f\n", avgTAT, avgWT, avgRT);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("\nEnter AT and BT for processes\n");
    printf("AT BT\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].remT = p[i].BT;
        p[i].flag = 0;
    }

    // Sort processes by Arrival Time (AT)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].AT > p[j + 1].AT) {
                pro temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    roundRobin(n);

    return 0;
}
