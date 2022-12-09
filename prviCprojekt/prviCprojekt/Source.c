#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define ERROR_BROJ_BODOVA (-5)
#define NEUSPJESNO_IZVRSENO (1)
#define USPJESNO_IZVRSENO (2)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define USPJESNO_ZAVRSEN_PROGRAM (0)

int izbrojiStudente(char* filename);

typedef struct student {
	char  ime[50];
	char  prezime[50];
	int   bodovi;
} student;

int unosStudenata(int, student*, char* filename);
int nadiMaxBodove(student*, int);
int ispisStudenata(int, int, student*);


int main(void) {
	
	student* nizStudenata;
	char filename[MAX_FILE_NAME] = { 0 };
	printf("Unesite ime dokumenta: ");
	scanf(" %s", filename);
	//printf("%s", filename);
	int brojStudenata = izbrojiStudente(filename);
	if (brojStudenata >= 0) {
		printf("Broj studenata u datoteci je: %d \n", brojStudenata);
	}

	
	nizStudenata = (student*)malloc(brojStudenata * sizeof(student));
	
	if (nizStudenata == NULL) {
		printf("Memorija nije alocirana!\n");
		return NEUSPJESNO_IZVRSENO;
	}
	
	unosStudenata(brojStudenata, nizStudenata,filename);
	int maxBrBodova = nadiMaxBodove(nizStudenata, brojStudenata);
	if (maxBrBodova == ERROR_BROJ_BODOVA) {
		printf("Problem pri trazenju najveceg broja bodova!\n");
		return NEUSPJESNO_IZVRSENO;
	}
	else {
		printf("Najvisi broj bodova: %d\n", maxBrBodova);
	}

	ispisStudenata(brojStudenata, maxBrBodova, nizStudenata);
	
	free(nizStudenata);
	
	return USPJESNO_ZAVRSEN_PROGRAM;
}

int izbrojiStudente(char* filename) {
	FILE* fp = NULL;
	int count = 0;
	char buffer[MAX_LINE] = { 0 };
	//printf("%s", filename);
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Dokument se nije otvorio. ");
		return FILE_DIDNT_OPEN_ERROR;
	}
	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		if (strcmp("\n", buffer) != 0) {
			count++;
		}
	}
	fclose(fp);
	return count;
}
int unosStudenata(int brojStudenata, student* nizStudenata, char* filename)
{
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	int i;
	for (i = 0; i < brojStudenata; i++) {
		fscanf(fp, " %s %s %d", nizStudenata[i].ime, nizStudenata[i].prezime, &nizStudenata[i].bodovi);
		//printf(" %s %s %d \n", nizStudenata[i].ime, nizStudenata[i].prezime, nizStudenata[i].bodovi);
		}
	fclose(fp);
	
	return USPJESNO_IZVRSENO;
}

int nadiMaxBodove(student* nizStudenata, int brojStudenata) {
	int maxBodova = ERROR_BROJ_BODOVA;
	int i;
	for (i = 0; i < brojStudenata; i++) {
		if (nizStudenata[i].bodovi > maxBodova) {
			maxBodova = nizStudenata[i].bodovi;
		}
	}
	return maxBodova;
}

int ispisStudenata(int brojStudenata, int maxBrBodova, student* nizStudenata) {
	int i;
	printf("IME \t PREZIMEM \t RELATIVAN BROJ BODOVA\n");
	for (i = 0; i < brojStudenata; i++) {
		float relativanBrBodova = (float)nizStudenata[i].bodovi / maxBrBodova *100;
		printf("%s\t %s\t\t %f \n", nizStudenata[i].ime, nizStudenata[i].prezime, relativanBrBodova);
	}
	return USPJESNO_IZVRSENO;
}
