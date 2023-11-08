#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN (50)

typedef struct people {

	char name[MAX_LEN];
	char surname[MAX_LEN];
	int year;
	struct people* next;

}person;

int Menu(person*);
person* Newperson();
int AddToTheFront(person*);
int AddToTheBack(person*);
int PrintList(person*);
person* FindBySurname(person*, char[]);
person* FindPrevSurname(person*, char[]);
int DeleteElement(person*, char[]);
int DeleteAll(person*);
int AddAfterElement(person*, char[]);
int AddBeforeElement(person*, char[]);
int SortBySurname(person*);
int WriteInList(person*);
int ReadFromList(person*);


int main() {

	person Head;
	Head.next = NULL;
	Menu(&Head);

	return 0;
}

int Menu(person *Head) {

	char choice;
	char surname[MAX_LEN];


	while (1) {
		system("cls");

		printf("Choose an option:");

		printf("A-Add to the front of the list\nB-Add to the back of the list\n");

		if (Head->next) {
			printf("C-Print the list\nD-Find an element (by surname)\nE-Delete chosen element from the list\nF-Add a person before chosen element\nG-add a person after a chosen element\nH-write in the file\nI-read from the file");
		}
		printf("X-end the program\n");

		scanf("%s", &choice);

		choice = tolower(choice);

		if (choice == 'a') {
			if (!AddToTheFront(Head)) {
				printf("Action executed successfuly.\n");
			}
			else printf("Failed task.\n");

		}

		else if (choice == 'c') {
			PrintList(Head->next);
		}

		else if (choice == 'b') {
			if (!AddToTheBack(Head)) {
				printf("Action executed successfuly.\n");
			}
			else printf("Failed task.\n");
		}


		else if (choice == 'd') {
			printf("Enter the surname of the person you want to find:");
			scanf("%s", surname);
			FindBySurname(Head->next, surname);
		}

		else if (choice == 'e') {

			printf("Enter the surname of the person you want to delete from the list:");
			scanf("%s", surname);
			DeleteElement(Head, surname);
		}

		else if (choice == 'f') {

			printf("Enter the surname before which you want to add a new person:")
			scanf("%s",surname);
			AddBeforeElement(Head,surname);

		}
		else if (choice == 'g') {

			printf("Enter the surname after which you want to add a new person:")
				scanf("%s", surname);
			AddAfterElement(Head, surname);

		}
		else if (choice == 'h') {
			WriteInList(head);
		}
		else if (choice == 'i') {
			ReadFromList(head->next);
		}
		else if (choice == 'x') {

			DeleteAll(Head);
			return 0;
		}

		else printf("You chose non-existent option.Try again");
	}
	printf("\n");
	system("pause");
}

person* Newperson() {

	person* newprsn = NULL;

	newprsn = (person*)malloc(sizeof(person));

	printf("Enter person's name:");
	scanf("%s",newprsn->name);
	printf("Enter person's surname:");
	scanf("%s", newprsn->surname);
	printf("Enter person's birthyear:");
	scanf("%d", &newprsn->year);

	return newprsn;
}

int AddToTheFront(person* element) {

	person* per = NULL;
	
	per = Newperson();

	if (per != NULL) {
		per->next = element->next;
		element->next = per;
		return 0;
	}
	else return 0;

}

int AddToTheBack(person* element) {

	person* per = NULL;

	per = Newperson();

	while (element->next != NULL) {
		element = element->next;

	}

	if (per != NULL) {
		per->next = element->next;
		element->next = per;
		return 0;
	}
	else return 0;
}

int PrintList(person* element) {

	while (element != NULL) {

		printf("NAME\tSURNAME\tBIRTHYEAR\n");
		printf("%s\t%s\t%d\n",element->name,element->surname,element->year);

		element = element->next;
	}
	return 0;
}

int DeleteAll(person* element) {

	person* temp;

	while (element->next != NULL) {

		temp = element->next;
		element->next = temp->next;

		free(temp);
	}
	return 0;
}

person* FindBySurname(person* element, char Surname[])
{
	while (element != NULL && strcmp(element->surname, Surname)) {
		element = element->next;
	}
	if (element == NULL) {
		printf("That person is not on the list.\n");
		return NULL;
	}
	return element;

}

person* FindPrevSurname(person* element, char Surname[])
{
	while (element != NULL && strcmp(element->next->surname, Surname)) {
		element = element->next;
	}
	if (element == NULL) {
		printf("That person is not on the list.\n");
		return NULL;
	}
	return element;

}

int DeleteElement(person* element, char Surname[]) {

	person* del;

	element = FindPrevSurname(element, Surname);

	if (element == NULL) {
		return 1;
	}

	else {
		del = element->next;
		element->next = del->next;

		free(del);
		return 0;
	}
}

int AddAfterElement(person* element, char Surname[]) {

	person* prsn = NULL;

	prsn = Newperson();

	element = FindBySurname(element, Surname);

	if (prsn != NULL) {

		prsn->next = element->next;
		element->next = prsn;
		return 0;
	}
	else return 2;

}

int AddBeforeElement(person* element, char Surname[]) {

	person* prsn = NULL;

	prsn = Newperson();

	element = FindPrevSurname(element, Surname);

	if (prsn != NULL) {

		prsn->next = element->next;
		element->next = prsn;
		return 0;
	}
	else return 2;

}

int ReadFromList(person* element) {

	FILE* filepointer;
	person* prsn = NULL;
	person* lastelement = element;
	char name[MAX_LEN];
	char surname[MAX_LEN];
	int year;

	filepointer = FILE fopen("ListaR.txt", "r");

	if (filepointer == NULL) {
		perror("fopen");
		return -1;
	}

	while (!feof(filepointer)) {

		fscanf(filepointer, "%s\t%s\t%d\n", name, surname, year);

		prsn = (person*)malloc(sizeof(person));

		if (prsn != NULL) {
			strcpy(prsn->name, name);
			strcpy(prsn->surname, surname);
			prsn->year, year;

			prsn->next = lastelement->next;
			lastelement->next = prsn;
		}
		lastelement = prsn;
	}

	fclose(filepointer);
	return 0;
}

int WriteInList(person* element) {

	FILE* filepointer;

	filepointer = fopen("ListaW.txt", "w");

	if (filepointer == NULL) {
		perror("fopen");
		return -1;
	}

	while (element != NULL) {

		fprintf(filepointer,"%s\t%s\t%d\n", element->name, element->surname, element->year);
		element = element->next;

	}

	fclose(filepointer);
	return 0;
}