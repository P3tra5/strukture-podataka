#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define USPJESNO_ZAVRSEN_PROGRAM (0)
#define UNOS_NA_POCETAK (1)
#define UNOS_NA_KRAJ (2)
#define ISPIS_LISTE (3)
#define NADI_ELEMENT (4)
#define U_TOKU (5)
#define IZBRISI_ELEMENT (7)
#define DODAJ_IZA (8)
#define DODAJ_ISPRED (9)
#define SORTIRAJ_LISTU (10)
#define USPJESNO_IZVRSENO (15)
#define NIJE_PRONADEN (99)
#define PRONADEN (100)
#define MAX_IME (1021)


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
Pozicija NadiElement(Pozicija,Pozicija);
int IzbrisiElement(Pozicija, osoba);
int DodajIza(osoba,Pozicija,Pozicija);
int DodajIspred(osoba, Pozicija, Pozicija);
int SortirajListu(Pozicija);

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
		printf("4-Nadi element prema imenu:\n7-Izbrisi element:\n8-Dodaj iza odredenog elementa\n");
		printf("9-Dodaj ispred elementa prema imenu:\n10-Sortiraj listu prema prezimenu:\n");

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
			Pozicija Trazena;
			Trazena = malloc(sizeof(osoba));
			Trazena->ime == NULL;
			printf("Unesi ime osobe koju trazis: ");
			scanf("%s", Trazena->ime);
			Trazena = NadiElement(Head.next, Trazena);
			if (Trazena->ime != NULL) {
				printf("Trazena osoba se preziva %s\n", Trazena->prezime);
			}
			else printf("Ta osoba ne postoji u listi");
		}
		if (naredba == IZBRISI_ELEMENT) {
			osoba Trazena;
			printf("Unesi ime osobe koju zelis izbrisat: ");
			scanf("%s", Trazena.ime);

			if (IzbrisiElement(&Head, Trazena) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno.\n");

			}
			else printf("Greska pri unosu!\n");
		}

		if (naredba==DODAJ_IZA){
			Pozicija Trazena;
			Trazena = malloc(sizeof(osoba));
			Trazena->ime == NULL;
			printf("Unesi ime osobe iza koje zelis dodati: ");
			scanf("%s", Trazena->ime);
			osoba Nova;
			printf("Unesite ime i prezime: ");
			scanf("%s %s", Nova.ime, Nova.prezime);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &Nova.godina_rodenja);
			if (DodajIza(Nova, Trazena, Head.next) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno\n");
			}
			else printf("Greska pri unosu!\n");
		
		}
		if (naredba == DODAJ_ISPRED) {
			Pozicija Trazena;
			Trazena = malloc(sizeof(osoba));
			Trazena->ime == NULL;
			printf("Unesi ime osobe ispred koje zelis dodati: ");
			scanf("%s", Trazena->ime);
			osoba Nova;
			printf("Unesite ime i prezime: ");
			scanf("%s %s", Nova.ime, Nova.prezime);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &Nova.godina_rodenja);
			if (DodajIspred(Nova, Trazena, Head.next) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno\n");
			}
			else printf("Greska pri unosu!\n");

		}

		if (naredba == SORTIRAJ_LISTU) {
			if (SortirajListu(Head.next) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno\n");
			}
			else printf("Greska pri unosu!");

		}



		printf("Unesite broj 5 za novu naredbu a 6 za prekid programa: ");
		scanf("%d", &rad_programa);
		
	}

	return USPJESNO_ZAVRSEN_PROGRAM;
}

int NaPocetak(Pozicija* Head_Next, osoba Unesena_Osoba) {
	osoba* Nova_Osoba = malloc(sizeof(osoba));
	*Nova_Osoba = Unesena_Osoba;
	Nova_Osoba->next = *Head_Next;
	*Head_Next = Nova_Osoba;

	return USPJESNO_IZVRSENO;

}
int IspisListe(Pozicija Head_Next) {
	while (Head_Next != NULL) {
		printf("%s %s\n", Head_Next->ime, Head_Next->prezime);
		Head_Next = Head_Next->next;
	}
	printf("Kraj liste.");
	return USPJESNO_IZVRSENO;
}

int NaKraj(osoba* Head, osoba Unesena_Osoba) {
	while (Head->next != NULL) {
		Head = Head->next;
	};
	osoba* Nova_Osoba = malloc(sizeof(osoba));
	*Nova_Osoba = Unesena_Osoba;
	Head->next = Nova_Osoba;
	Nova_Osoba->next = NULL;
	return USPJESNO_IZVRSENO;
}

Pozicija NadiElement(Pozicija Head_Next, Pozicija Trazena_Osoba) {
	while (Head_Next != NULL) {
		
		if (strcmp(Head_Next->ime, Trazena_Osoba->ime) == 0) {
			return Head_Next;
		}
		Head_Next = Head_Next->next;
	}
	
}

Pozicija NadiPrethodni(Pozicija P, Pozicija Trazena_Osoba) {
	while (P->next != NULL) {

		if (strcmp(P->next->ime, Trazena_Osoba->ime) == 0) {
			return P;
		}
		P = P->next;
	}

}

int DodajIza(osoba Unesena_Osoba,Pozicija Trazena_Osoba,Pozicija P){
	osoba* Nova_Osoba = malloc(sizeof(osoba));
	*Nova_Osoba = Unesena_Osoba;
	Trazena_Osoba = NadiElement(P, Trazena_Osoba);
	Nova_Osoba->next = Trazena_Osoba->next;
	Trazena_Osoba->next = Nova_Osoba;
	return USPJESNO_IZVRSENO;
}

int DodajIspred(osoba Unesena_Osoba, Pozicija Prethodna_Osoba, Pozicija P) {
	osoba* Nova_Osoba = malloc(sizeof(osoba));
	*Nova_Osoba = Unesena_Osoba;
	Prethodna_Osoba = NadiPrethodni(P, Prethodna_Osoba);
	Nova_Osoba->next = Prethodna_Osoba->next;
	Prethodna_Osoba->next = Nova_Osoba;
	
	return USPJESNO_IZVRSENO;
}

int IzbrisiElement(Pozicija P, osoba Trazena) {
	
	while (strcmp((P->next->ime), Trazena.ime) != 0 && P->next->next != NULL) {
		P = P->next;
	}
	if (strcmp((P->next->ime), Trazena.ime) == 0) {
		P->next = (P->next)->next;
		printf("Izbrisano.\n");
	}
	else printf("Ta osoba ne postoji u listi.\n");
	return USPJESNO_IZVRSENO;

}

int SortirajListu(Pozicija P) {
	Pozicija i, j, temp,zadnji;
	zadnji = NULL;
	while (P->next != zadnji) {
		i = P;
		j = P->next;
		while (j->next != zadnji){
			if (strcmp(j->prezime, j->next->prezime)>0) {
				temp = j->next;
				i->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}
			i = j;
			j = j->next;
		}
		zadnji = j;
	}
	return USPJESNO_IZVRSENO;
}

//Dodat slucaj ako ne postoji iza ili ispred koga se dodaje
