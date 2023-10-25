#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_line 1024

struct person;
typedef struct person pozicija;
typedef struct person {

	char name[max_line];
	char surname[max_line];
	int year;
	pozicija next;
}per;

int AddPerson(pozicija p);
int ispis(pozicija p);
int AddLast(pozicija p);

/*void main() {

	per people[max_p];
	int br = 0;
	int red_broj = 0;
	char izbor = 0;

	while (izbor != 'e' && izbor != 'E') {

		printf("\n Unesite zeljenu radnju:");
		printf("\n1- unos na pocetak liste");
		printf("\n2- ispis");
		printf("\n3- unos elementa na kraj liste");
		printf("\n4- trazenje elementa po prezimenu");
		printf("\n5- brisi odredeni element");

		printf("\ne/E- za kraj");
		scanf("%c",&izbor);


		switch (izbor) {

		case '1':
			br = AddPerson(people, br);
			break;

		case '2':
			ispis(people,br);
			break;

		case '3':
			AddLast(people, br);
			break;

		default:
				printf("\nKrivi unos!");
		}
	}


}*/

int main() {

	int n = 0;
	int i = 0;
	person head;
	
	head.next = NULL;

	
	printf("koliko osoba zelite dodati?");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		printf("dodaj na pocetak liste:\n");
		printf("\nOsoba broj %d.", i + 1);
		AddPerson(&head);
	}

	for (i = 0; i < n; i++)
	{
		printf("dodaj na kraj liste:\n");
		printf("\nOsoba broj %d.:\n", i + 1);
		AddLast(head.next);
	}


	ispis(head.next);

	return 0;

}

int AddPerson(pozicija p) {
	
	pozicija q;

	q = (pozicija)malloc(sizeof(person));
	printf("unesite ime:");
	scanf("%s", q->name);
	printf("unesite prezime:");
	scanf("%s", q->surname);
	printf("unesite godinu rodenja:");
	scanf("%d", &q->year);

	q->next = p->next;
	p->next = q;
	return 0;

}


int ispis(pozicija p) {

	while (p != NULL) {

		printf("\nIme osobe: %s",p->name);
		printf("\n Prezime osobe: %s", p->surname);
		printf("\nGodina rodenja osobe: %d", p->year);

	}
	return 0;
}

int AddLast(pozicija p) {

	pozicija q;

	q = (pozicija)malloc(sizeof(person));

	printf("unesite ime:");
	scanf("%s", q->name);
	printf("unesite prezime:");
	scanf("%s", q->surname);
	printf("unesite godinu rodenja:");
	scanf("%d", &q->year);
	printf("\n");

	while (p->next != NULL) {
		p = p->next;
		q->next = p->next;
		p->next = p;
	}

	return 0;

}
