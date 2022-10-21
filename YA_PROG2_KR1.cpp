#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> // FILE, fopen(), fclose(), printf(), fgets, getchar()
#include <string.h> // strlen(), strcmp(), strcpy()
#include <stdlib.h> // malloc(), free()

struct student
{
	char surName[15];
	char grNumber[8];
	char marker[3];
};

void del_new_line(char* str);
void print_all(student* listOfStudents, int lenOfList);
void sort_by_surname(student *listOfStudents, int lenOfList);
void print_hostel(student* listOfStudents, int lenOfList);


int main()
{
	FILE *fStudents;
	char numOfStudents[6];
	int lenOfnum, lenOfList= 0;
	if (!(fStudents = fopen("Students.txt", "rt")))
		printf("Students.txt does not exist.");
	else
	{
		fgets(numOfStudents, 6, fStudents);					// получаем количество студентов в списке
		lenOfnum = strlen(numOfStudents) - 1;
		for (int i = 0; i < lenOfnum; i++)
			lenOfList = lenOfList * 10 + (numOfStudents[i] - '0');
		student *listOfStudents;
		listOfStudents = (struct student*) malloc(sizeof(struct student)*lenOfList);

		for (int i = 0; i < lenOfList; i++)					// заполняем список студентов из файла
		{
			fgets(listOfStudents[i].surName, 15, fStudents);
			del_new_line(listOfStudents[i].surName);
			fgets(listOfStudents[i].grNumber, 8, fStudents);
			del_new_line(listOfStudents[i].grNumber);
			fgets(listOfStudents[i].marker, 3, fStudents);
			del_new_line(listOfStudents[i].marker);
		}
		printf("without sort:\n\n");
		print_all(listOfStudents, lenOfList);
		sort_by_surname(listOfStudents, lenOfList);
		printf("\nsorted:\n\n");
		print_all(listOfStudents, lenOfList);
		print_hostel(listOfStudents, lenOfList);
		free(listOfStudents);
		fclose(fStudents);
	}
	getchar();
	return 0;
}

void del_new_line(char* str)
{
	size_t len = strlen(str);
	if ((len > 0) && (str[len - 1] == '\n'))
	{
		str[len - 1] = '\0';
	}
}

void sort_by_surname(student *listOfStudents, int lenOfList)
{
	struct student temp;
	for (int i = 0; i < lenOfList - 1; i++)
	{
		for (int j = lenOfList - 1; j > i; --j)
		{
			if (strcmp(listOfStudents[j - 1].surName, listOfStudents[j].surName) > 0 ) 
			{
				strcpy(temp.surName, listOfStudents[j - 1].surName);
				strcpy(temp.grNumber, listOfStudents[j - 1].grNumber);
				strcpy(temp.marker, listOfStudents[j - 1].marker);
				strcpy(listOfStudents[j - 1].surName, listOfStudents[j].surName);
				strcpy(listOfStudents[j - 1].grNumber, listOfStudents[j].grNumber);
				strcpy(listOfStudents[j - 1].marker, listOfStudents[j].marker);
				strcpy(listOfStudents[j].surName, temp.surName);
				strcpy(listOfStudents[j].grNumber, temp.grNumber);
				strcpy(listOfStudents[j].marker, temp.marker);
			}
		}
	}
}

void print_all(student* listOfStudents, int lenOfList)
{
	printf("\t\tLIST OF ALL STUDENTS");
	printf("\n====================================================================\n");
	printf("% 4s\t", "N");
	printf("%-10s\t", "Surname");
	printf("%-16s\t", "Group number");
	printf("%-20s", "Lives in hostel");
	printf("\n====================================================================\n");
	for (int i = 0; i < lenOfList; i++)
	{
		printf("% 4d\t", i + 1);
		printf("%-10s\t", listOfStudents[i].surName);
		printf("%-16s\t", listOfStudents[i].grNumber);
		printf("%-20s\n", listOfStudents[i].marker);
	}
}

void print_hostel(student* listOfStudents, int lenOfList)
{
	printf("\n\n\tLIST OF STUDENTS WHO LIVE IN THE HOSTEL");
	printf("\n=====================================================\n");
	printf("% 4s\t", "N");
	printf("%-10s\t", "Surname");
	printf("%-16s", "Group number");
	printf("\n=====================================================\n");
	int n = 1;
	for (int i = 0; i < lenOfList; i++)
	{
		if (strcmp(listOfStudents[i].marker, "+") == 0)
		{
			printf("% 4d\t", n);
			printf("%-10s\t", listOfStudents[i].surName);
			printf("%-16s\n", listOfStudents[i].grNumber);
			n++;
		}
	}
	printf("\t\tTotal students on this list: ");
	printf("%d", n - 1);
}