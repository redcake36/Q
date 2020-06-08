#include "Header.h"
void OutputQueue(Queue Q, FILE* logFile)
{
	Queue Dop;
	CreatEmptyQueue(&Dop);
	Trab rab;
	if (Empty(Q))
		fprintf(logFile, "О нет!... Очередь пуста!\n");
	else {
		fprintf(logFile, "                           ФИО|   ГОД РОЖДЕНИЯ|    СТАЖ РАБОТЫ|       ДОЛЖНОСТЬ|   ОБРАЗОВАНИЕ|\n");
		fprintf(logFile, "______________________________________________________________________________________________\n");
		while (!Empty(Q))
		{
			rab = PopQueue(&Q);
			fprintf(logFile, "%10s%10s%10s|%15d|%15d|%16s|%14s|\n", rab.F, rab.I,
				rab.O, rab.god, rab.staj, rab.dol, rab.obr);
			fprintf(logFile, "______________________________________________________________________________________________\n");
			PushQueue(&Dop, rab);
		}
	}
	CopyQueue(&Q, &Dop);
	return;
}

float Find(Queue* Q) {
	Trab rab;
	char SUp[31];
	Queue Dop;
	int kol = 0; float rez = 0.0;
	CreatEmptyQueue(&Dop);
	while (!Empty(*Q)) {
		rab = PopQueue(&*Q);
		if (strcmp(ANSIUpperCase(rab.obr, SUp), "ВЫСШЕЕ") == 0 &&
			strcmp(ANSIUpperCase(rab.dol, SUp), "МАСТЕР") == 0) {
			CorrectElem(&rab);
			kol++; rez += rab.staj;
			PushQueue(&Dop, rab);
		}
	}
	CopyQueue(&*Q, &Dop);
	if (kol == 0 || (rez / kol) < 0.0)
		return 0;
	else
		return rez / kol;
}

void CreateQueueFromFile(Queue* Q, int argc, char* argv[]) {
	if (Empty(*Q))
		CreatEmptyQueue(&*Q);

	FILE* ft = fopen(argv[1], "rt");
	if (ft == NULL) {
		printf("Error: не удалось открыть файл с \
исходными данными %s\n", argv[1]);
		system("pause");
		return;
	}

	Trab rab;
	int nw = 1;
	char s[10];
	while (nw) {
		fscanf(ft, "%30s", rab.F);
		if (strcmp(rab.F, "**") == 0 || feof(ft)) break;
		fscanf(ft, "%30s", rab.I);
		fscanf(ft, "%30s", rab.O);

		fscanf(ft, "%5s", s); rab.god = atoi(s);
		fscanf(ft, "%5s", s); rab.staj = atoi(s);
		fscanf(ft, "%30s", rab.dol);
		fscanf(ft, "%30s", rab.obr);

		PushQueue(*&Q, rab);
	}
	if (nw != 1) printf("Error: Ошибка при записи");
	fclose(ft);
	return;
}

void AddElem(Queue* Q, FILE* logFile) {
	Trab rab;
	char s[10];
	printf("Введите данные для нового сотрудника:\n");
	printf("Фамилия:");	scanf("%30s", &rab.F);
	printf("Имя:");scanf("%30s", &rab.I);
	printf("Отчество:");scanf("%30s", &rab.O);
	printf("Год рождения:");scanf("%5s", s); rab.god = atoi(s);
	printf("Стаж Работы:");scanf("%5s", s); rab.staj = atoi(s);
	printf("Должность:");scanf("%30s", &rab.dol);
	printf("Образование:");scanf("%30s", &rab.obr);
	if (CorrectElem(&rab))
		fprintf(logFile, "\nЭлемент скорректирован!...");
	PushQueue(Q, rab);
	return;
}

void FreeQueue(Queue* Q) {
	Trab rab;
	while (!Empty(*Q))
		rab = PopQueue(&*Q);
	Q->k = 0;
	return;
}

