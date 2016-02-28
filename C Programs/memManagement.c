/*
Joseph Johnson IV
Simulating OS Process Memory Management using different Memory fit algorithms
COP 4600 - Operating Systems
*/


#include <Windows.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

#define MAX_PROCESSES 10

// Datatype for each memoryBlock
typedef struct
{
	int start, end, internalFragmentation;
	char  status[5];

} memBlock;

// Datatype for each Process
typedef struct
{
	char name[3];
	int space;

} processData;

// Helper function that returns the current wall clock time
double get_wall_time()
{
    LARGE_INTEGER time,freq;
    if (!QueryPerformanceFrequency(&freq)){
        //  Handle error
        return 0;
    }
    if (!QueryPerformanceCounter(&time)){
        //  Handle error
        return 0;
    }
    return (double)time.QuadPart / freq.QuadPart;
}

// Function to swap a process with one already in memory using FIFO
// Takes the current state of memory, a list of processes orded by arrival time, a list of processes to be swapped in, the number of processes, the number of blocks, and the number of processes to be swapped
void FIFOSwap(memBlock memArray[], processData processList[], processData swapList[], int numProcesses, int numBlocks, int numSwap)
{
	int i, j;
	for (i = 0; i < numSwap; i++)
	{
		j = 0;

		// Searching for the victim
		while (strcmp(memArray[j].status, processList[i].name) != 0)
			j++;

		// Making sure there is enough space before swapping
		if ( ((memArray[j].end - memArray[j].start) - swapList[i].space) >= 0)
		{
			strcpy(memArray[j].status, swapList[i].name);
			memArray[j].internalFragmentation = (memArray[j].end - memArray[j].start) - swapList[i].space;
		}
	}
}

// Function to insert processes into memory using First Fit
// Takes the current state of memory, a list of processes ordered by arrival time, th enumber of processes, the number of blocks, and an array to hold its results
void FirstFit(memBlock mem[], processData processList[], int numProcesses, int numBlocks, double stats[])
{
	double start, end;

	start = get_wall_time();

	int i, j, placed, numExtFrag = 0, numIntFrag = 0, amnExtFrag = 0, amnIntFrag = 0, numSwap = 0;

	processData swapList[numProcesses];

	// Creating a copy of the state of memory to preserve the original
	memBlock memArray[numBlocks];

	for (i = 0; i < numBlocks; i++)
        memArray[i] = mem[i];


	// For each process, search for a space in memory it can fit in
	for (i = 1; i < numProcesses; i++)
	{
		j = 0;
		placed = 0;

		while (placed == 0 && j < numBlocks)
		{
			if ( (strcmp(memArray[j].status, "free") == 0) && ((memArray[j].end - memArray[j].start) >= processList[i].space) )
			{
				placed = 1;
				strcpy(memArray[j].status, processList[i].name);

				memArray[j].internalFragmentation = (memArray[j].end - memArray[j].start) - processList[i].space;
			}

			j++;
		}

		// If the process was not placed, add it to the swap list
		if (placed == 0 && j != 0)
		{
			swapList[numSwap] = processList[i];
			numSwap++;
		}
	}

	// If there are processes to swap, swap them
	if (numSwap > 0)
		FIFOSwap(memArray, processList, swapList, numProcesses, numBlocks, numSwap);

	end = get_wall_time();


	printf("\nResults for First Fit \n*************************************************\n\nMemory Status\n\nStart Address       End Address          Process\n--------------------------------------------------\n\n");

	for (i = 0; i < numBlocks; i++)
	{
		printf("%d                    %d                    %s\n\n", memArray[i].start, memArray[i].end, memArray[i].status);

		if (strcmp(memArray[i].status, "free") == 0)
		{
			numExtFrag++;
			amnExtFrag = amnExtFrag + (memArray[i].end - memArray[i].start);
		}

		else if (memArray[i].internalFragmentation != 0)
		{
			numIntFrag++;
			amnIntFrag = amnIntFrag + memArray[i].internalFragmentation;
		}
	}

	printf("--------------------------------------------------\n\n");
	printf("Number of External Fragments: %d\nTotal External Fragmentation: %d MB\nNumber of Internal Fragments: %d\nTotal Internal Fragmentation: %d MB\nTotal time taken to run the algorithm %.3fms\n\n*************************************************\n",
	numExtFrag, amnExtFrag, numIntFrag, amnIntFrag, (double)((end - start) * 1000));

	double tempStats[] = {numExtFrag, amnExtFrag, numIntFrag, amnIntFrag, (double)((end - start) * 1000)};

	for(i = 0; i < 5; i++)
        stats[i] = tempStats[i];
}

