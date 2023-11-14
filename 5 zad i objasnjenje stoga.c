#define _CRT_SECURE_NO_WARNINGS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN (1024)
#define MAX_SIZE(50)

/*              2 2 * 3 - 5 + 3 3 * *

stog H - 2) - 2/////// onda zbog todeleta mi brisemo ovaj drugi 2 pa je H - 2 i za result pisemo 2 tj operant1 je 2

onda ova druga duja postaje todelete i brisemo i to pa nan ostaje stog prazan i pisemo da je operant2 = 2

i onda u result (imamo posebnu funkciju u kojoj gledamo o kojej se racunalnoj operaciji radi) nakon ovog mnozenja pisemo da je 4

stog H - 3) - 4(ovo je ono sta smo dobili sa 2*2)     sad nan operation postaje - za result dobivamo 3 kojeg onda brisemo iz stoga H - 4

operant1 nam postaje = 3 onda opet sa stoga brisemo 4 tj stog ostaje prazan H operant2 = 4     a za result sad imamo 1

stog H - 5) - 1(ovo nan ostaje od 4-3) za operation sad imamo + onda  pisemo da je result = 5 brisemo 5 iz stoga i pisemo da je operant1 = 5

stog H - 1 nakon toga brisemo 1 sa stoga i pisemo da je operant2 = 1 i ostaje nan prazan stog a result nan je result = 6

stog H - 3)) - 3) - 6 (dobijemo od 5+1) ugl za operation = * sad imamo 

prvi put pisemo da je result=3 brisemo prvu 3 i dobijemo operant1=3 

onda brisemo drugu 3 i pisemo da je opreant2 = 3 onda to mnozimo u za result dobijemo result = 9

stog H - 9) - 6 onda u operation opet pisemo * 

9 stavljamo u result posli toga ga brisemo i pisemo operation1 = 9

brisemo 6 i pisemo da je operation2 = 6     stog ostaje prazan

i onda pisemo da je 6 * 9 = 54


int readFile(char* filename, char* buffer);

int main() {

	return 0;


}


int pop(position head, double* result) {
	
	position todelete = NULL;



}
int readFile(char* filename, char* buffer) {

	FILE* filepointer = NULL;
	
	filepointer = fopen("imefila.txt", "r");

	char buffer[MAX_LEN] = NULL;

	if (!filepointer) {
		perror();

	}
	fgets(, MAX_LEN, filepointer);

	free(filepointer);
	return 0;

}



u cetvrtom zadatku triba dodat free element i triba dodat da kad je zbroj 0 onda se triba brisat taj element


*/

typedef struct _stackElement {

	double number;
	struct _stackElement* next;
} stackElement;

stackElement* CreateElement(double number);
int readFile(char* buffer);
int StringIntoPostfix(stackElement* head, char* buffer, double* result);
int pop(stackElement* head, double* result);
int push(stackElement* head, stackElement* newStackElement);
int performOperation(stackElement* head, char* buffer, double* result);

int main() {

	stackElement head = { .number = 0.0,.next = NULL };
	char buffer[MAX_LEN] = "";
	double result = 0.0;

	if (readFile(buffer)) {
		return 1;
	}

	printf("postfix: %s \n", buffer);

	if (StringIntoPostfix(&head, buffer, &result)) {
		return 1;
	}

	printf("Result: %0.1f\n", result);

	return 0;
}

stackElement* CreateElement(dpuble number) {

	stackElement* newEl = NULL;

	newEl = (stackElement*)malloc(sizeof(stackElement));

	if (newEl == NULL) {
		perror("malloc");
		return NULL;
	}

	newEl->number = number;
	newEl->next = NULL;

	return newEl;
}

int readFile(char* buffer) {

	FILE* filepointer = NULL;
	filepointer = fopen("number.txt", "r");

	if (!filepointer) {

		perror("fopen");
		return 1;
	}

	fgets(buffer, MAX_LEN, filepointer);

	fclose(filepointer);

	return 0;

}

int StringIntoPostfix(stackElement* head, char* buffer, double* result) {

	char* currentBuffer = buffer;
	int status = 0;
	int numBytes = 0;
	double number = 0;
	char operation = 0;
	stackElement* newEl = NULL;

	while (strlen(currentBuffer) > 0) {

		status = sscanf(currentBuffer, "%lf %n", &number, &numBytes);

		if (status != 1) {
			sscanf(currentBuffer, "%c %n", &operation, &numBytes);

			if (performOperation(head, operation, result)) {
				return 1;
			}
			number = *result;

		}
		newEl = CreateElement(number);
		if (!newEl) {
			return 1;
		}

		push(head, newEl);
		currentBuffer += numBytes;

	}

	return 0;
}

int PerformOperation(stackElement* head, char operation, double* result) {

	double operand1 = 0.0;
	double operand2 = 0.0;

	if (pop(head, &operand1)) {
		return 1;
	}

	if (pop(head, operand2)) {
		return 1;
	}


	switch(operation) {

	case '+':
		*result = operand2 + operand1;
		break;
	case '-':
		*result = operand2 - operand1;
		break;
	case '*':
		*result = operand2 * operand1;
		break;
	case '/':
		*result = operand2 / operand1;
		break;
	default:
		printf("operation %c not supported!\n", operation);
		break;

	}

	return 0;
}

int pop(stackElement* head, double* result) {

	stackElement* toPop = NULL;

	toPop = head->next;
	if (!toPop) {
		printf("Stack empty!\n");
		return 1;
	}

	head->next = toPop->next;

	*result = toPop->number;

	free(toPop);

	return 0;
}

int push(stackElement* head, stackElement* newStackElement) {

	newStackElement->next = head->next;
	head->next = newStackElement;

	return 0;
}
