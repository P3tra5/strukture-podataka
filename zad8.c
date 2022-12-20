/*Napisati program koji omoguæava rad s binarnim stablom pretraživanja.
Treba omoguæiti unošenje novog elementa u stablo,ispis elemenata(inorder, preorder, postorder i level order),brisanje i pronalaženje nekog elementa.*/#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum ERROR_CODE {
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
}Stablo;

Pozicija StvoriPrazno(Pozicija); //
Pozicija TraziMin(Pozicija);
Pozicija TraziMax(Pozicija);
Pozicija Trazi(int, Pozicija);
Pozicija DodajEl(int, Pozicija);
Pozicija BrisiEl(int, Pozicija);
int IspisInorder(Pozicija);
int IspisPreorder(Pozicija);
int IspisPostorder(Pozicija);
int IspisLevelOrder(Pozicija);



int main(void) {

	Pozicija root = NULL;
	root = DodajEl(4, root);
	root = DodajEl(1, root);
	root = DodajEl(12, root);
	root = DodajEl(10, root);
	root = DodajEl(3, root);
	root = DodajEl(14, root);
	root = DodajEl(2, root);

	int naredba = 0;
	printf(
		"Unesite broj za naredbu.\n"
		"_________________________\n"
		"1-Dodaj element:\n"
		"2-Ispis elemenata inorder\n"
		"3-Ispis elemenata preorder:\n"
		"4-Ispis elemenata postorder:\n"
		"5-Ispis elemenata level order:\n"
		"6-Brisanje elementa\n"
		"7-Trazenje elementa\n"
	);

	return USPJESNO_ZAVRSEN_PROGRAM;
}

Pozicija StvoriPrazno(Pozicija p) {

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
	
	if (p == NULL) {
		return NULL;
	}

	if (p->El < x) {
		p->D = Trazi(x, p->D);
	}
	else if (p->El > x) {
		p->L = Trazi(x, p->L);
	}
	return p;
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

Pozicija BrisiEl(int x, Pozicija p) {
	
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
	}
	return p;

}

int IspisInorder(Pozicija p) {
	
	if (p == NULL) {
		return 0;
	}
	print(p->L);
	printf(" %s", p->El);
	print(p->D);

	return USPJESNO_IZVRSENO;
}

int IspisPreorder(Pozicija p) {

	if (p == NULL) {
		return 0;
	}
	printf(" %s", p->El);
	print(p->L);
	print(p->D);

	return USPJESNO_IZVRSENO;
}

int IspisPostorder(Pozicija p) {

	if (p == NULL) {
		return 0;
	}
	print(p->L);
	print(p->D);
	printf(" %s", p->El);

	return USPJESNO_IZVRSENO;
}

int IspisLevelOrder(Pozicija p) {

	return USPJESNO_IZVRSENO;
}