void DelNElem(Queue* Q, int n) {
	int i;
	for (i = 0; i < n; i++)
		PopQueue(*&Q);
	return;
}
int CorrectElem(Trab* rab) {
	int flag = 0;
	if (rab->staj < 0) { rab->staj = 0; flag = 1; }
	if (rab->staj > 60) { rab->staj = 60; flag = 1; }
	if (rab->staj > 2020 - rab->god - 15) {
		if (2020 - rab->god - 15 < 0) { rab->staj = 0; }
		else { rab->staj = 2020 - rab->god - 15; }
		flag = 1;
	}
	return flag;
}

char* ANSIUpperCase(char* s, char* Str) {
	Str = strcpy(Str, s);
	char* ch = Str;
	while (*ch) {
		if (*ch >= 'a' && *ch <= 'z' || *ch >= 'а' && *ch <= 'я') *ch = *ch - 32;
		if (*ch == 'ё') *ch = 'Ё';
		ch++;
	}
	return Str;
}

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	char ch;
	int n;
	float abc;
	Queue Q;
	CreatEmptyQueue(&Q);
	system("mkdir str");
	if (argc < 3) {
		printf("Мало параметров\n");
		system("pause");
		return 0;
	}
	FILE* logFile = fopen(argv[2], "w");
	fprintf(logFile, "==================================================================");

	do {
		printf("Q - очистить очередь\nS - создание очереди из файла\nD - добавить элемент в очередь\
\nA - обработать n элементов \nF - Выполнение задачи\nE - выход \nВаш выбор:");
		scanf(" %c", &ch);
		ch = toupper(ch);
		switch (ch) {
		case 'Q':
			if (Empty(Q)) {
				fprintf(logFile, "\nНевозможно очистить очередь!\nОчередь уже пуста!\n");
			}
			else {
				FreeQueue(&Q);
				fprintf(logFile, "\nОчередь очищена!...\nОчередь:\n");
				OutputQueue(Q, logFile);
			}
			printf("Очередь очищена!\n");
			break;
		case 'S':
			CreateQueueFromFile(&Q, argc, argv);
			printf("Очередь создана из файла!...\n");
			fprintf(logFile, "\nОчередь создана из файла!...\nОчередь:\n");
			OutputQueue(Q, logFile);
			break;
		case 'D':
			AddElem(&Q, logFile);
			printf("Элемент добавлен!...\n");
			fprintf(logFile, "\nЭлемент добавлен!...\nОчередь:\n");
			OutputQueue(Q, logFile);
			break;
		case 'A':
			if (Empty(Q)) {
				fprintf(logFile, "\nНечего обрабатывать!");
				printf("Очередь пуста!\n");
			}
			else {
				printf("В очереди %d элементов.Сколько элементов вы хотите обработать:", Q.k);
				scanf("%d", &n);
				if (n<1 || n>Q.k){
					printf("Некорректное количество элементов!\n");
					fprintf(logFile, "\nВведено некорректное количество элементов!\n");
				}
				else
				{
					DelNElem(&Q, n);
					fprintf(logFile, "\n %d элементов очереди обработано!...\nОчередь:\n", n);
					printf("%d элементов очереди обработано!...\n", n);
					OutputQueue(Q, logFile);
				}
			}
			break;
		case 'F':
			if (Empty(Q)) {
				printf("Очередь пуста...\n");
				fprintf(logFile, "\nОчередь пуста...\nПоиск и корректирровка не возможны\n");
			}
			else {
				abc = Find(&Q);
				printf("Поиск и корректирровка выполненна!\n");
				fprintf(logFile, "\nCредний стаж высших мастеров:%4.1f\nОткорректированная чередь:\n", abc);
				OutputQueue(Q, logFile);
			}
			break;
		case 'E': End(Q); break;
		default:
			system("pause");
		}
		fprintf(logFile, "\n==================================================================");
	} while (ch != 'E');
	fclose(logFile);
	return 0;
}