// Function to insert processes into memory using Best Fit
// Takes the current state of memory, a list of processes ordered by arrival time, th enumber of processes, the number of blocks, and an array to hold its results
void BestFit(memBlock mem[], processData processList[], int numProcesses, int numBlocks, double stats[])
{

	double start, end;

	start = get_wall_time();

	int i, j, placed, bestIndex, waste, numExtFrag = 0, numIntFrag = 0, amnExtFrag = 0, amnIntFrag = 0, numSwap = 0;
	processData swapList[numProcesses];

	memBlock memArray[numBlocks];

	for (i = 0; i < numBlocks; i++)
        memArray[i] = mem[i];


	// for each process find the best fit and mark that index
	for (i = 1; i < numProcesses; i++)
    {
        j = 0;
		placed = 0;
		bestIndex = 9999;
		waste = 9999;

		while (j < numBlocks)
		{
			if ((strcmp(memArray[j].status, "free") == 0) && ((memArray[j].end - memArray[j].start) >= processList[i].space))
			{

				if ( ((memArray[j].end - memArray[j].start) - processList[i].space) < waste)
				{
					placed = 1;
					bestIndex = j;
					waste = (memArray[j].end - memArray[j].start) - processList[i].space;
				}

			}
			j++;
		}

		// If we found a good spot, place the process in memory
		if (placed ==1)
		{
			strcpy(memArray[bestIndex].status, processList[i].name);
			memArray[bestIndex].internalFragmentation = waste;
		}

		// Add it to the swap list if we didn't
		if (placed == 0 && j != 0)
		{
			swapList[numSwap] = processList[i];
			numSwap++;
		}

    }

	// If we need to swap, do it
	if (numSwap > 0)
		FIFOSwap(memArray, processList, swapList, numProcesses, numBlocks, numSwap);

	end = get_wall_time();


	printf("\nResults for Best Fit \n*************************************************\n\nMemory Status\n\nStart Address       End Address          Process\n--------------------------------------------------\n\n");

	for (i = 0; i < numBlocks; i++)
	{
		printf("%d                    %d                    %s\n\n", memArray[i].start, memArray[i].end, memArray[i].status);

		if (strcmp(memArray[i].status, "free") == 0)
		{
			numExtFrag++;
			amnExtFrag = amnExtFrag + (memArray[i].end - memArray[i].start);
		}

		else if (memArray[i].internalFragmentation != 0)
		{
			numIntFrag++;
			amnIntFrag = amnIntFrag + memArray[i].internalFragmentation;
		}
	}

	printf("--------------------------------------------------\n\n");
	printf("Number of External Fragments: %d\nTotal External Fragmentation: %d MB\nNumber of Internal Fragments: %d\nTotal Internal Fragmentation: %d MB\nTotal time taken to run the algorithm %.3fms\n\n*************************************************\n",
	numExtFrag, amnExtFrag, numIntFrag, amnIntFrag, (double)((end - start) * 1000));

	double tempStats[] = {numExtFrag, amnExtFrag, numIntFrag, amnIntFrag, (double)((end - start) * 1000)};

	for(i = 0; i < 5; i++)
        stats[i] = tempStats[i];
}

