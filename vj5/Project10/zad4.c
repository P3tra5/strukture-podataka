/*
Napisati program za zbrajanje i množenje polinoma.
Koeficijenti i eksponenti se èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.
*/

// 1. procitati koef i bazu iz txt i staviti ih sortirano u vezanu listu
// 2. zbrojit
// 3. pomnozit koristeci funkciju za zbrajanje
// 4. ispis rezultata

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum ERROR_CODE{
	USPJESNO_ZAVRSEN_PROGRAM,
	USPJESNO_IZVRSENO,
	NEUSPJESNO_IZVRSENO,
	NIJE_PRONADEN ,
	PRONADEN,
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

int main(void) {

	clan Head1 = {
		.iznos= 0,
		.next = NULL
	};

	


	UpisIzDat(&Head1);
	printf("Rezulatat: %f", (Head1.next->iznos));

	

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
	int n=0;
	char znak[MAX_LINE];
	char buffer [MAX_LINE] = { 0 };
	char *p = buffer;
	FILE* fp = NULL;

	fp = fopen("postfix.txt", "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return NIJE_PRONADEN;
	}

	fgets(buffer, MAX_LINE, fp);
	while(strlen(p)>0) {
		
		if (sscanf(p, " %s %n", znak, &n) == 1) {
			float broj = atof(znak);
			push(head1, broj);
		}
		
		else if (sscanf(p, " %s %n", znak, &n) == 0) {
			if (strcmp(znak, "+") == 0)
			{
				float rezultat = head1->next->next->iznos + head1->next->iznos;
				pop(head1, head1->next->next);
				pop(head1, head1->next);
			}
			else if (strcmp(znak, "-") == 0)
			{
				float rezultat = head1->next->next->iznos - head1->next->iznos;
				pop(head1, head1->next->next);
				pop(head1, head1->next);
			}
			else if (strcmp(znak, "*") == 0)
			{
				float rezultat = head1->next->next->iznos * head1->next->iznos;
				pop(head1, head1->next->next);
				pop(head1, head1->next);
			}
			else if (strcmp(znak, "/") == 0)
			{
				float rezultat = head1->next->next->iznos / head1->next->iznos;
				pop(head1, head1->next->next);
				pop(head1, head1->next);
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

