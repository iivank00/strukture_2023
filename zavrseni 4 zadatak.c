#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN (1024)

struct element;
typedef struct element* position;
typedef struct element {
	int coefficient;
	int exponent;
	position next;
}elem;

int ReadFile(elem* HeadPoly1,elem* HeadPoly2);
elem* CreateElem(int coefficient, int exponent);
int StringIntoList(elem* Head, char* buffer);
int InsertSorted(elem* Head, elem* element);
int PolyMultiply(elem* Firstelem1, elem* Firstelem2, elem* HeadProduct);
int PolySum(elem* Firstelem1, elem* Firstelem2, elem* HeadSum);
int PrintInFile(char* text, elem* Firstelem);


int main() {

	elem HeadPoly1 = { .coefficient = 0,.exponent = 0,.next = NULL };
	elem HeadPoly2 = { .coefficient = 0,.exponent = 0,.next = NULL };
	elem HeadSum = { .coefficient = 0,.exponent = 0,.next = NULL };
	elem HeadProduct = { .coefficient = 0,.exponent = 0,.next = NULL };

	ReadFile(&HeadPoly1, &HeadPoly2);
	
	PrintInFile("first polinomial: ", HeadPoly1.next);
	PrintInFile("second polinomial: ", HeadPoly2.next);

	PolySum(HeadPoly1.next, HeadPoly2.next, &HeadSum);
	PrintInFile("Sum of the polinomials: ", HeadSum.next);

	PolyMultiply(HeadPoly1.next, HeadPoly2.next, &HeadProduct);
	PrintInFile("Product of the polinomials", HeadProduct.next);
	
	return 0;

}

int ReadFile(elem* HeadPoly1, elem* HeadPoly2) {

	FILE* filepointer;
	filepointer = NULL;

	char buffer[MAX_LEN]= "";

	filepointer = fopen("polinomi.txt", "r");

	if (!filepointer) {
		perror("fopen");
		return 2;

	}

	fgets(buffer, MAX_LEN, filepointer);
	if (StringIntoList(HeadPoly1, buffer)) return 1;

	fgets(buffer, MAX_LEN, filepointer);
	if (StringIntoList(HeadPoly2, buffer)) return 1;

	fclose(filepointer);

	return 0;
}


int StringIntoList(elem* Head, char* buffer) {

	elem* currentelem = 0;
	elem* element = NULL;
	char* currentbuffer = buffer;
	int status = 0;
	int coefficient = 0;
	int exponent = 0;
	int NumberBytes = 0;

	while (strlen(currentbuffer) > 0) {
		status = sscanf(currentbuffer, "%dx^%d %n", &coefficient, &exponent, &NumberBytes); //sscanf broji koliko smo varijbli unijeli (oni nan to triba bit 2)

		if (status != 2) {
			printf("Not good");
			return 2;
		}


		element = CreateElem(coefficient, exponent);

		if (!element) return 1;

		InsertSorted(Head, element);

		currentbuffer += NumberBytes;


	}
	return 0;
}


elem* CreateElem(int coefficient, int exponent) {

	elem* newelement = NULL;

	newelement = (elem*)malloc(sizeof(elem));

	if (!newelement) {
		perror("malloc");
			return NULL;
	}

	newelement->coefficient = coefficient;
	newelement->exponent = exponent;

	return newelement;

}

int InsertSorted(elem* Head, elem* element) {

	elem* current = Head;

	while (current->next != NULL && element->exponent < element->next->exponent) {

		current = current->next;
	}

	if (current->next != NULL && current->next->exponent == element->exponent) {

		current->next->coefficient = current->next->coefficient + element->coefficient;
	}
	else {
		element->next = current->next;
		current->next = element;
	}

	return 0;
}

