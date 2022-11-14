/*Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
rezultat.Stog je potrebno realizirati preko vezane liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum KRATICE {
	USPJESNO_ZAVRSEN_PROGRAM,
	USPJESNO_IZVRSENO,
	NEUSPJESNO_IZVRSENO,
	NIJE_PRONADEN,
	PRONADEN,
	MAX_LINE= 1024,
};


struct clan;
typedef struct clan* Pozicija;
typedef struct clan {
	float iznos;
	Pozicija next;
}clan;

int push(Pozicija, float);
int UpisIzDat(Pozicija);
int pop(Pozicija);
int BrisiSve(Pozicija);

int main(void) {

	clan Head1 = {
		.iznos = 0,
		.next = NULL
	};




	UpisIzDat(&Head1);
	printf("Rezulatat: %f", (Head1.next->iznos));
	BrisiSve(&Head1);



	return USPJESNO_ZAVRSEN_PROGRAM;
}


int push(Pozicija Head, float broj) {
	Pozicija NoviBroj = malloc(sizeof(clan));
	NoviBroj->iznos = broj;
	NoviBroj->next = Head->next;
	Head->next = NoviBroj;
	return USPJESNO_IZVRSENO;
}



int UpisIzDat(Pozicija head1) {
	int n = 0;
	float znak[MAX_LINE];
	float broj = 0;
	char buffer[MAX_LINE] = { 0 };
	char* p = buffer;
	FILE* fp = NULL;

	fp = fopen("postfix.txt", "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return NIJE_PRONADEN;
	}

	fgets(buffer, MAX_LINE, fp);
	while (strlen(p) > 0) {

		if (sscanf(p, " %f %n", &broj, &n) == 1) {
			push(head1, broj);
		}

		else if (sscanf(p, " %s %n", znak, &n) == 1) {
			if (strcmp(znak, "+") == 0)
			{
				float rezultat = head1->next->next->iznos + head1->next->iznos;
				pop(head1, head1->next->next);
				pop(head1, head1->next);
				push(head1, rezultat);
			}
			else if (strcmp(znak, "-") == 0)
			{
				float rezultat = head1->next->next->iznos - head1->next->iznos;
				pop(head1, head1->next->next);
				pop(head1, head1->next);
				push(head1, rezultat);
			}
			else if (strcmp(znak, "*") == 0)
			{
				float rezultat = head1->next->next->iznos * head1->next->iznos;
				pop(head1, head1->next->next);
				pop(head1, head1->next);
				push(head1, rezultat);
			}
			else if (strcmp(znak, "/") == 0)
			{
				float rezultat = head1->next->next->iznos / head1->next->iznos;
				pop(head1, head1->next->next);
				pop(head1, head1->next);
				push(head1, rezultat);
			}
			else
			{
				printf("Kriva operacija");
			}
		}
		p += n;
	}
	fclose(fp);

	return USPJESNO_IZVRSENO;
}

int pop(Pozicija Head, Pozicija zaBrisat) {
	while (Head->next != zaBrisat) {
		Head = Head->next;
	}
	Head->next = zaBrisat->next;
	free(zaBrisat);
	if (zaBrisat != NULL) {
		//printf("Izbrisano!");
	}
	else printf("Nije izbrisano.");
}


int BrisiSve(Pozicija Head) {
	Pozicija temp;
	while (Head->next != NULL) {
		temp = Head->next;
		Head->next = Head->next->next;
		free (temp);
	}
	return USPJESNO_IZVRSENO;
}

