#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define max_size [50]
#define max_line [1024]
#define FILE_ERROR_OPEN (-1)

typedef struct _student {

	char name[max_size];
	char surname[max_size];
	double points;
}student;


int ReadNoRowsInFile() {

	int counter = 0;
	char buffer[max_line] = { 0 };

	FILE* fp = NULL;
	fp = fopen("student.txt", "r");

	fclose(fp);

	while (!feof(fp)) {

		fgets(buffer, max_line, fp);
		counter++;

	}

	return counter;
}

int main() {

		int norows = 0;

		norows = ReadNoRowsInFile();

		if (!fp) {

			printf("file is not open\n");
			return FILE_ERROR_OPEN;

		}

		printf("%d",norows);

		fclose(fp);
		return EXIT_SUCCESS;

}