// Function to insert processes into memory using Best Fit
// Takes the current state of memory, a list of processes ordered by arrival time, th enumber of processes, the number of blocks, and an array to hold its results
void WorstFit(memBlock mem[], processData processList[], int numProcesses, int numBlocks, double stats[])
{
	double start, end;

	start = get_wall_time();

	int i, j, placed, bestIndex, waste, numExtFrag = 0, numIntFrag = 0, amnExtFrag = 0, amnIntFrag = 0, numSwap = 0;
	processData swapList[numProcesses];

	memBlock memArray[numBlocks];

	for (i = 0; i < numBlocks; i++)
        memArray[i] = mem[i];


	// Algorithm works the same as best fit, only this time we mark the index with the worst fit as the best index
	for (i = 1; i < numProcesses; i++)
    {
        j = 0;
		placed = 0;
		bestIndex = 9999;
		waste = 0;

		while (j < numBlocks)
		{
			if ((strcmp(memArray[j].status, "free") == 0) && ((memArray[j].end - memArray[j].start) >= processList[i].space))
			{

				if ( ((memArray[j].end - memArray[j].start) - processList[i].space) > waste)
				{
					bestIndex = j;
					placed = 1;
					waste = (memArray[j].end - memArray[j].start) - processList[i].space;
				}

			}
			j++;
		}

		if (placed ==1)
		{
			strcpy(memArray[bestIndex].status, processList[i].name);
			memArray[bestIndex].internalFragmentation = waste;
		}

		if (placed == 0 && j != 0)
		{
			swapList[numSwap] = processList[i];
			numSwap++;
		}

    }

	if (numSwap > 0)
		FIFOSwap(memArray, processList, swapList, numProcesses, numBlocks, numSwap);

	end = get_wall_time();


	printf("\nResults for Worst Fit \n*************************************************\n\nMemory Status\n\nStart Address       End Address          Process\n--------------------------------------------------\n\n");

	for (i = 0; i < numBlocks; i++)
	{
		printf("%d                    %d                    %s\n\n", memArray[i].start, memArray[i].end, memArray[i].status);

		if (strcmp(memArray[i].status, "free") == 0)
		{
			numExtFrag++;
			amnExtFrag = amnExtFrag + (memArray[i].end - memArray[i].start);
		}

		else if (memArray[i].internalFragmentation != 0)
		{
			numIntFrag++;
			amnIntFrag = amnIntFrag + memArray[i].internalFragmentation;
		}
	}

	printf("--------------------------------------------------\n\n");
	printf("Number of External Fragments: %d\nTotal External Fragmentation: %d MB\nNumber of Internal Fragments: %d\nTotal Internal Fragmentation: %d MB\nTotal time taken to run the algorithm %.3fms\n\n*************************************************\n",
	numExtFrag, amnExtFrag, numIntFrag, amnIntFrag, (double)((end - start) * 1000));

	double tempStats[] = {numExtFrag, amnExtFrag, numIntFrag, amnIntFrag, (double)((end - start) * 1000)};

	for(i = 0; i < 5; i++)
        stats[i] = tempStats[i];
}

int main(int argc, char *argv[])
{
	int i = 0, j = 0, numBlocks, tempStart, tempEnd, tempSpace, minExt = 9999, maxExt = 0, minInt = 9999, maxInt = 0;
    char tempName[3], tempStatus[5], fileName[100];
    char string[3][10] = {"First Fit", "Best Fit", "Worst Fit"};
	double minTime = 9999, maxTime = -1;
	double results[3][5];
	int winners[3], losers[3];


	memBlock tempBlock;
	processData tempData, processList[MAX_PROCESSES];


	FILE *fp = fopen(argv[1], "r");

	if (fp == 0) {
		printf("Error: File name not passed as command line argument. \nPlease enter the file name: ");
		scanf("%s", fileName);

		fp = fopen(fileName, "r");
	}

	if (fp ==0) {
		printf("Error: File not found.");
		return 0;
	}

	fscanf(fp,"%d", &numBlocks);
	memBlock memArray[numBlocks];

	for (i = 0; i < numBlocks; i++)
	{
		fscanf(fp, "%d %d %s", &tempStart, &tempEnd, tempStatus);

		tempBlock.start = tempStart;
		tempBlock.end = tempEnd;
		strcpy(tempBlock.status, tempStatus);

		memArray[i] = tempBlock;

		if (strcmp(tempStatus, "free") != 0)
		{
			strcpy(tempData.name, tempBlock.status);
			tempData.space = 0;

			processList[j] = tempData;

			j++;
		}
	}

	while (fscanf(fp, "%s %d", tempName, &tempSpace) == 2)
	{
		strcpy(tempData.name, tempName);
		tempData.space = tempSpace;

		processList[j] = tempData;
		j++;
	}

	fclose(fp);

    FirstFit(memArray, processList, j, numBlocks, results[0]);

    BestFit(memArray, processList, j, numBlocks, results[1]);

    WorstFit(memArray, processList, j, numBlocks, results[2]);


    for (i = 0; i < 3; i++)
    {
        if ((int)results[i][1] <= minExt)
        {
            minExt = results[i][1];
            winners[0] = i;
        }

        if ((int)results[i][1] >= maxExt)
        {
            minExt = results[i][1];
            losers[0] = i;
        }

        if ((int)results[i][3] <= minInt)
        {
            minInt = results[i][3];
            winners[1] = i;
        }

        if ((int)results[i][3] >= maxInt)
        {
            maxExt = results[i][3];
            losers[1] = i;
        }

        if (results[i][4] <= minTime)
        {
            minTime = results[i][4];
            winners[2] = i;
        }

        if (results[i][4] >= maxTime)
        {
            maxTime = results[i][4];
            losers[2] = i;
        }

    }

    printf("\n%s had the lowest time and %s had the highest\n%s had the least External Fragmentation and %s had the most\n%s had the least Internal Fragmentation and %s had the most\n",
           string[winners[2]], string[losers[2]], string[winners[0]], string[losers[0]], string[winners[1]], string[losers[1]]);

	return 0;

}
