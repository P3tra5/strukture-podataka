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


typedef struct Drzava* P_Drzava;
typedef struct Drzava {
	char Naziv_Drzava[MAX_LINE];
	P_Drzava L;
	P_Drzava D;
	P_Grad head;
}Drzava;

typedef struct Grad* P_Grad;
typedef struct Grad {
	char Naziv_Grad[MAX_LINE];
	int broj_stanovnika;
	P_Grad next;
}Grad;

int CitaDatDrzave(P_Drzava);
P_Drzava UnosDrzava(P_Drzava, char*, char*);
int CitaDatGradovi(P_Drzava, char*);
int NoviGrad(char*, int, P_Drzava);
int UnosGrada(P_Grad, P_Grad);
int PrintAll(P_Drzava);
//int PrintSome(P_Drzava, char*, int);
int ispisListe(P_Grad);
//int FiltriraniIspisStabla(P_Grad, int);



int main(void) {

	Drzava Root_Drzava = {
		.Naziv_Drzava = { 0 },
		.L = NULL,
		.D = NULL,
		.head = NULL
	};


	if (CitaDatDrzave(&Root_Drzava) == USPJESNO_IZVRSENO)
	{
		printf("Uspjesno uneseno. \n");
	}


	char drzava[MAX_LINE] = { 0 };
	int broj_st = 0;
	PrintAll(&Root_Drzava);

	printf("Unesi drzavu pa minimalan broj stanovnika: ");
	scanf(" %s %d", drzava, &broj_st);

	PrintSome(&Root_Drzava, &drzava, broj_st);

	return 0;
}

int CitaDatDrzave(P_Drzava root) { //
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char* p = buffer;
	char drzava[MAX_LINE] = { 0 };
	char file[MAX_LINE] = { 0 };
	fp = fopen("drzave.txt", "r");
	if (fp == NULL) {
		printf("Dokument se nije otvorio.\n");
		return FILE_NOT_OPEN;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		sscanf(p, " %s %s", drzava, file);
		P_Drzava Nova_Drzava = malloc(sizeof(Drzava));
		Nova_Drzava->L = NULL;
		Nova_Drzava->D = NULL;
		if (Nova_Drzava == NULL) {
			printf("Memorija nije alocirana.");
			return NEUSPJESNO_IZVRSENO;
		}
		strcpy(Nova_Drzava->Naziv_Drzava, drzava);
		UnosDrzava(root, Nova_Drzava, &file);
	}

	fclose(fp);
}

P_Drzava UnosDrzava(P_Drzava root, char* Nova, char* file) { //
	
	if (root == NULL)
		{
			root->head = NULL;
			root->head = ProcitajDatGradovi(root->head, file);
		}
		else if (strcmp(root->Naziv_Drzava, Nova) > 0)
			root->L = UnosDrzava(root->L, Nova, file);
		else if (strcmp(root->Naziv_Drzava, Nova) < 0)
			root->D = UnosDrzava(root->D, Nova, file);

	CitaDatGradovi(Nova, file);

		return root;
	}

int CitaDatGradovi(P_Drzava Nova_Drzava, char *file) { //
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char* p = buffer;
	char naziv_grada[MAX_LINE] = { 0 };
	int broj_stanovnika = 0;

	fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Dokument se nije otvorio.\n");
		return FILE_NOT_OPEN;
	}
	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		sscanf(p, " %s %d", naziv_grada, &broj_stanovnika);
		NoviGrad(&naziv_grada, broj_stanovnika, Nova_Drzava);
	}

	return USPJESNO_IZVRSENO;
}

int NoviGrad(char* Naziv_Grada, int broj_stanovnika, P_Drzava drzava) { //
	//P_Grad Novi_Grad = NULL;

	P_Grad Novi_Grad = malloc(sizeof(Grad));
	Novi_Grad->next = NULL;
	Novi_Grad->broj_stanovnika = broj_stanovnika;
	if (Novi_Grad == NULL) {
		printf("Memorija nije alocirana.");
		return NEUSPJESNO_IZVRSENO;
	}
	strcpy(Novi_Grad->Naziv_Grad, Naziv_Grada);

	UnosGrada(&(drzava->head), Novi_Grad);

	return USPJESNO_IZVRSENO;
}

int UnosGrada(P_Grad head, P_Grad Novi_Grad) { //

	while (head->next != NULL)
	{
		if (Novi_Grad->broj_stanovnika < head->next->broj_stanovnika)
			break;
		else if (Novi_Grad->broj_stanovnika == head->next->broj_stanovnika)
		{
			if (strcmp(Novi_Grad->Naziv_Grad, head->next->Naziv_Grad) < 0)
				break;
			else if (strcmp(Novi_Grad->Naziv_Grad, head->next->Naziv_Grad) > 0)
			{
				head = head->next;
				continue;
			}
		}
		head = head->next;
	}
	Novi_Grad->next = head->next;
	head->next = Novi_Grad;

	return USPJESNO_IZVRSENO;
}

int PrintAll(P_Drzava root) { //valjda al vjv ne
	if (root->L != NULL) {
		PrintAll(root->L);
	}
	printf("Gradovi iz %s: ", root->Naziv_Drzava);
	ispisListe(root->head);
	printf("\n");
	while (root->D != NULL) {
		printf("Gradovi iz %s: ", root->Naziv_Drzava);
		ispisListe(root->head);
		printf("\n");
		root = root->D;
	}

	return USPJESNO_IZVRSENO;
}

int ispisListe(P_Grad head) { //
	while (head->next != NULL) {
			head = head->next;
			printf(" %s", head->Naziv_Grad);
		}

	return USPJESNO_IZVRSENO;
}

/*PrintSome(P_Drzava head_drzava, char* naziv_drzave, int broj_stanovnika) {
	while (strcmp(head_drzava->Naziv_Drzava, naziv_drzave) != 0 && head_drzava != NULL) {
		head_drzava = head_drzava->next;
	}
	if (head_drzava == NULL) {
		printf("Nema te drzave.");
	}
	else {
		printf("Gradovi iz %s: sa vise od %d stanovnika: ", head_drzava->Naziv_Drzava, broj_stanovnika);
		FiltriraniIspisStabla(head_drzava->root, broj_stanovnika);
		printf("\n");
	}

	return USPJESNO_IZVRSENO;
}

int FiltriraniIspisStabla(P_Grad root, int broj_stanovnika) {

	if (root->broj_stanovnika >= broj_stanovnika) {
		printf("%s ", root);
		if (root->L != NULL) {
			ispisStabla(root->L);
		}
		if (root->D != NULL) {
			FiltriraniIspisStabla(root->D, broj_stanovnika);
		}

	}
	else {
		if (root->L != NULL) {
			FiltriraniIspisStabla(root->L, broj_stanovnika);
		}

	}

	return USPJESNO_IZVRSENO;
}*/