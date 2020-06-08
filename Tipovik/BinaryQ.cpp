//#include "Header.h"
//
//void CreatEmptyQueue(Queue* Q) {
//	long long id = time(0);
//	id *= 1000;
//	id += rand();
//	snprintf(Q->fileB, 30, "str/%lld.dat", id);
//	Q->k = 0;
//}
//
//bool Empty(Queue Q) {
//	if (Q.k == 0) return true;
//	else return false;
//}
//
//void PushQueue(Queue* Q, Trab R) {
//	FILE* f = fopen(Q->fileB, "ab");
//	fwrite(&R, sizeof(R), 1, f);
//	Q->k++;
//	fclose(f);
//}
//
//Trab PopQueue(Queue* Q) {
//	Trab R, rab;
//	Queue Dop;
//	CreatEmptyQueue(&Dop);
//	int nr = 1;
//	FILE* f = fopen(Q->fileB, "ab+");
//	FILE* newf = fopen(Dop.fileB, "wb");
//	fseek(f, 0, SEEK_SET);
//	fread(&R, sizeof(R), 1, f);
//	Q->k--;
//
//	while (nr == 1) {
//		nr = fread(&rab, sizeof(rab), 1, f);
//		fwrite(&rab, sizeof(rab), 1, newf);
//	}
//	fclose(f);
//	fclose(newf);
//	strcpy(Q->fileB, Dop.fileB);
//	return R;
//}
//
//void CopyQueue(Queue*Q,Queue*Dop){
//	char str[30];
//	Q->k = Dop->k;
//	strcpy(str, Q->fileB);
//	remove(str);
//	strcpy(Q->fileB, Dop->fileB);
//}
//
//void End(Queue Q) {
//	char str[30];
//	strcpy(str, "mv ");
//	strcat(str, Q.fileB);
//	strcat(str, " ..");
//	system(str);
//	system("rm -r str");
//	printf("Завершение...");
//}