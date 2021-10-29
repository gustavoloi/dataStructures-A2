/*
*  FILE          : hashing.cpp
*  PROJECT       : SENG1050 - Assignment 2
*  PROGRAMMER    : Gustavo Luiz
*  FIRST VERSION : 2020-04-01
*  DESCRIPTION   :
*   The function of this file is to hold the code and functions related to the hash table.
*/

#include "dsA2.h"

//  
// FUNCTION      : unsigned int djbHash
// DESCRIPTION   : 
//   This function will use the hash function djb2 and returns a hash value determining the bucket position that is going to be used. It's originally
//	 created by Dan Bernstein and can be found in http://www.cse.yorku.ca/~oz/hash.html.
//
// PARAMETERS	: 
//	char* str		:	String that is going to have the bucket value calculated.
// RETURNS		:
//	unsigned int	:	This function will return a songInfo* that is going to be used to check the rating later.
//

unsigned int djbHash(char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = (((hash << 5) + hash) + c) % MAX_HASH_TABLE_SIZE; //Division method paired with djb2 hash function

	return hash;
}


//  
// FUNCTION      : wordNode* searchWordInNode
// DESCRIPTION   : 
//   This function will get a word to search in the parameter and will loop the list in the bucket until the word found, while displaying the search comparison.
//
// PARAMETERS	: 
//	char* wordToSearch				:	String that is going to be searched.
//	wordNode hashTableToSearch[]	:	Node index that is going to be searched.
// RETURNS		:
//	wordNode*	:	This function will return a wordNode* that can be used on other functions.
//
wordNode* searchWordInNode(char* wordToSearch, wordNode* hashTableToSearch, int* comparisonCount)
{
	wordNode* currentNode = NULL;
	wordNode* nextNode = NULL;

	comparisonCount[1] = 0; //Resetting the counter every time the search is executed.

	currentNode = hashTableToSearch;

	while (currentNode != NULL) //While the current node is not empty, keeps going
	{
		comparisonCount[1]++; //Increase the local search value

		if (strcmp(currentNode->wordStorage, wordToSearch) == 0) //Compares the two words
		{
			return currentNode; //Return the current node if it matches the search parameters
		}
		else
		{
			currentNode = currentNode->next; //Search on the next node...
		}

	}
	return NULL;
}