#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
#include <stdio.h> 
#include <conio.h>    
#include <string.h>
#include <time.h>
//queue based on binary file
//struct Queue {
//	char fileB[30];
//	int k;
//};
struct Trab {
	char F[31], I[31], O[31], dol[31], obr[31];
	int god, staj;
};
struct Node{
	Trab rab;
	Node* next;
};
//queue based on list
struct Queue {
	Node* first;
	Node* last;
	int k;
};
char* ANSIUpperCase(char* s, char* Str);
int CorrectElem(Trab* rab);
void CopyQueue(Queue* Q, Queue* Dop);
void FreeQueue(Queue* Q);
void OutputQueue(Queue Q, FILE* logFile);
Trab PopQueue(Queue* Q);
void PushQueue(Queue *Q, Trab R);
bool Empty(Queue Q);
void CreatEmptyQueue(Queue* Q);
void CreateQueueFromFile(Queue* Q, int argc, char* argv[]);
void AddElem(Queue* Q, FILE* logFile);
void DelNElem(Queue *Q, int n);
float Find(Queue* Q);
void End(Queue Q);