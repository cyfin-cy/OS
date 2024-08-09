#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int id, AT, BT, CT, TAT, WT, RT, prio, fins;
} pro;

pro p[15];

void prioN(int n)
{
    int tTAT = 0, tWT = 0, tRT = 0, curTime = 0, remP = n, minIndex, minPrio;
    float aTAT = 0, aWT = 0, aRT = 0;
    printf("\nGantt chart:\n");

    while (remP)
    {
        minIndex = -1;
        minPrio = 99999;
        for (int i = 0; i < n; i++)
        {
            if (!p[i].fins && p[i].AT <= curTime && (p[i].prio < minPrio || (p[i].prio == minPrio && p[i].AT < p[minIndex].AT)))
            {
                minIndex = i;
                minPrio = p[i].prio;
            }
        }
        if (minIndex == -1)
        {
            printf("|%d *** %d ", curTime, ++curTime);
        }
        else
        {
            p[minIndex].RT = curTime - p[minIndex].AT;
            int temp = curTime;
            curTime += p[minIndex].BT;
            p[minIndex].CT = curTime;
            p[minIndex].TAT = p[minIndex].CT - p[minIndex].AT;
            p[minIndex].WT = p[minIndex].TAT - p[minIndex].BT;
            tTAT += p[minIndex].TAT;
            tRT += p[minIndex].RT;
            tWT += p[minIndex].WT;
            printf("|%d P%d %d", temp, p[minIndex].id, curTime);
            remP--;
            p[minIndex].fins = 1;
        }
    }
    printf("|\nObservation table:\nPID\tAT\tBT\tP\tCT\tTAT\tWT\tRT");
    for (int i = 0; i < n; i++)
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", p[i].id, p[i].AT, p[i].BT, p[i].prio, p[i].CT, p[i].TAT, p[i].WT, p[i].RT);

    aTAT = (float)tTAT / n;
    aWT = (float)tWT / n;
    aRT = (float)tRT / n;
    printf("\nAvg TAT: %f\nAvg WT: %f\nAvg RT: %f", aTAT, aWT, aRT);
}

int main()
{
    int n;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    if (n > 15)
    {
        printf("Number of processes exceeds the array limit of 15.\n");
        return 1;
    }
    printf("\nEnter AT, BT, and Priority of processes:\n");
    printf("AT BT Priority\n");
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].prio);
        p[i].fins = 0;
    }

    prioN(n);
    return 0;
}
