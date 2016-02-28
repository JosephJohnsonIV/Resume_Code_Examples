#Joseph Johnson IV
#Introduction to C Programming
#Program to create a times table

#Allow user to determine width of the table.

width = int(input("Please enter the width of the times table.\n"))

#Creating the function to compute and print the values for the table.

def print_times_table(width):

#Have to initialize both the row and column values.

    row = 0
    column = 0

#Need to set up a while loop that will fill in values as long as row <= width.

    while row <= width:
        column = 0

#Need to do the same for column <=width.

        while column <= width:
            number = row * column #This will compute the number that needs to be printed.

#I am now going to use a series of if statements; A,B, and C, to alter the spacing in between the printed values.
#I'm not sure if this is required, but it makes the table look a lot better.
#Removing one space everytime a new digit is added.

            if number >=10 and number < 100:
                print(number,end = '   ')
            elif number >= 100 and number < 1000: # A
                print(number,end = '  ')
            elif number >= 1000 and number < 10000: # B
                print(number,end = ' ')
            elif number >= 10000 and number < 100000:# C
                print(number, end = '')
            else:
                print(number,end = '    ')

#Must remember to increase column and row values at the end of their loops.

            column += 1
        row += 1
        print('\n',end='') #Will form rows.

print_times_table(width)
