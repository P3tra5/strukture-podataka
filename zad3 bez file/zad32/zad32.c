#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*enum ERROR_CODE{
    USPJESNO_ZAVRSEN_PROGRAM,
    UNOS_NA_POCETAK,
    UNOS_NA_KRAJ,
    ISPIS_LISTE,
    NADI_ELEMENT,
    U_TOKU,
    IZBRISI_ELEMENT = 7,
    DODAJ_IZA,
    DODAJ_ISPRED,
    SORTIRAJ_LISTU,
    BRISI_SVE,
    UPIS_DAT,
    CITA_DAT,
    USPJESNO_IZVRSENO = 15,
    NEUSPJESNO_IZVRSENO,
    NIJE_PRONADEN = 99,
    PRONADEN = 100,
    MAX_IME = 1021
};*/

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
#define BRISI_SVE (11)
#define UPIS_DAT (12)
#define CITA_DAT (13)
#define USPJESNO_IZVRSENO (15)
#define NEUSPJESNO_IZVRSENO (16) //error pa vrijednost triba bit neg?
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

int NaPocetak(Pozicija*, osoba);
int IspisListe(Pozicija);
int NaKraj(osoba*, osoba);
Pozicija NadiElement(Pozicija, Pozicija);
int IzbrisiElement(Pozicija, osoba);
int DodajIza(osoba, Pozicija, Pozicija);
int DodajIspred(osoba, Pozicija, Pozicija);
int SortirajListu(Pozicija);
int BrisiSve(Pozicija);
int UpisUDat(Pozicija, char*);
int IspisIzDat(Pozicija, char*);

