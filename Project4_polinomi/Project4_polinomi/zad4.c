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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum ERROR_CODE{
	USPJESNO_ZAVRSEN_PROGRAM,
	USPJESNO_IZVRSENO = 15,
	NEUSPJESNO_IZVRSENO,
	NIJE_PRONADEN = 99,
	PRONADEN = 100,
	MAX_LINE = 1024
};

struct polinom;
typedef struct polinom* Pozicija;
typedef struct polinom {
	int koeficijent;
	int eksponent;
	Pozicija next;
}polinom;

int Zbrajanje(Pozicija p, Pozicija q);
int Mnozenje(Pozicija p, Pozicija q);
int Ispis(Pozicija Head_Next);
int UnosElemenata(polinom*, polinom);

int main(void) {

	polinom Head1 = {
		.koeficijent = 0,
		.eksponent = 0,
		.next = NULL
	};

	polinom Head2 = {
		.koeficijent = 0,
		.eksponent = 0,
		.next = NULL
	};

	polinom HeadZbroj = {
		.koeficijent = 0,
		.eksponent = 0,
		.next = NULL
	};

	polinom HeadProdukt = {
		.koeficijent = 0,
		.eksponent = 0,
		.next = NULL
	};

	//DODAT cita iz datoteke i unosi u listu sortirano

	printf("Program zbraja i mnozi dva polinoma iz datoteke\n");
	printf("\nPrvi polinom je:\n");
	Ispis(Head1.next);
	printf("\nDrugi polinom je:\n");
	Ispis(Head2.next);

	Zbrajanje(&Head1, &Head2);
	printf("\nZbroj polinoma je:\n");
	Ispis(HeadZbroj.next);

	Mnozenje(&Head1, &Head2);
	printf("\nProdukt polinoma je:\n");
	Ispis(HeadProdukt.next);

	return USPJESNO_ZAVRSEN_PROGRAM;
}


int Zbrajanje(Pozicija Head1, Pozicija Head2) {
	Pozicija p = Head1;
	Pozicija q = Head2;
	Pozicija HeadZbroj = NULL;

	while (p->next != NULL && q->next != NULL) {
		
		if (p->eksponent > q->eksponent) {
			HeadZbroj = UnosElemenata(HeadZbroj, p->koeficijent, p->eksponent);
			p = p->next;
		}
		else if (p->eksponent < q->eksponent) {
			HeadZbroj = UnosElemenata(HeadZbroj, q->koeficijent, q->eksponent);
			q = q->next;
		}
		else{ //eksponenti su jednaki
			HeadZbroj = UnosElemenata(HeadZbroj, p->koeficijent + q->koeficijent, q->eksponent);
			p = p->next;
			q = q->next;
		}
	}
	//kad jedna lista dode do kraja da ispise kraj druge u rezultat
	while (p != NULL) {
		HeadZbroj = UnosElemenata(HeadZbroj, p->koeficijent, p->eksponent);
		p = p->next;
	}
	while (q != NULL) {
		HeadZbroj = UnosElemenata(HeadZbroj, q->koeficijent, q->eksponent);
		q = q->next;
	}
	
	return USPJESNO_IZVRSENO;
}

int Mnozenje(Pozicija p, Pozicija q) {



	return USPJESNO_IZVRSENO;
}

int UnosElemenata(polinom* Head, int k, int e) {
	Pozicija temp;
	polinom* NoviPolinom = malloc(sizeof(polinom));
		if (NoviPolinom == NULL) {
			printf("Memorija nije alocirana!\n");
			return USPJESNO_IZVRSENO;
		}
		else {
			printf("Memorija alocirana!\n");
		}
	NoviPolinom->koeficijent = k;
	NoviPolinom->eksponent = e;
	NoviPolinom->next = NULL;

	//ako je u listi samo Head ili je eksponent novog elementa veci od trenutno prvog elementa
	//spajamo novi element i on postaje novi head (sortirani unos padajuci)
	if (Head == NULL || e > Head->eksponent) { 
		NoviPolinom->next = Head;
		Head = NoviPolinom;
	}
	else {
		temp = Head;
		//micemo polinom kroz listu dok ne nademo di treba ic
		while (temp->next != NULL && temp->next->eksponent > e)
			temp = temp->next;
		NoviPolinom->next = temp->next;
		temp->next = NoviPolinom;
	}
	return USPJESNO_IZVRSENO;
}

int Ispis(Pozicija Head_Next) {
	while (Head_Next != NULL) {
		printf("%d^%d  ", Head_Next->koeficijent, Head_Next->eksponent);
		Head_Next = Head_Next->next;
	}
	printf("Kraj liste.");

	return USPJESNO_IZVRSENO;
}

/*int IspisIzDat(Pozicija head) {
	int c, e, n;
	char buffer[MAX_LINE] = { 0 };
	char *p = buffer;
	FILE* fp = NULL;

	fp = fopen(polinomi.txt, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return NIJE_PRONADEN;
	}

	fgets(buffer, MAX_LINE, fp);
	while(strlen(p)>0) {
		polinom Novi = {
		.koeficijent = 0,
		.eksponent = 0,
		.next = NULL
		};
		sscanf(p, " %d %d %n", &c, &e, &n);
		p += n;
		
		if (NaPocetak(head, Nova) == USPJESNO_IZVRSENO) {
			printf("Uspjesno izvrseno.\n");
		}
		else printf("Nije izvrseno.\n");
	}
	
	fclose(fp);

	return USPJESNO_IZVRSENO;
}*/

/*za citanje iz datoteke (sa ploce)
char buffer[MAX_LINE] = { 0 };
char *p = buffer;
fgets(buffer, MAX_LINE, fp);
while(strlen(p)>0){
sscanf(p, " %d %d %n", &c, &e, &n);
p += n;
}
*/