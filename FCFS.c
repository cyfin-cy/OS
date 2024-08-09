#include <stdio.h>

typedef struct node
{
    int pid, AT, BT, CT, TAT, RT, WT;
} Process;

void fcfs(Process[], int);

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];

    for (int i = 0; i < n; i++)
    {
        printf("AT\t\tBT\n");
        scanf("%d\t\t%d", &processes[i].AT, &processes[i].BT);
        processes[i].pid = i + 1;
        printf("\n");
    }
    // sorting
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (processes[i].AT > processes[i + 1].AT)
            {
                int temp = processes[i].pid;
                processes[i].pid = processes[i + 1].pid;
                processes[i + 1].pid = temp;
            }
        }
    }
    fcfs(processes, n);
    return 0;
}

void fcfs(Process processes[], int n)
{
    int ET = 0, totalWT = 0, totalTAT = 0, totalRT = 0;
    float avgWT = 0, avgTAT = 0, avgRT = 0;

    printf("\nGant chart: \n");

    for (int i = 0; i < n; i++)
    {
        if (processes[i].AT > ET)
            ET = processes[i].AT;

        int temp = ET;

        processes[i].RT = ET - processes[i].AT;
        ET = ET + processes[i].BT;
        processes[i].CT = ET;
        processes[i].TAT = processes[i].CT - processes[i].AT;
        processes[i].WT = processes[i].TAT - processes[i].BT;
        totalWT += processes[i].WT;
        totalRT += processes[i].RT;
        totalTAT += processes[i].TAT;
        printf("|(%d) %d (%d)", temp, processes[i].pid, ET);
    }

    printf("\nObservation table: \n");
    printf("PID\t AT\t BT\t CT\t TAT\t RT\t WT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\n", processes[i].pid, processes[i].AT, processes[i].BT, processes[i].CT, processes[i].TAT, processes[i].RT, processes[i].WT);
    }
    avgTAT = totalTAT / n;
    avgRT = totalRT / n;
    avgWT = totalWT / n;
    printf("The average WT, TAT and BT are: %f\t%f\t%f\n", avgWT, avgTAT, avgRT);
}
