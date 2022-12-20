/*Napisati program koji omoguæava rad s binarnim stablom pretraživanja.
Treba omoguæiti unošenje novog elementa u stablo,
ispis elemenata(inorder, preorder, postorder i level order),
brisanje i pronalaženje nekog elementa.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum ERROR_CODE {
	DODAJ_EL = 1,
	ISPIS_INORDER,
	ISPIS_PREORDER,
	ISPIS_POSTORDER,
	ISPIS_LEVELORDER,
	BRISI_EL,
	TRAZI_EL,
	EXIT,
	USPJESNO_ZAVRSEN_PROGRAM,
	USPJESNO_IZVRSENO,
	NEUSPJESNO_IZVRSENO,
	MAX_LINE = 1024
};

typedef struct cvorStabla* Pozicija;
typedef struct cvorStabla {
	int El;
	Pozicija L;
	Pozicija D;
}cvorStabla;

Pozicija StvoriPrazno(int);
Pozicija TraziMin(Pozicija);
Pozicija TraziMax(Pozicija);
Pozicija Trazi(int, Pozicija);
Pozicija DodajEl(int, Pozicija);
Pozicija BrisiEl(Pozicija, int);
int IspisInorder(Pozicija);
int IspisPreorder(Pozicija);
int IspisPostorder(Pozicija);
int IspisLevelOrder(Pozicija);
int Visina(Pozicija);
int IspisTrenutniLevel(Pozicija, int);



int main(void) {

	Pozicija root = NULL;

	root = DodajEl(4, root);
	DodajEl(1, root);
	DodajEl(12, root);
	DodajEl(10, root);
	DodajEl(3, root);
	DodajEl(14, root);
	DodajEl(2, root);

	int naredba = 0;
	int br = 0;

	do {
			printf(
				"\n__________________________\n"
				"Unesite broj za naredbu.\n"
				"__________________________\n"
				"1-Dodaj element\n"
				"2-Ispis elemenata inorder\n"
				"3-Ispis elemenata preorder\n"
				"4-Ispis elemenata postorder\n"
				"5-Ispis elemenata level order\n"
				"6-Brisanje elementa\n"
				"7-Trazenje elementa\n"
				"8-Zavrsi program\n"
			);
			scanf(" %d", &naredba);

		if (naredba == DODAJ_EL) {
			printf("Koji element zelis dodati u stabla?\n");
			scanf(" %d", &br);
			root = DodajEl(br, root);
		}
		else if (naredba == ISPIS_INORDER) {
			IspisInorder(root);
		}
		else if (naredba == ISPIS_PREORDER) {
			IspisPreorder(root);
		}
		else if (naredba == ISPIS_POSTORDER) {
			IspisPostorder(root);
		}
		else if (naredba == ISPIS_LEVELORDER) {
			IspisLevelOrder(root);
		}
		else if (naredba == BRISI_EL) {
			
			printf("Koji element zelis izbrisati iz stabla?\n");
			scanf(" %d", &br);
			root = BrisiEl(root, br);
		}
		else if (naredba == TRAZI_EL) {
			Pozicija P = NULL;
			printf("Koji element trazis u stablu?\n");
			scanf(" %d", &br);
			P = Trazi(br, root);
			if (P == NULL) {
				printf("Nema elementa\n");
			} else 
			printf("Element %d je na poziciji %d\n", br, P);
		}
		else if (naredba != EXIT) {
			printf("Nepoznata naredba\n");
		}

	} while (naredba != EXIT);

	return USPJESNO_ZAVRSEN_PROGRAM;
}

Pozicija StvoriPrazno(int x) {

	Pozicija Pozicija_Nova = (Pozicija)malloc(sizeof(cvorStabla));

	if (Pozicija_Nova == NULL) {
		printf("Memorija nije alocirana!\n");
		return NEUSPJESNO_IZVRSENO;
	}
	Pozicija_Nova->El = x;
	Pozicija_Nova->L = NULL;
	Pozicija_Nova->D = NULL;

	return Pozicija_Nova;
}

Pozicija TraziMin(Pozicija p) {
	while (p->L)
		p = p->L;
	return p;
}
Pozicija TraziMax(Pozicija p) {
	while (p->D)
		p = p->D;
	return p;
}

Pozicija Trazi(int x, Pozicija p) {
	
	while (p != NULL) {

		if (p->El < x) {
			p = p->D;
		}
		else if (p->El > x) {
			p = p->L;
		}
		else
			return p;
	}
	return NULL;
}

Pozicija DodajEl(int x, Pozicija p) {

	if (p == NULL) {
		return StvoriPrazno(x);
	}

	if (p->El < x) {
		p->D = DodajEl(x, p->D);
	}
	else if (p->El > x) {
		p->L = DodajEl(x, p->L);
	}
	return p;
}

Pozicija BrisiEl(Pozicija p, int x) {
	
	if (p == NULL) {
		return NULL;
	}

	if (p->El < x) {
		p->D = BrisiEl(p->D, x);
	}
	else if (p->El > x) {
		p->L = BrisiEl(p->L, x);
	}
	else {
		if (p->L) {
			Pozicija temp = TraziMax(p->L);
			p->El = temp->El;
			p->L = BrisiEl(p->L, temp->El);
		}
		else if (p->D) {
			Pozicija temp = TraziMin(p->D);
			p->El = temp->El;
			p->D = BrisiEl(p->D, temp->El);
		}
		else {
			free(p);
			return NULL;
		}
	}
	return p;

}

int IspisInorder(Pozicija p) {
	
	if (p == NULL) {
		return 0;
	}
	IspisInorder(p->L);
	printf(" %d", p->El);
	IspisInorder(p->D);

	return USPJESNO_IZVRSENO;
}

int IspisPreorder(Pozicija p) {

	if (p == NULL) {
		return 0;
	}
	printf(" %d", p->El);
	IspisPreorder(p->L);
	IspisPreorder(p->D);

	return USPJESNO_IZVRSENO;
}

int IspisPostorder(Pozicija p) {

	if (p == NULL) {
		return 0;
	}
	IspisPostorder(p->L);
	IspisPostorder(p->D);
	printf(" %d", p->El);

	return USPJESNO_IZVRSENO;
}

int IspisLevelOrder(Pozicija p) {

	if (p == NULL) {
		return 0;
	}

	int h = Visina(p);
	for (int i = 0; i < h; i++)
		IspisTrenutniLevel(p, i);

	return USPJESNO_IZVRSENO;
}

int Visina(Pozicija p) {

	if (p == NULL)
		return 0;
	else {
		int LVisina = Visina(p->L);
		int RVisina = Visina(p->D);

		if (LVisina > RVisina)
			return (LVisina + 1);
		else
			return (RVisina + 1);
	}
}

int IspisTrenutniLevel(Pozicija p, int lvl) {
	
	if (p == NULL)
		return 0;

	if (lvl == 1)
		printf(" %d ", p->El);
	else if (lvl > 1) {
		IspisTrenutniLevel(p->L, lvl - 1);
		IspisTrenutniLevel(p->D, lvl - 1);
	}

	return USPJESNO_IZVRSENO;
} 
