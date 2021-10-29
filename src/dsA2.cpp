/*
*  FILE          : dsA2.cpp
*  PROJECT       : SENG1050 - Assignment 2
*  PROGRAMMER    : Gustavo Luiz
*  FIRST VERSION : 2020-04-01
*  DESCRIPTION   :
*   The function of this file is to hold the main section of the project, which will take a text file and insert every word into both a 
	linked list and a hash table. Then the user will be prompted to search for a word and the program will show how many searches were
	realize for that word, displaying the total when exiting the program.
*/

#include "dsA2.h"


int main(void)
{

	int comparisonCounter[MAX_ARRAY_COUNTER] = { 0 }; //Counter for the total comparison values
	int totalSearches = 0; //Counter for the total number of searches

	//Hash Table
	wordNode* hashTable[MAX_HASH_TABLE_SIZE] = { NULL };
	wordNode* longLinkedList = NULL;

	//Hash value storage
	unsigned int bucketPos = 0;
	unsigned int searchBucketPos = 0;

	//Char buffers
	char insertBuffer[CHARACTER_LENGHT] = "";
	char searchBuffer[CHARACTER_LENGHT] = "";

	//Menu loops
	bool menuLoop = true;
	bool searchLoop = true;

	//File management
	FILE* inputFile = NULL;
	inputFile = fopen("../words.txt", "r");


	if (inputFile == NULL) //File error checking
	{
		printf("Error reading the file!");
		return 1;
	}
	else
	{
		while (fgets(insertBuffer, sizeof(insertBuffer), inputFile) != NULL) //Insert the words into the hash tables/linked lists
		{
			clearCR(insertBuffer); //Function to take out the '\n' at the end of the input.

			bucketPos = djbHash(insertBuffer); //Sets the bucket position by realizing a hash function
			hashTable[bucketPos] = insertWordIntoNode(insertBuffer, hashTable[bucketPos]); //Insert the new node in the right place, ordered.
			longLinkedList = insertWordIntoNode(insertBuffer, longLinkedList);
		}

		while (searchLoop) //Search loop
		{
			fgets(searchBuffer, sizeof(searchBuffer), stdin); //Take the words from the text file as inputs
			clearCR(searchBuffer); //Function to take out the '\n' at the end of the input.
			if (strcmp(searchBuffer, "") == 0) //Checking for an empty string, which can cause the hash function to return an invalid bucket
			{
				printf("Invalid character!\n");
			}
			else
			{
				searchBucketPos = djbHash(searchBuffer); //Function to calculate the bucket position for the has table.

				if (*searchBuffer == '.' && (strlen(searchBuffer) == 1)) //Check if the user inputed a '.', which leads to a program exit.
				{
					searchLoop = false;

					//Print the final number of searches.
					printf("\tTotal Number of Searches: %d\n", totalSearches);
					printf("\tTotal Number of Comparisons in Linked List: %d\n", comparisonCounter[0]);
					printf("\tTotal Number of  Comparisons in Hash Table: %d\n", comparisonCounter[1]);
				}
				else
				{
					totalSearches++; //Increase the total number of searches executed so far

					searchForWordTwice(searchBuffer, longLinkedList, hashTable[searchBucketPos], comparisonCounter); //Perform the search again
				}
			}
		}

	}

	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//Free all the used memory after the program ends
	{
		freeAll(hashTable[i]);
	}
	freeAll(longLinkedList); //Also frees the memory for the linked list.

	return 0;
}