int main(void) {

	osoba Head = {
		.ime = {0},
		.prezime = {0},
		.godina_rodenja = 0,
		.next = NULL
	};
	char imedatoteke[MAX_IME] = { 0 };
	int rad_programa = U_TOKU;
	while (rad_programa == U_TOKU) {

		int naredba = 0;
		printf(
			"Unesite broj za naredbu.\n"
			"1-Unos na pocetak liste:\n"
			"2-Unos na kraj liste\n"
			"3-Ispis liste:\n"
			"4-Nadi element prema imenu:\n"
			"7-Izbrisi element:\n"
			"8-Dodaj iza odredenog elementa\n"
			"9-Dodaj ispred elementa prema imenu:\n"
			"10-Sortiraj listu prema prezimenu:\n"
			"11-Izbrisi cijelu listu\n"
			"12-Upisuje listu u datoteku:\n13-Cita listu iz datoteke:\n\n"
		);

		scanf(" %d", &naredba);


		if (naredba == UNOS_NA_POCETAK) {
			osoba Nova;
			printf("Unesite ime i prezime: ");
			scanf(" %s %s", Nova.ime, Nova.prezime);
			printf("Unesite godinu rodenja: ");
			scanf(" %d", &Nova.godina_rodenja);
			if (NaPocetak(&Head, Nova) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno.\n");
			}
			else printf("Nije izvrseno.\n");
		}

		else if (naredba == UNOS_NA_KRAJ) {
			osoba nova;
			printf("Unesite ime i prezime: ");
			scanf("%s %s", nova.ime, nova.prezime);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &nova.godina_rodenja);
			if (NaKraj(&Head, nova) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno.\n");
			}
			else printf("Nije izvrseno.\n");
		}
		else if (naredba == ISPIS_LISTE) {
			if (IspisListe(Head.next) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno.\n");
			}
			else printf("Nije izvrseno.\n");
		}
		else if (naredba == NADI_ELEMENT) {
			Pozicija Trazena;
			Trazena = malloc(sizeof(osoba));
			if (Trazena != NULL) {
				Trazena->prezime == NULL;
				printf("Unesi ime osobe koju trazis: ");
				scanf("%s", Trazena->ime);
				Trazena = NadiElement(Head.next, Trazena);
				if (Trazena != NULL) {
					printf("Trazena osoba se preziva %s\n", Trazena->prezime);
				}
				else printf("Ta osoba ne postoji u listi\n");
			}
			else printf("Memorija nije alocirana");
		}
		else if (naredba == IZBRISI_ELEMENT) {
			osoba Trazena;
			printf("Unesi ime osobe koju zelis izbrisat: ");
			scanf("%s", Trazena.ime);

			if (IzbrisiElement(&Head, Trazena) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno.\n");

			}
			else printf("Greska pri unosu!\n");
		}

		else if (naredba == DODAJ_IZA) {
			Pozicija Trazena;
			Trazena = malloc(sizeof(osoba));
			if (Trazena != NULL) {
				Trazena->prezime == NULL;
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
			else printf("Memorija nije alocirana.\n");

		}
		else if (naredba == DODAJ_ISPRED) {
			Pozicija Trazena;
			Trazena = malloc(sizeof(osoba));
			if (Trazena != NULL) {
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
			else printf("Greska pri unosu!\n");

		}

		else if (naredba == SORTIRAJ_LISTU) {
			if (SortirajListu(&Head) == USPJESNO_IZVRSENO) {
				printf("Uspjesno izvrseno\n");
			}
			else printf("Greska pri unosu!");

		}

		else if (naredba == BRISI_SVE) {
			if (BrisiSve(Head.next) == USPJESNO_IZVRSENO) {
				Head.next = NULL;
				printf("Memorija ociscena\n");
			}
			else printf("Memorija nije ociscena!\n");

		}

		else if (naredba == UPIS_DAT) {
			printf("Unesite ime datoteke: ");
			scanf(" %s", imedatoteke);
			UpisUDat(Head.next, imedatoteke);
		}

		else if (naredba == CITA_DAT) {
			printf("Unesite ime datoteke: ");
			scanf(" %s", imedatoteke);
			IspisIzDat(&Head,imedatoteke);
		}

		else {
			printf("Greska pri unosu!\n");
		}


		printf("Unesite broj 5 za novu naredbu a 6 za prekid programa: ");
		scanf(" %d", &rad_programa);

	}
	if (BrisiSve(Head.next) == USPJESNO_IZVRSENO) {
		printf("Memorija ociscena");
	}
	else printf("Memorija nije ociscena");

	return USPJESNO_ZAVRSEN_PROGRAM;
}

int NaPocetak(Pozicija Head, osoba Unesena_Osoba) {
	osoba* Nova_Osoba = malloc(sizeof(osoba));
	if (Nova_Osoba != NULL) {
		*Nova_Osoba = Unesena_Osoba;
		Nova_Osoba->next = Head->next;
		Head->next = Nova_Osoba;

		return USPJESNO_IZVRSENO;
	}
	else return NEUSPJESNO_IZVRSENO;

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
	if (Nova_Osoba != NULL) {
		*Nova_Osoba = Unesena_Osoba;
		Head->next = Nova_Osoba;
		Nova_Osoba->next = NULL;
		return USPJESNO_IZVRSENO;
	}
	else return NEUSPJESNO_IZVRSENO;
}

Pozicija NadiElement(Pozicija Head_Next, Pozicija Trazena_Osoba) {
	while (Head_Next != NULL && strcmp(Head_Next->ime, Trazena_Osoba->ime) != 0) {

		Head_Next = Head_Next->next;
	}

	return Head_Next;
}

Pozicija NadiPrethodni(Pozicija P, Pozicija Trazena_Osoba) {
	while (P->next != NULL) {

		if (strcmp(P->next->ime, Trazena_Osoba->ime) == 0) {
			return P;
		}
		P = P->next;
	}

}

int DodajIza(osoba Unesena_Osoba, Pozicija Trazena_Osoba, Pozicija P) {
	osoba* Nova_Osoba = malloc(sizeof(osoba));
	if (Nova_Osoba != NULL) {
		*Nova_Osoba = Unesena_Osoba;
		Trazena_Osoba = NadiElement(P, Trazena_Osoba);
		Nova_Osoba->next = Trazena_Osoba->next;
		Trazena_Osoba->next = Nova_Osoba;
		return USPJESNO_IZVRSENO;
	}
	else return NEUSPJESNO_IZVRSENO;
}

int DodajIspred(osoba Unesena_Osoba, Pozicija Prethodna_Osoba, Pozicija P) {
	osoba* Nova_Osoba = malloc(sizeof(osoba));
	if (Nova_Osoba != NULL) {
		*Nova_Osoba = Unesena_Osoba;
		Prethodna_Osoba = NadiPrethodni(P, Prethodna_Osoba);
		Nova_Osoba->next = Prethodna_Osoba->next;
		Prethodna_Osoba->next = Nova_Osoba;

		return USPJESNO_IZVRSENO;
	}
	else return NEUSPJESNO_IZVRSENO;
}

int IzbrisiElement(Pozicija P, osoba Trazena) {

	while (strcmp((P->next->ime), Trazena.ime) != 0 && P->next->next != NULL) {
		P = P->next;
	}
	if (strcmp((P->next->ime), Trazena.ime) == 0) {
		Pozicija temp = NULL;
		temp = P->next;
		P->next = (P->next)->next;
		free(temp);
		printf("Izbrisano.\n");
	}
	else printf("Ta osoba ne postoji u listi.\n");
	return USPJESNO_IZVRSENO;

}

int SortirajListu(Pozicija P) {
	Pozicija i, j, temp, zadnji;
	i = NULL;
	j = NULL;
	temp = NULL;
	zadnji = NULL;
	while (P->next != zadnji) {
		i = P;
		j = P->next;
		while (j->next != zadnji) {
			if (strcmp(j->prezime, j->next->prezime) > 0) {
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


int BrisiSve(Pozicija head)
{
	Pozicija prev = head;

	while (head != NULL)
	{
		head = head->next;

		printf("%s izbrisan!\n", prev->ime);
		free(prev);
		prev = head;
	}
	return USPJESNO_IZVRSENO;

}

int UpisUDat(Pozicija p, char* imedatoteke) {
	FILE* fp = NULL;
	fp = fopen(imedatoteke, "w");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return NIJE_PRONADEN;
	}
	while (p != NULL) {
		fprintf(fp, "%s\t %s\t %10d\n", p->ime, p->prezime, p->godina_rodenja);
		p = p->next;
	}
	fclose(fp);

	return USPJESNO_IZVRSENO;
}

int IspisIzDat(Pozicija head, char* imedatoteke) {
	
	FILE* fp = NULL;

	fp = fopen(imedatoteke, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return NIJE_PRONADEN;
	}

	while (!feof(fp)) {
		osoba Nova = {
		.ime = {0},
		.prezime = {0},
		.godina_rodenja = 0,
		.next = NULL
		};
		fscanf(fp, " %s %s %d", Nova.ime, Nova.prezime, &Nova.godina_rodenja);
		
		
		if (NaPocetak(head, Nova) == USPJESNO_IZVRSENO) {
			printf("Uspjesno izvrseno.\n");
		}
		else printf("Nije izvrseno.\n");
	}
	
	fclose(fp);

	return USPJESNO_IZVRSENO;
}
//Dodat slucaj ako ne postoji iza ili ispred koga se dodaje
