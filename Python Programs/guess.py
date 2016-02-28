#Joseph Johnson IV
#Introduction to C Programming
#Program for a random number guessing game.

#First we need to import the random function.

import random

#Now to define our function for the game.

def number_guessing_game(x):

#Before we continue, we have to set some initial values.

    MAX_VAL = 100 #Highest value we want to use.
    num_guesses = 0
    guess = -1 #Setting the guess to a value that will never be the secret number.
    max_guesses = x
    secret = random.randint(1, MAX_VAL)
    win = 0 # Initializing the variable we will be using to determine the output.

    while guess != secret and num_guesses < max_guesses:

#This while loop will ensure that the user will continue to be prompted until they either guess the number or run out of chances.

        guess = int(input("Enter your guess(1 to "+ str(MAX_VAL)+"): ")) #Gathering the user's guesses.
        if guess == secret:
            print("You win!")
            win = 1 #if the guess is correct we want to reset the win variable.
        elif guess < secret:
            print("Your guess is too low. Try again!")
        else:
            print("Your guess is too high. Try again!")

#Remembering to add 1 to the value of num_guesses after each cycle.

        num_guesses = num_guesses + 1

#Using another if statement to determine whether to print a win message or loss message.

    if win == 1:
        print("You won with",num_guesses,"guesses.")
    else:
        print("You lost with",num_guesses,"guesses.")

number_guessing_game(5)

print("Thanks for playing!")
