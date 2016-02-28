/*
 Joseph Johnson IV
 Intro to C Programming
 Program to count how many times a person has signed in.
*/

#include <stdio.h>
#include <string.h> // I will be needing the string functions.

//I'm going to need to capitalize letters in a name. So I have to create a function that takes in a string and then uses the toupper function.
void to_upper(char *current_name)
{
    int i = 0;
    while (current_name[i] != '\0') //This loop will continue capitalizing letters in the string until it reaches the null character.
    {
        current_name[i] = toupper(current_name[i]);
        i++;
    }
}

int main (void)
{
    const int name_length = 10, num_new_visitors = 50; // The assignment specifies that no name will be longer than 10 characters and there will be no more than 50 different visitors.
    int v = 0,w,x,y,z,num_names,new_row; // I need 5 total counters for loops.
    char current_name [name_length]; // I also need an array to temporarily hold a name for comparison and capitalization.

    FILE*ifp = fopen("input.txt", "r"); //Creating a file pointer.
    fscanf(ifp,"%d", &num_names); // This will scan the first value in the file and set it as the number of name entries in the file.

    char name_array [num_names - 1] [name_length]; // I will now define a 2D array to hold the names. The row will be set by the number read in, and the given max name length.
    int num_visits [num_names - 1]; // I also need an array that will record each visitor's total number of visits.

    for(z = 0; z < num_names; z++) // This for loop will set all of the values in both the 2D and 1D array to 0.
    {
        strcpy(name_array[z], "0");
        num_visits[z] = 0;
    }

    for(x = 0; x < num_names; x++) // This loop will count what entry in the file is being scanned.
    {
        fscanf(ifp,"%s", current_name); // Scanning the next name.

        to_upper(current_name); // Sending the name to the to_upper function for capitalization.
        new_row = 1; // This variable will control whether or not I will enter the current name into the next empty row in the 2D array.

        for(y = 0; y < num_names; y++) // This for loop will take the current word and compare it to all of the current entries in the array and check for repitition.
            {
                if (strcmp(current_name, name_array[y]) == 0) // This if will run if there is a match in the loop.
                {
                    num_visits[y]++; // Increasing the value in the spot in the 1D array which corresponds with the current row in the 2D array.
                    new_row = 0; // Since we have found a match already in the 2D array we will make sure not to add this name into the next available row.
                }
            }
        if (new_row == 1) // If we didn't find a match, this will evaluate true and execute.
        {
            strcpy(name_array[v], current_name); // This will take the current name and input it into the current row in the 2D array.
            num_visits[v]++; // This will increase the value of the spot in the 1D array that corresponds with the new row we will be entering this name into.
            v++; // This will then shift to the next row so that if the next name again goes unmatched, it will be entered in the next empty row.
        }
    }

    for(w = 0; w < num_names; w++) // This loop will allow us to step through the rows of the 2D array and spots on the 1D array simultaneously. That way we can pull the values and print them together.
    {
        if((strcmp(name_array[w], "0") != 0) && num_visits[w] != 0) // This will make sure that the current row in the 2D array and it's corresponding value in the 1D array aren't empty before printing.
            printf("%s: %d\n", name_array[w], num_visits[w]);
        else // If the row and value are empty, then we know that we don't need to check any of the subsequent rows and can break the loop now.
            break;
    }

    fclose(ifp); // ALWAYS CLOSE THE FILE.
    return 0;
}
