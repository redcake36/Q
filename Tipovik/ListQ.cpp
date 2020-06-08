#include "Header.h"

void CreatEmptyQueue(Queue* Q)
{
	Q->first = new Node;
	Q->first->next = NULL;
	Q->last = Q->first;
	Q->k = 0;
}

bool Empty(Queue Q)
{
	if (Q.first == Q.last) return true;
	else return false;
}

void PushQueue(Queue* Q, Trab R)
{
	Q->last->next = new Node;
	Q->last->rab = R;
	Q->last = Q->last->next;
	Q->last->next = NULL;
	Q->k++;
}

Trab PopQueue(Queue* Q) {
	Node* N = Q->first;
	Trab R = N->rab;
	Q->first = Q->first->next;
	Q->k--;
	return R;
}

void CopyQueue(Queue* Q, Queue* Dop) {
	while (!Empty(*Dop)) {
		Node* N = Dop->first;
		Q->k++;
		Dop->k--;
		Trab rab = N->rab;
		Dop->first = Dop->first->next;
		delete N;
		Q->last->next = new Node;

		Q->last->rab = rab;
		Q->last = Q->last->next;
	}
	return;
}
void End(Queue Q) { printf("Завершение..."); }