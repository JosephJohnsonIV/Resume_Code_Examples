/*
 Joseph Johnson IV
 Computer Science 1
 Program to turn a string into a linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListString.h"

// Function to create a node that holds a single character
node *createNode(char data)
{
	node *newNode = calloc(1, sizeof(node));
	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}

// Function to step through a linked list and return the last node
node *findTail(node *head)
{
	node *temp;

	if (head == NULL)
		return head;

	for (temp = head; temp->next != NULL; temp = temp->next) ;

	return temp;
}

// Function to add a new node to a list
node *insertNode(node *head, char data)
{
	node *tail;

	if (head == NULL)
		return createNode(data);

	tail = findTail(head);
	tail->next = createNode(data);

	return head;
}

// Function to convert a string into a linked list
node *stringToList(char *str)
{
	int i;
	node *head = NULL;

	// Return an empty list if given a NULL or empty string
	if (str == NULL || strcmp(str, "") == 0)
		return NULL;

	// Create a node for each character in the string
	for (i = 0; i < strlen(str); i++)
		head = insertNode(head, str[i]);

	return head;
}

// Function to create a new list for the string to be added and swapping it with the node to be replaced
node *swapList(node *link, char *str)
{
	int i;
	node *newStr = NULL;
	node *newStrTail = NULL;

	// Creating a node for each character
	for (i = 0; i < strlen(str); i++)
		newStr = insertNode(newStr, str[i]);

	// Finding the tail of the new list and pointing it to the next node in the original list
	newStrTail = findTail(newStr);
	newStrTail->next = link->next;

	// Replacing the old node with the head of the new list
	link = newStr;

	return link;
}

// Function to replace all instances of a character in the list with a new string
node *replaceChar(node *head, char key, char *str)
{
	node *temp, *newStrTail;
	node *newStr = NULL;
	int i, flag = 0;


	if(head == NULL)
		return head;

	// Setting a flag to only delete the character if the new string is empty or null
	if (str == NULL || strcmp(str, "") == 0)
		flag = 1;

	// This loop will handle checking and replacing all nodes EXCEPT the head of the list
	for (temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->next == NULL)
			continue;

		// Check the next node for the key
		if (temp->next->data == key)
		{
			// Determine whether replacing the node or deletion is necessary
			if (flag == 1)
				temp->next = temp->next->next;
			else
			{
				// Using the helper function to handle creating the new list and swapping it with the node to be replaced
				temp->next = swapList(temp->next, str);

				// Making sure the loop resumes at the end of the new string to avoid infinitely replacing a node
				for (i = 0; i < strlen(str); i++)
					temp = temp->next;
			}
		}

		// Checking the next node before resuming the loop to account for double characters
		if (temp->next == NULL || temp->next->next == NULL)
			continue;

		// The same process as with the previous node
		if (temp->next->next->data == key)
		{
			if (flag == 1)
				temp->next->next = temp->next->next->next;

			else
			{
				temp->next->next = swapList(temp->next->next, str);

				for (i = 0; i < strlen(str); i++)
					temp = temp->next;
			}
		}
	}

	// Checking the head of the original list and deleting/replacing as necessary
	if (head->data == key && flag == 1)
		head = head->next;

	else if (head->data == key && flag == 0)
		head = swapList(head, str);

	return head;
}

// Function to reverse a linked list
node *reverseList(node *head)
{
	node *new, *temp;
	new = NULL;

	// While loop to continue cycling through the original list
	while(head != NULL)
	{
		temp = new;
		new = head;
		head = head->next;
		new->next = temp;
	}

	return new;
}

// Function to print the contents of a linked list as a string
void printList(node *head)
{
	node *temp;

	if (head == NULL)
		printf("(empty string)\n");

	else
	{
		for (temp = head; temp->next != NULL; temp = temp->next)
			printf("%c", temp->data);

		printf("%c\n", temp->data);
	}
}

int main(int argc, char **argv)
{


	int numLines;
	char c;

	// Creating a string large enough for the maximum size specified
	char *s = calloc(1024, sizeof(char));
	node *head;
	FILE *ifp;

	// Opening the input file and scanning the first string
	ifp = fopen(argv[1], "r");
	fscanf(ifp, "%s", s);

	// Converting the string to a linked list
	head = stringToList(s);

	// Continuing through the input until all text is scanned
	while (fscanf(ifp, " %c", &c) != EOF)
	{
		// If statements to perform each symbol's assigned operation

		if (c == '!')
			printList(head);

		else if (c == '~')
			head = reverseList(head);

		else if (c == '-')
		{
			fscanf(ifp, " %c", &c);
			head = replaceChar(head, c, "");
		}

		else if (c == '@')
		{
			fscanf(ifp, " %c %s", &c, s);
			head = replaceChar(head, c, s);
		}
	}

	// Making sure to close the pointer to the file
	fclose(ifp);

	return 0;
}
