/*
*  FILE          : dsA2.h
*  PROJECT       : SENG1050 - Assignment 2
*  PROGRAMMER    : Gustavo Luiz
*  FIRST VERSION : 2020-04-01
*  DESCRIPTION   :
*   The function of this file is to hold all the information and declarations that are going to be used in the main code.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#pragma warning(disable:4996)

#define CHARACTER_LENGHT 21		//Word limit plus null termination
#define MAX_ARRAY_SIZE 11		//Max array size
#define MAX_HASH_TABLE_SIZE 127 //Maximum size of the hash table
#define MAX_ARRAY_COUNTER 2		//Size of the counter array

//wordNode struct
struct wordNode {
	char* wordStorage;
	wordNode* next;
};

//Prototypes
unsigned int djbHash(char* str);
void clearCR(char* pBuffer);
void freeAll(wordNode* head);

wordNode* insertWordIntoNode(char* wordToInsert, wordNode nodeBucketToInsert[]);

wordNode* searchWordInNode(char* wordToSearch, wordNode* hashTableToSearch, int* comparisonCount);
wordNode* searchLinkedList(char* searchWord, struct wordNode* linkedList, int* comparisonCount);

void searchForWordTwice(char* searchWord, struct wordNode* linkedList, struct wordNode* hashTable, int comparisonCount[MAX_ARRAY_COUNTER]);


