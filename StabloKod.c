/*
Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/



#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum ERROR_CODE {
	USPJESNO_ZAVRSEN_PROGRAM,
	USPJESNO_IZVRSENO,
	NEUSPJESNO_IZVRSENO,
};


typedef struct Dir* P_Dir;
typedef struct Dir {
	char Naziv[MAX_LINE];
	P_Dir PrvoDijete;
	P_Dir Brat;
}Dir;

typedef struct Stog* P_Stog;
typedef struct Stog {
	P_Dir Dir;
	P_Stog Sljedeci;
} Stog;

int DodajNaStog(P_Stog, P_Dir);
P_Dir NoviDir(char*);
P_Dir NadiDir(char*, P_Stog);
int Put(P_Stog);
P_Stog StogZadnji(P_Stog);
int MakniSaStoga(P_Stog);
int Ispis_PodDirektorija(P_Stog);
int deleteAll(P_Dir);


int main(void) {

	Dir Roditelj;
	Roditelj.PrvoDijete = NULL;
	Roditelj.Brat = NULL;
	strcpy(Roditelj.Naziv, "MAIN");

	Stog StogHead;
	StogHead.Dir = NULL;
	StogHead.Sljedeci = NULL;

	
	DodajNaStog(&StogHead, &Roditelj);

	char linija[MAX_LINE];
	char uputa[MAX_LINE];
	char ImeDirektorija[MAX_LINE];
	printf("Unos: ");


	do {

		fgets(linija, MAX_LINE, stdin);
		sscanf(linija, "%s %s", uputa, ImeDirektorija);

		if (!strcmp(uputa, "md"))
		{

			//P_Dir P_NoviDir = NoviDir(ImeDirektorija);
			P_Dir P_NoviDir = (P_Dir)malloc(sizeof(Dir));
			if (P_NoviDir) {
				P_NoviDir->Brat = NULL;
				P_NoviDir->PrvoDijete = NULL;
				printf("Alocirano");
				strcpy(P_NoviDir->Naziv, ImeDirektorija);
			}

			P_Dir temp = StogZadnji(&StogHead)->Dir->PrvoDijete;

			if (temp == NULL) {
				StogZadnji(&StogHead)->Dir->PrvoDijete = P_NoviDir;
			}
			else {
				while (temp->Brat != NULL) {
					temp = temp->Brat;
				}
				temp->Brat = P_NoviDir;
			}

			DodajNaStog(&StogHead, P_NoviDir);

			Put(StogHead.Sljedeci);

			
		}
		else if (!strcmp(uputa, "cd"))
		{
			P_Dir CD_Dir=NadiDir(&ImeDirektorija,StogZadnji(&StogHead));

			DodajNaStog(&StogHead, CD_Dir);

			Put(StogHead.Sljedeci);
			
		}

		else if (!strcmp(uputa, "cd.."))
		{
			
			MakniSaStoga(&StogHead);

			Put(StogHead.Sljedeci);

		}
		else if (!strcmp(uputa, "dir"))
		{

			Ispis_PodDirektorija(StogZadnji(&StogHead));

			Put(StogHead.Sljedeci);

		}
		else {
			printf("Nepravilan unos. Pokšajte ponovo.\n ");

		}


	} while (strcmp(uputa, "exit"));

	deleteAll(&Roditelj);
	printf("Pozz");

	return USPJESNO_ZAVRSEN_PROGRAM;
}

int DodajNaStog (P_Stog StogHead, P_Dir NoviDir){
	P_Stog P_NoviStog = (P_Stog)malloc(sizeof(Stog));
	P_NoviStog->Dir = NoviDir;
	P_Stog StogTemp = StogHead;
	if (P_NoviStog) {
		printf("Alocirano u stogu\n");
		while (StogTemp->Sljedeci != NULL) {
			StogTemp = StogTemp->Sljedeci;
		}
		P_NoviStog->Sljedeci = StogTemp->Sljedeci;
		StogTemp->Sljedeci = P_NoviStog;
		

		return USPJESNO_IZVRSENO;
	}
	else {
		printf("Nije alocirano na stog");
		return NEUSPJESNO_IZVRSENO;
	}

}
/*P_Dir NoviDir(char* Ime) {
	P_Dir P_NoviDir = (P_Dir)malloc(sizeof(Dir));
	P_NoviDir->Naziv;
	if (P_NoviDir) {
		P_NoviDir->Brat = NULL;
		P_NoviDir->PrvoDijete = NULL;
		printf("Alocirano");
		strcpy(P_NoviDir->Naziv, *Ime);
		
		return P_NoviDir;
	}
	else {
		printf("Nije alocirano");
	}
}*/

int Put(P_Stog Stog)
{
	while (Stog!=NULL)
	{
		printf("%s //",Stog->Dir->Naziv);
		Stog = Stog->Sljedeci;
	}
	printf("> ");
	return USPJESNO_IZVRSENO;
}

P_Stog StogZadnji(P_Stog StogHead){
	while (StogHead->Sljedeci !=NULL)
	{
		StogHead = StogHead->Sljedeci;
	}
	return StogHead;
}

P_Dir NadiDir(char* Ime, P_Stog Stog) {
	P_Dir temp = Stog->Dir->PrvoDijete;
	while (strcmp(temp->Naziv,*Ime)!=0 ){
		temp = temp->Brat;
	}
	return temp;
}

int MakniSaStoga(P_Stog Head){
	{
		P_Stog temp = Head->Sljedeci, prev = Head->Sljedeci;
		if (!temp->Sljedeci)
			return NULL;
		while (temp->Sljedeci)
		{
			prev = temp;
			temp = temp->Sljedeci;
		}
		prev->Sljedeci = temp->Sljedeci;
		free(temp);
	}
}

int Ispis_PodDirektorija(P_Stog Stog) {

	P_Dir temp;
	temp = Stog->Dir->PrvoDijete;
	if (temp==NULL) printf("Direktorij je prazan");
	else {
		while (temp->Brat) {
			printf("-%s \n", temp);
			temp = temp->Brat;
		}
		printf("-%s \n", temp);

	}
	return USPJESNO_IZVRSENO;
}

int deleteAll(P_Dir p) {
	if (p == NULL) {
		return USPJESNO_IZVRSENO;
	}
	deleteAll(p->PrvoDijete);
	deleteAll(p->Brat);
	free(p);
	
	return USPJESNO_IZVRSENO;
}
