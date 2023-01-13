#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum ERROR_CODE {
	FILE_NOT_OPEN = -1,
	USPJESNO_ZAVRSEN_PROGRAM,
	USPJESNO_IZVRSENO,
	NEUSPJESNO_IZVRSENO,
};


typedef struct Grad* P_Grad;
typedef struct Grad {
	char Naziv_Grad[MAX_LINE];
	int broj_stanovnika;
	P_Grad L;
	P_Grad D;
}Grad;

typedef struct Drzava* P_Drzava;
typedef struct Drzava {
	char Naziv_Drzava[MAX_LINE];
	P_Drzava next;
	P_Grad root;
}Drzava;

int NovaDrzava(char, char, P_Drzava);

int Unos_Gradova(P_Drzava, char);
int NoviGrad(char, int, P_Grad);



int main(void) {
	char buffer[MAX_LINE];
	FILE* fp=NULL;
	char* p = buffer;
	char drzava[MAX_LINE];
	char file[MAX_LINE];
	fp = fopen("drzave.txt", "r");
	if (fp == NULL) {
		printf("Dokument se nije otvorio.\n");
		return FILE_NOT_OPEN;
	}

	Drzava Head_Drzava = {
		.Naziv_Drzava = {0},
		.next = NULL,
		.root = NULL
	};
	


	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		sscanf(p, " %s %s", drzava, file);
		NovaDrzava(drzava, file, &Head_Drzava);
	}


	fclose(fp);

}

int NovaDrzava(char naziv, char file, P_Drzava Head) {
	P_Drzava Nova_Drzava = malloc(sizeof(Drzava));
	Nova_Drzava->root = NULL;
	Nova_Drzava->next = NULL;
	if (Nova_Drzava == NULL) {
		printf("Memorija nije alocirana.");
		return NEUSPJESNO_IZVRSENO;
	}
	strcpy(Nova_Drzava->Naziv_Drzava, naziv);

	if (Head->next == NULL) {
		Head->next = Nova_Drzava;
	}
	while (Head->next != NULL && strcmp(Head->next->Naziv_Drzava, Nova_Drzava->Naziv_Drzava) < 0) {
		Head = Head->next;
	}
	Nova_Drzava->next = Head->next;
	Head->next = Nova_Drzava;

	int Unos_Gradova(Nova_Drzava, file);

	return USPJESNO_IZVRSENO;

}

int Unos_Gradova(P_Drzava Nova_Drzava, char file) {
	
	
	char buffer[MAX_LINE];
	FILE* fp = NULL;
	char* p = buffer;
	char drzava[MAX_LINE];
	char file[MAX_LINE];
	fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Dokument se nije otvorio.\n");
		return FILE_NOT_OPEN;
	}

	char naziv_grada[MAX_LINE];
	int broj_stanovnika;
	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		sscanf(p, " %s %d", naziv_grada, broj_stanovnika);
		NoviGrad(naziv_grada,broj_stanovnika,Nova_Drzava->root);
	}



}
int NoviGrad(naziv_grada, broj_stanovnika, Nova_Drzava->root) {


}