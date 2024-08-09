#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int id, AT, BT, CT, TAT, WT, RT, prio, remT;
} pro;

pro p[15];

void prioP(int n)
{
    int tTAT = 0, tWT = 0, tRT = 0, curTime = 0, remP = n, minIndex, minPrio, delay = 0;
    float aTAT = 0, aWT = 0, aRT = 0;
    printf("\nGantt chart:\n");

    while (remP)
    {
        minIndex = -1;
        minPrio = 99999;
        for (int i = 0; i < n; i++)
        {
            if (p[i].remT && p[i].AT <= curTime && (p[i].prio < minPrio || (p[i].prio == minPrio && p[i].AT < p[minIndex].AT)))
            {
                minIndex = i;
                minPrio = p[i].prio;
            }
        }
        if (minIndex == -1)
        {
            delay++;
            curTime++;
            continue;
        }
        if (delay > 0)
        {
            printf("| ideal till %d", curTime);
            delay = 0;
        }
        if (p[minIndex].remT == p[minIndex].BT)
        {
            p[minIndex].RT = curTime - p[minIndex].AT;
            tRT += p[minIndex].RT;
        }
        p[minIndex].remT--;
        curTime++;
        printf("|%d P%d %d", (curTime - 1), p[minIndex].id, curTime);
        if (p[minIndex].remT == 0)
        {
            p[minIndex].CT = curTime;
            p[minIndex].TAT = p[minIndex].CT - p[minIndex].AT;
            p[minIndex].WT = p[minIndex].TAT - p[minIndex].BT;
            tTAT += p[minIndex].TAT;
            tWT += p[minIndex].WT;
            remP--;
        }
    }
    printf("|\nObservation table:\nPID\tAT\tBT\tP \tCT\tTAT\tWT\tRT");
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
    printf("\nEnter AT, BT, and priority of processes:\n");
    printf("AT BT Priority\n");
    for (int i = 0; i < n; i++)
    {
        p[i].id = (i + 1);
        scanf("%d %d %d", &p[i].AT, &p[i].BT, &p[i].prio);
        p[i].remT = p[i].BT;
    }
    prioP(n);
    return 0;
}
