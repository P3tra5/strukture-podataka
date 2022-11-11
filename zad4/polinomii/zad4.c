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


struct polinom;
typedef struct polinom* Pozicija;
typedef struct polinom {
	int koeficijent;
	int eksponent;
	Pozicija next;
}polinom;

int Zbrajanje(Pozicija p, Pozicija q, Pozicija);
int Mnozenje(Pozicija p, Pozicija q);
int Ispis(Pozicija Head_Next);
int UnosElemenata(polinom*, int,int);
int UpisIzDat(Pozicija,Pozicija);
int BrisiElement(Pozicija,Pozicija);

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

	UpisIzDat(&Head1,&Head2);

	printf("Program zbraja i mnozi dva polinoma iz datoteke\n");
	printf("\nPrvi polinom je:\n");
	Ispis(Head1.next);
	printf("\nDrugi polinom je:\n");
	Ispis(Head2.next);

	Zbrajanje(Head1.next, Head2.next, &HeadZbroj);
	printf("\nZbroj polinoma je:\n");
	Ispis(HeadZbroj.next);

	Mnozenje(Head1.next, Head2.next, &HeadProdukt);
	printf("\nProdukt polinoma je:\n");
	Ispis(HeadProdukt.next);

	return USPJESNO_ZAVRSEN_PROGRAM;
}


int Zbrajanje(Pozicija Head1, Pozicija Head2,Pozicija HeadZbroj) {
	Pozicija p = Head1;
	Pozicija q = Head2;

	while (p != NULL && q != NULL) {
		
		if (p->eksponent > q->eksponent) {
			if (UnosElemenata(HeadZbroj, p->koeficijent, p->eksponent) == USPJESNO_IZVRSENO) {
				printf("Zbroj(%d %d)\n", p->koeficijent, p->eksponent);
			}
			else printf("Nije izvrseno.\n");
			p = p->next;
		}
		else if (p->eksponent < q->eksponent) {
			if (UnosElemenata(HeadZbroj, q->koeficijent, q->eksponent) == USPJESNO_IZVRSENO) {
				printf("Zbroj(%d %d)\n", q->koeficijent, q->eksponent);
			}
			else printf("Nije izvrseno.\n");
			q = q->next;
		}
		else{ //eksponenti su jednaki
			if (UnosElemenata(HeadZbroj, p->koeficijent + q->koeficijent, q->eksponent) == USPJESNO_IZVRSENO) {
				printf("Zbroj(%d %d).\n", p->koeficijent + q->koeficijent, q->eksponent);
			}
			else printf("Nije izvrseno.\n");
			p = p->next;
			q = q->next;
		}
	}
	//kad jedna lista dode do kraja da ispise kraj druge u rezultat
	while (p != NULL) {
		if (UnosElemenata(HeadZbroj, p->koeficijent, p->eksponent) == USPJESNO_IZVRSENO) {
			printf("Zbroj(%d %d).\n", p->koeficijent, p->eksponent);
		}
		else printf("Nije izvrseno.\n");
		p = p->next;
	}
	while (q != NULL) {
		if (UnosElemenata(HeadZbroj, q->koeficijent, q->eksponent) == USPJESNO_IZVRSENO) {
			printf("Zbroj(%d %d).\n", q->koeficijent, q->eksponent);
		}
		else printf("Nije izvrseno.\n");
		q = q->next;
	}
	
	return USPJESNO_IZVRSENO;
}

int Mnozenje(Pozicija p, Pozicija q, Pozicija HeadProdukt) {
	

	while (p != NULL) {
		
		Pozicija temp=q;
		while (temp != NULL) {
			int k = p->koeficijent * temp->koeficijent;
			int e = p->eksponent + temp->eksponent;
			if (UnosElemenata(HeadProdukt, k, e) == USPJESNO_IZVRSENO) {
				//printf("Uspjesno.\n");
			}
			else printf("Nije izvrseno.\n");
			temp = temp->next;
		}
		temp = q;
		p = p->next;
	}


	return USPJESNO_IZVRSENO;
}

int UnosElemenata(polinom* Head, int k, int e) {
	Pozicija temp;
	polinom* NoviPolinom = malloc(sizeof(polinom));
		if (NoviPolinom == NULL) {
			printf("Memorija nije alocirana!\n");
			return USPJESNO_IZVRSENO;
		}
		/*else {
			printf("Memorija alocirana!\n");
		}*/
	NoviPolinom->koeficijent = k;
	NoviPolinom->eksponent = e;
	NoviPolinom->next = NULL;

	if (Head->next == NULL ) {
		NoviPolinom->next = Head->next;
		Head->next = NoviPolinom;
	}
	else {
		temp = Head;
		//micemo polinom kroz listu dok ne nademo di treba ic
		while (temp->next != NULL && temp->next->eksponent >= e)
			temp = temp->next;
		if (temp->eksponent==e){
			if ((temp->koeficijent + k) == 0) {
				BrisiElement(Head,temp);
			}
			else {
				temp->koeficijent = temp->koeficijent + k;
			}
		}
		else {
			NoviPolinom->next = temp->next;
			temp->next = NoviPolinom;
		}
	}
	return USPJESNO_IZVRSENO;
}

int Ispis(Pozicija Head_Next) {
	while (Head_Next != NULL) {
		printf("%d^%d  ", Head_Next->koeficijent, Head_Next->eksponent);
		Head_Next = Head_Next->next;
	}
	printf("Kraj liste.\n");

	return USPJESNO_IZVRSENO;
}

int UpisIzDat(Pozicija head1,Pozicija head2) {
	int c, e, n;
	char buffer [MAX_LINE] = { 0 };
	char *p = buffer;
	FILE* fp = NULL;

	fp = fopen("polinomi.txt", "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return NIJE_PRONADEN;
	}

	fgets(buffer, MAX_LINE, fp);
	while(strlen(p)>0) {
		
		sscanf(p, " %d %d %n", &c, &e, &n);
		p += n;
		if (c == 0) {
			printf("Koeficijent je 0\n");
		}
		else {
			if (UnosElemenata(head1, c, e) == USPJESNO_IZVRSENO) {
				//printf("Uspjesno izvrseno.\n");
			}
			else printf("Nije izvrseno.\n");
		}
	}
	
	fgets(buffer, MAX_LINE, fp);
	char* b = buffer;
	while (strlen(b) > 0) {

		sscanf(b, " %d %d %n", &c, &e, &n);
		b += n;
		if (c == 0) {
			printf("Koef je 0\n");
		}
		else {
			if (UnosElemenata(head2, c, e) == USPJESNO_IZVRSENO) {
				//printf("Uspjesno izvrseno.\n");
			}
			else printf("Nije izvrseno.\n");
		}
	}
	
	fclose(fp);

	return USPJESNO_IZVRSENO;
}

int BrisiElement(Pozicija Head, Pozicija zaBrisat) {
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

/*za citanje iz datoteke (sa ploce)
char buffer[MAX_LINE] = { 0 };
char *p = buffer;
fgets(buffer, MAX_LINE, fp);
while(strlen(p)>0){
sscanf(p, " %d %d %n", &c, &e, &n);
p += n;
}
*/


//provjera za sscanf i brisanje memorije
//inicijalizacija svih variabili na 0
