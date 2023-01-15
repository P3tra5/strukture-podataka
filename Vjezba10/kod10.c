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

int CitaDatDrzave(P_Drzava head);
int NovaDrzava(char, char, P_Drzava);
int CitaDatGradovi(P_Drzava, char);
int NoviGrad(char, int, P_Grad);
int UnosGrada(P_Grad root, P_Grad Novi_Grad);



int main(void) {
	
	return 0;
}

int CitaDatDrzave(P_Drzava head){
	FILE* fp=NULL;
	char buffer[MAX_LINE] = { 0 };
	char* p = buffer;
	char drzava[MAX_LINE] = { 0 };
	char file[MAX_LINE] = { 0 };
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

	while (Head->next != NULL && strcmp(Head->next->Naziv_Drzava, Nova_Drzava->Naziv_Drzava) < 0) {
		Head = Head->next;
	}
	Nova_Drzava->next = Head->next;
	Head->next = Nova_Drzava;

	int Unos_Gradova(Nova_Drzava, file);

	return USPJESNO_IZVRSENO;

}

int CitaDatGradovi(P_Drzava Nova_Drzava, char file) {
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char* p = buffer;
	char drzava[MAX_LINE] = { 0 };
	char file[MAX_LINE] = { 0 };
	char naziv_grada[MAX_LINE]  = { 0 };
	int broj_stanovnika = 0;
	
	fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Dokument se nije otvorio.\n");
		return FILE_NOT_OPEN;
	}
	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		sscanf(p, " %s %d", naziv_grada, &broj_stanovnika);
		NoviGrad(naziv_grada,broj_stanovnika,Nova_Drzava->root);
	}

	return USPJESNO_IZVRSENO;

}

int NoviGrad(char Naziv_Grada, int broj_stanovnika, Nova_Drzava->root) {
	P_Grad Novi_Grad = NULL;
	
	P_Grad Novi_Grad = malloc(sizeof(Grad));
	Novi_Grad->L = NULL;
	Novi_Grad->D = NULL;
	Novi_Grad->broj_stanovnika = 0;
	if (Nova_Drzava == NULL) {
		printf("Memorija nije alocirana.");
		return NEUSPJESNO_IZVRSENO;
	}
	strcpy(Novi_Grad->Naziv_Grad, Naziv_Grad);
	
	return USPJESNO_IZVRSENO;
}

int UnosGrada(P_Grad root, P_Grad Novi_Grad){
	if(root == NULL)
		root = Novi_Grad;
	else if(Novi_Grad->broj_stanovnika > root->broj_stanovnika)
		root->D = UnosGrad(root->D, Novi_Grad);
	else if(Novi_Grad->broj_stanovnika < root->broj_stanovnika)
		root->L = UnosGrad(root->L, Novi_Grad);
	else{
		if(strcmp(Novi_Grad->Naziv_Grad, root->Naziv_Grad) > 0)
			root->D = UnosGrad(root->D, Novi_Grad);
		else if(strcmp(Novi_Grad->Naziv_Grad, root->Naziv_Grad) < 0)
			root->L = UnosGrad(root->L, Novi_Grad);
	}
	
	return USPJESNO_IZVRSENO;
}
