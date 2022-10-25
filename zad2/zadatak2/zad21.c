#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_IME (1021)
#define USPJESNO_ZAVRSEN_PROGRAM (0)
#define USPJESNO_IZVRSENO (10)
#define U_TOKU (5)
#define ISPIS_LISTE (3)
#define UNOS_NA_POCETAK (1)
#define UNOS_NA_KRAJ (2)
#define NADI_ELEMENT (4)
#define NIJE_PRONADEN (99)
#define PRONADEN (100)
#define IZBRISI_ELEMENT (7)


struct osoba;
typedef struct osoba* Pozicija;
typedef struct osoba {
	char ime[MAX_IME];
	char prezime[MAX_IME];
	int godina_rodenja;
	Pozicija next;
}osoba;

int NaPocetak(Pozicija*,osoba );
int IspisListe(Pozicija);
int NaKraj(osoba*,osoba);
int NadiElement(Pozicija,osoba);
int IzbrisiElement();

int main(void) {

	osoba Head;
	Head.ime[MAX_IME] = (0);
	Head.prezime[MAX_IME] = (0);
	Head.godina_rodenja = 0;
	Head.next = NULL;
	int rad_programa = U_TOKU;
	while (rad_programa == U_TOKU) {
		
		int naredba = 0;
		printf("Unesite broj za naredbu.\n1-Unos na pocetak liste:\n2-Unos na kraj liste\n3-Ispis liste:\n4-Nadi element prema imenu:\n7-Izbrisi element:\n");
		scanf("%d", &naredba);


		if (naredba == UNOS_NA_POCETAK) {
			osoba Nova;
			printf("Unesite ime i prezime: ");
			scanf("%s %s", Nova.ime, Nova.prezime);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &Nova.godina_rodenja);
			if (NaPocetak(&Head.next, Nova) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno.\n");
			}
			else printf("Nije izvrseno.\n");
		}

		if (naredba == UNOS_NA_KRAJ) {
			osoba Nova;
			printf("Unesite ime i prezime: ");
			scanf("%s %s", Nova.ime, Nova.prezime);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &Nova.godina_rodenja);
			if (NaKraj(&Head, Nova) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno.\n");
			}
			else printf("Nije izvrseno.\n");
		}
		if (naredba == ISPIS_LISTE) {
			if (IspisListe(Head.next) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno.\n");
			}
			else printf("Nije izvrseno.\n");
		}
		if (naredba == NADI_ELEMENT) {
			osoba Trazena;
			printf("Unesi ime osobe koju trazis: ");
			scanf("%s", Trazena.ime);
			if (NadiElement(Head.next, Trazena) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno.\n");
			}
			else printf("Nije izvrseno.\n");
		}
		if (naredba == IZBRISI_ELEMENT) {
			osoba Trazena;
			printf("Unesi ime osobe koju zelis izbrisat: ");
			scanf("%s", Trazena.ime);
			if (strcmp((Head.next->ime), Trazena.ime) == 0) {
				Head.next = (Head.next->next);
				printf("Izbrisano.\n");
			}
			else if(IzbrisiElement(Head.next, Trazena) == USPJESNO_IZVRSENO){
				printf("Uspjesno izvrseno.\n");
			}
		}
		
		printf("Unesite broj 5 za novu naredbu a 6 za prekid programa: ");
		scanf("%d", &rad_programa);
		
	}

	return USPJESNO_ZAVRSEN_PROGRAM;
}

int NaPocetak(Pozicija* Head_Next, osoba Unos) {
	osoba* Nova = malloc(sizeof(osoba));
	*Nova = Unos;
	Nova->next = *Head_Next;
	*Head_Next = Nova;

	return USPJESNO_IZVRSENO;

}
int IspisListe(Pozicija Head_Next) {
	while (Head_Next != NULL) {
		printf("%s\n", Head_Next->ime);
		Head_Next = Head_Next->next;
	}
	printf("Kraj liste.");
	return USPJESNO_IZVRSENO;
}

//PITANJE: Da san za argument umisto osoba* Head stavia Pozicija* Head.Next kako bi izvea WHILE petlju?
int NaKraj(osoba* Head, osoba Unos) {
	while (Head->next != NULL) {
		Head = Head->next;
	};
	osoba* Nova = malloc(sizeof(osoba));
	*Nova = Unos;
	Head->next = Nova;
	Nova->next = NULL;
	return USPJESNO_IZVRSENO;
}

int NadiElement(Pozicija Head_Next, osoba Trazena) {
	while (Head_Next != NULL) {
		
		if (strcmp(Head_Next->ime, Trazena.ime) == 0) {
			printf("Trazena osoba se preziva %s\n", Head_Next->prezime);
		}
		Head_Next = Head_Next->next;
	}
	return USPJESNO_IZVRSENO;
}

int IzbrisiElement(Pozicija P, osoba Trazena) {
	
	//else {
		while (strcmp((P->next->ime), Trazena.ime) != 0 && P->next->next != NULL) {
			P = P->next;
		}
		if (strcmp((P->next->ime), Trazena.ime) == 0) {
			P->next = (P->next)->next;
			printf("Izbrisano.\n");
		}
		else printf("Ta osoba ne postoji u listi.\n");
	//}
	return USPJESNO_IZVRSENO;

}