/*#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_IME (1021)
#define USPJESNO_ZAVRSEN_PROGRAM (0)
#define USPJESNO_IZVRSENO (10)
#define U_TOKU (5)
#define UNOS_NA_POCETAK (1)
#define UNOS_NA_KRAJ (2)
#define ISPIS_LISTE (3)

struct osoba;
typedef struct osoba* Pozicija;
typedef struct osoba {
	char ime[MAX_IME];
	char prezime[MAX_IME];
	int godina_rodenja;
	Pozicija next;
}osoba;

Pozicija NaPocetak(Pozicija*);
int NaKraj(osoba, Pozicija);
int IspisListe(Pozicija);

int main(void) {
	
	osoba Head;
	Head.ime[MAX_IME] = (0);
	Head.prezime[MAX_IME] = (0);
	Head.godina_rodenja = 0;
	Head.next = NULL;

	int rad_programa = U_TOKU;
	while (rad_programa == U_TOKU) {
		
		int naredba = 0;
		printf("Unesite broj za naredbu.\n1-Unos na pocetak liste:\n2-Unos na kraj liste\n3-Ispis liste:\n");
		scanf("%d", &naredba);

		if (naredba == UNOS_NA_POCETAK) {			
			Pozicija temp = Head.next;
			Head.next=NaPocetak(Head.next);
			if (temp != Head.next) {
				printf("Dodano na pocetak!");
			}
		}
		if (naredba == ISPIS_LISTE) {
			if (IspisListe(Head.next) == USPJESNO_IZVRSENO) {
				printf("Uspjesno ispisana lista.");
			}
			else printf("Neuspjesno ispisana lista.");

		}
		if (naredba == UNOS_NA_KRAJ) {
			osoba Nova;
			printf("Unesite ime i prezime: ");
			scanf("%s %s", Nova.ime, Nova.prezime);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &Nova.godina_rodenja);
			int c=NaKraj(Nova, Head.next);
		}
		
		
		
		printf("Unesite broj 5 za novu naredbu a 6 za prekid programa: ");
		scanf("%d", &rad_programa);

		printf("\nRadi.");
		
	
	}
	


	return USPJESNO_ZAVRSEN_PROGRAM;
}

Pozicija NaPocetak(Pozicija* Head_Next){
	osoba* Nova=(osoba*)malloc(sizeof(osoba));
	printf("Unesite ime i prezime: ");
	scanf("%s %s", Nova->ime, Nova->prezime);
	printf("Unesite godinu rodenja: ");
	scanf("%d", &Nova->godina_rodenja);
	Nova->next = Head_Next;
	
	return Nova;
}

int NaKraj(osoba Unos, Pozicija Head_Next) {
	Pozicija P;
	
	while (Head_Next->next != NULL) {
		Head_Next=Head_Next->next;
	}
	P = (Pozicija)malloc(sizeof(osoba));
	*P = Unos;
	Head_Next->next = P;
	P->next = NULL;
	
	return USPJESNO_IZVRSENO;

}

int IspisListe(Pozicija Head_Next) {
	while (Head_Next != NULL) {
		printf("%s\n", Head_Next->ime);
		Head_Next = Head_Next->next;
	}
	printf("Kraj liste.");
	return USPJESNO_IZVRSENO;
}*/