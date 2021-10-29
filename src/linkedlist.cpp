/*
*  FILE          : linkedlists.cpp
*  PROJECT       : SENG1050 - Assignment 2
*  PROGRAMMER    : Gustavo Luiz
*  FIRST VERSION : 2020-04-01
*  DESCRIPTION   :
*   The function of this file is to hold the code related to the linked lists.
*/

#include "dsA2.h"


//  
// FUNCTION      : wordNode* insertWordIntoNode
// DESCRIPTION   : 
//   This function will take a word and a node and will insert said word into the list in order.
//
// PARAMETERS	: 
//	char* wordToInsert				:	String that is going to be inserted in the corresponding bucket.
//	wordNode nodeBucketToInsert[]	:	Node array position to check if there is any prevNodeious node in the same index.
// RETURNS		:
//	wordNode*	:	This function will return a wordNode* that is going to insert the word in the right index and order.
//

wordNode* insertWordIntoNode(char* wordToInsert, wordNode nodeBucketToInsert[]) {
	wordNode* newNode = NULL;
	wordNode* currentNode = NULL;
	wordNode* prevNode = NULL;

	newNode = (wordNode*)malloc(sizeof(wordNode)); //Memory allocation for the new node
	if (newNode == NULL) //Error checking
	{
		printf("Error! No more memory\n");
		return nodeBucketToInsert;
	}

	newNode->wordStorage = (char*)malloc(strlen(wordToInsert) + 1); //Memory allocation for the word
	if (newNode->wordStorage == NULL) //Error checking
	{
		printf("Error! No more memory\n");
		return nodeBucketToInsert;
	}
	strcpy(newNode->wordStorage, wordToInsert); //Copy the new word into the new node
	newNode->next = NULL; //Set the next node as NULL

	if (nodeBucketToInsert == NULL) //If the current node is empty and...
	{
		nodeBucketToInsert = newNode; //...set a value to it

	}
	else if (strcmp(nodeBucketToInsert->wordStorage, newNode->wordStorage) > 0) //It compared the new word to the word in the current node
	{
		//If it meets the criteria, sets the next node to the current, and the parameter node to the new node.
		newNode->next = nodeBucketToInsert;
		nodeBucketToInsert = newNode;

	}
	else //If the prevNodeious criteria was not enough
	{
		prevNode = nodeBucketToInsert;
		currentNode = nodeBucketToInsert->next;

		while (currentNode != NULL) //While the current node is not empty
		{
			if (strcmp(currentNode->wordStorage, newNode->wordStorage) >= 0) //Check for criteria
			{
				break; //Break when the criteria is met
			}
			//Set nodes as needed
			prevNode = currentNode;
			currentNode = currentNode->next;
		}

		newNode->next = currentNode; //Set the next node of newNode as the current
		prevNode->next = newNode; //Set the previous node next element as the new node
	}
	return nodeBucketToInsert; //return the list that is going to be in the bucket
}


//  
// FUNCTION      : wordNode* searchLinkedList
// DESCRIPTION   : 
//   This function will search in the ordered linked list for the word specified in the parameter, while also the number the strcmp was called.
//
// PARAMETERS	: 
//	char* searchWord				:	Word that is going to be searched.
//	struct wordNode* linkedList		:	Linked list that is going to be used in the search.
//	int* comparisonCount			:	An array of INT that is going to be used to store the number of times strcmp was called.
// RETURNS		:
//	wordNode*	:	This function will return NULL every time the search finds the result.
//
wordNode* searchLinkedList(char* searchWord, struct wordNode* linkedList, int* comparisonCount)
{
	wordNode* currentNode = NULL;
	wordNode* nextNode = NULL;

	comparisonCount[0] = 0; //Resetting the counter every time it starts

	currentNode = linkedList;
	
	while (currentNode != NULL) //While the current node is not empty, keeps going
	{
		comparisonCount[0]++; //Increase the search counter
		if (strcmp(currentNode->wordStorage, searchWord) >= 0) //Compares the two words
		{
			return currentNode; //End the comparison as soon as the word is found
		}
		else
		{
			currentNode = currentNode->next; //If not found, switch to the next node
		}
	}
	return NULL; //If nothing is found, return NULL
}


//  
// FUNCTION      : void freeAll
// DESCRIPTION   : 
//   This function will free all memory that was allocated for the list.
// PARAMETERS	: 
//	songNode* head		:	Head of the list being freed.
//
void freeAll(wordNode* head)
{
	wordNode* currentNode = NULL, * next = NULL;
	currentNode = head;
	while (currentNode != NULL) //While the current node is not empty, keeps going
	{
		//Free the current node and keep going forward
		next = currentNode->next;
		free(currentNode);
		currentNode = next;
	}

}

// FUNCTION      : clearCR
// DESCRIPTION   : 
//   This function will search for a '\n' in the pBuffer and switch that into a '\0' so it doesn't show extra line breaks.
// PARAMETERS	: 
//	char* pBuffer		:	Pointer to a char variable.
//
void clearCR(char* pBuffer)
{
	char* locationCR = strchr(pBuffer, '\n');
	if (locationCR != NULL)
	{
		*locationCR = '\0';
	}
}



//  
// FUNCTION      : void searchForWordTwice
// DESCRIPTION   : 
//   This function will call the 2 search functions and keep track of the total number of searches, as well as displaying messages.
// PARAMETERS	: 
//	char* searchWord							:	Word that is being searched.
//	struct wordNode* linkedList					:	Linked list struct.
//	struct wordNode* hashTable					:	Hash table struct.
//	int comparisonCount[MAX_ARRAY_COUNTER]		:	Array containing the search results.
//
void searchForWordTwice(char* searchWord, struct wordNode* linkedList, struct wordNode* hashTable, int comparisonCount[MAX_ARRAY_COUNTER])
{
	int localCounter[MAX_ARRAY_COUNTER] = { 0 }; //Local counter to store the local number of searches.

	if (searchWordInNode(searchWord, hashTable, localCounter) == NULL) //If the search in the hash table returns NULL, do the linked list search
	{
		searchLinkedList(searchWord, linkedList, localCounter); //Execute the list search to find the number of comparisons

		printf("\t%s was NOT found in the linked list in %d comparisons.\n", searchWord, localCounter[0]);
		printf("\t%s was NOT found in the hash table bucket in %d comparisons.\n", searchWord, localCounter[1]);
		
		for (int i = 0; i < MAX_ARRAY_COUNTER; i++) //Setting the number of total searches that is going to be displayed in the end
		{
			comparisonCount[i] += localCounter[i];
		}
	}
	else //In the case that the search result is not NULL
	{
		searchLinkedList(searchWord, linkedList, localCounter); //Do the list search

		printf("\t%s was found in the linked list in %d comparisons.\n", searchWord, localCounter[0]);
		printf("\t%s was found in the hash table bucket in %d comparisons.\n", searchWord, localCounter[1]);
		
		for (int i = 0; i < MAX_ARRAY_COUNTER; i++) //Set the number of total searches.
		{
			comparisonCount[i] += localCounter[i];
		}
	}
}

