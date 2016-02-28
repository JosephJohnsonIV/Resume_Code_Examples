/*
Joseph Johnson IV
Simulation of an OS CPU Scheduler
COP 4600 - Operating Systems
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Defining values that will be recurring throughout my program
#define MAX_PROCESSES 20
#define MAX_PARAM 5
#define NAME_INDEX 0
#define ARRIVAL_INDEX 1
#define BURST_INDEX 2
#define PRIORITY_INDEX 3
#define EXECUTED_INDEX 4


// Function that takes in a sorted list of processes, the number of processes in the list, and an output file pointer.
void FCFS (int processList[MAX_PROCESSES][MAX_PARAM], int numProcesses, FILE *fp2)
{
    int i, currentTime = processList[0][ARRIVAL_INDEX];

    fprintf(fp2, "\nFCFS\n----------\n");

    // The array passed to this function is sorted by arrival time so all we have to do is print the properly formated output to the file
    for (i = 0; i < numProcesses; i++)
    {
        fprintf(fp2, "P%d runs from %d-%d\n", processList[i][NAME_INDEX], currentTime, (currentTime + processList[i][BURST_INDEX]));
        currentTime = currentTime + processList[i][BURST_INDEX];
    }

}

// Function that takes in a sorted list of processes, the number of processes in the list, and a file pointer to an output file.
void SJF (int processList[MAX_PROCESSES][MAX_PARAM], int numProcesses, FILE *fp2)
{
    // This function uses two counters, a variable to track time, and a variable to store the shortest job's burst time.
    int i = 0, j, temp, shortest = 9999999, currentTime = processList[0][ARRIVAL_INDEX];

    fprintf(fp2, "\nSJF\n----------\n");

    // Since the array is sorted by arrival time and guaranteed to have unique arrival times, we know the first entry goes first
    fprintf(fp2, "P%d runs from %d-%d\n", processList[i][NAME_INDEX], currentTime, (currentTime + processList[i][BURST_INDEX]));
    currentTime = currentTime + processList[i][BURST_INDEX];

    // Making sure to flag this process as executed
    processList[i][EXECUTED_INDEX] = 1;

    for (i = 1; i < numProcesses; i++)
    {
        // If there is a lag between the last finished process and the next we have to idle for that time.
        if (currentTime < processList[i][ARRIVAL_INDEX])
        {
            currentTime = processList[i][ARRIVAL_INDEX];
            fprintf(fp2, "P%d runs from %d-%d\n", processList[i][NAME_INDEX], currentTime, (currentTime + processList[i][BURST_INDEX]));

            // Setting the time to the turnaround time for the executed process and marking it executed
            currentTime = currentTime + processList[i][BURST_INDEX];
            processList[i][EXECUTED_INDEX] = 1;
            continue;
        }

        // If there is no lag, then we need to search for the shortest process available
        for (j = 0; j < numProcesses; j++)
        {
            if ( (processList[j][EXECUTED_INDEX] == 0) && (currentTime >= processList[j][ARRIVAL_INDEX]) && (shortest > processList[j][BURST_INDEX]) )
                {
                    temp = j;
                    shortest = processList[j][BURST_INDEX];
                }
        }

        fprintf(fp2, "P%d runs from %d-%d\n", processList[temp][NAME_INDEX], currentTime, (currentTime + processList[temp][BURST_INDEX]));

        // Setting the time to the turnaround time for the new process, marking it executed and resetting the shortest variable
        currentTime = currentTime + processList[temp][BURST_INDEX];
        processList[temp][EXECUTED_INDEX] = 1;
        shortest = 999999;
    }
}

// Function that takes a sorted list of processes, the numbe rof processes in the list, the rounr robin time quantum, and a file pointer to an output file
void RR (int processList[MAX_PROCESSES][MAX_PARAM], int numProcesses, int quantum, FILE *fp2)
{
    // Need a counter, a variable for the max time needed, the current time, and a array to hold the remaining time for each process
    int i, neededTime = 0, currentTime = processList[0][ARRIVAL_INDEX], remainingTime[MAX_PROCESSES];

    fprintf(fp2, "\nRR with quantum time of %d\n----------\n", quantum);

    // initializing the needed time, remaining times, and executed flags
    for (i = 0; i < numProcesses; i++)
    {
        neededTime = neededTime + processList[i][BURST_INDEX];
        remainingTime[i] = processList[i][BURST_INDEX];
        processList[i][EXECUTED_INDEX] = 0;
    }

    // We will continue RR until we have hit the max time needed to execute all processes
    while(currentTime < neededTime)
    {
        for (i = 0; i < numProcesses; i++)
        {
            // if the process we are looking at has not been executed we can check it
            if (processList[i][EXECUTED_INDEX] == 0)
            {
                //if the process will finish during the quantum we have to handle it differently
                if (quantum <= remainingTime[i])
                {
                    fprintf(fp2, "P%d runs from %d-%d\n", processList[i][NAME_INDEX], currentTime, (currentTime + quantum));
                    currentTime = currentTime + quantum;
                    remainingTime[i] = remainingTime[i] - quantum;

                    if (remainingTime[i] == 0)
                        processList[i][EXECUTED_INDEX] = 1;
                }

                // if the process will not finish during the quantum we do not mark it executed
                else if (quantum > remainingTime[i])
                {
                    fprintf(fp2, "P%d runs from %d-%d\n", processList[i][NAME_INDEX], currentTime, (currentTime + remainingTime[i]));
                    currentTime = currentTime + remainingTime[i];
                    remainingTime[i] = 0;
                    processList[i][EXECUTED_INDEX] = 1;
                }
            }
        }
    }
}

void preEmptivePriority (int processList[MAX_PROCESSES][MAX_PARAM], int numProcesses, FILE *fp2)
{
    int i, j, preEmpted = 0, currentTime = processList[0][ARRIVAL_INDEX], neededTime = 0, remainingTime[MAX_PROCESSES];

    fprintf(fp2, "\nPre-emptive Priority\n----------\n");

    for(i = 0; i < numProcesses; i++)
    {
        neededTime = neededTime + processList[i][BURST_INDEX];
        remainingTime[i] = processList[i][BURST_INDEX];
        processList[i][EXECUTED_INDEX] = 0;
    }

    while(currentTime < neededTime)
    {
        for (i = 0; i < numProcesses; i++)
        {

            preEmpted = 0;

            if (processList[i][EXECUTED_INDEX] == 1)
                continue;

            for (j = 0; j < numProcesses; j++)
            {
                if ((processList[j][EXECUTED_INDEX] == 0) && (processList[i][PRIORITY_INDEX] > processList[j][PRIORITY_INDEX]))
                {
                    preEmpted = 1;

                    if (currentTime < processList[j][ARRIVAL_INDEX])
                    {
                        fprintf(fp2, "P%d runs from %d-%d\n", processList[i][NAME_INDEX], currentTime, processList[j][ARRIVAL_INDEX]);

                        remainingTime[i] = remainingTime[i] - (processList[j][ARRIVAL_INDEX] - currentTime);
                        currentTime = processList[j][ARRIVAL_INDEX];

                        if (remainingTime[i] == 0)
                            processList[i][EXECUTED_INDEX] = 1;

                        i = j - 1;
                    }
                    break;
                }
            }

            if (preEmpted != 1)
            {
                fprintf(fp2, "P%d runs from %d-%d\n", processList[i][NAME_INDEX], currentTime, (currentTime + remainingTime[i]));

                currentTime = currentTime + remainingTime[i];
                remainingTime[i] = 0;
                processList[i][EXECUTED_INDEX] = 1;

            }

        }
    }
}

void arrivalSort(int processList[MAX_PROCESSES][MAX_PARAM], int numProcesses)
{
    int i, j, k, temp;

        for (i = 0; i < numProcesses; i++)
    {
        for (j = 0; j < (numProcesses - 1) - i; j++)
        {
            if (processList[j][ARRIVAL_INDEX] > processList[j + 1][ARRIVAL_INDEX])
            {
                for (k = 0; k < MAX_PARAM; k++)
                {
                    temp = processList[j][k];
                    processList[j][k] = processList[j+1][k];
                    processList[j+1][k] = temp;
                }
            }
        }
    }
}

int main (int argc, char *argv[])
{
	int processList[MAX_PROCESSES][MAX_PARAM];
	int tempArrival, tempBurst, tempPriority, numProcesses, timeQuantum, i = 0;

	char fileName[100], tempName[4], tempAlgorithm[20];

	FILE *fp = fopen(argv[1], "r");
	FILE *fp2 = fopen("Output.txt", "w");

	if (fp == 0) {
		printf("Error: File name not passed as command line argument. \nPlease enter the file name: ");
		scanf("%s", fileName);

		fp = fopen(fileName, "r");
	}

	if (fp ==0) {
		printf("Error: File not found.");
		return 0;
	}

	// Will scan each line until a scan does not pick up a string and three integers
	while (fscanf(fp, "%s %d %d %d", tempName, &tempArrival, &tempBurst, &tempPriority) == 4)
	{
	    if (strlen(tempName) > 2)
            processList[i][NAME_INDEX] = tempName[1] - '0' + tempName[2] - '0';
        else
            processList[i][NAME_INDEX] = tempName[1] - '0';

		processList[i][ARRIVAL_INDEX] = tempArrival;
		processList[i][BURST_INDEX] = tempBurst;
		processList[i][PRIORITY_INDEX] = tempPriority;
		processList[i][EXECUTED_INDEX] = 0;

		i++;
	}

    numProcesses = i;
    arrivalSort(processList, numProcesses);

	strcpy(tempAlgorithm, tempName);

	while (strcmp (tempAlgorithm, "0") != 0)
	{
        if (strcmp(tempAlgorithm, "FCFS") == 0)
            FCFS(processList, numProcesses, fp2);

        else if (strcmp(tempAlgorithm, "SJF") == 0)
            SJF(processList, numProcesses, fp2);

        else if (strcmp(tempAlgorithm, "RR") == 0) {
            fscanf(fp, "%d", &timeQuantum);
            RR(processList, numProcesses, timeQuantum, fp2);
        }

        else if (strcmp(tempAlgorithm,"Pre-emptive") == 0) {
            fscanf(fp, "%s", tempAlgorithm);
            preEmptivePriority(processList, numProcesses, fp2);
        }

        fscanf(fp, "%s", tempAlgorithm);
    }

	fclose(fp);
	fclose(fp2);
	return 0;
}