int PolyMultiply(elem* Firstelem1, elem* Firstelem2, elem* HeadProduct) {

	elem* start = Firstelem2;
	elem* newelement = NULL;

	if (!Firstelem1 || Firstelem2) {

		printf("Empty polinomials");
		return 2;
	}

	while (Firstelem1) {
		while (Firstelem2) {

			newelement = CreateElem(Firstelem1->coefficient * Firstelem2->coefficient, Firstelem1->exponent + Firstelem2->exponent);

			if (!newelement) return 2;

			InsertSorted(HeadProduct, newelement);

			Firstelem2 = Firstelem2->next;
		}
		Firstelem2 = start;
		Firstelem1 = Firstelem1->next;
	}

	return 0;

}

int PolySum(elem* Firstelem1, elem* Firstelem2, elem* HeadSum) {

	elem* newelement = NULL;

	if (!Firstelem1 || Firstelem2) {

		printf("Empty polinomials");
		return 1;
	}

	while (Firstelem1) {

		newelement = CreateElem(Firstelem1->coefficient, Firstelem1->exponent);
		if (!newelement) return 2;

		InsertSorted(HeadSum, newelement);
		Firstelem1 = Firstelem1->next;
	}

	while (Firstelem2) {

		newelement = CreateElem(Firstelem2->coefficient, Firstelem2->exponent);
		if (!newelement) return 2;

		InsertSorted(HeadSum, newelement);
		Firstelem2 = Firstelem1->next;
	}


	return 0;
}


int PrintInFile(char* text, elem* Firstelem)
{
	printf(" %s ", text);

	if (Firstelem) {
		if (Firstelem->exponent < 0) {
			if (Firstelem->coefficient == 1) {
				printf("x^(%d)", Firstelem->exponent);
			}
			else {
				printf("%dx^(%d)", Firstelem->coefficient, Firstelem->exponent);
			}
		}
		else {
			if (Firstelem->coefficient == 1) {
				printf("x^%d", Firstelem->exponent);
			}
			else {
				printf("%dx^%d", Firstelem->coefficient, Firstelem->exponent);
			}
		}

		Firstelem = Firstelem->next;
	}

	while (Firstelem != NULL) {
		if (Firstelem->coefficient < 0) {
			if (Firstelem->exponent < 0) {
				printf(" - %dx^(%d)", abs(Firstelem->coefficient), Firstelem->exponent);
			}
			else {
				printf(" - %dx^%d", abs(Firstelem->coefficient), Firstelem->exponent);
			}
		}
		else {
			if (Firstelem->exponent < 0) {
				if (Firstelem->coefficient == 1) {
					printf(" + x^(%d)", Firstelem->exponent);
				}
				else {
					printf(" + %dx^(%d)", Firstelem->coefficient, Firstelem->exponent);
				}
			}
			else {
				if (Firstelem->coefficient == 1) {
					printf(" + x^%d", Firstelem->exponent);
				}
				else {
					printf(" + %dx^%d", Firstelem->coefficient, Firstelem->exponent);
				}
			}
		}
		Firstelem = Firstelem->next;
	}

	printf("\n");

	return 0;
}

/*int MergeAfter();
int InsertSorted(position head, position newelement);

int main() {
	elem headpoly1= {.coefficient=0}


	return 0;
}

na pocetku stvorimo novi head i onda stvorimo element koji je npr 5x^5
mi postavaljamo da je head current i nakon toga postavljamo da je 5x^5 taj koji ima adresu NULL, a head dobiva adresu koju je ima 5x^5
onda dodajemo novi element npr 2x^3 i usporedujemo koji je eksponent veci (veci je 5x^5) i onda postavljamo da je 2x^3 NULL
ako onda dodajemo 4x^4 čiji je eksponent veći od 3 tako da 2x^3 i 4x^4 mijenjaju mjesta unutar liste tako da eksponenti budu sortirani
tako radimo sa svim elementima unutar neke jednadžbe
ako se u jednadžbi nalazi element sa eksponentom koji je isti ka onaj koji smo već imali npr 5x^3 onda izlazimo iz petlje u novu funkciju gdje se u elsu (ako smo već tako postavili 
i tu će se koeficijneti istih eksponenata zbrojiti i postat 7 

*/


